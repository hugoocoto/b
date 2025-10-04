CC    = g++
FLAGS = -Wall -Wextra -fPIC 
LIBS  = `cat compile_flags.txt`

b: main.cpp config.h compile_flags.txt
	$(CC) $(FLAGS) main.cpp -o b $(LIBS)

clean:
	rm -f b 
	rm -f ~/.local/bin/b 
	rm -f ~/.local/share/applications/b.desktop 

compile_flags.txt: 
	pkg-config --cflags --libs Qt6WebEngineWidgets Qt6Widgets Qt6Core | \
	sed 's/ /\n/g' > compile_flags.txt

install: b
	mv b ~/.local/bin/b

desktop-entry: install 
	cp b.desktop ~/.local/share/applications/b.desktop
	
