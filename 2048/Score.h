/* COMP11 Fall 2017 
 * Homework 6
 * Ryan Sheehan
 * Signoff by [Leah Stern] [11/16/2017]*/

#ifndef Score_H
#define Score_H

using namespace std;

class Score {

	private:

		// current score
		int total_score;

	public:

		// constructor
		Score();

		// show top 5 highscores 
		void show_highscores();

		// sort highscore file
		void update_highscores(string name_to_update);

		// getters and setters

		// get function for returning user score
		int get_user_score();

		// set function for changing current user score
		void set_user_score(int score);

};

#endif
