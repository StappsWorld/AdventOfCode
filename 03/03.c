/* 
   Advent of Code 2021 - Day 03
   Samuel Rembisz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 
#define PRINTBIN(x) printf(BYTETOBINARYPATTERN "\n", BYTETOBINARY(x)); 


#define MAX_LEN (size_t) 100

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

int part1() {
    FILE *fp = fopen(FILE_NAME, "r");
    char *line = malloc(MAX_LEN), c;
    size_t lines = 0, word_len = 0, i;
    int *sum, c_is_great;
    unsigned int gamma = 0, epsilon = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    for(c = getc(fp); c != EOF; c = getc(fp), lines += c == '\n');

    fseek(fp, 0, SEEK_SET);

    for(c = getc(fp); c != '\n' && c != EOF; c = getc(fp), word_len++);
    printf("Word length is %lu\n", word_len);

    fseek(fp, 0, SEEK_SET);

    sum = malloc(sizeof(int) * word_len);
    
    if(sum == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    memset(sum, 0, sizeof(int) * word_len);
    
    while(fgets(line, MAX_LEN, fp) != NULL) {
        if(line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        printf("%s\n", line);

        i = 0;
        c = line[i];
        while(c != '\n' && c != EOF && c != '\0') {
            if (i >= word_len) {
                printf("Word length got corrupted! Current char is %c and i is %lu! Exitting...\n", c, i);
                return EXIT_FAILURE;
            }
            
            if(c == '1') {
                sum[i]++;
            }
            i++;
            c = line[i];
        }
    }

    printf("Sum: ");
    for(i = 0; i < word_len; i++) {
        printf("%d", sum[i]);
    }
    printf("\n");
    
    for(c_is_great = word_len - 1; c_is_great >= 0; c_is_great--) {
        if ((sum[c_is_great] * 100) / lines >= 50) {
            gamma |= 1 << (word_len - c_is_great - 1);
        } else {
            epsilon |= 1 << (word_len - c_is_great - 1);
        }
    }
    
    PRINTBIN(gamma);
    PRINTBIN(epsilon);

    printf("Parsed all bits\n");

    printf("\nGamma: %u, Epsilon: %u, Power Consumption: %u\n", gamma, epsilon, gamma * epsilon);

    return EXIT_SUCCESS;
}

int part2() {


    return EXIT_SUCCESS;
}

int main(void) {
    
    int part_1 = part1();
    /*int part_2 = part2();*/
    
    return part_1;   
}
