#ifndef __CMD_H__
#define __CMD_H__

typedef const char * CommandName;
typedef const char * CommandHelp;

/**
 *
 *  命令处理句柄类型
 *  返回处理掉的字符个数,char *参数传递给句柄函数的字符串,length是这些字符的个数.
 *
 *
 */
typedef int (*CommandHandler)(int ,char **);

typedef struct _commandlist{
    CommandHandler  handler;
    CommandName     name;
    CommandHelp     help;
    struct  _commandlist *next;
}*CommandList,Command;

#define MAKE_CMD(c,i,n,h) {(c)[i].name = (n);(c)[i].handler = (h);i++;}
#define NR_HASH 20

int exec(char *cmd,int,char **);
void cmdInit(void);

#endif

