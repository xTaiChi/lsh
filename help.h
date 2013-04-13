#ifndef __HELP_H__
#define __HELP_H__

#define HELP_QUIT   "User: quit\n\t退出控制台"
#define HELP_OPEN   "User: open device\n\t打开设备"
#define HELP_CLOSE  "User: close\n\t关闭设备"
#define HELP_RATE   "User: rate <-i> <rate> <-o> <rate>\n \
    -i inrate  设置输入波特率.\n \
    -o outrate 设置输出波特率\n \
    不带参数查询设备的波特率,\n \
    带一个数值,则设备输入输出的波特率."

#define HELP_EX     "User: ex\n\t查询上一条命令的退出状态"
#define HELP_HELP   "Uaer: help <cmd>"
#define HELP_SEND   "Uaer: send <index|data>\n\t发送索引里面的数据,或者发送data"


#endif
