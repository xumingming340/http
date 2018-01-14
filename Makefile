CC	= gcc
CFLAGS	= -std=c99 -Wall -D_GNU_SOURCE

LIBS	= -lpthread

PROGS =	http

OBJS = 	main.o http_comm.o unix_error.o unix_readn.o unix_rio.o wrappthread.o \
		wrapsock.o wrapstdio.o wrapunix.o unix_writen.o unix_signal.o unix_readline.o

all:	${PROGS}

${OBJS}: unix_inc.h unpthread.h http_comm.h

sock:	${OBJS}		
		${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

clean:		
		rm -f ${PROGS} core core.* *.o temp.* *.out typescript*
