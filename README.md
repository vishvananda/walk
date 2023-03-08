# Walk (2023 Version) #

A large graph walk implemented in multiple languages to compare performance.

## C ##

    $ gcc -O3 -o walk walk.c; ./walk

0.051575
BASELINE

## Go ##

    $ go run -gcflags -m walk.go

0.030771
167.60% speed of C
.59X slower than C

## PyPy ##

    $ pypy3 walk.py

0.3357088565826416
9.16% speed of GO
6.50X slower than C

## Python ##

    $ python3 walk.py

1.912165880203247:
17.55% speed of PyPy
37.07X slower than C

