#include <ncurses.h>
#include "../config/constants.h"
#include "frame.h"


int draw_walk(int i, int j) {
    if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
        mvaddch(i + 1, j, '#');
        return 1;
    }
    return 0;
}


int draw_ball(int i, int j, int ball_pos_x, int ball_pos_y) {
    if (i == ball_pos_y && j == ball_pos_x) {
        mvaddch(i + 1, j, 'O');
        return 1;
    }
    return 0;
}


int draw_racket_left(int i, int j, int racket_left_y) {
    if (j == RACKET_LEFT_POS_X && i >= racket_left_y && i < racket_left_y + RACKET_LEN) {
        mvaddch(i + 1, j, ']');
        return 1;
    }
    return 0;
}


int draw_racket_right(int i, int j, int racket_right_y) {
    if (j == RACKET_RIGHT_POS_X && i >= racket_right_y && i < racket_right_y + RACKET_LEN) {
        mvaddch(i + 1, j, '[');
        return 1;
    }
    return 0;
}


int draw_middle_line(int i, int j) {
    if (j == COLS / 2) {
        mvaddch(i + 1, j, '.');
        return 1;
    }
    return 0;
}


void draw_scores(int score_first_player, int score_second_player) {
    mvprintw(0, 0, "Player 1: %d\t\t\t\t\t\tPlayer 2: %d", score_first_player, score_second_player);
}


void draw_frame(int ball_pos_x, int ball_pos_y, int racket_left_y, int racket_right_y, int score_first_player, int score_second_player) {
    clear();

    draw_scores(score_first_player, score_second_player);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            int is_draw = draw_walk(i, j) || draw_ball(i, j, ball_pos_x, ball_pos_y) || 
                draw_racket_left(i, j, racket_left_y) || draw_racket_right(i, j, racket_right_y) || 
                draw_middle_line(i, j);
            
            if (!is_draw) {
                printf(" ");
            }   
        }
    }

    mvprintw(ROWS + 1, 0, "a/z - left racket, k/m - right racket: ");
    refresh();
}

void get_winner(int score_first_player) {
    if (score_first_player >= WIN_SCORE) {
        mvprintw(ROWS + 2, 0, "Player 1 wins!");
    } else {
        mvprintw(ROWS + 2, 0, "Player 2 wins!");
    }
}