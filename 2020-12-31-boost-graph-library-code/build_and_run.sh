#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

this_script_parent="$(realpath "$(dirname "$0")" )"
BUILD_DIR="$this_script_parent/_build"
CMAKE_ROOT_DIR="$this_script_parent"
echo "BUILD_DIR=$BUILD_DIR"
echo "CMAKE_ROOT_DIR=$CMAKE_ROOT_DIR"


pushd "$CMAKE_ROOT_DIR"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
conan install --install-folder="$BUILD_DIR" .
cmake -B"$BUILD_DIR" -H"$CMAKE_ROOT_DIR"
popd

make -j -C "$BUILD_DIR"

"$BUILD_DIR/bin/dijkstra-bin"
"$BUILD_DIR/bin/oldproperties-bin"
"$BUILD_DIR/bin/propertymap-map-bin"
"$BUILD_DIR/bin/propertymap-vector-bin"
