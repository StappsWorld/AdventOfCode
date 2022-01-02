/* 
   Advent of Code 2021 - Day 06
   Samuel Rembisz
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define TABLE_SIZE (size_t) 9
#define DAYS (size_t) 256

size_t table[TABLE_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
size_t new_table[TABLE_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0}; 


void next_day() {
    size_t i;

    memset(new_table, 0, sizeof(size_t) * TABLE_SIZE);

    new_table[8] = table[0];
    new_table[6] = table[0];

    for(i=1; i < TABLE_SIZE; i++) {
        new_table[i - 1] += table[i];
    }

    memcpy(table, new_table, sizeof(size_t) * TABLE_SIZE);
}

size_t count_fish() {
    size_t i, total = 0;
    for(i = 0; i < TABLE_SIZE; i++) {
        total += table[i];
    }
    return total;
}

void print_table() {
    size_t i; 

    putchar('{');
    for(i = 0; i < TABLE_SIZE; i++) {
        printf("%lu", table[i]);
        if(i != TABLE_SIZE - 1) {
            printf(", ");
        }
    }
    printf("} => Total Fish: %lu\n", count_fish());
}

int part1() {
    FILE *fp = fopen(FILE_NAME, "r");
    char *c = malloc(sizeof(char) * 5);
    size_t i;
    
    if(c == NULL) {
        printf("Failed to malloc character! Exitting...");
        return EXIT_FAILURE;
    }

    while(fgets(c, 2, fp) != NULL) {
        fseek(fp, 1, SEEK_CUR);
        assert(*c >= '1' && *c <= '8');
        i = atol(c);
        assert(i >= 1 && i <= 8);
        table[i]++;
    }

    print_table();
    for(i = 0; i < DAYS; i++) {
        next_day();
        print_table();
    }

    return EXIT_SUCCESS;
}

int main(void) {
    
    int part_1 = part1();
    /* int part_2 = part2(); */

    return part_1;
}