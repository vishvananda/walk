import time
import sys

data = """* 8 1 7 8 8 5 2 9 5 9 5
8 5 1 1 5 6 9 4 4 5 2 1
7 2 3 5 2 9 2 6 9 3 9 4
9 2 5 9 8 9 5 7 7 5 9 6
2 4 6 7 1 4 2 6 6 2 5 8
2 8 1 5 3 8 4 9 7 5 2 3
2 9 3 5 6 7 2 4 9 4 2 5
6 3 1 7 8 2 3 3 6 7 9 3
2 5 7 4 2 7 8 5 5 3 5 8
5 2 9 8 3 6 1 4 9 5 6 3
4 6 9 8 5 4 9 7 6 4 6 8
2 7 7 1 9 9 7 3 7 2 2 ^"""
chips = 444

height = len(data.split('\n'))
last_height = height - 1
width = len(data.split('\n')[0].split())
last_width = width - 1
data = data.replace(' ', '').replace('\n', '')
start = data.index('*')
goal = data.index('^')
start_x = start % width
start_y = start // width
goal_x = goal % width
goal_y = goal // width
data = data.replace('*', '0')
data = data.replace('^', '5')
data = [ord(c) - 48 for c in data]
average = sum(data) / len(data)

n = 0
e = 1
s = 2
w = 3
charmoves = "nesw"


def print_solution(moves, depth):
    result = bytearray(depth)
    for i in xrange(depth - 1, -1, -1):
        result[i] = charmoves[moves & 3]
        moves >>= 2
    print result

solutions = 0
def walk(moves, x, y, chips, depth):
    global solutions
    if solutions >= 100000:
        return
    chips -= data[y * width + x]
    if x == goal_x and y == goal_y:
        if chips == 0:
            solutions += 1
            #print_solution(moves, depth)
            #print moves
        return
    elif x != start_x or y != start_y:
        chips -= depth - 1

    distance = abs(x - goal_x) + abs(y - goal_y) - 1
    cost = distance * (average + depth + distance / 2)
    if chips - cost <= -10:
        return
    next_depth = depth + 1
    moves <<= 2
    if x < last_width:
        walk(moves + e, x + 1, y, chips, next_depth)
    if y < last_height:
        walk(moves + s, x, y + 1, chips, next_depth)
    if x > 0:
        walk(moves + w, x - 1, y, chips, next_depth)
    if y > 0:
        walk(moves + n, x, y - 1, chips, next_depth)

# prerun once to let pypy jit
solutions = 99999
walk(0, start_x, start_y, chips, 0)
solutions = 0
a = time.time()
walk(0, start_x, start_y, chips, 0)
print >> sys.stderr, time.time() - a
print >> sys.stderr, solutions
