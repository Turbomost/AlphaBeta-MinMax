/*
 * @Author: Turbomošt
 * @Date: 2022-03-10 15:31:45
 * @Last Modified by: Turbomošt
 * @Last Modified time: 2022-03-16 10:08:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UND_A -6969
#define UND_B 6969
#define INF 1000
#define Space_Size 2
#define Inf_size 3

// Global vars
int MAX_Y = 5;
int alpha[100][100][5];
int beta[100][100][5];
int branches[5][100];
int numbers[100];
int numbers2[6][100];
int level_branches[5];
int breakpoint[6][100];
int minmax[6][100][20];
int term_count = 0;

/**
 * @brief Set up game structure
 *
 * @param structure number of branches
 * @param terminals values divided by ' '
 */
void load_structure(char *structure) {
    // Load game structure
    int x = 0;
    int y = 0;

    level_branches[0] = 1;
    char *token;
    token = strtok(structure, " ");
    while (token != NULL) {
        int number = atoi(token);
        branches[y][x] = number;
        if (number != -1) {
            level_branches[y + 1] += abs(number);
        }
        if (++x >= level_branches[y]) {
            y++;
            x = 0;
            term_count++;
        }
        token = strtok(NULL, " ");
    }

    MAX_Y = y;
}

void load_terminals(char *terminals) {
    // Load terminals
    int x = 0;
    int y = 0;
    char *token;
    token = strtok(terminals, " ");
    while (token != NULL) {
        if (branches[y][x] == -1) {
            int number = atoi(token);
            numbers2[y][x] = number;
            token = strtok(NULL, " ");
        }
        if (++x >= level_branches[y]) {
            y++;
            x = 0;
        }
    }
}

/**
 * @brief Initialize Alpha and Beta to UNDEFINED value
 *
 */
void initialize() {
    // Set all alpha, beta to UNDEFINED
    for (int i = 0; i <= MAX_Y; i++) {
        for (int j = 0; j < 100; j++) {
            branches[i][j] = -1;
            for (int c = 0; c < 5; c++) {
                alpha[i][j][c] = UND_A;
                beta[i][j][c] = UND_B;
            }
            for (int c = 0; c < 20; c++) {
                minmax[i][j][c] = UND_A;
            }
        }
    }
}

/**
 * @brief Print given number of spaces
 *
 * @param spaces number of spaces to print
 */
void fill_spaces(int spaces) {
    for (int i = 0; i < spaces; i++)
        printf(" ");
}

/**
 * @brief Print output aplhas and betas
 *
 * @param y y-coordinate
 * @param x x-coordinate
 * @param lengths 3d array of string lenghts
 */
void print_alphabeta(int y, int lengths[2][10][100]) {
    // Print Aplha
    for (int x = 0; x < 100; x++) {
        if (branches[y][x] != -1) {
            printf("| ");
            if (alpha[y][x][0] != UND_A) {
                printf("a: ");
                for (int c = 0; c < 5; c++) {
                    if (alpha[y][x][c] != UND_A) {
                        if (alpha[y][x][c + 1] != UND_A) {
                            if (alpha[y][x][c] == INF)
                                printf("Inf, ");
                            else if (alpha[y][x][c] == -INF)
                                printf("-Inf, ");
                            else
                                printf("%i, ", alpha[y][x][c]);
                        } else {
                            if (alpha[y][x][c] == INF)
                                printf("Inf ");
                            else if (alpha[y][x][c] == -INF)
                                printf("-Inf ");
                            else
                                printf("%i ", alpha[y][x][c]);

                            fill_spaces((lengths[1][y][x]) - (lengths[0][y][x]));
                        }
                    }
                }
            } else {
                printf(".. ");
            }
        }

        // Print terminals
        else if (level_branches[y] > x) {
            if (breakpoint[y][x] == 0)
                printf("| .. ");
            else {
                printf("| ");
                if (numbers2[y][x] == INF)
                    printf("Inf ");
                else if (numbers2[y][x] == -INF)
                    printf("-Inf ");
                else
                    printf("%i ", numbers2[y][x]);
            }
        }
    }

    // Print Beta
    printf("|\n| ");
    for (int x = 0; x < 100; x++) {
        if (branches[y][x] != -1) {
            if (beta[y][x][0] != UND_B) {
                printf("b: ");
                for (int c = 0; c < 5; c++) {
                    if (beta[y][x][c] != UND_B) {
                        if (beta[y][x][c + 1] != UND_B) {
                            if (beta[y][x][c] == INF)
                                printf("Inf, ");
                            else if (beta[y][x][c] == -INF)
                                printf("-Inf, ");
                            else
                                printf("%i, ", beta[y][x][c]);
                        } else {
                            if (beta[y][x][c] == INF)
                                printf("Inf ");
                            else if (beta[y][x][c] == -INF)
                                printf("-Inf ");
                            else
                                printf("%i ", beta[y][x][c]);

                            fill_spaces((lengths[0][y][x]) - (lengths[1][y][x]));
                        }
                    }
                }
            } else {
                printf(".. ");
            }

            printf("| ");
        }

        // Print spaces
        else if (level_branches[y] > x) {
            if (breakpoint[y][x] == 0)
                printf(".. | ");
            else {
                if (numbers2[y][x] == INF)
                    fill_spaces(4);
                else if (numbers2[y][x] == -INF)
                    fill_spaces(5);
                else {
                    char snum[5];
                    sprintf(snum, "%d", numbers2[y][x]);
                    fill_spaces(strlen(snum) + 1);
                }
                printf("| ");
            }
        }
    }
}

/**
 * @brief Print minmax list
 *
 * @param y Y-coordinate
 */
void print_minmax(int y) {
    for (int x = 0; x < 100; x++) {
        if (branches[y][x] != -1) {
            printf("| ");
            if (minmax[y][x][0] != UND_A) {
                for (int c = 0; c < 20; c++) {
                    if (minmax[y][x][c] != UND_A) {
                        if (minmax[y][x][c + 1] != UND_A) {
                            if (minmax[y][x][c] == INF)
                                printf("Inf, ");
                            else if (minmax[y][x][c] == -INF)
                                printf("-Inf, ");
                            else
                                printf("%i, ", minmax[y][x][c]);
                        } else {
                            if (minmax[y][x][c] == INF)
                                printf("Inf ");
                            else if (minmax[y][x][c] == -INF)
                                printf("-Inf ");
                            else
                                printf("%i ", minmax[y][x][c]);
                        }
                    }
                }
            } else {
                printf(".. ");
            }
        }

        // Print terminals
        else if (level_branches[y] > x) {
            printf("| ");
            if (numbers2[y][x] == INF)
                printf("Inf ");
            else if (numbers2[y][x] == -INF)
                printf("-Inf ");
            else
                printf("%i ", numbers2[y][x]);
        }
    }
}

/**
 * @brief Recursive AlphaBeta function
 *
 * @param y y-coordinate
 * @param x x-coordinate
 * @param A Alpha value
 * @param B Beta value
 * @param maximazing maximazing(1) or minimizing(0)
 * @return Min or Max value of branch
 */
int alphabeta(int y, int x, int A, int B, int maximazing) {
    int alpha_counter = 0;
    int beta_counter = 0;
    int temp;
    int branch_skip = 0;

    alpha[y][x][0] = A;
    beta[y][x][0] = B;

    // Calculate x-coordinate
    for (int xx = 0; xx < x; xx++)
        if (branches[y][xx] != -1)
            branch_skip += branches[y][xx];

    // Return terminal
    if (branches[y][x] == -1) {
        breakpoint[y][x] = 1;
        return numbers2[y][x];
    }

    // Alpha
    if (maximazing) {
        for (int i = 0; i < branches[y][x]; i++) {
            if ((temp = alphabeta(y + 1, branch_skip + i, A, B, 0)) > A) {
                alpha[y][x][++alpha_counter] = temp;
                A = temp;
            }
            if (A >= B) {
                for (; i < branches[y][x] - 1; i++)
                    breakpoint[y + 1][branch_skip + i + 1] = 0;
                break;
            }
        }
        return A;
    }

    // Beta
    else {
        for (int i = 0; i < branches[y][x]; i++) {
            if ((temp = alphabeta(y + 1, branch_skip + i, A, B, 1)) < B) {
                beta[y][x][++beta_counter] = temp;
                B = temp;
            }
            if (A >= B) {
                for (; i < branches[y][x] - 1; i++)
                    breakpoint[y + 1][branch_skip + i + 1] = 1;
                break;
            }
        }
        return B;
    }
    return 0;
}

/**
 * @brief Recursive MinMax function
 *
 * @param y y-coordinate
 * @param x x-coordinate
 * @param maximazing maximazing(1) or minimizing(0)
 * @return Min or Max value of the branch
 */
int minmaxfunc(int y, int x, int maximazing) {
    int temp;
    int branch_skip = 0;
    int counter = 0;

    // Calculate x-coordinate
    for (int xx = 0; xx < x; xx++)
        if (branches[y][xx] != -1)
            branch_skip += branches[y][xx];

    // Return terminal
    if (branches[y][x] == -1) {
        return numbers2[y][x];
    }

    // MAX
    if (maximazing) {
        minmax[y][x][0] = minmaxfunc(y + 1, branch_skip, 0);
        for (int i = 1; i < branches[y][x]; i++) {
            if ((temp = minmaxfunc(y + 1, branch_skip + i, 0)) > minmax[y][x][counter]) {
                minmax[y][x][++counter] = temp;
            }
        }
        return minmax[y][x][counter];
    }

    // MIN
    else {
        minmax[y][x][0] = minmaxfunc(y + 1, branch_skip, 1);
        for (int i = 1; i < branches[y][x]; i++) {
            if ((temp = minmaxfunc(y + 1, branch_skip + i, 1)) < minmax[y][x][counter]) {
                minmax[y][x][++counter] = temp;
            }
        }
        return minmax[y][x][counter];
    }
}

/**
 * @brief Calculate string length for alpha and beta
 *
 * @param lengths 3d array of lenghts
 */
void get_string_lenghts(int lengths[2][10][100]) {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < 100; x++) {
            if (branches[y][x] != -1) {
                lengths[0][y][x] = 0;
                lengths[1][y][x] = 0;
                for (int c = 0; c < 5; c++) {
                    if (alpha[y][x][c] != UND_A) {
                        char snum[5];
                        sprintf(snum, "%d", alpha[y][x][c]);
                        lengths[0][y][x] += strlen(snum);

                        if (alpha[y][x][c] == -INF || alpha[y][x][c] == INF)
                            lengths[0][y][x] -= (4 - Inf_size);

                        if (alpha[y][x][c + 1] != UND_A)
                            lengths[0][y][x] += Space_Size;
                    }
                }
                ++lengths[0][y][x];
                for (int c = 0; c < 5; c++) {
                    if (beta[y][x][c] != UND_B) {
                        char snum[5];
                        sprintf(snum, "%d", beta[y][x][c]);
                        lengths[1][y][x] += strlen(snum);

                        if (beta[y][x][c] == -INF || beta[y][x][c] == INF)
                            lengths[1][y][x] -= (4 - Inf_size);

                        if (beta[y][x][c + 1] != UND_B)
                            lengths[1][y][x] += Space_Size;
                    }
                }
                ++lengths[1][y][x];
            }
        }
    }
}

/**
 * @brief Print help to stdout
 *
 */
void print_help() {
    printf("\n");
    printf("Running:\n");
    printf(" ./run [bottom row terminals]{36}      -> Run custom input \n");
    printf(" ./run custom [struct] end [terms] end -> Run custom input with custom structure \n");
    printf(" ./run custom help                     -> More info for custom structures \n");
    printf(" ./run help                            -> Print this help \n\n");
    printf("Guide:\n");
    printf(" | .. | -> node skipped (a >= b)\n");
    printf(" | 12 | -> terminal node\n\n");
}

int main(int argc, char *argv[]) {
    // Init vars
    initialize();
    char terminals[1024];
    char structure[] = "4 2 1 2 1 2 2 2 2 2 1 2 1 2 2 2 2 -1 2 1 2 2 -1 3 -1 1 3 3 2 3 3 1 4 3 3 -1 2 2 1 2";

    // Not enough arguments
    if (argc < 2) {
        print_help();
        fprintf(stderr, "Not enough arguments!\n\n");
        exit(EXIT_FAILURE);
    }

    // Custom input
    if (!strcmp(argv[1], "custom")) {
        // No arguments
        if (argc < 3) {
            print_help();
            fprintf(stderr, "No arguments after 'custom'!\n\n");
            exit(EXIT_FAILURE);
        }

        // Can't find "end" two times
        int count;
        for (int i = 2; i < argc; i++) {
            if (!strcmp(argv[i], "end"))
                count++;
        }
        if (count != 2) {
            print_help();
            fprintf(stderr, "Can't find 'end' two times!\n\n");
            exit(EXIT_FAILURE);
        }

        if (!strcmp(argv[2], "help")) {
            printf(" > ./run custom [number of branches from up to down, left to right (-1 if terminal)] end\n");

            printf(
                "\n             _2_\n             / \\\n          _2_   0 (-1)\n          / \\\n     1 (-1)  _1_\n              |\n            \n\n    -> ./run custom 2 2 -1 -1 1 end ... \n");

            printf("\n > ./run custom [...] end [Terminals from up to down, left to right] end\n");
            printf(
                "\n             ___\n             / \\\n          ___   0\n          / \\\n         1   ___\n              |\n             inf\n\n    -> ./run custom 2 2 -1 -1 1 end 0 1 inf end\n\n");

            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            int i;
            strcpy(structure, "");
            char buffer[1024] = {0};
            for (i = 2;; i++) {
                long num;

                if (strcmp(argv[i], "end") == 0) {
                    break;
                }

                char *check = NULL;
                num = strtol(argv[i], &check, 10);
                if (*check != 0) {
                    print_help();
                    fprintf(stderr, "Invalid parameter '%s'!\n\n", argv[i]);
                    exit(EXIT_FAILURE);
                }

                char buffer_num[256] = {0};
                snprintf(buffer_num, 256, "%li ", num);
                strncat(buffer, buffer_num, 1024 - strlen(buffer));
            }
            strcpy(structure, buffer);
            structure[strlen(structure) - 1] = '\0';

            load_structure(structure);
            // Wrong number of terms
            if ((argc - i - 2) != (term_count + level_branches[MAX_Y] - 1)) {
                print_help();
                fprintf(stderr, "Unexpected number of terms : %i\nExpected: %i\n\n", argc - i - 2, term_count + level_branches[MAX_Y] - 1);
                exit(EXIT_FAILURE);
            }
            char new_buffer[1024] = {0};
            while (strcmp(argv[++i], "end")) {
                long num;

                if (strcmp(argv[i], "inf") == 0) {
                    num = 1000;
                }

                else if (strcmp(argv[i], "-inf") == 0) {
                    num = -1000;
                }

                else {
                    char *check = NULL;
                    num = strtol(argv[i], &check, 10);
                    if (*check != 0) {
                        print_help();
                        fprintf(stderr, "Invalid parameter '%s'!\n", argv[i]);
                        exit(EXIT_FAILURE);
                    }
                }
                char buffer_num[256] = {0};
                snprintf(buffer_num, 256, "%li ", num);
                strncat(new_buffer, buffer_num, 1024 - strlen(new_buffer));
            }
            strcpy(terminals, new_buffer);
            terminals[strlen(terminals) - 1] = '\0';
        }
    } else if (argc == 37) {
        char buffer[1024] = {0};
        strcat(buffer, "1000 0 -1000 0 ");
        for (int i = 1; i < 37; i++) {
            long num;

            if (strcmp(argv[i], "inf") == 0) {
                num = 1000;
            }

            else if (strcmp(argv[i], "-inf") == 0) {
                num = -1000;
            }

            else {
                char *check = NULL;
                num = strtol(argv[i], &check, 10);
                if (*check != 0) {
                    print_help();
                    fprintf(stderr, "Invalid parameter '%s'!\n", argv[i]);
                    exit(EXIT_FAILURE);
                }
            }
            char buffer_num[256] = {0};
            if (i != 36) {
                snprintf(buffer_num, 256, "%li ", num);
            } else {
                snprintf(buffer_num, 256, "%li", num);
            }
            strncat(buffer, buffer_num, 1024 - strlen(buffer));
        }
        strcpy(terminals, buffer);
    }

    else {
        print_help();
        fprintf(stderr, "No arguments!\n");
        exit(EXIT_FAILURE);
    }

    // Load structure
    load_terminals(terminals);

    // Run recursive alphabeta
    alphabeta(0, 0, -INF, INF, 1);

    // Run recursive minmax function
    minmaxfunc(0, 0, 1);

    // Print output
    printf("\nAlphaBeta:\n\n");
    int lengths[2][10][100];
    get_string_lenghts(lengths);
    for (int y = 0; y <= MAX_Y; y++) {
        print_alphabeta(y, lengths);
        printf("\n\n");
    }
    printf("\n\nMinMax:\n\n");
    for (int y = 0; y <= MAX_Y; y++) {
        print_minmax(y);
        printf("|\n\n");
    }
    printf("\n");

    return 0;
}