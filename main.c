/*
#include    <termios.h>
#include    <fcntl.h>
#include    <sys/select.h>
*/
#include    <stdio.h>
#include    <unistd.h>
#include    <string.h>
#include    <ncurses/ncurses.h>
#include    "globl.h"
#include    <signal.h>
#include    "cmd.h"
#include    "win.h"
#include    "cipher.h" 
#include    "x.h"

#define iseq(x) ((*(x) == '\r') || (*(x) == '\n') || (*(x) == ' '))

int uart = -1;
int ex = 0;

WINDOW *cmdwin = NULL,*infowin = NULL;

int ex_handler(void){
    wprint(cmdwin,"$? = %d\n",ex);
    return 0;
}



static int tok(char *str,char *args[],int len){
    char *ptr = str;
    char *mptr = str;
    int i = 0;
    while(*mptr){
        if(*mptr == '"'){
            mptr++;
            while((*mptr) && (*mptr != '"')){
                if(*mptr == '\\'){
                    mptr++;
                    switch(*(mptr)){
                        case 'r':
                            *ptr++ = '\r';
                            mptr++;
                            break;
                        case 'n':
                            *ptr++ = '\n';
                            mptr++;
                            break;
                        default:
                            *ptr++ = *mptr++;
                            break;
                    }
                }
                else
                    *ptr++ = *mptr++;
            }
            if(*mptr == '"') mptr++;
            else if (*mptr == 0) break;
        }
        if(iseq(mptr)){
            *ptr++ = '\xFF';
            mptr++;
            while(iseq(mptr)) mptr++;
            continue;
        }
        *ptr++ = *mptr++;
    }
    *ptr = '\0';
    args[i++] = strtok(str,"\xFF");
    for(;i < len;i++){
        args[i] = strtok(NULL,"\xFF");
        if(isnull(args[i])) return i;
    }
    return i;
}

static void initwin(void){
    int cmdx,cmdy,cmdw,cmdh;
    int infox,infoy,infow,infoh;

    initscr();
    cbreak();
    start_color();
    refresh();

    infoy = cmdy = cmdx = 0;
    infoh = cmdh = LINES;
    infox = infow = cmdw = COLS / 2;
    cmdwin = newwin(cmdh,cmdw,cmdy,cmdx);
    wrefresh(cmdwin);
    scrollok(cmdwin,true);
    infowin = newwin(infoh,infow,infoy,infox);
    wrefresh(infowin);
    scrollok(infowin,true);

    init_pair(style_input,COLOR_CYAN,COLOR_BLACK);
    init_pair(style_output,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(style_info,COLOR_RED,COLOR_BLACK);
    wattron(infowin,COLOR_PAIR(style_info));
    wattron(cmdwin,COLOR_PAIR(style_input));

    refresh();
}


static void putpromt(void){
    wattron(cmdwin,COLOR_PAIR(style_output));
    wprintw(cmdwin,">");
    wattron(cmdwin,COLOR_PAIR(style_input));
}
int main(int argc,char **argv){

    int argn = 0;
    char    buf[1024];
    char    *args[MAX_ARG];

    cmdInit();
    initwin();
    signal(SIGINT,SIG_IGN);
    while(1){
        putpromt();
        wgetnstr(cmdwin,buf,1024);
        wattron(cmdwin,COLOR_PAIR(style_output));
        argn = tok(buf,args,MAX_ARG);
        /* wprint(cmdwin,args[1]);   */
        ex = exec(args[0],argn,args);
    }

    return 0;

}


