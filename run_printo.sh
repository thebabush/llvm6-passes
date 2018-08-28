#!/bin/sh

cd test

CLANG_PATH=../llvm_build/bin

CLANG="$CLANG_PATH/clang"
OPT="$CLANG_PATH/opt"

rm test_printo test_printo.ll test.ll 2> /dev/null
$CLANG -O2 -S -emit-llvm test.c
$CLANG -O2 -c helper.c
echo "================================================================================"

$OPT -load=../build/passes/printo/PrintoPass.so --printo ./test.ll -S -o test_printo.ll
echo "================================================================================"

cat test_printo.ll
echo "================================================================================"

echo "Compiling instrumented program..."
$CLANG -O0 -o test_printo test_printo.ll helper.o
echo "================================================================================"

echo "Running..."
echo
echo

./test_printo

