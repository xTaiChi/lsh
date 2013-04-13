#include    <unistd.h>
#include    <fcntl.h>
#include    <stdio.h>
#include    <string.h>
#include    "globl.h"
#include    "win.h"

static unsigned char outbuf[512];
int send_handler(int argc,char **argv){
    int buflen = 0;
    if(uart < 0){
        wprint(cmdwin,"UART don't connect!\n");
        return -1;
    }
    for(int i = 1;i < argc;i++){
        int len = strlen(argv[i]);
        memcpy(outbuf + buflen,argv[i],len);
        buflen += len;
    }
    write(uart,outbuf,buflen);
    return 0;
}
