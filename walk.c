#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0

#define height 12
#define width 12
#define start_x 0
#define start_y 0
#define goal_x 11
#define goal_y 11
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
#define n 0
#define e 1
#define s 2
#define w 3

char intdata[width * height];

int solutions = 0;

void walk(unsigned long long moves, int position, int chips, char depth, char backs) {
    if(solutions >= 100000)
        return;
    chips -= intdata[position];

    if(position == goal_y * width + goal_x) {
        if (chips == 0) {
            solutions += 1;
            //printf("%lld\n", moves);
        }
        return;
    } else if(position != start_y * width + start_x) {
        chips -= depth - 1;
    }

    if(chips < 5)
        return;

    int next_depth = depth + 1;
    moves <<= 2;
    char x = position % 12;
    if(x < width - 1) {
        walk(moves + e, position + 1, chips, next_depth, backs);
    }
    if(position < height * (width - 1)) {
        walk(moves + s, position + width, chips, next_depth, backs);
    }
    if(backs < 2) {
        if(x > 0) {
            walk(moves + w, position - 1, chips, next_depth, backs + 1);
        }
        if(position > width - 1) {
            walk(moves + n, position - width, chips, next_depth, backs + 1);
        }
    }
}

int main(int argc, char * argv[]) {
    int i;
    for(i = 0; i < sizeof(intdata); i++) {
        intdata[i] = data[i] - '0';
    }
    clock_t c0, c1;
    c0 = clock();
    walk(0, 0, start_chips, 0, 0);
    c1 = clock();
    fprintf(stderr, "%f\n", (float) (c1 - c0)/CLOCKS_PER_SEC);

    return 0;
}
