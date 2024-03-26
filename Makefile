CC 		= clang
FLAGS	= -Wall -Wextra -Werror
SANIT 	= -fsanitize=address
DBG   	= -g3
REDL	= -lreadline


all:
	$(CC) $(FLAGS) $(REDL) $(DBG) helpers.c parser.c pipeline.c main.c -o psh

sanit:
	$(CC) $(FLAGS) $(SANIT) main.c -o psh

pipeline:
	$(CC) $(FLAGS) helpers.c parser.c pipeline.c test_pipeline.c -o pipeline

run:
	./main

%: %.c
	$(CC) $(FLAGS) $< -o $@ 

clean: 
	rm main