CXX     = g++
CXXFLAGS= -Wall -Wextra -fPIC `pkg-config --cflags Qt6Core Qt6Widgets Qt6WebEngineWidgets` -DQTANGLE
LIBS    = `pkg-config --libs Qt6Core Qt6Widgets Qt6WebEngineWidgets`

all: b

b: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o b $(LIBS)

clean:
	rm -f b

compile_flags.txt: 
	pkg-config --cflags --libs Qt6WebEngineWidgets Qt6Widgets Qt6Core | sed 's/ /\n/g' > compile_flags.txt
