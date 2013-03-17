# Walk #

A large graph walk implemented in multiple languages to compare performance.

## Python ##

    $ python walk.py
    22.7430679798
    100000

## PyPy ##

    $ pypy walk.py
    1.32472109795
    100000

## Go ##

    $ go run -gcflags -m walk.go
    ...
    0.213832
    100000

## C ##

    gcc -O3 -o walk walk.c; ./walk
    0.110297
    100000
