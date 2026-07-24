#include <ncurses.h>
#include "./config/constants.h"
#include "./modules/frame.h"


int main(void) {
    int ball_pos_x = BALL_START_X;
    int ball_pos_y = BALL_START_Y;
    int ball_dir_x = 1;
    int ball_dir_y = 1;

    int racket_left_y = RACKET_LEFT_START_Y;
    int racket_right_y = RACKET_RIGHT_START_Y;

    int score_first_player = SCORE_FIRST_PLAYER;
    int score_second_player = SCORE_SECOND_PLAYER;

    int game_loop = 1;
    int input;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(SPEED_BALL);

    while (game_loop) {
        draw_frame(ball_pos_x, ball_pos_y, racket_left_y, racket_right_y, score_first_player, score_second_player);
        input = getch();

        if (input == 'a' && racket_left_y > 1) {
            racket_left_y--;
        } else if (input == 'z' && racket_left_y + RACKET_LEN < ROWS - 1) {
            racket_left_y++;
        } else if (input == 'k' && racket_right_y > 1) {
            racket_right_y--;
        } else if (input == 'm' && racket_right_y + RACKET_LEN < ROWS - 1) {
            racket_right_y++;
        }

        ball_pos_x += ball_dir_x;
        ball_pos_y += ball_dir_y;

        if (ball_pos_y <= 1 || ball_pos_y >= ROWS - 2) {
            ball_dir_y = -ball_dir_y;
        }
        if (ball_pos_x == RACKET_LEFT_POS_X + 1 && ball_pos_y >= racket_left_y && ball_pos_y < racket_left_y + RACKET_LEN) {
            ball_dir_x = -ball_dir_x;
        }
        if (ball_pos_x == RACKET_RIGHT_POS_X - 1 && ball_pos_y >= racket_right_y && ball_pos_y < racket_right_y + RACKET_LEN) {
            ball_dir_x = -ball_dir_x;
        }
        if (ball_pos_x <= 0) {
            score_second_player++;
            ball_pos_x = BALL_START_X;
            ball_pos_y = BALL_START_Y;
            ball_dir_x = 1;
            ball_dir_y = 1;
        }
        if (ball_pos_x >= COLS - 1) {
            score_first_player++;
            ball_pos_x = BALL_START_X;
            ball_pos_y = BALL_START_Y;
            ball_dir_x = -1;
            ball_dir_y = 1;
        }
        if (score_first_player >= WIN_SCORE || score_second_player  >= WIN_SCORE) {
            draw_frame(ball_pos_x, ball_pos_y, racket_left_y, racket_right_y, score_first_player, score_second_player);
            get_winner(score_first_player);

            mvprintw(ROWS + 3, 0, "Press any key to exit...");

            refresh();
            timeout(-1);
            getch();
            game_loop = 0;
        }

    }
    endwin();

    return 0;
}