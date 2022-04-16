/**************************************************************************************
 * Names: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
 * Emails: jliebov@nd.edu, nachkar@nd.edu, mjzydlow@nd.edu, mcichon@nd.edu
 * File Name: clue_sheet.cpp
 * Date Created: 4/12/2022
 * File Contents: This file contains the main function for the Cheers! Final Project
 ***************************************************************************************/

#include "../include/clue_headers.h"

int main( ){

	int player_count = introduction();
	
	VECTOR<Player> players(player_count);
	MAP<STRING, int> master = {		{"Miss Scarlet", 0},
									{"Colonel Mustard", 0},
									{"Mrs. White", 0},
									{"Mr. Green", 0},
									{"Mrs. Peacock", 0},
									{"Professor Plum", 0},
	
								 	{"Revolver", 0},
									{"Knife", 0},
									{"Lead Pipe", 0},
									{"Rope", 0},
									{"Candlestick", 0},
									{"Wrench", 0},

									{"Kitchen", 0},
									{"Hall", 0},
									{"Ballroom", 0},
									{"Conservatory", 0},
									{"Dining Room", 0},
									{"Cellar", 0},
									{"Billiard Room", 0},
									{"Library", 0},
									{"Lounge", 0},
									{"Study", 0}};


	build_players_array(players, player_count);

	int cards_per_player = update_initial_knowns(players, player_count, master);

	COUT << cards_per_player << ENDL; //this is just here to run without the unused parameter warning lol

	while (1) { //i know this scares Bui but it's the best thing for this case haha
		COUT << ENDL;
		int choice = print_menu();

		switch (choice) {
			case 1: //print full clue sheet
				break;
			case 2: //print a player
				int personInt;
				COUT << ENDL << "Which player information would you like to print? (1 - " << player_count << ") : " << ENDL;
					for (int iter = 0; iter < player_count; iter++) {
						COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
					}
				CIN >> personInt;
				print_player(players, personInt);
				break;
			case 3: //print items in a category
				break;
			case 4: //update info
				update_info(players, player_count, master);
				break;
			case 5: //check for solution
				break;
			case 6: //quit
				return 0;
		}
	}

	return 0;
}
