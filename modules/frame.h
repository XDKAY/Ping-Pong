#ifndef FRAME_MODULE

#define FRAME_MODULE

int draw_walk(int i, int j);
int draw_ball(int i, int j, int ball_pos_x, int ball_pos_y);
int draw_racket_left(int i, int j, int racket_left_y);
int draw_racket_right(int i, int j, int racket_right_y);
int draw_middle_line(int i, int j);
void draw_scores(int score_first_player, int score_second_player);
void draw_frame(int ball_pos_x, int ball_pos_y, int racket_left_y, int racket_right_y, int score_first_player, int score_second_player);
void get_winner(int score_first_player);

#endif