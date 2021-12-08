/* 
   Advent of Code 2021 - Day 03
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

unsigned int binary_to_int(char *str)
{
    size_t i;
    unsigned int j, result = 0;
    size_t len = strlen(str);
    for (i = 0, j = len - 1; i < len && j >= 0; i++, j--) {
        if (str[j] == '1') {
            result += (1 << i);
        }
    }
    return result;
}

char* int_to_binary(unsigned int num)
{
    size_t len = sizeof(num) * 8, j;
    char *str = malloc(sizeof(char) * len + 1);
    int i;
    if(str == NULL) {
        printf("Error allocating memory\n");
        return NULL;
    }

    memset(str, 0, len + 1);

    for (i = len - 1, j = 0; i >= 0; i--, j++) {
        str[j] = (num & (1u << i)) ? '1' : '0';
    }
    str[len] = '\0';
    return str;
}

int part1() {
    FILE *fp = fopen(FILE_NAME, "r");
    char *line = malloc(MAX_LEN), c;
    size_t lines = 0, word_len = 0, i;
    int *sum, c_is_great;
    unsigned int gamma = 0, epsilon = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        free(line);
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Error allocating memory!\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    for(c = getc(fp); c != EOF; c = getc(fp), lines += (c == '\n' || c == EOF));

    fseek(fp, 0, SEEK_SET);

    for(c = getc(fp); c != '\n' && c != EOF; c = getc(fp), word_len++);
    printf("Word length is %lu\n", word_len);

    fseek(fp, 0, SEEK_SET);

    sum = malloc(sizeof(int) * word_len);
    
    if(sum == NULL) {
        printf("Error allocating memory!\n");
        fclose(fp);
        free(line);
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
                fclose(fp);
                free(line);
                free(sum);
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
        printf("%d ", sum[i]);
    }
    printf("\n");
    
    for(c_is_great = word_len - 1; c_is_great >= 0; c_is_great--) {
        if ((sum[c_is_great] * 100) / lines >= 50) {
            gamma |= 1 << (word_len - c_is_great - 1);
        } else {
            epsilon |= 1 << (word_len - c_is_great - 1);
        }
    }

    printf("Parsed all bits\n");

    printf("\nGamma: %u, Epsilon: %u, Power Consumption: %u\n", gamma, epsilon, gamma * epsilon);

    fclose(fp);
    free(line);
    free(sum);

    return EXIT_SUCCESS;
}

int part2() {
    FILE *fp = fopen(FILE_NAME, "r");
    char *line = malloc(MAX_LEN), c, *binary_str = NULL;
    size_t lines = 0, word_len = 0, i, j, total = 0, found = 0;
    int c_is_great, *indexes, cot_raw = -1, oxy_raw = -1;
    unsigned int cot = 0, oxy = 0, *nums, bit, sig_bit;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    for(c = getc(fp); c != EOF; c = getc(fp), lines += (c == '\n' || c == EOF));

    fseek(fp, 0, SEEK_SET);

    for(c = getc(fp); c != '\n' && c != EOF; c = getc(fp), word_len++);
    printf("Word length is %lu\n", word_len);

    fseek(fp, 0, SEEK_SET);

    nums = malloc(sizeof(unsigned int) * lines);
    indexes = malloc(sizeof(int) * lines);
    
    if( nums == NULL || indexes == NULL) {
        printf("Error allocating memory!\n");
        free(nums);
        free(indexes);
        fclose(fp);
        free(line);
        return EXIT_FAILURE;
    }

    memset(nums, 0, sizeof(unsigned int) * lines);
    memset(indexes, 1, sizeof(int) * lines);

    j = 0;

    while(fgets(line, MAX_LEN, fp) != NULL) {
        if(line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        nums[j++] = binary_to_int(line);
    }

    printf("Nums: \n");
    for(j = 0; j < lines; j++) {
        binary_str = int_to_binary(nums[j]);
        printf("%s\n", (binary_str + strlen(binary_str) - word_len));
        free(binary_str);
    }

    for(c_is_great = word_len - 1; c_is_great >= 0 && total != 1; c_is_great--) {
        sig_bit = 1 << (c_is_great);

        found = 0;
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                found += (nums[j] & sig_bit) > 0;
                total++;
            }
        }

        bit = (found * 100) / total >= 50;
        
        printf("---------------------\n%lu%% of the bits in the %d place are 1, meaning we ", (found * 100) / total, c_is_great);
        if(bit) {
            printf("should filter the 0's \n");
        } else {
            printf("should filter the 1's \n");
        }

        binary_str = int_to_binary(sig_bit);
        printf("\n%s", (binary_str + strlen(binary_str) - word_len));
        free(binary_str);

        printf(" removes:\n");
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                if((bit && (nums[j] & sig_bit) > 0) || (!bit && ((nums[j] & sig_bit) | 0) == 0)) {
                    continue;
                } else {
                    for(i = 0; i < lines; i++) {
                        if(i == j) {
                            continue;
                        }

                        if(indexes[i]) {
                            break;
                        }
                    }
                    if(indexes[i]) {
                        binary_str = int_to_binary(nums[j]);
                        printf("%s\n", (binary_str + strlen(binary_str) - word_len));
                        free(binary_str);
                        indexes[j] = 0;
                        total++;
                    } else {
                        oxy_raw = nums[j];
                        goto EXIT_OXY;
                    }
                }
            }
        }
        if(total == 0) {
            printf("None!\n");
        }
        printf("\nArray is now:\n");
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                binary_str = int_to_binary(nums[j]);
                printf("%s\n", (binary_str + strlen(binary_str) - word_len));
                free(binary_str);
                total++;
            }
        }
        printf("\n");
    }

EXIT_OXY:

    if(oxy_raw == -1) {
        for(i = 0; i < lines; i++) {
            if(indexes[i]) {
                oxy = nums[i];
                break;
            }
        }
        if(i == lines) {
            printf("Error finding Oxy!\n");
            free(nums);
            free(indexes);
            fclose(fp);
            free(line);
            return EXIT_FAILURE;
        }
    } else {
        oxy = (unsigned int)oxy_raw;
    }

    binary_str = int_to_binary(oxy);
    printf("Oxy is %u => %s\n\n", oxy, (binary_str + strlen(binary_str) - word_len));
    free(binary_str);

    memset(indexes, 1, sizeof(int) * lines);

    printf("Moving to C02\n\n");
    printf("Nums: \n");
    for(j = 0; j < lines; j++) {
        binary_str = int_to_binary(nums[j]);
        printf("%s\n", (binary_str + strlen(binary_str) - word_len));
        free(binary_str);
    }
    total = 0;
    for(c_is_great = word_len - 1; c_is_great >= 0 && total != 1; c_is_great--) {
        sig_bit = 1 << (c_is_great);

        found = 0;
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                found += (nums[j] & sig_bit) > 0;
                total++;
            }
        }

        bit = (found * 100) / total < 50;
        
        printf("---------------------\n%lu%% of the bits in the %d place are 1, meaning we ", (found * 100) / total, c_is_great);
        if(bit) {
            printf("should filter the 0's \n");
        } else {
            printf("should filter the 1's \n");
        }

        binary_str = int_to_binary(sig_bit);
        printf("\n%s", (binary_str + strlen(binary_str) - word_len));
        free(binary_str);

        printf(" removes:\n");
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                if((bit && (nums[j] & sig_bit) > 0) || (!bit && ((nums[j] & sig_bit) | 0) == 0)) {
                    continue;
                } else {
                    for(i = 0; i < lines; i++) {
                        if(i == j) {
                            continue;
                        }

                        if(indexes[i]) {
                            break;
                        }
                    }
                    if(indexes[i]) {
                        binary_str = int_to_binary(nums[j]);
                        printf("%s\n", (binary_str + strlen(binary_str) - word_len));
                        free(binary_str);
                        indexes[j] = 0;
                        total++;
                    } else {
                        cot_raw = nums[j];
                        goto EXIT_COT;
                    }
                }
            }
        }
        if(total == 0) {
            printf("None!\n");
        }
        printf("\nArray is now:\n");
        total = 0;
        for(j = 0; j < lines; j++) {
            if(indexes[j]) {
                binary_str = int_to_binary(nums[j]);
                printf("%s\n", (binary_str + strlen(binary_str) - word_len));
                free(binary_str);
                total++;
            }
        }
        printf("\n");
    }

EXIT_COT:

    if(cot_raw == -1) {
        for(i = 0; i < lines; i++) {
            if(indexes[i]) {
                cot = nums[i];
                break;
            }
        }
        if(i == lines) {
            printf("Error finding C02!\n");
            free(nums);
            free(indexes);
            fclose(fp);
            free(line);
            return EXIT_FAILURE;
        }
    } else {
        cot = (unsigned int)cot_raw;
    }

    binary_str = int_to_binary(cot);
    printf("Cot is %u => %s\n", cot, (binary_str + strlen(binary_str) - word_len));
    free(binary_str);

    printf("Oxygen: %u, Carbon: %u, Life Support Rating: %u\n", oxy, cot, oxy * cot);
    
    fclose(fp);

    free(nums);
    free(indexes);
    free(line);

    return EXIT_SUCCESS;
}

int main(void) {
    /*int part_1 = part1();*/
    int part_2 = part2();
    
    return part_2;
}
