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

void toUpper(STRING &word) {

	for (auto & c: word) c = (char) toupper(c);
}

bool errorCheck( VECTOR<Player> & players, STRING item, int categoryInt) { //runs through a player list and compares the input to the items 
	toUpper(item);

	if (categoryInt == 1) {
		for (auto &i : players[0].characters) {
			if (i.first == item) {
				return true;	// if the item matches an item in the list, then the input is valid
			}
		}
	}

	else if (categoryInt == 2) {
		for (auto &i : players[0].weapons) {
			if (i.first == item) {
				return true;
			}
		}
	}

	else if (categoryInt == 3) {
		for (auto &i : players[0].rooms) {
			if (i.first == item) {
				return true;
			}
		}
	}

	return false; //otherwise the input is not valid --> ask the user to try again
}

void  build_players_array(VECTOR<Player> & players, int player_count) {

	COUT << "Please input your name: ";

	CIN >> players[0].player_name;
	toUpper(players[0].player_name);
	players[0].num_knowns = 0; //set your amount of known cards to zero

	for (int iter = 1; iter < player_count; iter++) {
		COUT << "Please input the name of the next player: ";
		CIN >> players[iter].player_name;
		toUpper(players[iter].player_name);
		players[iter].num_knowns = 0;//set this player instance's number of known cards
	}

	COUT << ENDL;

	return;
}

int  update_initial_knowns(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {
	
	int cards_per_player = 19 / player_count;
	int extra_cards = 19 % player_count;

	players[0].num_knowns = cards_per_player;

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
		bool tryagain = true;
		bool retry = true;
		
		while(tryagain) {
			COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
			CIN >> type;

			if (type < 1 || type > 3) { //error check
				COUT << "Incorrect input - please try again.." << ENDL;
				tryagain = true;
			} else {
				tryagain = false;
				break;
			}
		}

		COUT << "Please input the item name: ";

		switch(type) {
			case 1:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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
		bool tryagain = true;
		bool retry = true;

		while(tryagain) {
			COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
			CIN >> type;

			if (type < 1 || type > 3) {
				COUT << "Incorrect input - please try again.." << ENDL;
				tryagain = true;
			} else {
				tryagain = false;
			}
		}

		COUT << "Please input the item name: ";

		switch(type) {
			case 1:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}
				
					for (int jter = 0; jter < player_count; jter++) { //loops through the players
						i = players[jter].characters.find(item); //say you're searching for Miss Scarlet .. i.e. player[0]-Mr.Green-Miss Scarlet?
						if (i != players[jter].characters.end()) {
							i->second = 3;
						}
					}

				break;

			case 2:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

					for (int jter = 0; jter < player_count; jter++) {
						i = players[jter].weapons.find(item);
						if (i != players[jter].weapons.end()) {
							i->second = 3;
						}
					}

				break;

			case 3:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if(!errorCheck( players, item, type)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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
		bool tryagain = true;
		bool retry = true;

		while (tryagain)
		COUT << ENDL << "Which player information would you like to update? Please enter a number." << ENDL;
			for (int iter = 0; iter < player_count; iter++) {
				COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
			}
		CIN >> personInt;
		if (personInt < 0 || personInt > player_count) {
			tryagain = true;
		} else {
			tryagain = false;
		}
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
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, categoryInt)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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

					if (i != master.end()) { 
						i->second = 1; 
						players[personInt].num_knowns++; //increment that that player has another known card
					}

				} else {
					i = players[personInt].characters.find(item); //if it's just a maybe, then only update the specified player

					if (i != players[personInt].characters.end()) { 
						i->second = 2; 
					}
				}

				break;

			case 2: //Weapons
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, categoryInt)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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

					if (i != master.end()) { 
						i->second = 1; 
						players[personInt].num_knowns++; //increment that that player has another known card
					}

				} else {
					i = players[personInt].weapons.find(item); //if it's just a maybe, then only update the specified player
					
					if (i != players[personInt].weapons.end()) { 
						i->second = 2; 
					}
				
				}

				break;

			case 3: //Rooms
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);

					if (!errorCheck( players, item, categoryInt)) {
						COUT << "Incorrect input - please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

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

					if (i != master.end()) { 
						i->second = 1; 
						players[personInt].num_knowns++; //increment that that player has another known card
					}

				} else {
					i = players[personInt].rooms.find(item); //if it's just a maybe, then only update the specified player

					if (i != players[personInt].rooms.end()) { 
						i->second = 2; 
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

	COUT << "Characters:" << ENDL;
	for (int jter = 0; jter <= 11; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].characters) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << setfill(' ') << setw(10) << " --> HAS";
		} else if (i.second == 2) {
			COUT << setfill(' ') << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << setfill(' ') << setw(22) << "--> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }

	COUT << ENDL << "Weapons:" << ENDL;
	for (int jter = 0; jter <= 8; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].weapons) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << setfill(' ') << setw(10) << " --> HAS";
		} else if (i.second == 2) {
			COUT << setfill(' ') << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << setfill(' ') << setw(22) << "--> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }

	COUT << ENDL << "Rooms:" << ENDL;
	for (int jter = 0; jter <= 6; jter++) { COUT << "-"; }
	COUT << ENDL;

	for (auto i : players[num].rooms) {
		COUT << i.first;
		if (i.second == 1) {
			COUT << setfill(' ') << setw(10) << " --> HAS";
		} else if (i.second == 2) {
			COUT << setfill(' ') << setw(20) << " --> maybe has.. ";
		} else if (i.second == 3) {
			COUT << setfill(' ') << setw(22) << "--> does not have ";
		}
		COUT << ENDL;
	}

	for (iter = 0; iter < 45; iter++) { COUT << "-"; } //ending for the display "box"

	COUT << ENDL;
}

void print_category(MAP<STRING, int> & master, VECTOR<Player> & players, int num, int player_count, VECTOR<STRING> & thecharacters, VECTOR<STRING> & theweapons, VECTOR<STRING> & therooms) {
	MAP<STRING, int>::iterator i;
	COUT << ENDL;
	bool playersHand = false;
	bool inMiddle = true;
	int display;

	for (display = 0; display < 45; display++) { COUT << "-" ; } //display header
	COUT << ENDL;

	if (num == 1) { //CHARACTERS  --> map #1-6

		COUT << "CHARACTERS:" << ENDL; //title
		for (int jter = 0; jter <= 11; jter++) { COUT << "-"; }
		COUT << ENDL;

		for (int iter = 0; iter < 6; iter++) {
			COUT << thecharacters[iter];
			i = master.find(thecharacters[iter]);

			if (i != master.end() && i->second == 0) { //iterate through the master list to check for 0s
				COUT << "\t " << ENDL;
			} 
			
			else if (i != master.end() && i->second == 1) { //iterate through master to check for 1s
				
				for (int jter = 0; jter < player_count; jter++) { //if a 1 is found, iterate through all players and display which player has this card
					for (auto x : players[jter].characters) { 
						if (i->first == x.first && x.second == 1) {
							playersHand = true;
							inMiddle = false;
							break;
						} else {
							playersHand = false;
						}
					}

					if (playersHand) {
						COUT << "\t--> " << players[jter].player_name << ENDL;
					}
				}
				if (!playersHand && inMiddle) {
					COUT << "\t--> Extra card" << ENDL; //or if the card is unavailable but not with a player - display that it's in the middle
				}
			}
		}
	}
	
	else if (num == 2) { //WEAPONS --> map #7-12

	COUT << "WEAPONS:" << ENDL;
	for (int jter = 0; jter <= 8; jter++) { COUT << "-"; }
	COUT << ENDL;

		for (int iter = 0; iter < 6; iter++) {
			COUT << theweapons[iter];
			i = master.find(theweapons[iter]);

			if (i != master.end() && i->second == 0) { //iterate through the master list
				COUT << "\t " << ENDL;
			} 
			
			else if (i != master.end() && i->second == 1) { //iterate through master to check for 1s
				
				for (int jter = 0; jter < player_count; jter++) {
					for (auto x : players[jter].weapons) { 
						if (i->first == x.first && x.second == 1) {
							playersHand = true;
							inMiddle = false;
							break;
						} else {
							playersHand = false;
						}
					}

					if (playersHand) {
						COUT << "\t--> " << players[jter].player_name << ENDL;
					}
				}
				if (!playersHand && inMiddle) {
					COUT << "\t--> Extra card" << ENDL;
				}
			}
		}
	} 
	
	else if (num == 3) { //ROOMS --> map #13-22

	COUT << "ROOMS:" << ENDL;
	for (int jter = 0; jter <= 6; jter++) { COUT << "-"; }
	COUT << ENDL;

		for (int iter = 0; iter < 10; iter++) {
			COUT << therooms[iter];
			i = master.find(therooms[iter]);

			if (i != master.end() && i->second == 0) { //iterate through the master list
				COUT << "\t " << ENDL;
			} 
			
			else if (i != master.end() && i->second == 1) { //iterate through master to check for 1s
				
				for (int jter = 0; jter < player_count; jter++) {
					for (auto x : players[jter].rooms) { 
						if (i->first == x.first && x.second == 1) {
							playersHand = true;
							inMiddle = false;
							break;
						} else {
							playersHand = false;
						}
					}

					if (playersHand) {
						COUT << "\t--> " << players[jter].player_name << ENDL;
					}
				}
				if (!playersHand && inMiddle) {
					COUT << "\t--> Extra card" << ENDL;
				}
			}
		}
	}

		for (display = 0; display < 45; display++) { COUT << "-"; } //display ending
		COUT << ENDL;
}

bool solver(MAP<STRING, int> & master) {

	//First possible way to solve:

	int zeros = 0;		
	MAP <STRING, int>::iterator i = master.begin();
	int whichItem = 0;
	STRING person;
	STRING weapon;
	STRING room;


	while (i != master.end()) {
		if (i->second == 0)	 {
			zeros++;	
			if (whichItem == 0) { //people
				person = i->first;
			}
			else if (whichItem == 1) { //weapons
				weapon = i->first;
			}
			else { //rooms
				room = i->first;
			}
			whichItem++;
		}
		i++;		
	}

	if (zeros == 3) {
		COUT << "Game is solvable!!!!!!!!\n";
		COUT << "It was " << person << " with the " << weapon << "in the " << room << "! dun dun DUNNNNN\n";
		return true;
	}	
	else {
		COUT << "Puzzle not currently solvable. :( \n";
		return false;
	}


}
