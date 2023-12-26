#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"screen.h"
#include"2048.h"
#include"input.h"
#include<curses.h>
#define N 4

//printf("Present Line: %d\n", __LINE__);  打印当前行。

int main()
{
    int mv,p;
    open_screen();
    init_window();
    fill_a_number();
    draw_matrix();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);

    initmatrix_2048();
    drawmatrix_2048();
    while (1)
    {
        mv = get_user_input();
        if (change_matrix(mv))
        {
            fill_a_number();
            drawmatrix_2048();
         
        }
        p = game_over();
        if (p == 1)
        {
            draw_gameover();
            break;
        }
        
    }
    close_screen();
    return 0;

   
  
   


}
