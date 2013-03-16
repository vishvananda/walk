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
data = bytearray(ord(c) - 48 for c in data)
average = sum(data) / len(data)

solutions = 0
def walk(moves, x, y, chips, depth):
    global solutions
    if solutions >= 100000:
        return
    chips -= data[y * width + x]
    if x == goal_x and y == goal_y:
        if chips == 0:
            solutions += 1
            #print moves[:depth]
        return
    elif x != start_x or y != start_y:
        chips -= depth - 1

    distance = abs(x - goal_x) + abs(y - goal_y) - 1
    cost = distance * (average + depth + distance / 2)
    if chips - cost <= -10:
        return
    next_depth = depth + 1
    if x < last_width:
        moves[depth] = 'e'
        walk(moves, x + 1, y, chips, next_depth)
    if y < last_height:
        moves[depth] = 's'
        walk(moves, x, y + 1, chips, next_depth)
    if x > 0:
        moves[depth] = 'w'
        walk(moves, x - 1, y, chips, next_depth)
    if y > 0:
        moves[depth] = 'n'
        walk(moves, x, y - 1, chips, next_depth)

# prerun once to let pypy jit
solutions = 99999
walk(bytearray(40), start_x, start_y, chips, 0)
solutions = 0
a = time.time()
walk(bytearray(40), start_x, start_y, chips, 0)
print >> sys.stderr, time.time() - a
print >> sys.stderr, solutions
