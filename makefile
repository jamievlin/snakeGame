CXX=g++
CXXFLAGS=-Wall -std=c++14 -g
LIBS=ncurses
default: snakeGame

snakeGame: snakeGame.cc mainTerminal.o Snake.o
	$(CXX) $(CXXFLAGS) -l$(LIBS) -o $@ $^

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f snakeGame *.o *.gch