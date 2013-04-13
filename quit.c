#include    <stdlib.h>
#include    "globl.h"
#include    "win.h"

static void exitwin(void){
    endwin();
}
int quit(){
    uart_close();
    exitwin();
    exit(0);
}
