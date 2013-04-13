#include    "x.h"
#include    "cmd.h"
#include    "help.h"
#include    "cipher.h"
#include    "cmdtable.h"
#include   "win.h"
#include    <string.h>
#include    <stdio.h>

static CommandList hashlist[NR_HASH];

/**************************************************************/
#define SEED    131
static int  bkdrhash(const char *str){
    int   hash = 0;
    while(*str){
        hash = hash * SEED + *str++;
    }
    return hash % NR_HASH;
}

/*************************************************************/
static CommandList match(char *str){
    int hash = 0;
    CommandList cmd = NULL;

    if(isnull(str)) return NULL;
    hash = bkdrhash(str);
    cmd = hashlist[hash];
    for(;cmd;cmd = cmd->next){
        if(0 == strcmp(cmd->name,str))
            return cmd;
    }
    return NULL;
}

/*************************************************************/

int help(int argc,char **args){
    CommandList cmd = NULL;
    if(argc == 1){
        for(int i = 0;i < cmdnr;i++){
            if(!(i % 10)) putchar('\n');
            wprint(cmdwin,"%-10s ",cmdlist[i].name);
        }
    }else{
        cmd = match(args[1]);
        if(notnull(cmd)){
            wprint(cmdwin,cmd->help);
        }
        else{
            wprint(cmdwin,"%s don't find!",args[1]);
        }
    }
    putchar('\n');
    return 0;
}

/*************************************************************/
int exec(char *cmdstr,int argc,char **args){
    CommandList cmd = NULL;

    cmd = match(cmdstr);
    if(notnull(cmd)){
        return (cmd->handler)(argc,args);
    }
    return -1;
}

/************************************************************/
void cmdInit(void){
    int hash = 0;
    int i = 0;
    memset(hashlist,0,NR_HASH * sizeof(CommandList));
    for(;i < cmdnr;i++){
        hash = bkdrhash(cmdlist[i].name);
        cmdlist[i].next = hashlist[hash];
        hashlist[hash] = cmdlist + i;
    }
}
