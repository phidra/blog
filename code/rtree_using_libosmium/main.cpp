#include <iostream>
#include <vector>

#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mmap_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using Point = bg::model::point<double, 2, bg::cs::spherical_equatorial<bg::degree> >;
using Segment = bg::model::segment<Point>;
using WaySegment = std::pair<Segment, osmium::object_id_type>;
using RTree = bgi::rtree< WaySegment, bgi::linear<8> >;


struct RTreeFillingHandler : public osmium::handler::Handler {
    explicit RTreeFillingHandler(RTree& rtree) : m_rtree{rtree} { }
    void way(const osmium::Way& w) {
        if (w.tags()["highway"] != nullptr)  // we're only interested in highways
        {
            if (w.nodes().size() >= 2)
            {
                auto from = w.nodes().begin();
                for (auto to = (from+1); to < w.nodes().end(); ++to)
                {
                    m_rtree.insert({
                        {
                            {from->location().lon(), from->location().lat()},
                            {to->location().lon(), to->location().lat()},
                        },
                        w.id()
                    });
                    from = to;
                }
            }
        }
    }
    RTree& m_rtree;
};


RTree build_rtree_from_osm_data(const char* const osmfile) {
    RTree rtree;
    try {
        auto relevant_types = osmium::osm_entity_bits::node | osmium::osm_entity_bits::way;
        osmium::io::Reader reader{osmfile, relevant_types};

        // location handler, needed to use nodes' locations :
        using Index = osmium::index::map::SparseMmapArray<osmium::unsigned_object_id_type, osmium::Location>;
        using LocationHandler = osmium::handler::NodeLocationsForWays<Index>;
        Index index;
        LocationHandler location_handler{index};

        RTreeFillingHandler rtree_handler{rtree};
        osmium::apply(reader, location_handler, rtree_handler);
        reader.close();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::exit(2);
    }
    return rtree;
}


std::tuple<Segment, osmium::object_id_type, float> find_nearest(const RTree& rtree, const Point& requested_point) {
    std::vector<WaySegment> result;
    auto nb_found = rtree.query(bgi::nearest(requested_point, 1), std::back_inserter(result));
    if (nb_found == 0)
    {
        std::cerr << "unable to find nearest value in rtree (currently containing " << rtree.size() << " segments)" << '\n';
        std::exit(3);
    }

    auto found = result.front();
    auto distance = bg::distance(found.first, requested_point, bg::strategy::distance::cross_track<double>(6'371'000));
    return std::make_tuple(found.first, found.second, static_cast<float>(distance));
}


void display(std::tuple<Segment, osmium::object_id_type, float>& nearest, float MAX_ALLOWED_DISTANCE_IN_M) {
    const Segment& found_segment = std::get<0>(nearest);
    osmium::object_id_type way_id = std::get<1>(nearest);
    float distance = std::get<2>(nearest);

    std::cout << "Nearest segment is " << std::setprecision(2) << distance << " meters far : " << std::setprecision(6);
    std::cout << "(" << bg::get<0, 0>(found_segment) << ";" << bg::get<0, 1>(found_segment) << ")";
    std::cout << " -> ";
    std::cout << "(" << bg::get<1, 0>(found_segment) << ";" << bg::get<1, 1>(found_segment) << ")";
    std::cout << "\n\n";

    std::cout << "This segment belongs to way " << way_id << " : ";
    std::cout << "https://www.openstreetmap.org/way/" << way_id << "\n\n";

    if (static_cast<float>(distance) > MAX_ALLOWED_DISTANCE_IN_M)
    {
        std::cerr << "ERROR : nearest segment seems further than the max allowed distance = " << MAX_ALLOWED_DISTANCE_IN_M << " meters.\n";
        std::exit(4);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " OSMFILE\n";
        std::exit(1);
    }

    const char* const osmfile = argv[1];
    double requested_longitude = std::stod(argv[2]);
    double requested_latitude = std::stod(argv[3]);
    const Point requested_point = Point{requested_longitude, requested_latitude};
    constexpr const float MAX_ALLOWED_DISTANCE_IN_M = 30;
    std::cout << "Querying nearest way to point : " << requested_longitude << ";" << requested_latitude << std::endl;
    std::cout << "Loading file : " << osmfile << std::endl;

    RTree rtree = build_rtree_from_osm_data(osmfile);
    auto nearest = find_nearest(rtree, requested_point);
    display(nearest, MAX_ALLOWED_DISTANCE_IN_M);

    return 0;
}

