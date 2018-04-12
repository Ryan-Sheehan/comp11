/* COMP11 Fall 2017
 * Homework 6
 * Ryan Sheehan
 * Prof. Strange
 */

#include <iostream>
#include "Score.h"
#include "Board.h"

using namespace std;

int main()
{
	// Variable declarations
	char input;

	// Score constructor
	Score game_score;

	// Read prexisting high scores
	cout << "Current leaderboards:" << endl;
	game_score.show_highscores();

	// Constructs a board, populates it
	// and displays its initial state
	Board* my_board = new Board(4);
	my_board->populate_board();
	my_board->display_board();



	// Plays the game until the user quits voluntarily
	// or there are no more moves possible
	do 
	{
		cin >> input;
		cout << endl;

		// If the user quit, do nothing
		if (input != 'q')
		{
			my_board->update_board(input);
			my_board->display_board();
		}

	} while (!my_board->game_over() && input != 'q');

	// Finishing up
	my_board->wrap_up();
	delete my_board;
	
	return 0;
}
