#!/bin/bash
set -euo pipefail
rm -rf build

cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER="clang++-18" -DCMAKE_C_COMPILER="clang-18" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --target tests

clang-format  --dry-run --Werror exercise.hpp && echo 'clang-format: ok' >> ../summary.txt || { echo 'FAILED: code formatting. Run `clang-format -i *.cpp *.hpp`.'; echo 'clang-format: failed' >> ../summary.txt; }
clang-tidy -p build/compile-commands.json --config-file="../.clang-tidy" exercise.hpp && echo 'clang-tidy: ok' >> ../summary.txt || { echo 'FAILED: clang-tidy`.'; echo 'clang-tidy: failed' >> ../summary.txt; }
build/tests && echo 'tests: ok' >> ../summary.txt || { echo 'FAILED: tests failed`.'; echo 'tests: failed' >> ../summary.txt; }
exit 1