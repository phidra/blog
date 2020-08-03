#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail
# set -o xtrace


cat << EOF
+++ Cette POC montre le false_sharing en action :
    - elle lance deux calculs identiques et assez intensifs dans deux threads
    - elle mesure le temps nécessaire pour que les deux threads terminent
    - 4 version de la POC existent :
        - sequential (REFERENCE) = les calculs sont faits séquentiellement plutôt que dans des threads
        - parallel naive = chaque thread travaile directement sur la variable résultat, et les deux variables sont contigües en mémoire
        - parallel fast aligned = chaque thread travaile directement sur la variable résultat, mais les deux variables sont séparées en mémoire
        - parallel fast offline = chaque thread travaille sur une variable locale, et ne mets à jour la variable résultat qu'une fois, en fin de calcul

EOF

function measure()
{
    # local format="""time took               = %E
# ctx switch (involuntar) = %c
# ctx switch (voluntar)   = %w
# """
    local format="""time took  = %E"""
    env time -f "${format}" $@
}


echo ""
echo "+++ compiling :"
for version in  sequential  parallel_naive  parallel_fast_aligned  parallel_fast_offline
do
    g++ -std=c++14 -pthread ${version}.cpp -O0 -o bin_${version}.GITIGNORE
done


ITERATION_NUMBER=500000000  # attention à ne pas overflow l'int
echo ""
echo "+++ ITERATION_NUMBER=${ITERATION_NUMBER}"
echo "    à adapter en fonction de la patate de la machine qui fait tourner la POC"
echo "    pour que la POC soit intéressante, l'implémentation de référence doit tourner en quelques secondes"

echo ""
echo "+++ running SEQUENTIAL implementation as a REFERENCE :"
measure ./bin_sequential.GITIGNORE $ITERATION_NUMBER

echo ""
echo "+++ running PARALLEL NAIVE implementation :"
measure ./bin_parallel_naive.GITIGNORE $ITERATION_NUMBER

echo ""
echo "+++ running PARALLEL FAST ALIGNED implementation :"
measure ./bin_parallel_fast_aligned.GITIGNORE $ITERATION_NUMBER

echo ""
echo "+++ running PARALLEL FAST OFFLINE implementation :"
measure ./bin_parallel_fast_offline.GITIGNORE $ITERATION_NUMBER

