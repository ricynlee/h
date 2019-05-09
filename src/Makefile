CC=gcc

test.exe:test.o term.o
	@${CC} $^ -o $@

test.o:test.c term/term.h
	@${CC} -c $< -o $@

term.o:term/term.c
	${CC} -c $< -o $(notdir $(basename $<)).o

.PHONY:clean
clean:
	-@rm *.exe
	-@rm *.o
