/* COMP11 Fall 2017
 * Homework 6
 * Ryan Sheehan
 * Prof. Strange
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Score.h"
#include "Board.h"

using namespace std;
	
/* Constructor for a board object
*
* @param: the board's desired dimensions
* return: a board
*/
Board::Board(int board_size)
{

	set_board_size(board_size);

	board = new int *[board_size];
	for (int i = 0; i < board_size; i++)
	    board[i] = new int[board_size];
}

/* Destuctor for the board seeing as it is dynamically allocated
*
* @param: void
* return: void
*/
Board::~Board()
{
	for (int i = 0; i < board_size; i++) 
	    delete [] board[i];
	delete []board;
}

/* Populates an empty board object with "empty" tiles and two tiles
* with values of either 2 or 4 to begin the game
*
* @param: void
* return: void
*/
void Board::populate_board()
{
	srand(time(NULL));

	int num_tiles = pow(board_size,2);

	int beginner_tile1_pos = rand() % num_tiles;

	int beginner_tile2_pos = rand() % num_tiles;

	while (beginner_tile2_pos == beginner_tile1_pos)
		beginner_tile2_pos = rand() % num_tiles;


	int current_tile_pos = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
	 		int current_tile_val;
	 		
	 		if(current_tile_pos == beginner_tile1_pos
	 			|| current_tile_pos == beginner_tile2_pos)
	 		{
	 			// in the initial population of the board, there
	 			// is roughly a 90% chance of spawning a 2 and
	 			// a 10% chance of spawning a 4
	 			current_tile_val = rand() < 0.9*RAND_MAX ? 2 : 4;

	 			board[i][j] = current_tile_val;
	 		}
	 		else
	 		{
	 			current_tile_val = -1;
	 			board[i][j] = current_tile_val;


	 		}
	 		current_tile_pos += 1;
 		}
 	}
}

/* Prints the board to the console and prints 'X's if a tile has value -1
*
* @param: void
* return: void
*/
void Board::display_board()
{
	int current_tile;
	cout << "Score: " << game_score.get_user_score() << endl;
	for (int i = 0; i < board_size; i++)
	{
		for ( int j = 0; j < board_size; j++)
		{
			current_tile = board[i][j];
			if (current_tile == -1)
				cout << 'X' << " ";
			else
				cout << current_tile << " ";
		}
		cout << endl;
	}
}

/* Updates the board according to user input and then spawns a new tile
* if necessary. If the user inputs an h rather than a direction the leaderboards
* will instead be displayed
* @param: user input in the form of a char
* return: void
*/
void Board::update_board(char move)
{
	valid_move = false;
	switch (move)
	{
		case 'w':
			shift_up();
			break;
		case 'a':
			shift_left();
			break;
		case 's':
			shift_down();
			break;
		case 'd':
			shift_right();
			break;
		case 'h':
			game_score.show_highscores();
			break;
	}
	if (valid_move)
		spawn_tile();
}

/* Shifts tiles in the upwards direction, combining as necessary
* @param: void
* return: void
*/
void Board::shift_up()
{
	int current_tile, next_tile;
	for (int col = 0; col < board_size; col++)
	{
		for (int row = 1; row < board_size; row++)
		{
			current_tile = board[row][col];
			next_tile = board[row-1][col];

			if (current_tile > 0 && next_tile == -1)
			{
				valid_move = true;
				board[row-1][col] = current_tile;
				board[row][col] = -1;
				if (row > 1)
					row-=2;
			}
			else if (current_tile != -1 && next_tile != -1 && current_tile == next_tile)
			{
				valid_move = true;
				game_score.set_user_score(game_score.get_user_score() + current_tile + next_tile);
				board[row-1][col] = 2*next_tile;
				board[row][col] = -1;
				if (col > 1)
					col-=2;
			}
		}
	}
}

/* Shifts tiles to the left, combining as necessary
* @param: void
* return: void
*/
void Board::shift_left()
{
	int current_tile, next_tile;
	for (int row = 0; row < board_size; row++)
	{
		for (int col = 1; col < board_size; col++)
		{
			current_tile = board[row][col];
			next_tile = board[row][col-1];

			if (current_tile > 0 && next_tile == -1)
			{
				valid_move = true;
				board[row][col-1] = current_tile;
				board[row][col] = -1;
				if (col > 1)
					col-=2;
			}
			else if (current_tile != -1 && next_tile != -1 && current_tile == next_tile)
			{
				valid_move = true;
				game_score.set_user_score(game_score.get_user_score() + current_tile + next_tile);
				board[row][col-1] = 2*next_tile;
				board[row][col] = -1;
				if (col > 1)
					col-=2;
			}
		}
	}
}

/* Shifts tiles in the downwards direction, combining as necessary
* @param: void
* return: void
*/
void Board::shift_down()
{
	int current_tile, next_tile;
	for (int col = 0; col < board_size; col++)
	{
		for (int row = board_size-2; row >= 0; row--)
		{
			current_tile = board[row][col];
			next_tile = board[row+1][col];

			if (current_tile > 0 && next_tile == -1)
			{
				valid_move = true;
				board[row+1][col] = current_tile;
				board[row][col] = -1;
				if (row < board_size-2)
					row+=2;
			}
			else if (current_tile != -1 && next_tile != -1 && current_tile == next_tile)
			{
				valid_move = true;
				game_score.set_user_score(game_score.get_user_score() + current_tile + next_tile);
				board[row+1][col] = 2*next_tile;
				board[row][col] = -1;
				if (col > 1)
					col-=2;
			}
		}
	}
}

/* Shifts tiles to the right, combining as necessary
* @param: void
* return: void
*/
void Board::shift_right()
{
	int current_tile, next_tile;
	for (int row = 0; row < board_size; row++)
	{
		for (int col = board_size-2; col >= 0; col--)
		{
			current_tile = board[row][col];
			next_tile = board[row][col+1];

			if (current_tile > 0 && next_tile == -1)
			{
				valid_move = true;
				board[row][col+1] = current_tile;
				board[row][col] = -1;
				if (col < board_size-2)
					col+=2;
			}
			else if (current_tile != -1 && next_tile != -1 && current_tile == next_tile)
			{
				valid_move = true;
				game_score.set_user_score(game_score.get_user_score() + current_tile + next_tile);
				board[row][col+1] = 2*next_tile;
				board[row][col] = -1;
				if (col > 1)
					col-=2;
			}
		}
	}
}

void Board::spawn_tile()
{
	int new_tile_pos = rand() % (int)pow(board_size,2);
	while (board[new_tile_pos/board_size][new_tile_pos%board_size] > 0)
		new_tile_pos = rand() % (int)pow(board_size,2);

	int new_tile_val = rand() < 0.9*RAND_MAX ? 2 : 4;
	board[new_tile_pos/board_size][new_tile_pos%board_size] = new_tile_val;
}

bool Board::game_over()
{
	int current_tile, next_tile;

	// Checks if the board is full
	for (int row = 0; row < board_size; row++)
	{
		for (int col = 0; col < board_size; col++)
		{
			current_tile = board[row][col];
			if (current_tile == -1)
				return false;
		}
	}

	// Checks for possible moves in vertical direction
	for (int row = 1; row < board_size; row++)
	{
		for (int col = 0; col < board_size; col++)
		{
			current_tile = board[row][col];
			next_tile = board[row-1][col];
			if (current_tile == next_tile)
				return false;
		}
	}

	// Checks for possible moves in horizontal direction
	for (int col = 1; col < board_size; col++)
	{
		for (int row = 0; row < board_size; row++)
		{	
			current_tile = board[row][col];
			next_tile = board[row][col-1];
			if (current_tile == next_tile)
				return false;
		}
	}

	return true;
}

/* Helper function for finishing up the game, thanks the user for playing
* and puts their name on the leader board
*
* @param: void
* return: void
*/
void Board::wrap_up()
{
	string name;
	cout << "You lost, but thanks for playin " << endl;

	cout << "Please input your name for the leaderboards: " << endl;
	cin >> name;
	game_score.update_highscores(name);
}

/* Setter for board size
*
* @param: desired board dimensions in the form of an int
* return: void
*/
void Board::set_board_size(int current_board_size)
{
	board_size = current_board_size;
}

/* Getter for board size
*
* @param: void
* return: board size
*/
int Board::get_board_size()
{
	return board_size;
}



