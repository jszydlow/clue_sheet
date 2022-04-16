/**************************************************************************************
 * Names: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
 * Emails: jliebov@nd.edu, nachkar@nd.edu, mjzydlow@nd.edu, mcichon@nd.edu
 * File Name: clue_functions.cpp
 * Date Created: 4/12/2022
 * File Contents: This file contains the functions for the Cheers! Final Project
 ***************************************************************************************/

#include "../include/clue_headers.h"

int introduction() {

	int player_count;

	COUT << "Welcome to the Clue Helper!" << ENDL << "Please input a valid number of players (3-6): ";
	CIN >> player_count;

	return player_count;

}

void  build_players_array(VECTOR<Player> & players, int player_count) {

	COUT << "Please input your name: ";

	CIN >> players[0].player_name;

	for (int iter = 1; iter < player_count; iter++) {
		COUT << "Please input the name of the next player: ";
		CIN >> players[iter].player_name;
	}

	COUT << ENDL;

	return;
}

int  update_initial_knowns(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {

	int cards_per_player = 19 / player_count;
	int extra_cards = 19 % player_count;

	if (extra_cards != 0) {
	
		input_extra_cards(players, player_count, master);

	}

	COUT << ENDL << "You will now input the cards in your hand. You will first indicate the type of item, and then enter the item name (case sensitive)." << ENDL;	

	input_user_cards(players, cards_per_player, player_count, master);

	return cards_per_player;
}

void input_user_cards(VECTOR<Player> & players, int cards_per_player, int player_count, MAP<STRING, int> & master) {
	
	MAP <STRING, int>::iterator i;
	int type;
	STRING item;


	for (int iter = 0; iter < cards_per_player; iter++) {
		
		COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
		CIN >> type;

		COUT << "Please input the item name: ";

		switch(type) {
			case 1:
				GETLINE(CIN >> WS, item);

				i = players[0].characters.find(item);

				if (i != players[0].characters.end()) {
					i->second = 1;
				}

				for (int jter = 1; jter < player_count; jter++) {
					i = players[jter].characters.find(item);
					if (i != players[jter].characters.end()) {
						i->second = 3;
					}
				}

				break;

			case 2:
				GETLINE(CIN >> WS, item);

				i = players[0].weapons.find(item);

				if (i != players[0].weapons.end()) {
					i->second = 1;
				}

				for (int jter = 1; jter < player_count; jter++) {
					i = players[jter].weapons.find(item);
					if (i != players[jter].weapons.end()) {
						i->second = 3;
					}
				}

				break;

			case 3:
				GETLINE (CIN >> WS, item);

				i = players[0].rooms.find(item);

				if (i != players[0].rooms.end()) {
					i->second = 1;
				}

				for (int jter = 1; jter < player_count; jter++) {
					i = players[jter].rooms.find(item);
					if (i != players[jter].rooms.end()) {
						i->second = 3;
					}
				}

				break;
		}
	
		i = master.find(item);

		if (i != master.end()) {
			i->second = 1;
		}
	}

	return;
}

void input_extra_cards(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {

	int extra_cards = 19 % player_count;
	MAP <STRING, int>::iterator i;
	int type;
	STRING item;

	COUT << "First, you will input the cards in the middle. You will first indicate the type of item, and then enter the item name (case sensitive)." << ENDL;

	for (int iter = 0; iter < extra_cards; iter++) {
		COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
		CIN >> type; //input the type of category

		COUT << "Please input the item name: ";

		switch(type) {
			case 1:
				GETLINE(CIN >> WS, item);
				
				for (int jter = 0; jter < player_count; jter++) { //loops through the players
					i = players[jter].characters.find(item); //say you're searching for Miss Scarlet .. i.e. player[0]-Mr.Green-Miss Scarlet?
					if (i != players[jter].characters.end()) {
						i->second = 3;
					}
				}

				break;

			case 2:
				GETLINE(CIN >> WS, item);

				for (int jter = 0; jter < player_count; jter++) {
					i = players[jter].weapons.find(item);
					if (i != players[jter].weapons.end()) {
						i->second = 3;
					}
				}

				break;

			case 3:
				GETLINE (CIN >> WS, item);

				for (int jter = 0; jter < player_count; jter++) {
					i = players[jter].rooms.find(item);
					if (i != players[jter].rooms.end()) {
						i->second = 3;
					}
				}

				break;
		}
	
		i = master.find(item);

		if (i != master.end()) {
			i->second = 1;
		}

	}

	return;
}


void update_info(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {
	int personInt;
	int categoryInt;
	MAP <STRING, int>::iterator i;
	STRING item;
	bool forsure = false; //if the user is positive about their info, then this will become true
	STRING posCheck; //this will be the y/n that the user inputs if they are/are not postive
	STRING continueCheck; //this will be the y/n the user inputs if they want to keep updating info
	bool keepgoing = true;

  	while (keepgoing) {

		COUT << ENDL << "Which player information would you like to update? Please enter a number." << ENDL;
			for (int iter = 0; iter < player_count; iter++) {
				COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
			}
		CIN >> personInt;
		personInt--; //since c++ iterates starting from 0 but people don't

		COUT << "Are you positive about the information you are about to update? (y/n) ";
		GETLINE (CIN >> WS, posCheck); //this will help figure out if the value in the maps should be a 1 or 2 for the user's given value

		if (posCheck == "y") {
			forsure = true;
			COUT << "Fantastic! Let's update.." << ENDL;
		} else if (posCheck == "n") {
			forsure = false;
			COUT << "Ok, let's update your \"maybe's\"!" << ENDL;
		}

		COUT << ENDL << "Which category would you like to update? Please enter a number." << ENDL;
		COUT << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
		CIN >> categoryInt;


		COUT << "Please input the item name: ";

		switch(categoryInt) {
			case 1: //Characters
				GETLINE (CIN >> WS, item);

				if (forsure) {

					i = players[personInt].characters.find(item); //update the specified player's map

					if (i != players[personInt].characters.end()) {
						i->second = 1;
					}
			
					for (int jter = 0; jter < player_count; jter++) { //since the user is positive, set all the other players' cards to 3 (def don't have)
						i = players[jter].characters.find(item);
						if (jter == personInt) { continue; }
						if (i != players[jter].characters.end()) {
							i->second = 3;
						}
					}
			
					i = master.find(item); //iterate through and update the master list since we have a definite (1) value

					if (i != master.end()) { i->second = 1; }

				} else {
					i = players[personInt].characters.find(item); //if it's just a maybe, then only update the specified player

					if (i != players[personInt].characters.end()) {
						i->second = 2;
					}
				}

				break;

			case 2: //Weapons
				GETLINE (CIN >> WS, item);

				if (forsure) {

					i = players[personInt].weapons.find(item);

					if (i != players[personInt].weapons.end()) {
						i->second = 1;
					}

					for (int jter = 0; jter < player_count; jter++) { //set other players' cards to 3
						i = players[jter].weapons.find(item);
						if (jter == personInt) { continue; }
						if (i != players[jter].weapons.end()) {
							i->second = 3;
						}
					}

					i = master.find(item);

					if (i != master.end()) { i->second = 1; }
				} else {
					i = players[personInt].characters.find(item);

					if (i != players[personInt].characters.end()) {
						i->second = 2;
					}
				}

				break;

			case 3: //Rooms
				GETLINE (CIN >> WS, item);

				if (forsure) {

					i = players[personInt].rooms.find(item);

					if (i != players[personInt].rooms.end()) {
						i->second = 1;
					}

					for (int jter = 0; jter < player_count; jter++) { //set other players' cards to 3
						i = players[jter].rooms.find(item);
						if (jter == personInt) { continue; }
						if (i != players[jter].rooms.end()) {
							i->second = 3;
						}
					}

					i = master.find(item);

					if (i != master.end()) { i->second = 1; }
				} else {
					i = players[personInt].characters.find(item);

					if (i != players[personInt].characters.end()) {
						i->second = 2;
						COUT << item << "is a maybe" << ENDL;
					}
				}

				break;
		}

	COUT << ENDL << "Would you like to update again? (y/n) ";
	GETLINE (CIN >> WS, continueCheck);
	if (continueCheck == "n") {
		keepgoing = false;
		break;
	}
  }
	
}

int print_menu() {
	int choice = 0;

	COUT << "Select the action you would like to perform.\n";
	COUT << "1: Print full Clue Sheet.\n";
	COUT << "2: Print a player.\n";
	COUT << "3: Print items in a category.\n";
	COUT << "4: Update info.\n";
	COUT << "5: Check for a solution.\n";
	COUT << "6: Quit.\n";
	
	CIN >>  choice;

	return choice;
	
}

void print_player(VECTOR<Player> & players, int num) {
	int iter;
	num--; //reset to follow c++ iteration rules
	COUT << ENDL;

	for (iter = 0; iter < 45; iter++) { COUT << "-"; } //header for the display "box"
	COUT << ENDL << "\t" << players[num].player_name << "\'s Known Information" << ENDL;
	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }
	COUT << ENDL;

	COUT << "CHARACTERS:" << ENDL;
	for (int jter = 0; jter <= 11; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].characters) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << std::right << setw(11) << " --> HAS";
		} else if (i.second == 2) {
			COUT << std::right << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << std::right << setw(22) << " --> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }

	COUT << ENDL << "WEAPONS:" << ENDL;
	for (int jter = 0; jter <= 8; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].weapons) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << std::right << setw(11) << " --> HAS";
		} else if (i.second == 2) {
			COUT << std::right << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << std::right << setw(22) << " --> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }

	COUT << ENDL << "ROOMS:" << ENDL;
	for (int jter = 0; jter <= 6; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].rooms) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << std::right << setw(11) << " --> HAS";
		} else if (i.second == 2) {
			COUT << std::right << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << std::right << setw(22) << " --> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 45; iter++) { COUT << "-"; } //ending for the display "box"

	COUT << ENDL;
}