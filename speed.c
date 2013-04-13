#include    <termios.h>
#include    <unistd.h>
#include    <stdio.h>
#include    <string.h>
#include    "globl.h"
#include    "cipher.h"
#include    "win.h"

static char *outspeed(speed_t speed){
    switch(speed){
        case B0:
            return("idle");
        case B50:
            return("50");
        case B75:
            return("75");
        case B110:
            return("110");
        case B134:
            return("134");
        case B150:
            return("150");
        case B200:
            return("200");
        case B300:
            return("300");
        case B600:
            return("600");
        case B1200:
            return("1200");
        case B1800:
            return("1800");
        case B2400:
            return("2400");
        case B4800:
            return("4800");
        case B9600:
            return("9600");
        case B19200:
            return("19200");
        case B38400:
            return("38400");
        case B115200:
            return("115200");
    }
    return "unkonw";
}

static speed_t tospeed(char *str){
    if(0 == strcmp(str,"50"))
        return B50;
    if(0 == strcmp(str,"75"))
        return B75;
    if(0 == strcmp(str,"110"))
        return B110;
    if(0 == strcmp(str,"134"))
        return B134;
    if(0 == strcmp(str,"150"))
        return B150;
    if(0 == strcmp(str,"200"))
        return B200;
    if(0 == strcmp(str,"300"))
        return B300;
    if(0 == strcmp(str,"600"))
        return B600;
    if(0 == strcmp(str,"1200"))
        return B1200;
    if(0 == strcmp(str,"1800"))
        return B1800;
    if(0 == strcmp(str,"2400"))
        return B2400;
    if(0 == strcmp(str,"4800"))
        return B4800;
    if(0 == strcmp(str,"9600"))
        return B9600;
    if(0 == strcmp(str,"19200"))
        return B19200;
    if(0 == strcmp(str,"38400"))
        return B38400;
    if(0 == strcmp(str,"115200"))
        return B115200;
    return B0;
}

int speed_handler(int argc,char **argv){
    speed_t ispeed,ospeed;
    struct termios   term;
    char *opts = "i:o:";
    char opt;


    if(uart < 0){
        wprint(cmdwin,"UART don't connect!\n");
        return -1;
    }
    if(tcgetattr(uart,&term)){
        perror("speed");
        return -1;
    }
    ispeed = cfgetispeed(&term);  
    ospeed = cfgetospeed(&term);
    if(argc == 1){
        wprint(cmdwin,"input rate :%s\n",outspeed(ispeed));
        wprint(cmdwin,"output rate :%s\n",outspeed(ospeed));
        return 0;
    }
    if(argc == 2){
        ospeed = ispeed = tospeed(argv[1]);
    }else{
        while(-1 != (opt = getopt(argc,argv,opts))){
            switch(opt){
                case 'i':
                    ispeed = tospeed(optarg);
                    break;
                case 'o':
                    ospeed = tospeed(optarg);
                    break;
                default:
                    wprint(cmdwin,"Eror option \n");
                    return -1;
            }
        }
    }
    if(ispeed == B0 || ospeed == B0){
        wprint(cmdwin,"Rate is error\n");
        return -1;
    }
    cfsetospeed(&term,ospeed);
    cfsetispeed(&term,ispeed);
    tcsetattr(uart,TCSANOW,&term);

    return 0;
}
