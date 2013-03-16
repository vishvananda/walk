package main

import (
    "fmt"
    "os"
    "time"
)

const (
    height = 12
    width = 12
    start_x = 0
    start_y = 0
    goal_x = 11
    goal_y = 11
    average = 5
    start_chips = 444
    data =
    "081788529595" +
    "851156944521" +
    "723529269394" +
    "925989577596" +
    "246714266258" +
    "281538497523" +
    "293567249425" +
    "631782336793" +
    "257427855358" +
    "529836149563" +
    "469854976468" +
    "277199737225"
)

var (
    solutions = 0
    intdata [144]byte
)

func abs(x int) int {
    if (x > 0) { return x }
    return -x
}

func walk(moves *[40]byte, x int, y int, chips int, depth int) {
    if solutions >= 100000 {
        return
    }
    chips -= int(data[y * width + x] - '0')
    if x == goal_x && y == goal_y {
        if chips == 0 {
            solutions += 1
            //fmt.Printf("%s\n", moves[:depth])
        }
        return
    } else if x != start_x || y != start_y {
        chips -= depth - 1
    }

    // cutoff for dead branches
    var distance int = abs(x - goal_x) + abs(y - goal_y) - 1
    var cost int
    cost = distance * (average + depth + distance / 2);
    if chips - cost <= -10 {
        return
    }

    var next_depth int = depth + 1
    if x < width - 1 {
        moves[depth] = 'e'
        walk(moves, x + 1, y, chips, next_depth)
    }
    if y < height - 1 {
        moves[depth] = 's'
        walk(moves, x, y + 1, chips, next_depth)
    }
    if x > 0 {
        moves[depth] = 'w'
        walk(moves, x - 1, y, chips, next_depth)
    }
    if y > 0 {
        moves[depth] = 'n'
        walk(moves, x, y - 1, chips, next_depth)
    }
    return
}

func main() {
    var i int
    for i = 0; i < len(data); i++ {
        intdata[i] = data[i] - '0'
    }
    var moves[40] byte
    now := time.Now()
    walk(&moves, start_x, start_y, start_chips, 0)
    fmt.Fprintf(os.Stderr, "%f\n", float64(time.Since(now)) / 1000000000.0)
    fmt.Fprintf(os.Stderr, "%d\n", solutions)
}
