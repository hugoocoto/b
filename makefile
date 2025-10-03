CC    = g++
FLAGS = -Wall -Wextra -fPIC 
LIBS  = `cat compile_flags.txt`

b: main.cpp config.h compile_flags.txt
	$(CC) $(FLAGS) main.cpp -o b $(LIBS)

clean:
	rm -f b 

compile_flags.txt: 
	pkg-config --cflags --libs Qt6WebEngineWidgets Qt6Widgets Qt6Core | \
	sed 's/ /\n/g' > compile_flags.txt

