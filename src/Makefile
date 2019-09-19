CC=gcc
CFLAGS=-D_WIN32_PREFER_ANSI_ESC_SEQ -std=c99 -pedantic

test.exe:test.o term.o
	@${CC} $^ -o $@

test.o:test.c term/term.h
	@${CC} ${CFLAGS} -c $< -o $@

term.o:term/term.c
	@${CC} ${CFLAGS} -c $< -o $(notdir $(basename $<)).o

.PHONY:clean
clean:
	-@rm *.exe
	-@rm *.o
