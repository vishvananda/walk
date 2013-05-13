# Walk #

A large graph walk implemented in multiple languages to compare performance.

## C ##

    $ gcc -O6 -o walk walk.c; ./walk

0.041135
BASELINE

## Go ##

    $ go run -gcflags -m walk.go

0.052420
78.47% speed of C
1.27X slower than C

## PyPy ##

    $ pypy walk.py

0.726972103119
7.21% speed of GO
17.67X slower than C

## Python ##

    $ python walk.py

5.77282810211:
12.59% speed of PyPy
140.33X slower than C

