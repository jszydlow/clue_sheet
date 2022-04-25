/**************************************************************************************
 * Names: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
 * Emails: jliebov@nd.edu, nachkar@nd.edu, mjzydlow@nd.edu, mcichon@nd.edu
 * File Name: clue_sheet.cpp
 * Date Created: 4/12/2022
 * File Contents: This file contains the main function for the Cheers! Final Project
 ***************************************************************************************/

#include "../include/clue_headers.h"

int main( ){

	int player_count = introduction();	//calls introduction function and obtains the number of players
	
	//intializes the players vector of Player structs (to the player_count)
	VECTOR<Player> players(player_count);

	//initializes the master map to store overarching information
	MAP<STRING, int> master = {		{"MISS SCARLET", 0},
									{"COLONEL MUSTARD", 0},
									{"MRS. WHITE", 0},
									{"MR. GREEN", 0},
									{"MRS. PEACOCK", 0},
									{"PROFESSOR PLUM", 0},
	
								 	{"REVOLVER", 0},
									{"KNIFE", 0},
									{"LEAD PIPE", 0},
									{"ROPE", 0},
									{"CANDLESTICK", 0},
									{"WRENCH", 0},

									{"KITCHEN", 0},
									{"HALL", 0},
									{"BALLROOM", 0},
									{"CONSERVATORY", 0},
									{"DINING ROOM", 0},
									{"CELLAR", 0},
									{"BILLIARD ROOM", 0},
									{"LIBRARY", 0},
									{"LOUNGE", 0},
									{"STUDY", 0}};

	//create vectors for each category - makes it easier to access for printing purposes
	VECTOR<STRING> thecharacters{"MISS SCARLET", "COLONEL MUSTARD", "MRS. WHITE", "MR. GREEN", "MRS. PEACOCK", "PROFESSOR PLUM"};
	VECTOR<STRING> theweapons{"REVOLVER", "KNIFE", "LEAD PIPE", "ROPE", "CANDLESTICK", "WRENCH"};
	VECTOR<STRING> therooms{"KITCHEN", "HALL", "BALLROOM", "CONSERVATORY", "DINING ROOM", "CELLAR", "BILLIARD ROOM", "LIBRARY", "LOUNGE", "STUDY"};


	//calls build_players_array function to set up the vector of players
	build_players_array(players, player_count);

	//calls update_inital_knowns function and returns the number of cards each player has
	int cards_per_player = update_initial_knowns(players, player_count, master);

	bool retry = true; //error check for printing a category
	bool tryagain = true; //error check for printing a player

	//main while loop to run the program
	while (1) { 
		COUT << ENDL;
		int choice = print_menu();	//prints the menu of options to the user and returns their chosen action

		switch (choice) {
			case 1: //print full clue sheet
				print_all(players, player_count);
				break;
				
			case 2: //print a player
				int personInt;

				while (tryagain) {	//until a valid input is given, continues to ask user for input
					COUT << ENDL << "Which player information would you like to print? (1 - " << player_count << ") : " << ENDL;
						for (int iter = 0; iter < player_count; iter++) {
							COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
						}
					CIN >> personInt;

					if (personInt < 0 || personInt > player_count) { //error check
						COUT << "--> Incorrect input -- please try again.." << ENDL;
								tryagain = true;
							} else {
								tryagain = false; //valid input given, exits the loop
								break;
							}
				}

				print_player(players, personInt);	//prints the known information about the player
				tryagain = true;
				break;

			case 3: //print items in a category
				int categoryInt;

				while(retry) {	//until a valid input is given, continues to ask user for input
					COUT << "Which category would you like to print?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
					CIN >> categoryInt;
					COUT << categoryInt;
					
					if (categoryInt < 1 || categoryInt > 3) { //error check
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						retry = true;
					} else {
						retry = false; //valid input given, exits the loop
						break;
					}
				}

				print_category(master, players, categoryInt, player_count, thecharacters, theweapons, therooms); //prints information about the chosen category
				retry = true;

				break;

			case 4: //update info
				update_info(players, player_count, master,cards_per_player);
				break;

			case 5: //check for solution
				solver(master);
				break;

			case 6: //quit
				return 0;
		}
	}

	return 0;
}
