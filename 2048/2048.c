#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <ncurses.h>
#include "screen.h"
#include "input.h"
#define N 4
#define N 4
#define TARGET 2048
int matrix_2048[N][N] = {0};
WINDOW* win=NULL;
WINDOW* win2=NULL;

void init_window()
{
    win = newwin(150, 88, 0, 0);
}

void initmatrix_2048()
{
    // 在随机位置放置两个数字2或4
    srand(time(NULL));
    int i, j;
    for (i = 0; i < 2; i++)
    {
        int row = rand() % N;
        int col = rand() % N;
        int val = (rand() % 2 + 1) * 2;
        matrix_2048[row][col] = val;
    }
}

void drawTile(int y, int x, int val)
{
    int color = 1;
    while (val > 2)
    {
        val /= 2;
        color++;
    }
    attron(COLOR_PAIR(color));
    mvprintw(y, x, "      ");
    mvprintw(y + 1, x, "      ");
    mvprintw(y + 2, x, "      ");
    mvprintw(y + 1, x + 2, "%d", matrix_2048[y / 3][x / 6]);
    attroff(COLOR_PAIR(color));
}

void drawmatrix_2048()
{
    clear();
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            int val = matrix_2048[i][j];
            if (val != 0)
            {
                drawTile(i * 3, j * 6, val);
            }
            else
            {
                mvprintw(i * 3 + 1, j * 6 + 2, ".");
            }
        }
    }
    refresh();
}

int get_0_num() // 返回0的个数
{
    int i, j;
    int flag = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (matrix_2048[i][j] == 0)
                flag++;
        }
    }
    return flag;
}

void fill_a_number()
{
    int num = get_0_num();
    int i, j, pos;
    int a = 0;
    if (get_0_num() == 0)
    {
        return;
    }
    srandom((unsigned)time(NULL));
    pos = random() % num + 1;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (matrix_2048[i][j] == 0)
            {
                a++;
                if (a == pos)
                {
                    matrix_2048[i][j] = random() % 6 ? 2 : 4;
                    return;
                }
            }
        }
    }
} // 有时候会没有填充？   pos已解决。

void show_array()
{
    fill_a_number();
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; i++)
        {
            printf("%d", matrix_2048[i][j]);
        }
        printf("\n");
    }
}

void draw_matrix()
{
    // fill_a_number();
    int i, j;
    char str[9];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {

            wmove(win, i, j * 8);
            sprintf(str, "%8d", matrix_2048[i][j]);
            waddstr(win, str);
        }
    }
    wrefresh(win);
}


int change_matrix(int move)
{
    fill_a_number();
    int a[N][N], i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            a[i][j] = matrix_2048[i][j];
        }
    }
    if (move == 0)
        move_left();
    if (move == 1)
        move_down();
    if (move == 2)
        move_right();
    if (move == 3)
        move_up();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (a[i][j] != matrix_2048[i][j])
                return 1; // 1代表有变化
        }
    }
    return 0;
}

void move_left()
{
    int i;
    int j;
    int x = 0;
    int m = 0;
    for (i = 0; i < N; i++)
    {
        m = 0;
        x = 0;
        for (j = 0; j < N; j++)
        {
            if (matrix_2048[i][j] != 0) // if (matrix_2048[i][j])
            {
                // 和比较值比较
                if (x == 0)
                {
                    x = matrix_2048[i][j];
                    matrix_2048[i][j] = 0;
                }
                else // x != 0
                {
                    // 相等（可以合并）
                    if (matrix_2048[i][j] == x)
                    {
                        x = matrix_2048[i][j] + x;
                        matrix_2048[i][m] = x;
                        m++;
                        matrix_2048[i][j] = 0;
                        x = 0;
                    }
                    else // 不相等
                    {
                        matrix_2048[i][m] = x;
                        m++;
                        x = matrix_2048[i][j];
                        matrix_2048[i][j] = 0;
                    }
                }
            }
        }
        matrix_2048[i][m] = x;
    }
}

void move_right()
{
    int i, j, x, m;
    for (i = 0; i < N; i++)
    {
        m = 0;
        x = 0;
        for (j = N - 1; j >= 0; j--)
        {
            if (matrix_2048[i][j] != 0) // if (matrix_2048[i][j])
            {
                // 和比较值比较
                if (x == 0)
                {
                    x = matrix_2048[i][j];
                    matrix_2048[i][j] = 0;
                }
                else // x != 0
                {
                    // 相等（可以合并）
                    if (matrix_2048[i][j] == x)
                    {
                        x = matrix_2048[i][j] + x;
                        matrix_2048[i][N - 1 - m] = x;
                        m++;
                        matrix_2048[i][j] = 0;
                        x = 0;
                    }
                    else // 不相等
                    {
                        matrix_2048[i][N - 1 - m] = x;
                        m++;
                        x = matrix_2048[i][j];
                        matrix_2048[i][j] = 0;
                    }
                }
            }
        }
        matrix_2048[i][N - 1 - m] = x;
    }
}

void move_down()
{
    int i;
    int j;
    int x = 0;
    int m = 0;
    for (j = 0; j < N; j++)
    {
        m = 0;
        x = 0;
        for (i = N - 1; i >= 0; i--)
        {
            if (matrix_2048[i][j] != 0) /* if (matrix_2048[i][j]) */
            {
                // 和比较值比较
                if (x == 0)
                {
                    x = matrix_2048[i][j];
                    matrix_2048[i][j] = 0;
                }
                else /*x != 0*/
                {
                    // 相等（可以合并）
                    if (matrix_2048[i][j] == x)
                    {
                        x = matrix_2048[i][j] + x;
                        matrix_2048[N - 1 - m][j] = x;
                        m++;
                        matrix_2048[i][j] = 0;
                        x = 0;
                    }
                    else /*不相等*/
                    {
                        matrix_2048[N - 1 - m][j] = x;
                        m++;
                        x = matrix_2048[i][j];
                        matrix_2048[i][j] = 0;
                    }
                }
            }
        }
        matrix_2048[N - 1 - m][j] = x;
    }
}

void move_up()
{
    int i, j, x, m;
    for (j = 0; j < N; j++)
    {
        x = 0;
        m = 0;
        for (i = 0; i < N; i++)
        {
            if (matrix_2048[i][j] != 0)
            {
                if (x == 0)
                {
                    x = matrix_2048[i][j];
                    matrix_2048[i][j] = 0;
                }
                else
                {
                    if (x == matrix_2048[i][j])
                    {
                        x = x + matrix_2048[i][j];
                        matrix_2048[i][j] = 0;
                        matrix_2048[m++][j] = x;
                        x = 0;
                    }
                    else
                    {
                        matrix_2048[m++][j] = x;
                        x = matrix_2048[i][j];
                        matrix_2048[i][j] = 0;
                    }
                }
            }
        }
        matrix_2048[m][j] = x;
    }
}

int game_over()
{
    int i, j;
    if (get_0_num)
        return 0; // 1代表游戏结束，0代表游戏继续
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (j < N - 1 && matrix_2048[i][j] == matrix_2048[i][j + 1])
                return 0;
            if (i < N - 1 && matrix_2048[i][j] == matrix_2048[i + 1][j])
                return 0;
        }
    }
    return 1;
}

void draw_gameover()
{
    win2=newwin(300,150,160,90);
    wmove(win2,0,0);
    char str1[]="GAME OVER";
    waddstr(win2,str1);
    wrefresh(win2);
}
