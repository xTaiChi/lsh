/*! 命令列表 */

int help();
int quit();
int speed_handler();
int uart_open();
int uart_close();
int ex_handler();
int send_handler();

Command cmdlist [] = {
    {help,CMD_HELP,HELP_HELP,NULL},
    {quit,CMD_QUIT,HELP_QUIT,NULL},
    {speed_handler,CMD_RATE,HELP_RATE,NULL},
    {uart_open,CMD_OPEN,HELP_OPEN,NULL},
    {uart_close,CMD_CLOSE,HELP_CLOSE,NULL},
    {ex_handler,CMD_EX,HELP_EX,NULL},
    {send_handler,CMD_SEND,HELP_SEND,NULL},
};

const int cmdnr = sizeof(cmdlist) / sizeof(Command);
