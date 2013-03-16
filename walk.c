#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0

#define height 12
#define width 12
#define start_x 0
#define start_y 0
#define goal_x 11
#define goal_y 11
#define average 5
#define start_chips 444
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

char intdata[width * height];

int solutions = 0;
void walk(char * moves, char x, char y, int chips, char depth) {
    if(solutions >= 100000)
        return;
    chips -= intdata[y * width + x];
    if(x == goal_x && y == goal_y) {
        if (chips == 0) {
            solutions += 1;
            //moves[depth] = 0;
            //printf("%s\n", moves);
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
    if(x < width - 1) {
        moves[depth] = 'e';
        walk(moves, x + 1, y, chips, next_depth);
    }
    if(y < height - 1) {
        moves[depth] = 's';
        walk(moves, x, y + 1, chips, next_depth);
    }
    if(x > 0) {
        moves[depth] = 'w';
        walk(moves, x - 1, y, chips, next_depth);
    }
    if(y > 0) {
        moves[depth] = 'n';
        walk(moves, x, y - 1, chips, next_depth);
    }
    return;
}

int main(int argc, char * argv[]) {
    int i;
    for(i = 0; i < sizeof(intdata); i++) {
        intdata[i] = data[i] - '0';
    }
    char moves[40] = "";
    clock_t c0, c1;
    c0 = clock();
    walk(moves, start_x, start_y, start_chips, 0);
    c1 = clock();
    fprintf(stderr, "%f\n", (float) (c1 - c0)/CLOCKS_PER_SEC);
    fprintf(stderr, "%d\n", solutions);

    return 0;
}
