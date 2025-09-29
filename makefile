INCLUDE = `cat ./compile_flags.txt | xargs`
FLAGS = -Wall -Wextra

all: b

b: main.c
	gcc ${INCLUDE} -o b main.c 


