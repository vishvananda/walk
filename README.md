# Walk #

A large graph walk implemented in multiple languages to compare performance.

## Python ##

    $ python walk.py
    27.2528250217
    100000

## PyPy ##

    $ pypy walk.py
    1.53419208527
    100000

## Go ##

    $ go run -gcflags -m walk.go
    ...
    0.228865
    100000

## C ##

    gcc -O3 -o walk walk.c; ./walk
    0.147515
    100000
