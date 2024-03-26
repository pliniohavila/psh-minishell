CC 		= clang
FLAGS	= -Wall -Wextra -Werror
SANIT 	= -fsanitize=address
DBG   	= -g3
REDL	= -lreadline


all:
	$(CC) $(FLAGS) $(REDL) helpers.c parser.c main.c -o psh

sanit:
	$(CC) $(FLAGS) $(SANIT) main.c -o psh


run:
	./main

%: %.c
	$(CC) $(FLAGS) $< -o $@ 

clean: 
	rm main