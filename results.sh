#!/usr/bin/env bash

C_BUILD="gcc -O3 -o walk walk.c"
C_EXEC="./walk"
GO="go run -gcflags -m walk.go"
PYPY="pypy3 walk.py"
PYTHON="python3 walk.py"
`$C_BUILD`
C_TIME=`$C_EXEC 2>&1 | tail -n1`
GO_TIME=`$GO 2>&1 | tail -n1`
PYPY_TIME=`$PYPY 2>&1 | tail -n1`
PYTHON_TIME=`$PYTHON 2>&1 | tail -n1`
GO_PCT=`echo "scale=2; $C_TIME * 100/$GO_TIME" | bc -l`
PYPY_PCT=`echo "scale=2; $GO_TIME * 100/$PYPY_TIME" | bc -l`
PYTHON_PCT=`echo "scale=2; $PYPY_TIME * 100/$PYTHON_TIME" | bc -l`
GO_DIFF=`echo "scale=2; $GO_TIME/$C_TIME" | bc -l`
PYPY_DIFF=`echo "scale=2; $PYPY_TIME/$C_TIME" | bc -l`
PYTHON_DIFF=`echo "scale=2; $PYTHON_TIME/$C_TIME" | bc -l`

cat > README.md <<EOF
# Walk (2023 Version) #

A large graph walk implemented in multiple languages to compare performance.

## C ##

    $ $C_BUILD; $C_EXEC

$C_TIME
BASELINE

## Go ##

    $ $GO

$GO_TIME
${GO_PCT}% speed of C
${GO_DIFF}X slower than C

## PyPy ##

    $ $PYPY

$PYPY_TIME
${PYPY_PCT}% speed of GO
${PYPY_DIFF}X slower than C

## Python ##

    $ $PYTHON

$PYTHON_TIME:
${PYTHON_PCT}% speed of PyPy
${PYTHON_DIFF}X slower than C

EOF
