#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail
set -o xtrace

# affichage des derniers caractères du fichier 
od -c pouet.cpp
od -c pouet.h

# compilation succeeds (despite no endofline in both files) :
g++ -c pouet.cpp -o /dev/null

# displaying preprocessed source :
g++ -E pouet.cpp
