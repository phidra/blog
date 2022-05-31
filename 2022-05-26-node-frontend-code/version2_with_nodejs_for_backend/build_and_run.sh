#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

this_script_parent="$(realpath "$(dirname "$0")" )"

npm install moment

node "${this_script_parent}/main.js"
