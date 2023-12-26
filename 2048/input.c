#include"input.h"
#include<curses.h>
extern WINDOW* win;
int get_user_input()
{
    keypad(win,TRUE);
    int ch=wgetch(win);
    keypad(win,FALSE);
    if(ch=='a'||ch=='A'||ch==KEY_LEFT)  //KEY_LEFT类似ASCLL码，整数形式存放。
    return LEFT;                        //用宏定义，便于阅读
    if(ch=='s'||ch=='S'||ch==KEY_DOWN)
    return DOWN;
    if(ch=='d'||ch=='D'||ch==KEY_RIGHT)
    return RIGHT;
    if(ch=='w'||ch=='W'||ch==KEY_UP)
    return UP;
}