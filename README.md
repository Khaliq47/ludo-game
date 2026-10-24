# Ludo Arena

A console-based Ludo game for 2 or 4 players, written in C++17 using Object-Oriented Programming. Players can be human or bot.

**Team:** [Team number]
| Member   | Files                |
|----------|----------------------|
| Abhay    | position, token      |
| Dakshin  | player, dice, utils  |
| Khaliq   | board, rules         |
| Sriesh   | game, main           |

## Features
- 2-player (Red vs Yellow) and 4-player modes
- Human or bot for each player
- Capture, safe cells, home column and exact finish
- A 6 brings a token out and gives an extra turn
- Menu, rules screen and input validation

## Game Rules
1. Each player has 4 tokens, all starting in the yard.
2. A roll of 6 brings a token onto the board, and gives another roll.
3. Tokens move clockwise around a 52-cell track (start cells: Red 0, Green 13, Yellow 26, Blue 39).
4. After a full lap, a token enters its own 6-square home column.
5. Landing on an opponent sends it back to the yard, unless the cell is safe (`*`).
6. An exact roll is needed to finish.
7. The first player with all 4 tokens home wins.

## Project Structure
```
include/   headers (.hpp)
src/       source files (.cpp)
tests/     test programs
Makefile
```

## Build and Run
Requires a C++17 compiler (g++).

```
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o ludo
./ludo          # Windows PowerShell: .\ludo
```
Or use the Makefile: `make`, then run the program.

## Run the Tests
```
g++ -std=c++17 -Wall -Wextra -Iinclude tests/test_rules.cpp src/rules.cpp src/token.cpp src/position.cpp -o test_rules
g++ -std=c++17 -Wall -Wextra -Iinclude tests/test_board.cpp src/board.cpp src/player.cpp src/token.cpp src/position.cpp src/rules.cpp -o test_board
```

## How to Play
- Choose a menu option, then enter a name and `1` (human) or `2` (bot) for each player.
- The dice roll automatically. On your turn, type the token number (1-4) to move.
- Board key: `R4` = Red token 4 on that cell, `*` = safe cell, `[HOME]` = in yard, `[30]` = on cell 30, `[col 3]` = home column, `[DONE]` = finished.

## OOP Concepts Used
| Concept                                           | Where                                                                        |
|---------------------------------------------------|------------------------------------------------------------------------------|
| Encapsulation                                     | private data in Board, Token, Player                                         |
| Interface/implementation separation               | every class has `.hpp` and `.cpp`                                            |
| Constructors (default, parameterised, overloaded) | Token, Player, Dice, Game() / Game(int)                                      |
| Destructors                                       | `~Game()` (`delete[]`), trace messages in Board and Player                   |
| Composition                                       | Game has Board, Dice, Player[]; Player has Token[4]; Token has Position      |
| `this` pointer                                    | `Board::markSafe`, Dice and Player constructors                              |
| Cascading                                         | `markSafe(0).markSafe(13)...`, `Token::move`                                 |
| Function overloading                              | `Board::display()` (3 versions), `Token::move`, `Dice::roll`                 |
| Operator overloading                              | `+`, `==`, `++`, `[]`, `<<`                                                  |
| Function templates                                | `maxOf`, `printArray`, `findIndex` in utils                                  |
| Function pointers                                 | token chooser in Player, `DiceRule`/`TokenRule` in rules, menu array in main |

## Future Work
Inheritance and polymorphism (HumanPlayer / BotPlayer), exception handling, file handling (save/load, high scores).

## Notes
- `[Player X destroyed]` messages are destructor traces (a temporary Player is created during setup).
- Executables are not committed (see `.gitignore`).