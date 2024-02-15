#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void print_field(int, int, int, int, int, int);
int up_R(int);
int down_R(int);
int move_player(char);

int main() {
    int score1 = 0, score2 = 0;
    int x = 1, y = 12, alfa = 1;
    int racket_1 = 12, racket_2 = 12;
    char move = ' ';

    initscr();
    while (score1 < 21 && score2 < 21) {
        nodelay(stdscr, true);
        clear();
        usleep(10 * 1000);
        print_field(x, y, racket_1, racket_2, score1, score2);
        while (1) {
            if (x == 1) {
                if (fabs(racket_1 - y) <= 1) {
                    if (racket_1 == y) {
                        alfa = 1;
                    } else if ((racket_1 - 1) == y) {
                        alfa = 2;
                    } else {
                        alfa = 3;
                    }
                } else {
                    score2++;
                    x = 1;
                    y = 12;
                    alfa = 1;
                    racket_1 = 12;
                    racket_2 = 12;
                    break;
                }
            } else if (x == 78) {
                if (fabs(racket_2 - y) <= 1) {
                    if (racket_2 == y) {
                        alfa = 4;
                    } else if ((racket_2 - 1) == y) {
                        alfa = 5;
                    } else {
                        alfa = 6;
                    }
                } else {
                    score1++;
                    x = 1;
                    y = 12;
                    alfa = 1;
                    racket_1 = 12;
                    racket_2 = 12;
                    break;
                }
            }
            if (y == 0) {
                if (alfa == 2)
                    alfa = 3;
                else if (alfa == 5)
                    alfa = 6;
            } else if (y == 24) {
                if (alfa == 3)
                    alfa = 2;
                else if (alfa == 6)
                    alfa = 5;
            }

            move = getch();
            switch (move_player(move)) {
                case 0:
                    break;
                case 1:
                    racket_1 -= up_R(racket_1);
                    break;
                case 2:
                    racket_1 += down_R(racket_1);
                    break;
                case 3:
                    racket_2 -= up_R(racket_2);
                    break;
                case 4:
                    racket_2 += down_R(racket_2);
                    break;
                default:
                    break;
            }
            if (alfa == 1) {
                x++;  //передвигаемся вправо на 1
            } else if (alfa == 2) {
                x++;  //передвигаемся вправо-вверх на 1
                y--;
            } else if (alfa == 3) {
                x++;  //передвигаемся вправо-вниз на 1
                y++;
            } else if (alfa == 4) {
                x--;  //передвигаемся влево на 1
            } else if (alfa == 5) {
                x--;  // передвигаемся влево-вверх на 1
                y--;
            } else if (alfa == 6) {
                x--;
                y++;
            }
            clear();
            usleep(100 * 1000);
            print_field(x, y, racket_1, racket_2, score1, score2);
        }
    }
    endwin();
    return 0;
}

void print_field(int ball_x, int ball_y, int roc_1_y, int roc_2_y, int score1, int score2) {
    for (int i = 0; i < 28; i++) {
        printw("%c", ' ');
    }
    printw("player1 %2d : %2d player2", score1, score2);
    for (int i = 0; i < 29; i++) {
        printw("%c", ' ');
    }
    printw("\n");
    for (int j = 0; j < 80; j++) {
        printw("%c", '=');
    }
    printw("\n");
    for (int o_y = 0; o_y < 25; o_y++) {
        if (fabs(roc_1_y - o_y) <= 1) {
            printw("%c", '#');
            if (fabs(roc_2_y - o_y) <= 1) {
                if (o_y == ball_y) {
                    for (int o_x = 1; o_x < ball_x; o_x++) {
                        printw("%c", ' ');
                    }
                    printw("%c", '*');
                    for (int o_x = ball_x + 1; o_x < 79; o_x++) {
                        printw("%c", ' ');
                    }
                    printw("%c", '#');
                } else {
                    for (int o_x = 1; o_x < 79; o_x++) {
                        printw("%c", ' ');
                    }
                    printw("%c", '#');
                }
            } else if (o_y == ball_y) {
                for (int o_x = 1; o_x < ball_x; o_x++) {
                    printw("%c", ' ');
                }
                printw("%c", '*');
                for (int o_x = ball_x + 1; o_x < 80; o_x++) {
                    printw("%c", ' ');
                }
            } else {
                for (int o_x = 1; o_x < 80; o_x++) {
                    printw("%c", ' ');
                }
            }
        } else if (o_y == ball_y) {
            if (fabs(roc_2_y - o_y) <= 1) {
                for (int o_x = 0; o_x < ball_x; o_x++) {
                    printw("%c", ' ');
                }
                printw("%c", '*');
                for (int o_x = ball_x + 1; o_x < 79; o_x++) {
                    printw("%c", ' ');
                }
                printw("%c", '#');
            } else {
                for (int o_x = 0; o_x < ball_x; o_x++) {
                    printw("%c", ' ');
                }
                printw("%c", '*');
                for (int o_x = ball_x + 1; o_x < 80; o_x++) {
                    printw("%c", ' ');
                }
            }
        } else if (fabs(roc_2_y - o_y) <= 1) {
            for (int o_x = 0; o_x < 79; o_x++) {
                printw("%c", ' ');
            }
            printw("%c", '#');
        } else {
            for (int o_x = 0; o_x < 80; o_x++) {
                printw("%c", ' ');
            }
        }
        printw("%c", '\n');
    }
    for (int j = 0; j < 80; j++) {
        printw("%c", '=');
    }
    printw("%c", '\n');
}

int move_player(char move) {
    if (move == 'a' || move == 'A') {
        return 1;
    } else if (move == 'z' || move == 'Z') {
        return 2;
    } else if (move == 'k' || move == 'K') {
        return 3;
    } else if (move == 'm' || move == 'M') {
        return 4;
    } else if (move == ' ') {
        return 0;
    } else {
        return 9;
    }
}

int up_R(int roc_y) {
    if (roc_y != 1) {
        return 1;
    } else {
        return 0;
    }
}

int down_R(int roc_y) {
    if (roc_y != 23) {
        return 1;
    } else {
        return 0;
    }
}
