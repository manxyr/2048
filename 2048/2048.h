#ifndef __2048_H__
#define __2048_H__
void init_window();
int  get_0_num();
void fill_a_number();
void show_array();
void draw_matrix();
int change_matrix(int move);
void move_left();
void move_right();
void move_up();
void move_down();
int game_over();
void draw_score();
void initmatrix_2048();
void drawTile(int y, int x, int val);
void drawmatrix_2048();
void draw_gameover();

#endif