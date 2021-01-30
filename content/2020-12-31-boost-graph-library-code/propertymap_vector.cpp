#include <iostream>
#include <map>
#include <string>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

int main(void)
{

    vector<int> ages = {22, 22, 45, 58};

    map<string, size_t> offsets;
    offsets["luke"] = 0;
    offsets["leia"] = 1;
    offsets["anakin"] = 2;
    offsets["obi-wan"] = 3;
    // le dictionnaire doit avoir l'interface d'une pmap (une de plus...) :
    associative_property_map< map<string, size_t> > offsets_pmap(offsets);

    auto vector_pmap = make_iterator_property_map(ages.begin(), offsets_pmap);

    cout << "Âge de Luke = " << get(vector_pmap, "luke") << endl;
    cout << "Âge de Anakin = " << get(vector_pmap, "anakin") << endl;
    put(vector_pmap, "anakin", 999);  // gros coup d'vieux
    cout << "Nouvel âge d'Anakin = " << get(vector_pmap, "anakin") << endl;

  return EXIT_SUCCESS;
}
