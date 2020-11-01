#!/bin/bash

set -o errexit
set -o pipefail
set -o nounset

for i in {1..7}
do
    clang++ -std=c++14 -lpthread main${i}.cpp -o bin${i}_GITIGNORE
done

# NUMBER=2
# clang++ -std=c++11 -lpthread main${NUMBER}.cpp -o bin_GITIGNORE
# ./bin_GITIGNORE
