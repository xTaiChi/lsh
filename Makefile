.PHONY:clean

OBJS=main.o cmd.o quit.o speed.o uart.o send.o

OUTFILE=docklight.exe

CC=cc
LD=gcc
CFLAGS= -std=gnu99 -c -Wall
LDFLASG= -lncurses


$(OUTFILE): $(OBJS)
	$(LD)  $^ -o $@ $(LDFLASG)

%.o:%.c
	$(CC) $< $(CFLAGS) -o $@

cmd.o:cmd.c cmd.h cmdtable.h cipher.h help.h

clean:
	-rm *.o
