BUILD
-----

sudo apt-get install libosmium2-dev libbz2-dev zlib1g-dev libexpat1-dev
wget -O extract.osm.pbf "https://download.bbbike.org/osm/bbbike/Bordeaux/Bordeaux.osm.pbf"

mkdir _build
cd _build
conan install ..  # pip install conan if necessary
cmake .. && make


RUN
---

# Place de la Victoire à Bordeaux :
cd ..
_build/bin/rtree extract.osm.pbf "-0.572555" "44.831067"
