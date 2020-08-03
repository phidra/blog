#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

echo ""
echo "+++ compiling :"
g++ -std=c++14 -O0 -pthread code_sequential.cpp workers.cpp -o bin_SEQUENTIAL.GITIGNORE
g++ -std=c++14 -O0 -pthread code_parallel.cpp workers.cpp -o bin_PARALLEL.GITIGNORE

AMOUNT=50000000
echo ""
echo "+++ AMOUNT=${AMOUNT}"
echo "    à adapter en fonction de la puissance de la machine qui fait tourner le code"
echo "    pour que le code soit intéressant, le binaire séquentiel doit tourner en quelques secondes"


function measure()
{
    local format_with_ctx_switches="""time took               = %E
ctx switch (involuntar) = %c
ctx switch (voluntar)   = %w
"""
    local format_without_ctx_switches="time took               = %E"
    # local format="$format_without_ctx_switches"
    local format="$format_with_ctx_switches"
    env time -f "${format}" $@
}

echo ""
echo "+++ running SEQUENTIAL :"
measure ./bin_SEQUENTIAL.GITIGNORE $AMOUNT

echo ""
echo "+++ running CONCURRENT NON-PARALLEL :"
measure taskset -c 0 ./bin_PARALLEL.GITIGNORE $AMOUNT

echo ""
echo "+++ running CONCURRENT PARALLEL :"
measure ./bin_PARALLEL.GITIGNORE $AMOUNT
