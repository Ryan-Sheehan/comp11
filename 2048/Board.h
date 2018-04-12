/* COMP11 Fall 2017
 * Homework 6
 * Ryan Sheehan
 * Signoff by [Leah Stern] [11/16/2017]*/


#ifndef BOARD_H
#define BOARD_H

class Board {

	private:
		
		// if a move can be made
		bool valid_move;		

		// the score object for this game
		Score game_score;

		// Size of the board input
		int board_size;

		// 2D array of tiles
		int **board;

	public:

		// constructor 
		Board(int board_size);

		// destructor 
		~Board();

		// fill thr board with 2's, 4's, and X's
		void populate_board();

		// takes an integer and returns it as a char
		// char convert_int(int num);
		// int convert_char(char val);

		// display the board
		void display_board();

		// updates the board status after a move
		void update_board(char move);

		// movement helper functions
		void shift_up();
		void shift_down();
		void shift_right();
		void shift_left();

		// spawn a new tile randomly
		void spawn_tile();

		// checks to see if the game is over
		bool game_over();

		// helper function for the end of the game
		void wrap_up();

		//getters and setters

    	// set function for returning board dimensions
    	void set_board_size(int current_board_size);
    	// get function for board size
		int get_board_size();


};

#endif
