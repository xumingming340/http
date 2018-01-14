CC = gcc
CFLAGS = -std=c99 -Wall -D_GNU_SOURCE

LIBS = -lpthread

PROGS =	http

OBJS = 	main.o http_comm.o \
        unix_error.o unix_readline.o unix_readn.o unix_rio.o unix_signal.o unix_writen.o \
        wraplib.o wrappthread.o \
        wrapsock.o wrapstdio.o wrapunix.o

all:    ${PROGS}

${OBJS}: unix_inc.h unpthread.h http_comm.h

http:   ${OBJS}		
        ${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

clean:	
        rm -f ${PROGS} core core.* *.o temp.* *.out typescript*
        
