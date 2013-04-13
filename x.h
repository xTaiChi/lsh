#ifndef __X_H__
#define __X_H__

#ifndef NULL
#define NULL    (void *)0
#endif

#ifndef __X__
#define __X__
#endif

#define MIN_CMD_LEN 2   /* 命令最少字符数 */
#define MAX_CMD_LEN 10  /* 命令最长字符 */

#ifndef OK  
#define OK  0
#endif

#ifndef ERROR
#define ERROR   1
#endif

#define isnull(x)   ((x) == NULL)
#define isok(x)   ((x) == OK)
#define iser(x)     ((x) != OK)
#define iszero(x)   (!(x))
#define notnull(x) (x)
#define isfalse(x)  ((x) == FALSE)
#define istrue(x)   ((x) == TRUE)

#define isNR(x)     (((x)[0] == '\r') && ((x)[1] == '\n'))

#endif
