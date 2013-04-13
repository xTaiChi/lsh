#ifndef __WIN_H__
#define __WIN_H__

#include    <ncurses/ncurses.h>

enum{style_input,style_output,style_info}Style; 

extern WINDOW *cmdwin;
extern WINDOW *infowin;

#define wprint(w,fmt,...)   {wprintw(w,fmt,##__VA_ARGS__);wrefresh(w);refresh();}

#endif
