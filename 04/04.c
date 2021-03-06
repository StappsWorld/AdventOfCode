#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH (size_t) 5
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
#define MAX_DRAW (size_t) 100

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

int has_won(size_t *board) {
    size_t i, j, total = 0;
    for(i = 0, total = 0; i < WIDTH; i++, total = 0) {
        for(j = 0; j < WIDTH; j++) {
            if(board[i * WIDTH + j]) {
                total++;
            }
        }
        if(total == WIDTH) {
            /*printf("\nWon by row %lu\n", i + 1);*/
            return 1;
        }
    }

    for(i = 0, total = 0; i < WIDTH; i++, total = 0) {
        for(j = 0; j < WIDTH; j++) {
            if(board[j * WIDTH + i]) {
                total++;
            }
        }
        if(total == WIDTH) {
            /*printf("\nWon by column %lu\n", i + 1);*/
            return 1;
        }
    }

    return 0;
}

int part1() {
    FILE *fp = fopen(FILE_NAME, "r");
    size_t i = 0, j = 0, k = 0, l = 0, *draw_order = malloc(sizeof(size_t) * MAX_DRAW), **boards_arr, **mark_arr, boards = 0, current_board = 0, sum = 0;
    char *line = malloc(sizeof(char) * 300), *token = malloc(sizeof(char) * 300);

    if(fp == NULL) {
        printf("Failed to open %s\n", FILE_NAME);
        return EXIT_FAILURE;
    }

    if(line == NULL || token == NULL) {
        printf("Failed to allocate memory\n");
        free(line);
        free(token);
        fclose(fp);
        return EXIT_FAILURE;
    }

    fgets(line, 300, fp);
    while ((token = strtok(i ? NULL : line, " ,")) != NULL && i < MAX_DRAW)
        draw_order[i++] = atoi(token);


    while(fgets(line, 300, fp) != NULL) {
        if(line[0] == '\n') {
            boards++;
        }
    }

    boards_arr = malloc(sizeof(size_t*) * boards);
    mark_arr = malloc(sizeof(size_t*) * boards);

    for(i = 0; i < boards; i++) {
        boards_arr[i] = malloc(sizeof(size_t) * WIDTH * WIDTH);
        mark_arr[i] = malloc(sizeof(size_t) * WIDTH * WIDTH);
        memset(boards_arr[i], 0, sizeof(size_t) * WIDTH * WIDTH);
        memset(mark_arr[i], 0, sizeof(size_t) * WIDTH * WIDTH);
    }

    fseek(fp, 0, SEEK_SET);
    fgets(line, 300, fp);

    while(fgets(line, 300, fp) != NULL) {
        if(current_board >= boards) {
            printf("Too many boards\n");

            for(i = 0; i < boards; i++) {
                free(boards_arr[i]);
                free(mark_arr[i]);
            }
            free(boards_arr);
            free(mark_arr);

            free(line);
            free(token);
            fclose(fp);
            return EXIT_FAILURE;
        }

        for(i = 0, j = 0; i < WIDTH; i++, j = 0) {
            if(fgets(line, 300, fp) == NULL) {
                printf("Failed to get full board!\n");
                return EXIT_FAILURE;
            }

            /*printf("Parsing %s\n", line);*/

            while ((token = strtok(j ? NULL : line, " ")) != NULL) {
                /*printf("%s\n", token);*/
                boards_arr[current_board][i * WIDTH + j++] = atoi(token);
            }
            /*printf("%lu\n", i);*/
        }

        current_board++;
    }

    for(i = 0; i < MAX_DRAW; i++) {
        printf("%lu ", draw_order[i]);
        for(j = 0; j < boards; j++) {
            for(k = 0; k < WIDTH; k++) {
                for(l = 0; l < WIDTH; l++) {
                    if(boards_arr[j][k * WIDTH + l] == draw_order[i]) {
                        mark_arr[j][k * WIDTH + l] = 1;
                    }
                }
            }
            if(has_won(mark_arr[j])) {
                printf("\n");
                for(k = 0; k < WIDTH; k++) {
                    for(l = 0; l < WIDTH; l++) {
                        if(mark_arr[j][k * WIDTH + l]) {
                            printf(UNDERLINE"%02lu"CLOSEUNDERLINE" ", boards_arr[j][k * WIDTH + l]);
                        } else {
                            printf("%02lu ", boards_arr[j][k * WIDTH + l]);
                        }
                    }
                    printf("\n");
                }
                goto BREAK_LOOP;
            }
        }
    }

BREAK_LOOP:

    for(k = 0; k < WIDTH; k++) {
        for(l = 0; l < WIDTH; l++) {
            if(!mark_arr[j][k * WIDTH + l]) {
                sum += boards_arr[j][k * WIDTH + l];
            }
        }
    }
    

    printf("The final score is: %lu * %lu = %lu\n", draw_order[i], sum, draw_order[i] * sum);


    for(i = 0; i < boards; i++) {
        free(boards_arr[i]);
        free(mark_arr[i]);
    }
    free(boards_arr);
    free(mark_arr);
    fclose(fp);
    free(line);
    free(token);
    free(draw_order);

    return EXIT_SUCCESS;
}

int part2() {
    FILE *fp = fopen(FILE_NAME, "r");
    int *draw_order = malloc(sizeof(int) * MAX_DRAW);
    size_t i = 0, j = 0, k = 0, l = 0, order = 1, **boards_arr, **mark_arr, *order_arr, boards = 0, current_board = 0, sum = 0;
    char *line = malloc(sizeof(char) * 300), *token = malloc(sizeof(char) * 300);

    if(fp == NULL) {
        printf("Failed to open %s\n", FILE_NAME);
        return EXIT_FAILURE;
    }

    if(line == NULL || token == NULL) {
        printf("Failed to allocate memory\n");
        free(line);
        free(token);
        fclose(fp);
        return EXIT_FAILURE;
    }

    memset(draw_order, -1, sizeof(int) * MAX_DRAW);

    fgets(line, 300, fp);
    while ((token = strtok(i ? NULL : line, " ,")) != NULL && i < MAX_DRAW)
        draw_order[i++] = atoi(token);


    while(fgets(line, 300, fp) != NULL) {
        if(line[0] == '\n') {
            boards++;
        }
    }

    boards_arr = malloc(sizeof(size_t*) * boards);
    mark_arr = malloc(sizeof(size_t*) * boards);
    order_arr = malloc(sizeof(size_t) * boards);

    for(i = 0; i < boards; i++) {
        boards_arr[i] = malloc(sizeof(size_t) * WIDTH * WIDTH);
        mark_arr[i] = malloc(sizeof(size_t) * WIDTH * WIDTH);
        memset(boards_arr[i], 0, sizeof(size_t) * WIDTH * WIDTH);
        memset(mark_arr[i], 0, sizeof(size_t) * WIDTH * WIDTH);
    }

    memset(order_arr, 0, sizeof(size_t) * boards);

    fseek(fp, 0, SEEK_SET);
    fgets(line, 300, fp);

    while(fgets(line, 300, fp) != NULL) {
        if(current_board >= boards) {
            printf("Too many boards\n");

            for(i = 0; i < boards; i++) {
                free(boards_arr[i]);
                free(mark_arr[i]);
            }
            free(boards_arr);
            free(mark_arr);

            free(line);
            free(token);
            fclose(fp);
            return EXIT_FAILURE;
        }

        for(i = 0, j = 0; i < WIDTH; i++, j = 0) {
            if(fgets(line, 300, fp) == NULL) {
                printf("Failed to get full board!\n");
                return EXIT_FAILURE;
            }

            /*printf("Parsing %s\n", line);*/

            while ((token = strtok(j ? NULL : line, " ")) != NULL) {
                /*printf("%s\n", token);*/
                boards_arr[current_board][i * WIDTH + j++] = atoi(token);
            }
            /*printf("%lu\n", i);*/
        }

        current_board++;
    }

    for(i = 0; i < MAX_DRAW && draw_order[i] != -1; i++) {
        sum = 0;
        printf("%d ", draw_order[i]);
        for(j = 0; j < boards; j++) {
            if(order_arr[j] == 0) {
                for(k = 0; k < WIDTH; k++) {
                    for(l = 0; l < WIDTH; l++) {
                        if(boards_arr[j][k * WIDTH + l] == draw_order[i]) {
                            mark_arr[j][k * WIDTH + l] = 1;
                        }
                    }
                }
                if(has_won(mark_arr[j])) {
                    order_arr[j] = order++;
                }
            } else {
                sum++;
                if(sum == boards) {
                    goto EXIT_LOOP;
                }
            }
        }
    }
EXIT_LOOP:

    i--;

    if(order != boards + 1) {
        printf("There was a problem setting the order of the boards!\n (order is %lu, should be %lu)\n", order, boards);
        printf("Boards look like:\n");
        for(j = 0; j < boards; j++) {
            for(k = 0; k < WIDTH; k++) {
                for(l = 0; l < WIDTH; l++) {
                    if(mark_arr[j][k * WIDTH + l]) {
                        printf(UNDERLINE"%02lu"CLOSEUNDERLINE" ", boards_arr[j][k * WIDTH + l]);
                    } else {
                        printf("%02lu ", boards_arr[j][k * WIDTH + l]);
                    }
                }
                printf("\n");
            }
            printf("\n------------------\n");
        }
        for(i = 0; i < boards; i++) {
            free(boards_arr[i]);
            free(mark_arr[i]);
        }
        free(boards_arr);
        free(mark_arr);
        fclose(fp);
        free(line);
        free(token);
        free(draw_order);
        return EXIT_FAILURE;
    }

    j = boards;

    for(k = 0; k < boards; k++) {
        if(order_arr[k] == boards) {
            printf("Index %lu has the last board!\n", k);
            j = k;
            break;
        }
    }
    
    if(j == boards) {
        printf("Failed to find last board... Exitting...\n");
        for(i = 0; i < boards; i++) {
            free(boards_arr[i]);
            free(mark_arr[i]);
        }
        free(boards_arr);
        free(mark_arr);
        fclose(fp);
        free(line);
        free(token);
        free(draw_order);
        return EXIT_FAILURE;
    }

    sum = 0;
    for(k = 0; k < WIDTH; k++) {
        for(l = 0; l < WIDTH; l++) {
            if(!mark_arr[j][k * WIDTH + l]) {
                sum += boards_arr[j][k * WIDTH + l];
            }
        }
    }
    
    printf("\n");
    for(k = 0; k < WIDTH; k++) {
        for(l = 0; l < WIDTH; l++) {
            if(mark_arr[j][k * WIDTH + l]) {
                printf(UNDERLINE"%02lu"CLOSEUNDERLINE" ", boards_arr[j][k * WIDTH + l]);
            } else {
                printf("%02lu ", boards_arr[j][k * WIDTH + l]);
            }
        }
        printf("\n");
    }

    printf("The final score is: %lu * %d = %lu\n", sum, draw_order[i], draw_order[i] * sum);


    for(i = 0; i < boards; i++) {
        free(boards_arr[i]);
        free(mark_arr[i]);
    }
    free(boards_arr);
    free(mark_arr);
    fclose(fp);
    free(line);
    free(token);
    free(draw_order);

    return EXIT_SUCCESS;
}

int main(void) {
    /*int part_1 = part1();*/
    int part_2 = part2();
    
    srand(time(NULL));

    return part_2;
}
