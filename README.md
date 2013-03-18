# Walk #

A large graph walk implemented in multiple languages to compare performance.

## C ##

    $ gcc-4.7 -O3 -o walk walk.c; ./walk

0.041286
BASELINE

## Go ##

    $ go run -gcflags -m walk.go

0.060258
68.51% speed of C
1.45X slower than C

## PyPy ##

    $ pypy walk.py

0.751174926758
8.02% speed of GO
18.19X slower than C

## Python ##

    $ python walk.py

5.5545861721:
13.52% speed of PyPy
134.53X slower than C

