INCLUDE = `cat ./compile_flags.txt | xargs`
FLAGS = -Wall -Wextra

all: b

b: main.c compile_flags.txt
	gcc ${INCLUDE} ${FLAGS} -o b main.c 

compile_flags.txt: 
	pkg-config --cflags --libs gtk4 webkitgtk-6.0 > compile_flags.txt
