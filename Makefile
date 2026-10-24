CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC      = $(wildcard src/*.cpp)
HDR      = $(wildcard include/*.hpp)

# main program
ludo: $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o ludo

# tests
test_rules: tests/test_rules.cpp src/rules.cpp src/token.cpp src/position.cpp $(HDR)
	$(CXX) $(CXXFLAGS) tests/test_rules.cpp src/rules.cpp src/token.cpp src/position.cpp -o test_rules

test_board: tests/test_board.cpp src/board.cpp src/player.cpp src/token.cpp src/position.cpp src/rules.cpp $(HDR)
	$(CXX) $(CXXFLAGS) tests/test_board.cpp src/board.cpp src/player.cpp src/token.cpp src/position.cpp src/rules.cpp -o test_board

test: test_rules test_board
	./test_rules
	./test_board

clean:
	rm -f ludo ludo.exe test_rules test_rules.exe test_board test_board.exe out.txt out4.txt

.PHONY: test clean