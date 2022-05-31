#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

this_script_parent="$(realpath "$(dirname "$0")" )"

npm install "${this_script_parent}"

# npm run dev

npm run build

python3 -m http.server --directory dist/ 9000

# firefox localhost:9000
