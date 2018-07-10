CXX=g++
CXXFLAGS=-Wall -std=c++14 -O2
LIBS=ncurses
default: snakeGame

snakeGame: snakeGame.cc mainTerminal.o Snake.o
	$(CXX) $(CXXFLAGS) -l$(LIBS) -o $@ $^

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f snakeGame *.o *.gch