/* 
   Advent of Code 2021 - Day 02
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
    char *line = malloc(MAX_LEN), *space = NULL;
    FILE *fp = fopen(FILE_NAME, "r");
    size_t word_len = 0;
    int hp = 0, depth = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    while(fgets(line, MAX_LEN, fp) != NULL) {
        space = line;
        while(*space != '\0' && *space != ' ') {
            space++;
        }

        word_len = space - line;

        switch(word_len) {
            case 7: /* forward */
                hp += atoi(space);
                break;
            case 4: /* down */
                depth += atoi(space);
                break;
            case 2: /* up */
                depth -= atoi(space);
                break;
            default:
                printf("idk what this is %s\n", line);
                return EXIT_FAILURE;
                break;
        }
    }

    printf("Horizontal postion %d and depth %d, total %d\n", hp, depth, hp * depth);

    return EXIT_SUCCESS;
}

int part2() {
    char *line = malloc(MAX_LEN), *space = NULL;
    FILE *fp = fopen(FILE_NAME, "r");
    size_t word_len = 0;
    int hp = 0, depth = 0, aim = 0, val = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    while(fgets(line, MAX_LEN, fp) != NULL) {
        space = line;
        while(*space != '\0' && *space != ' ') {
            space++;
        }

        word_len = space - line;

        switch(word_len) {
            case 7: /* forward */
                val = atoi(space);
                hp += val;
                depth += val * aim;
                break;
            case 4: /* down */
                aim += atoi(space);
                break;
            case 2: /* up */
                aim -= atoi(space);
                break;
            default:
                printf("idk what this is %s\n", line);
                return EXIT_FAILURE;
                break;
        }
    }

    printf("Horizontal postion %d and depth %d, total %d\n", hp, depth, hp * depth);

    return EXIT_SUCCESS;


    return EXIT_SUCCESS;
}

int main(void) {
    
    /*int part_1 = part1();*/
    int part_2 = part2();
    
    return part_2;   
}
