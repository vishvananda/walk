data = """
* 8 1 7 8 8 5 2 9 5 9 5
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
2 7 7 1 9 9 7 3 7 2 2 ^
""".strip()
chips = 444
height = len(data.split('\n'))
width = len(data.split('\n')[0].split())
data = data.replace(' ', '').replace('\n', '')
start = data.index('*')
goal = data.index('^')
data = data.replace('*', '0')
data = data.replace('^', '5')
data = [ord(c) - 48 for c in data]

def walk(moves, position, chips, depth):
    chips -= data[position]
    if position == goal:
        if chips == 0:
            return moves
        return
    elif position != start:
        chips -= depth - 1

    if chips < data[goal]:
        return

    x = position % width
    y = position // width
    movements = (
        ('e', 1, x < width - 1),
        ('s', width, y < height - 1),
        ('w', -1, x > 0),
        ('n', -width, y > 0),
    )

    for (direction, delta, allowed) in movements:
        if allowed:
            res = walk(moves + direction, position + delta, chips, depth + 1)
            if res:
                return res

print walk('', start, chips, 0)
