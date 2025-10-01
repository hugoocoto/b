INCLUDE = `cat ./compile_flags.txt | xargs`
FLAGS = -Wall -Wextra

all: b

b: main.cpp compile_flags.txt
	g++ ${INCLUDE} ${FLAGS} -o b main.cpp

compile_flags.txt: 
	pkg-config --cflags --libs Qt6WebEngineWidgets Qt6Widgets | sed 's/ /\n/g' > compile_flags.txt
