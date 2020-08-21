#!/bin/bash

set -o nounset
set -o errexit
set -o pipefail

# on travaille dans un répertoire temporaire :
trap 'rm -rf "$workdir" ; popd &> /dev/null' EXIT
workdir="$(mktemp -d -t nested_quote_example.XXXXXXXX)"
echo ""
echo "===== workdir = $(pwd)"
pushd "$workdir" &> /dev/null


echo ""
echo "===== setup :"
mkdir "this directory"
myfile="this directory/that file.txt"
touch "$myfile"
tree


echo ""
echo "===== récupérer le répertoire parent, KO sans quoting :"
ko_parent=$(dirname $myfile)
echo "WRONG (unquoted) PARENT IS : '$ko_parent'"


echo ""
echo "===== récupérer le répertoire parent, OK avec quoting :"
ok_parent=$(dirname "$myfile")
echo "CORRECT (quoted) PARENT IS : '$ok_parent'"


set +o errexit
echo ""
echo "===== itérer sur le répertoire parent, KO sans second quoting :"
for directory in /usr/bin/ /usr/sbin $(dirname "$myfile") /bin
do
    du -sh "$directory"
done

echo ""
echo "===== itérer sur le répertoire parent, KO bis sans second quoting :"
for directory in /usr/bin/ /usr/sbin "$(dirname $myfile)" /bin
do
    du -sh "$directory"
done
set -o errexit

echo ""
echo "===== itérer sur le répertoire parent, OK avec second quoting :"
for directory in /usr/bin/ /usr/sbin "$(dirname "$myfile")" /bin
do
    du -sh "$directory"
done

echo ""
echo "===== reste OK même sur plusieurs niveaux :"
for directory in /usr/bin/ /usr/sbin "$(realpath "$(readlink -e "$(dirname "$myfile")")")" /bin
do
    du -sh "$directory"
done
