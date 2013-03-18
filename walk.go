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
    n = 0
    e = 1
    s = 2
    w = 3
)

var (
    solutions = 0
    intdata [144]int
)

func walk(moves uint64, position int, chips int, depth int, backs int) {
    if solutions >= 100000 {
        return
    }
    chips -= intdata[position]
    if position == goal_y * width + goal_x {
        if chips == 0 {
            solutions += 1
            //fmt.Printf("%d\n", moves)
        }
        return
    } else if position != start_y * width + start_x {
        chips -= int(depth - 1)
    }

    if chips < 5 {
        return
    }

    var next_depth int = depth + 1
    moves <<= 2
    var x int = position % 12
    if x < width - 1 {
        walk(moves + e, position + 1, chips, next_depth, backs)
    }
    if position < height * (width - 1) {
        walk(moves + s, position + width, chips, next_depth, backs)
    }
    if backs < 2 {
        if x > 0 {
            walk(moves + w, position - 1, chips, next_depth, backs + 1)
        }
        if position > width - 1 {
            walk(moves + n, position - width, chips, next_depth, backs + 1)
        }
    }
}

func main() {
    var i int
    for i = 0; i < len(data); i++ {
        intdata[i] = int(data[i] - '0')
    }
    now := time.Now()
    walk(0, 0, start_chips, 0, 0)
    fmt.Fprintf(os.Stderr, "%f\n", float64(time.Since(now)) / 1000000000.0)
}
