/*
Description: <This program is a simple game of checkers, it can be played between two users with this program.
It will be decided by a randomizer who will start the game between the two players.  A player must jump over
an opponent's piece if he or she is able to do so. The game ends when a player cannot move any further.>
Programmed by: <Atasha Dominique C. Pidlaoan>  <S20B>
Last modified: <December 4, 2022>
Version: <1>
[Acknowledgements: <https://codereview.stackexchange.com/questions/234619/chess-game-in-c>]
*/

/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned.
I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of
other students and/or persons.

<Atasha Dominique C. Pidlaoan>, DLSU ID# <12208507>
******************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define MAX 8

#define INVALID -1
#define VALID 1
#define JUMP 2
#define MOVE 3

#define DARK_PIECE 'D'
#define LIGHT_PIECE 'L'
#define FREE ' '

#define RED "\033[1;31m"
#define PURPLE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

#define WHITE_TILE printf("%c%c%c",219, 219, 219);
// structure that holds the coordinates input by user
typedef struct Coordinate{
        int x;
        int y;
} Coordinate;

// set max coordinates
typedef struct Set {
        int count;
        Coordinate coordinate[MAX * MAX];
} Set;

/** This function prints a loading phrase.
 @param int seconds - 3 seconds prints 3 periods when loading.
 */
void LoadingPhrase (int seconds) {
    for (int i = 0; i < seconds; i++) {
            printf (".");
            Sleep (200*seconds);
    }
	printf("\n");
}

/** This function displays the boardbyt using for loops.
 @param char cBoard[][] - 2d array that represents the board.
 @param char playerPiece - piece of the player playing.
 */
void displayBoard (char cBoard[8][8], char playerPiece) {
	int row, col, i;
	for ( i = 0; i < 31; i++) //prints the boarder for the prompt "Select Piece L or D to move"
			{
		if (i == 0) printf("%c", 201);
		if (i == 30) printf("%c", 187);
		else printf("%c", 205);
	}
	printf("\n%c Select a piece (%c) to move.. %c\n", 186, playerPiece, 186);

	for (i = 0; i < 31; i++)
	{
		if (i == 0) printf("%c", 200);
		if (i == 30) printf("%c\n", 188);
		else printf("%c", 205);
	}

	printf("     ");
	for (i = 1; i <= 8; i++) printf(" %d ", i);
	printf("\n");
	for (row = 1; row <= 8; row++) {
		printf("  %d ", row);
		for (col = 1; col <= 8; col++) {
		if (col % 2 == 1) {
			if (row % 2 == 0) printf(" %c ", cBoard[col-1][row-1]);
			else WHITE_TILE;
		} else {
			if (row % 2 == 1) printf(" %c ", cBoard[col-1][row-1]);
			else WHITE_TILE;
		}
		}
		printf("\n");

	}
}

/** This function displays the boardbyt using for loops.
 @param char cBoard[][] - 2d array that represents the board.
 @param char playerOnePiece - piece of player 1.
 @param char playerTwoPiece - piece of player 2.
 */
void initializeBoard(char cBoard[8][8], char playerOnePiece, char playerTwoPiece) {
	int col, row;
    for (row = 1; row <= 8; row++) {
	for (col = 1; col <= 8; col++) {
	cBoard[col-1][row-1] = FREE;
		if (((row == 1||row == 3) && col % 2 == 0) || (row == 2 && col % 2 == 1)) cBoard[col-1][row-1] = playerOnePiece;
		if ((row == 7 && col % 2 == 0) || ((row == 8||row == 6) && col % 2 == 1)) cBoard[col-1][row-1] = playerTwoPiece;
	}
    }
}

/** Counts the number of pieces in the board
 @param cBoard[8][8] - 2d array that represents the 8x8 board.
 */
void pieceCount(char cBoard[8][8]){
    int A_piecesL = 0, B_piecesD = 0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(cBoard[i][j] == 'L'){
                A_piecesL++;
            }
            else if(cBoard[i][j] == 'D'){
                B_piecesD++;
            }
        }
    }
    //prints the number of pieces left for each player
    printf("Player A now has %d pieces left\n", A_piecesL);
    printf("Player B now has %d pieces left\n", B_piecesD);
}

// Displays the main menu of the game
void displayMainMenu () {
	int i;
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 201);
		if (i == 47) printf("%c", 187);
		else printf("%c", 205);
	}
	printf("\n%c\t\tWELCOME TO CHECKERS!! \t\t%c\n", 186, 186); //welcoming prompt
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 204);
		if (i == 47) printf("%c", 185);
		else printf("%c", 205);
	}
	printf("\n%c\t[1]\tStart Game \t\t\t%c", 186, 186); //press 1 to start the game
	printf("\n%c\t[2]\tView Scores \t\t\t%c", 186, 186); //press 2 to view the scores
	printf("\n%c\t[3]\tExit \t\t\t\t%c\n", 186, 186); //press 3 to exit the game/program
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 200);
		if (i == 47) printf("%c\n", 188);
		else printf("%c", 205);
	}
}

/** This function checks if the scanned entry of the user is within the range that is accepted
 @param min - minimum accepted value
 @param max - maximum accepted value
 */
int promptChoice (int min, int max) {
        int choice;

        do {
                scanf ("%d", &choice);
                if (choice >= min && choice <= max) {
                        return choice;
                }
                else if(choice == 100) return 100;
                else {
                        printf ("%sInvalid input!%s\n", RED, RESET); //prompt to inform the user that his/her input is invalid, the text will also change its color to red
                        choice = INVALID;
                        printf ("Enter valid choice [%d - %d]: ", min, max); 

                }
        } while (choice == INVALID);
        return 0;
}

/** This Function is a random number generator that generates 1 and 2 to decide which player will start the game.
 @return returns 1 or 2 which is the player which will have the first turn.
 */
int rollDice(){
    srand (time(NULL));
    return (rand() % 2) + 1;
}

/** This function accepts the board as input and decides whether the game is over or still ongoing based on the entries on the board.
 @param cBoard[][8] - 2d array that represents the 8x8  board.
 @return TRUE if game is over, FALSE otherwise.
 */
int isGameOver (char cBoard[8][8]) {
	int row, col;
	int nLight = 0, nDark = 0;
	for (row = 1; row <= 8; row++) {
		for (col = 1; col <= 8; col++) {
			if (cBoard[col-1][row-1] == LIGHT_PIECE) nLight++;
			if (cBoard[col-1][row-1] == DARK_PIECE) nDark++;
		}
	}
	if (nLight == 0 || nDark == 0) return TRUE;
	else return FALSE;
}

/** This function checks if the piece chosen by the user is a valid piece
 @param cBoard[][8] - 2d array that represents the 8x8  board.
 @param x - value that represents the coordinate input of the user.
 @param y - another value that represents the coordinate input of the user.
 @param cPiece - represents the piece assigned to the current user.
 @return True if valid, false if invalid.
 */
int isCurrentValid (char cBoard[8][8], int x, int y, char playerPiece) {
	if (x < 1 || x > 8 || y < 1 || y > 8) return FALSE;
	if (cBoard[x-1][y-1] == playerPiece) return TRUE;
	else return FALSE;
}

/** This function checks if the piece chosen by the user is a valid piece and if the next set of pieces is a valid destination or the piece can be eaten by the player.
 @param cBoard[][8] - 2d array that represents the 8x8  board.
 @param x - value that represents the coordinate input of the user.
 @param y - another value that represents the coordinate input of the user.
 @param from_x - value that represents the coordinate input of the user.
 @param from_y - another value that represents the coordinate input of the user.
 @param playerPiece - represents the piece assigned to the current user.
 @param opponentPiece - represents the piece assigned to the other user.
 @return True if valid, false if invalid.
 */
int isNextValid (char cBoard[8][8], int x, int y, int from_x, int from_y, char playerPiece, char opponentPiece) {
	if (x < 1 || x > 8 || y < 1 || y > 8) return FALSE;
	//possible move if it is in black square and 1 up
	if (cBoard[x-1][y-1] == FREE && (x+y)%2 == 1){
        if(playerPiece == DARK_PIECE && from_y == y+1 && (from_x == x+1 || from_x == x-1)) return MOVE;
        else if(playerPiece == LIGHT_PIECE && from_y == y-1 && (from_x == x+1 || from_x == x-1)) return MOVE;
	}
	if (cBoard[x-1][y-1] == opponentPiece){
        if(opponentPiece == DARK_PIECE){
            if(from_x == x-1 && from_y == y-1){
                if(x<8 && y != 8 && cBoard[x][y] == FREE){
                    cBoard[x][y] = playerPiece;
                    return JUMP;
                }
            }
            else if(from_x == x+1 && from_y == y-1){
                if(x-2>=0 && y!=8 && cBoard[x-2][y] == FREE){
                    cBoard[x-2][y] = playerPiece;
                    return JUMP;
                }
            }
        }
        else if(opponentPiece == LIGHT_PIECE){
            if(from_x == x-1 && from_y == y+1){
                if(x<8 && y-2 >= 0 && cBoard[x][y-2] == FREE){
                    cBoard[x][y-2] = playerPiece;
                    return JUMP;
                }
            }
            else if(from_x == x+1 && from_y == y+1){
                if(x-2>=0 && y-2 >= 0 && cBoard[x-2][y-2] == FREE){
                    cBoard[x-2][y-2] = playerPiece;
                    return JUMP;
                }
            }
        }
	}
	else return FALSE;
}

/** This function is where the movement of pieces occur.
 @param cBoard[][8] - 2d array that represents the 8x8  board.
 @param nTurn - integer that represents the turn of players.
 @param currentPiece - the piece of the current player.
 @param selectRow - selected row.
 @param selectColumn - selected column.
 @param moveRow - row to move towards to.
 @param moveColumn - column to move towards to.

 */
int nextPlayerMove (char cBoard[8][8], int nTurn, char currentPiece) {
	int selectRow, selectColumn, moveRow, moveColumn;
	int nValid = FALSE;
	char cPiece;

	do {
        printf("TO SURRENDER, TYPE 100 AT ANY TIME WHEN ASKED A PROMPT!\n"); //will print each turn if player L or D would want to surrender
		printf ("Enter row of piece to move: ");
		selectColumn = promptChoice (1, 8);

        if(selectColumn != 100){

		printf ("Enter column of piece to move: ");
		selectRow = promptChoice (1, 8);

        if(selectRow != 100){
		nValid = isCurrentValid (cBoard, selectRow, selectColumn, currentPiece);

		if (nValid == TRUE) { ///switched moveColumn and moveRow in this ...Column represents row and ...Row represents column
                ///apologies for the confusion!
			printf ("Enter row of destination: ");
			moveColumn = promptChoice (1, 8);

			if(moveColumn != 100){
			printf ("Enter column of destination: ");
			moveRow = promptChoice (1, 8);

            if(moveRow != 100){
			nValid = isNextValid (cBoard, moveRow, moveColumn, selectRow, selectColumn, currentPiece, (currentPiece == LIGHT_PIECE) ? DARK_PIECE : LIGHT_PIECE);

			if (nValid == MOVE) {
				cBoard[moveRow-1][moveColumn-1] = cBoard[selectRow-1][selectColumn-1];
				cBoard[selectRow-1][selectColumn-1] = ' ';
				nValid = TRUE;
			}
			else if (nValid == JUMP) { ///to fix
				cBoard[selectRow-1][selectColumn-1] = ' ';
				cBoard[moveRow-1][moveColumn-1] = ' ';
				nValid = TRUE;
			} else { ///PROBLEM GOES TO THIS
				printf ("%sInvalid move!%s\n", RED, RESET);
				nValid = FALSE;
			}
            }}
		}
		else {
			printf ("%sInvalid move!%s\n", RED, RESET);
			nValid = FALSE;
		}
        }}
	} while (nValid == FALSE &&( selectColumn != 100 && selectRow != 100 && moveRow != 100 && moveColumn != 100));

	if(selectColumn == 100 || selectRow == 100 || moveRow == 100 || moveColumn == 100) return 1;

	return 0;
}

/** This function is where the game occurs
 @param cBoard[][8] - 2d array that represents the 8x8  board.
 @return - the number of the winnning player.
 */
int startGame (char cBoard[8][8]) { ///Player 1 is L, Player 2 is D

	int i, nTurn, force_stop = 0;
	char playerOnePiece, playerTwoPiece, currentPiece;
	nTurn = rollDice();
	
	//will print one of the following after the randomizer/rollDice function
	if (nTurn == PLAYER_TWO) {
		printf ("Player B will go first!\n"); 
		playerOnePiece = LIGHT_PIECE;
		playerTwoPiece = DARK_PIECE;
		currentPiece = DARK_PIECE;
	} else {
		printf ("Player A will go first!\n");
		playerOnePiece = LIGHT_PIECE;
		playerTwoPiece = DARK_PIECE;
		currentPiece = LIGHT_PIECE;
	}

	initializeBoard(cBoard, playerOnePiece, playerTwoPiece);
	displayBoard(cBoard, currentPiece);

	while (isGameOver(cBoard) == FALSE && force_stop == 0) {
        pieceCount(cBoard);
		force_stop = nextPlayerMove(cBoard, nTurn, currentPiece);

        if(force_stop == 1){
            if(nTurn == 2) nTurn = 1;
            else nTurn = 2;
        }
        else{
            if (currentPiece == LIGHT_PIECE) currentPiece = DARK_PIECE;
            else currentPiece = LIGHT_PIECE;

            displayBoard(cBoard, currentPiece);
            if (nTurn == 1) nTurn = 2;
            else nTurn = 1;
        }

	}
	if (isGameOver(cBoard) == TRUE || force_stop == 1) return nTurn;
}

/** Displays the score of both players.
 */
void displayScore (int playerOneScore, int playerTwoScore) {
	int i;
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 201);
		if (i == 47) printf("%c", 187);
		else printf("%c", 205);
	}
	printf("\n%c\t\t\tSCORES \t\t\t%c\n", 186, 186);
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 204);
		if (i == 47) printf("%c", 185);
		else printf("%c", 205);
	}
	printf("\n%c\tPlayer A:\t%d \t\t\t%c", 186, playerOneScore, 186);
	printf("\n%c\tPlayer B:\t%d \t\t\t%c\n", 186, playerTwoScore, 186);
	for (i = 0; i < 48; i++)
	{
		if (i == 0) printf("%c", 200);
		if (i == 47) printf("%c\n", 188);
		else printf("%c", 205);
	}

}

int main ()
{
	int playerOneScore = 0, playerTwoScore = 0, isOver = FALSE;
	int nChoice, nWinner;
	char cBoard[8][8];

	do {
		system("cls");
		displayMainMenu();
		nChoice = promptChoice (1, 3);
		switch (nChoice) {
		case 1:
			printf("Rolling dice");
			LoadingPhrase(3);
			printf("REMEMBER: IN ORDER TO CAPTURE A PIECE, MOVE TO THE SQUARE WITH THE OPPONENT ON IT!\n"); //guide prompt for the user
			nWinner = startGame(cBoard);

            system("cls");
			//condition to print of whoever wins the game, a point will be added to the score board of either player A or B
            if (nWinner == PLAYER_ONE){
                printf("Congratulationssss!!! Player A, you are the winner of this round\n"); 
                playerOneScore++;
			}
			else{
                printf("Congratulationssss!!! Player B, you are the winner of this round\n");
                playerTwoScore++;
			}
			getch();

			break;
		case 2:
			system("cls");
			displayScore(playerOneScore, playerTwoScore);
			printf("Press any key to continue...\n"); //when the user is viewing the scores this prompt will print below to inform how to return to the main menu
			getch();
			break;
		case 3:
			printf ("See you next time!"); //this will print if the user chose 3 on the main menu 
			break;
		default:
                break;
		}
	} while (!(nChoice == 3)); //condition of the quit option, to terminate the program

        return 0;
}

