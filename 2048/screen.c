#include"screen.h"
#include<curses.h>
void open_screen(void)
{
    initscr();			  // 初始化字符屏幕
	cbreak();			  // Ctrl + c
	noecho();			  // 不用回显
	keypad(stdscr, TRUE); // 使用功能键
    /*
//WINDOW* newwein(int nline,int ncols,int y0, int x0);
    WINDOW* win = newwin(250,300,0,0);
//int waddstr(WINDOW* win,const char* str);
    char str[] = "wo zhen de hao shuai";
    waddstr(win,str);
//int wrefresh(WINDOW* win);
    wrefresh(win);//刷新窗口
    */
}

void close_screen(void)
{
   endwin();
}