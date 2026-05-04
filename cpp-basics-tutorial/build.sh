#!/usr/bin/env bash
set -e
CXX=${CXX:-g++}
FLAGS="-std=c++17 -Wall -Wextra -g"
mkdir -p build
for src in step*/*.cpp; do
    name=$(basename "$src" .cpp)
    echo "  Compiling $src → build/$name"
    $CXX $FLAGS -o "build/$name" "$src" -lm
done
echo ""
echo "Done. Run: ./run_all.sh"
