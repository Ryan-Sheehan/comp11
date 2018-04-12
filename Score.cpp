/* COMP11 Fall 2017
 * Homework 6
 * Ryan Sheehan
 * Prof. Strange
 */

#include <iostream>
#include <fstream>
#include "Score.h"
#include "Board.h"

using namespace std;

/* Constructor for a score object
*
* @params: void
* return: void
*/
Score::Score()
{
	total_score = 0;
}

/* Getter for user score
*
* @param: void
* return: users current score
*/
int Score::get_user_score()
{
	return total_score;
}

/* Setter for user score
*
* @param: user score in the form of an int
* return: void
*/
void Score::set_user_score(int current_score)
{
	total_score = current_score;
}

/* Adds a new highscore to the leaderboards
*
* @param: the new name to put on the leaderboards
* return: void
*/
void Score::update_highscores(string name_to_update)
{
	ifstream highscores;
	highscores.open("highscores.txt");

	string line, name;
	int num_lines, score, stop;
	int score_to_update = total_score;

	if (highscores.is_open() && highscores != NULL)
	{
			num_lines = 0;
			stop = 0;
			while (getline(highscores, line))
        		num_lines++;

        	cout << num_lines << endl;

        	highscores.clear();
			highscores.seekg (0, ios::beg);

			string* names = new string[num_lines + 1];
			int* scores = new int[num_lines + 1];	

			for (int i = 0; i < (num_lines + 1); i++)
			{
				highscores >> name;
				highscores >> score;

				if (score < score_to_update)
				{
					names[i] = name_to_update;
					scores[i] = score_to_update;
					names[i + 1] = name;
					scores[i + 1] = score;
					stop = i + 2;
					break;

				}
				else
				{
					names[i] = name;
					scores[i] = score;
				}
			}

			if (stop != 0)
			{
				for (int i = stop; i < (num_lines + 1); i++)
				{
					highscores >> name;
					highscores >> score;

					scores[i] = score;
					names[i] = name;
				}
			}

			highscores.close();

			ofstream highscores;
			highscores.open("highscores.txt");

			for (int i = 0; i < num_lines + 1; i++)
			{
				highscores << names[i] << " " << scores[i] << endl;
			}

			highscores.close();

			delete [] names;
			delete [] scores;
	}
	else 
	{
		cout << "Error with file\n" << endl;
	}
	highscores.close();
}

/* Displays the leaderboards
*
* @params: void
* return: void
*/
void Score::show_highscores()
{
	ifstream highscores;
	highscores.open("highscores.txt");
	string line;
	int current_line;

	if (highscores.is_open() && highscores != NULL)
	{
			current_line = 0;
			while (!highscores.eof() && current_line < 5)
			{
				getline(highscores, line);
				cout << line << endl;
				current_line++;
			}
	}
	else 
	{
		cout << "Error with file\n" << endl;
	}
	highscores.close();
}




