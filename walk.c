#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char true = 1;
const char false = 0;

const char height = 12;
const char width = 12;
const char start_x = 0;
const char start_y = 0;
const char goal_x = 11;
const char goal_y = 11;
const char average = 5;
const int start_chips = 444;
const char * data =
    "081788529595"
    "851156944521"
    "723529269394"
    "925989577596"
    "246714266258"
    "281538497523"
    "293567249425"
    "631782336793"
    "257427855358"
    "529836149563"
    "469854976468"
    "277199737225";
const char n = 0;
const char e = 1;
const char s = 2;
const char w = 3;


char intdata[144];

int solutions = 0;
void walk(unsigned long long moves, char x, char y, int chips, char depth) {
    if(solutions >= 100000)
        return;
    chips -= intdata[y * width + x];
    if(x == goal_x && y == goal_y) {
        if (chips == 0) {
            solutions += 1;
            //printf("%lld\n", moves);
        }
        return;
    } else if(x != start_x || y != start_y) {
        chips -= depth - 1;
    }
    // cutoff for dead branches
    int distance = abs(x - goal_x) + abs(y - goal_y) - 1;
    int cost;
        cost = distance * (average + depth + distance / 2);
    if(chips - cost <= -10)
        return;

    int next_depth = depth + 1;
    moves <<= 2;
    if(x < width - 1) {
        walk(moves + e, x + 1, y, chips, next_depth);
    }
    if(y < height - 1) {
        walk(moves + s, x, y + 1, chips, next_depth);
    }
    if(x > 0) {
        walk(moves + w, x - 1, y, chips, next_depth);
    }
    if(y > 0) {
        walk(moves + n, x, y - 1, chips, next_depth);
    }
    return;
}

int main(int argc, char * argv[]) {
    int i;
    for(i = 0; i < sizeof(intdata); i++) {
        intdata[i] = data[i] - '0';
    }
    clock_t c0, c1;
    c0 = clock();
    walk(0, start_x, start_y, start_chips, 0);
    c1 = clock();
    fprintf(stderr, "%f\n", (float) (c1 - c0)/CLOCKS_PER_SEC);
    fprintf(stderr, "%d\n", solutions);

    return 0;
}
