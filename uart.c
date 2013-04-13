#include    <unistd.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <termios.h>
#include    <pthread.h>
#include    <stdlib.h>
#include    <signal.h>
#include    "globl.h"
#include    "win.h"
#include    "cipher.h"
static pthread_t    ntid;
static unsigned char buf[1024];
static int  length = 0;

static void *ltask(void *arg){
    unsigned char ch = 0;
    fd_set  rset;
    FD_ZERO(&rset);
    FD_SET(uart,&rset);
    while(1){
        read(uart,&ch,1);
        if(ch == '\r'){
            buf[length++] = '~';
        }else{
            buf[length++] = ch;
        }
        if((length >= (1024  - 1)) || (ch == '\n')){
            /*
            for(int i = 0;i < length - 1;i++){
                wprint(infowin,"%c",buf[i]);
            }
            */
            buf[length] = '\0';
            wprint(infowin,buf);
            length = 0;
        }
    }
}

int uart_open(int argc,char **argv){
    if(uart > 0){
        close(uart);
        uart = -1;
    }
    uart = open(argv[1],O_RDWR);
    if(uart < 0){
        perror("open uart");
        return -1;
    }
    if(pthread_create(&ntid,NULL,ltask,NULL)){
        perror("pthread_create");
        exit(1);
    }
    return 0;
}

int uart_close(void){
    if(uart >= 0){
        close(uart);
        pthread_cancel(ntid);
        /*! 回复定时信号的处理 !*/
        signal(SIGALRM,SIG_DFL);
    }
    uart = -1;
    return 0;
}
