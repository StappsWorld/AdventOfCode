/* 
   Advent of Code 2021 - Day 01
   Samuel Rembisz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN (size_t) 100

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

int part1() {
    FILE *f = fopen(FILE_NAME, "r");
    char *line = malloc(MAX_LEN);
    int current = -1, previous = -1;
    size_t increased = 0, decreased = 0;

    if (f == NULL) {
        printf("Could not open file %s\n", FILE_NAME);
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Could not allocate memory\n");
        return EXIT_FAILURE;
    }

    while (fgets(line, MAX_LEN, f) != NULL) {
        current = atoi(line);
        if (previous != -1) {
            if (current > previous) {
                printf("%d (increased)\n", current);
                increased++;
            } else if (current < previous) {
                printf("%d (decreased)\n", current);
                decreased++;
            } else {
                printf("%d (unchanged)\n", current);
            }
        } else {
            printf("%d (N/A - no previous measurement)\n", current);
        }
        previous = current;
    }

    printf("Submarine increased %lu times and decreased %lu times\n", increased, decreased);
    return EXIT_SUCCESS;
}

int part2() {
    int a = -1, b = -1, c = -1;
    int current = -1, previous = -1;
    FILE *f = fopen(FILE_NAME, "r");
    char *line = malloc(MAX_LEN), current_window = 'A';
    size_t increased = 0, decreased = 0;

    if (f == NULL) {
        printf("Could not open file %s\n", FILE_NAME);
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Could not allocate memory\n");
        return EXIT_FAILURE;
    }

    while (fgets(line, MAX_LEN, f) != NULL) {
        a = atoi(line);
        if (b != -1 && c != -1) {
            current = a + b + c;
            if (previous != -1) {
                if (current > previous) {
                    printf("%c: %d (increased)\n", current_window, current);
                    increased++;
                } else if (current < previous) {
                    printf("%c: %d (decreased)\n", current_window, current);
                    decreased++;
                } else {
                    printf("%c: %d (unchanged)\n", current_window, current);
                }
            } else {
                printf("%c: %d (N/A - no previous sum)\n", current_window, current);
            }
            previous = current;
            current_window++;
            if (current_window > 'z') {
                current_window = 'A';
            }
        }
        c = b;
        b = a;
    }

    printf("Submarine increased %lu times and decreased %lu times\n", increased, decreased);

    return EXIT_SUCCESS;
}

int main(void) {
    
    /*int part_1 = part1();*/
    int part_2 = part2();
    
    return part_2;   
}
