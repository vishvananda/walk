# Walk #

A large graph walk implemented in multiple languages to compare performance.

## Python ##

    $ python walk.py
    26.5076258183
    100000

## PyPy ##

    $ pypy walk.py
    1.51932787895
    100000

## Go ##

    $ go run -gcflags -m walk.go 2>/dev/null
    0.367364
    100000

## C ##

    gcc -O3 -o walk walk.c; ./walk
    0.145778
    100000
