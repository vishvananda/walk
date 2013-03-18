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

void walk_28(unsigned long long moves, int position, int chips, char depth, int spent) {
    int cost = intdata[position];
    spent += cost;
    chips -= cost;

    if(position == goal_y * width + goal_x) {
        if (chips == 0) {
            solutions += 1;
            //printf("%lld\n", moves);
        }
        return;
    } else if(position != start_y * width + start_x) {
        chips -= depth - 1;
    }

    // cutoff if the average after 10 or more moves goes over 4
    if(depth > 10 && spent > 4 * depth) {
        return;
    }

    int next_depth = depth + 1;
    moves <<= 2;
    char x = position % 12;
    if(x < width - 1) {
        walk_28(moves + e, position + 1, chips, next_depth, spent);
    }
    if(position < height * (width - 1)) {
        walk_28(moves + s, position + width, chips, next_depth, spent);
    }
}

void walk(unsigned long long moves, int position, int chips, char depth, int spent, char backs) {
    int cost = intdata[position];
    spent += cost;
    chips -= cost;

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
        walk(moves + e, position + 1, chips, next_depth, spent, backs);
    }
    if(position < height * (width - 1)) {
        walk(moves + s, position + width, chips, next_depth, spent, backs);
    }
    if(backs < 2) {
        if(x > 0) {
            walk(moves + w, position - 1, chips, next_depth, spent, backs + 1);
        }
        if(position > width - 1) {
            walk(moves + n, position - width, chips, next_depth, spent, backs + 1);
        }
    } else if(backs == 2) {
        // This will be a 28 move solution (3 n or w moves), so use an optimized method
        if(x > 0) {
            walk_28(moves + w, position - 1, chips, next_depth, spent);
        }
        if(position > width - 1) {
            walk_28(moves + n, position - width, chips, next_depth, spent);
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
    walk(0, 0, start_chips, 0, 0, 0);
    c1 = clock();
    fprintf(stderr, "%f\n", (float) (c1 - c0)/CLOCKS_PER_SEC);
    fprintf(stderr, "%d\n", solutions);

    return 0;
}
