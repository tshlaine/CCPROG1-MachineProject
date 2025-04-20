# CCPROG1-Machine Project

## Checkers Game Implementation

### Overview
This program implements a simple game of checkers designed to be played between two users. The game follows standard checkers rules with a randomized starting player. A player must jump over and capture an opponent's piece when possible, and the game concludes when a player cannot make any more moves.

### Features
- Two-player gameplay with pieces represented as 'L' (Light) and 'D' (Dark)
- Randomized player selection for first turn
- Mandatory piece capture when available
- Running score tracking between matches
- Surrender option during gameplay
- Visual board display with piece counts

### How to Play
1. Run the program and select "Start Game" from the main menu
2. The starting player will be randomly determined
3. On your turn:
   - Enter the row and column of the piece you wish to move
   - Enter the row and column of your intended destination
   - To capture an opponent's piece, move to the square with the opponent on it
4. To surrender at any point, type "100" when prompted for a coordinate

### Game Rules
- Players take turns moving their pieces
- Light pieces ('L') move upward, dark pieces ('D') move downward
- Players must capture opponent pieces when possible by jumping over them
- The game ends when a player has no valid moves or no pieces remaining
- The winner earns a point on the scoreboard

### Menu Options
1. **Start Game** - Begin a new match of checkers
2. **View Scores** - Display the current score tally for Players A and B
3. **Exit** - Quit the program

### Technical Information
- **Programmer:** Atasha Dominique C. Pidlaoan
- **Last Modified:** December 4, 2022
- **Version:** 1.0
- **Language:** C
- **Required Libraries:** stdio.h, string.h, stdlib.h, conio.h, time.h, windows.h

### Compilation & Execution
This program uses Windows-specific functions like `getch()` and `Sleep()`, so it's designed to run on Windows systems. Compile using a C compiler like GCC:

```
gcc PidlaoanCheckers.c -o Checkers
```

Then run the executable:
```
Checkers.exe
```

### Notes
- The board is displayed with white tiles represented as filled blocks
- The game uses colored text for warnings and error messages
- Remember that when capturing a piece, you must move directly to the square with the opponent's piece on it
