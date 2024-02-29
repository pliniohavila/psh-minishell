CC 		= clang
FLAGS	= -Wall -Wextra -Werror
SANIT 	= -fsanitize=address
DBG   	= -g3
REDL	= -lreadline


all:
	$(CC) $(FLAGS) main.c -o main

sanit:
	$(CC) $(FLAGS) $(SANIT) main.c -o main


run:
	./main

%: %.c
	$(CC) $(FLAGS) $< -o $@ 

clean: 
	rm main