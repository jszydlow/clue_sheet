/**************************************************************************************
 * Names: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
 * Emails: jliebov@nd.edu, nachkar@nd.edu, mjzydlow@nd.edu, mcichon@nd.edu
 * File Name: clue_functions.cpp
 * Date Created: 4/12/2022
 * File Contents: This file contains the functions for the Cheers! Final Project
 ***************************************************************************************/

#include "../include/clue_headers.h"

//introduction function:
int introduction() {

	int player_count;	//integer to track the number of players

	COUT << "Welcome to the Clue Helper!" << ENDL << "Please input a valid number of players (3-6): ";
	CIN >> player_count;

	return player_count;	//return number of players

}

//toUpper function:
void toUpper(STRING &word) {

	for (auto & c: word) c = (char) toupper(c);	//converts string to uppercase
}

//errorCheck function:
bool errorCheck( VECTOR<Player> & players, STRING item, int categoryInt) { //runs through a player list and compares the input to the items 
	toUpper(item);

	if (categoryInt == 1) {
		for (auto &i : players[0].characters) {
			if (i.first == item) {
				return true;	// if the item matches an item in characters, then the input is valid
			}
		}
	}

	else if (categoryInt == 2) {
		for (auto &i : players[0].weapons) {
			if (i.first == item) {
				return true;	// if the item matches an item in weapons, then the input is valid
			}
		}
	}

	else if (categoryInt == 3) {
		for (auto &i : players[0].rooms) {
			if (i.first == item) {
				return true;	// if the item matches an item in rooms, then the input is valid
			}
		}
	}

	return false; //otherwise the input is not valid --> ask the user to try again
}

//build_players_array function:
void  build_players_array(VECTOR<Player> & players, int player_count) {

	COUT << "Please input your name: ";

	CIN >> players[0].player_name;		//takes in the name of the player
	toUpper(players[0].player_name);	//converts string to uppercase
	players[0].num_knowns = 0; 			//set your amount of known cards to zero

	//for loop to input the strings of player names into the players vector
	for (int iter = 1; iter < player_count; iter++) {
		COUT << "Please input the name of the next player: ";
		CIN >> players[iter].player_name;	//takes in the name of the player
		toUpper(players[iter].player_name);	//converts string to uppercase
		players[iter].num_knowns = 0;		//set this player instance's number of known cards
	}

	COUT << ENDL;

	return;
}

//update_initial_knowns function:
int  update_initial_knowns(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {
	
	int cards_per_player = 19 / player_count;	//determines the amount of cards each player has
	int extra_cards = 19 % player_count;		//determines the amount of cards left over

	players[0].num_knowns = cards_per_player;	//the player knows all of the cards for themself...

	if (extra_cards != 0) {
	
		input_extra_cards(players, player_count, master);	//inputs the extra cards if there are any

	}

	COUT << ENDL << "You will now input the cards in your hand. You will first indicate the type of item, and then enter the item name." << ENDL;	

	input_user_cards(players, cards_per_player, player_count, master);	//input_user_cards, inputs the cards the user has in their hand

	check_num_knowns(players, 0, cards_per_player);
	
	return cards_per_player;	//returns the integer number of cards each player has
}

//input_user_cards function:
void input_user_cards(VECTOR<Player> & players, int cards_per_player, int player_count, MAP<STRING, int> & master) {
	
	MAP <STRING, int>::iterator i;
	int type;
	STRING item;

	//for loop to iterate through the number of cards the player has
	for (int iter = 0; iter < cards_per_player; iter++) {
		bool tryagain = true; //error check for type of item
		bool retry = true; //error check for item name
		
		//while loop to check that the user inputs a valid type 
		while(tryagain) {
			COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
			CIN >> type;

			if (type < 1 || type > 3) { //error check for valid input
				COUT << "--> Incorrect input -- please try again.." << ENDL;
				tryagain = true;
			} else {
				tryagain = false;
				break;
			}
		}

		COUT << "Please input the item name: ";

		//switch statement to properly input the item into its respective data stucture
		switch(type) {
			case 1:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);	//convert to uppercase

					//error checking
					if (!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

				//locate the key in the map
				i = players[0].characters.find(item);

				//set the value of the key to 1
				if (i != players[0].characters.end()) {
					i->second = 1;
				}
			
				//set the value of all other players' keys to 3
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
					toUpper(item);	//convert to uppercase

					//error checking
					if (!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

				//locate the key in the map
				i = players[0].weapons.find(item);

				//set the value of the key to 1
				if (i != players[0].weapons.end()) {
					i->second = 1;
				}

				//set the value of all other players' keys to 3
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
					toUpper(item);	//convert to uppercase

					//error checking
					if (!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

				//locate the key in the map
				i = players[0].rooms.find(item);

				//set the value of the key to 1
				if (i != players[0].rooms.end()) {
					i->second = 1;
				}

				//set the value of all other players' keys to 3
				for (int jter = 1; jter < player_count; jter++) {
					i = players[jter].rooms.find(item);
					if (i != players[jter].rooms.end()) {
						i->second = 3;
					}
				}

				break;
		}
	
		//update the key in the master map to mark that it was found
		i = master.find(item);

		if (i != master.end()) {
			i->second = 1;
		}
	}

	return;
}

void input_extra_cards(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master) {

	int extra_cards = 19 % player_count;	//calculate the number of extra cards left over
	MAP <STRING, int>::iterator i;
	int type;
	STRING item;

	COUT << "First, you will input the cards in the middle. You will first indicate the type of item, and then enter the item name." << ENDL;

	
	//for loop to iterate through the number of cards in the middle
	for (int iter = 0; iter < extra_cards; iter++) {
		bool tryagain = true; //error check for type of item
		bool retry = true; //error check for item name

		//while loop to check that the user inputs a valid type 
		while(tryagain) {
			COUT << "What is the type of the item?" << ENDL << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
			CIN >> type;

			if (type < 1 || type > 3) {	//error check for valid input
				COUT << "--> Incorrect input -- please try again.." << ENDL;
				tryagain = true;
			} else {
				tryagain = false;
			}
		}

		COUT << "Please input the item name: ";

		//switch statement to properly input the item into its respective data stucture
		switch(type) {
			case 1:
				while(retry) { //error check
					GETLINE(CIN >> WS, item);
					toUpper(item);	//convert to uppercase

					if (!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}
			
				// for loop to mark all players as not having the item	
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
					toUpper(item);	//convert to uppercase

					if (!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

				// for loop to mark all players as not having the item	
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
					toUpper(item);	//convert to uppercase

					if(!errorCheck( players, item, type)) {
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						COUT << "Please input the item name: ";
						retry = true;
					} else {
						retry = false;
						break;
					}
				}

				// for loop to mark all players as not having the item	
				for (int jter = 0; jter < player_count; jter++) {
					i = players[jter].rooms.find(item);
					if (i != players[jter].rooms.end()) {
						i->second = 3;
					}
				}

				break;
		}
	
		//update the key in the master map to mark that it was found
		i = master.find(item);

		if (i != master.end()) {
			i->second = 1;
		}

	}

	return;
}

//update_info function:
void update_info(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master,int cards_per_player) {
	int personInt;
	int categoryInt = -1;
	MAP <STRING, int>::iterator i;
	STRING item;
	bool forsure = false; //if the user is positive about their info, then this will become true
	STRING posCheck; //this will be the y/n that the user inputs if they are/are not postive
	STRING continueCheck; //this will be the y/n the user inputs if they want to keep updating info
	bool keepgoing = true;

  	while (keepgoing) {
		bool tryagain = true; //error check for player number
		bool retry = true; //error check for item name
		bool redo = true; //error check for category number

		while (tryagain) {
				COUT << ENDL << "Which player information would you like to update? Please enter a number." << ENDL;
					for (int iter = 0; iter < player_count; iter++) {
						COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
					}
				CIN >> personInt;
				if (personInt < 0 || personInt > player_count) {
					tryagain = true;
					COUT << "--> Incorrect input -- please try again.." << ENDL;
				} else {
					tryagain = false;
					break;
				}
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

			while(redo) {

				COUT << ENDL << "Which category would you like to update? Please enter a number." << ENDL;
				COUT << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
				CIN >> categoryInt;

				if (categoryInt < 1 || categoryInt > 3) { //error check
						COUT << "--> Incorrect input -- please try again.." << ENDL;
						redo = true;
					} else {
						redo = false;
						break;
					}

				}

			COUT << "Please input the item name: ";

			switch(categoryInt) {
				case 1: //Characters
					while(retry) { //error check
						GETLINE(CIN >> WS, item);
						toUpper(item);

						if (!errorCheck( players, item, categoryInt)) {
							COUT << "--> Incorrect input -- please try again.." << ENDL;
							COUT << "Please input the item name: ";
							retry = true;
						} else {
							retry = false;
							break;
						}
					}

					for (auto & checkmaster : master) { //iterate through the master list to check if the specified item
						if (checkmaster.first == item && checkmaster.second == 0) { //has or has not already been placed

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
									check_num_knowns(players,personInt,cards_per_player);	

								}

							} else {
								for (int it = 0; it < player_count; it++) {
									for (auto playercheck : players[it].characters) { //check through all of the players to make sure that the specifed item has not already been placed
										if ((playercheck.first == item && playercheck.second != 1) || (playercheck.first == item && playercheck.second != 3)) {
											i = players[personInt].characters.find(item); //if it's just a maybe, then only update the specified player

											if (i != players[personInt].characters.end()) { 
											i->second = 2; 
											}
										} else if ((playercheck.first == item && playercheck.second == 1) || (playercheck.first == item && playercheck.second == 3)) {
											COUT << "This card is already one of the extras or in a player's hand!" << ENDL; //if it has already been placed, this part of the function makes sure that the
																															// previous info is not overwritten
											break;
										}
									}
								}
							}
						} else if (checkmaster.first == item && checkmaster.second == 1) {
							COUT << "This card is already one of the extras or in a player's hand!" << ENDL;
							break;
						}
					}

					break;

				case 2: //Weapons
					while(retry) { //error check
						GETLINE(CIN >> WS, item);
						toUpper(item);

						if (!errorCheck( players, item, categoryInt)) {
							COUT << "--> Incorrect input -- please try again.." << ENDL;
							COUT << "Please input the item name: ";
							retry = true;
						} else {
							retry = false;
							break;
						}
					}

					for (auto & checkmaster : master) {
						if (checkmaster.first == item && checkmaster.second == 0) {

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
									check_num_knowns(players,personInt,cards_per_player);	

								}

							}  else {
										for (int it = 0; it < player_count; it++) {
											for (auto playercheck : players[it].weapons) {
												if ((playercheck.first == item && playercheck.second != 1) || (playercheck.first == item && playercheck.second != 3)) {
													i = players[personInt].weapons.find(item); //if it's just a maybe, then only update the specified player

													if (i != players[personInt].weapons.end()) { 
													i->second = 2; 
													}
												} else if ((playercheck.first == item && playercheck.second == 1) || (playercheck.first == item && playercheck.second == 3)) {
													COUT << "This card is already one of the extras or in a player's hand!" << ENDL;
													break;
												}
											}
										}
									}
						} else if (checkmaster.first == item && checkmaster.second == 1) {
							COUT << "This card is already one of the extras or in a player's hand!" << ENDL;
							break;
						}
					}

					break;

				case 3: //Rooms
					while(retry) { //error check
						GETLINE(CIN >> WS, item);
						toUpper(item);

						if (!errorCheck( players, item, categoryInt)) {
							COUT << "--> Incorrect input -- please try again.." << ENDL;
							COUT << "Please input the item name: ";
							retry = true;
						} else {
							retry = false;
							break;
						}
					}

					for (auto & checkmaster : master) {
						if (checkmaster.first == item && checkmaster.second == 0) {

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
									check_num_knowns(players,personInt,cards_per_player);	
				
								}

							} else {
										for (int it = 0; it < player_count; it++) {
											for (auto playercheck : players[it].rooms) {
												if ((playercheck.first == item && playercheck.second != 1) || (playercheck.first == item && playercheck.second != 3)) {
													i = players[personInt].rooms.find(item); //if it's just a maybe, then only update the specified player

													if (i != players[personInt].rooms.end()) { 
													i->second = 2; 
													}
												} else if ((playercheck.first == item && playercheck.second == 1) || (playercheck.first == item && playercheck.second == 3)) {
													COUT << "This card is already one of the extras or in a player's hand!" << ENDL;
													break;
												}
											}
										}
									}
						} else if (checkmaster.first == item && checkmaster.second == 1) {
							COUT << "This card is already one of the extras or in a player's hand!" << ENDL;
							break;
						}
					}

					break;
			}

		//asks if the user would like to continue updating
		COUT << ENDL << "Would you like to update again? (y/n) ";
		GETLINE (CIN >> WS, continueCheck);
		if (continueCheck == "n") {
			keepgoing = false;	//if not, breaks from the loop
			break;
		}
	}
	
}

//print_menu function:
int print_menu() {
	int choice = 0;

	//displays the menu to the user
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

//print_all function:
//print the entire clue sheet with all known information about all players
void print_all(VECTOR<Player> & players, int player_count) {

	// Explanation/key for each number in the clue sheet
	COUT << ENDL;
	COUT << "Explanation:" << ENDL;
	COUT << "0: We do not have information" << ENDL;
	COUT << "1: The current player has it" << ENDL;
	COUT << "2: The player might have it" << ENDL;
	COUT << "3: The player definitely does not have it" << ENDL << ENDL;

	for (int i = 0; i < 60; i++) {
		COUT << "-";
	}

	COUT << ENDL << "	";
	for (int i = 0; i < player_count; i++) {
		COUT << "	" <<  players[i].player_name;
	}
	COUT << ENDL;

	for (int i = 0; i < 20; i++) 
		COUT << "-- ";
	COUT << ENDL;

	// print the Characters
	COUT << "Characters:" << ENDL;
	for (int i = 0; i < 13; i++) 
		COUT << "-";
	COUT << ENDL; 

	for (auto j: players[0].characters) {
		COUT << j.first << "	";
		for (int i = 0; i < player_count; i++) {
			for (auto k: players[i].characters) {
				if (k.first == j.first) {
					COUT << k.second << "	";
				}
			}
			if (players[i].player_name.size() > 7) 
				COUT << "	";
		}	
		COUT << ENDL;
	}
			
	for (int i = 0; i < 20; i++) 
		COUT << "-- ";
	COUT << ENDL;

	// Print the Weapons
	COUT << "Weapons:" << ENDL;
	for (int i = 0; i < 7; i++) 
		COUT << "-";
	COUT << ENDL;

	for (auto j: players[0].weapons) {
		COUT << j.first << "	";
		if (j.first.size() < 7) 
			COUT <<  "	";
		for (int i = 0; i < player_count; i++) {
			for (auto k: players[i].weapons) {
				if (k.first == j.first) {
					COUT << k.second << "	";
				
				}
			}
			if (players[i].player_name.size() > 7) 
				COUT << "	";
		}	
		COUT << ENDL;
	}

	for (int i = 0; i < 20; i++) 
		COUT << "-- ";
	COUT << ENDL;

	// Print the Rooms
	COUT << "Rooms:" << ENDL;
	for (int i = 0; i < 7; i++) 
		COUT << "-";
	COUT << ENDL;

	for (auto j: players[0].rooms) {
		COUT << j.first << "	";
		if (j.first.size() < 8) 
			COUT <<  "	";
		for (int i = 0; i < player_count; i++) {
			for (auto k: players[i].rooms) {
				if (k.first == j.first) {
					COUT << k.second << "	";
				
				}
			}
			if (players[i].player_name.size() > 7) 
				COUT << "	";
		}	
		COUT << ENDL;
	}

	for (int i = 0; i < 60; i++) {
		COUT << "-";
	}

}


//print_player function:
void print_player(VECTOR<Player> & players, int num) {
	int iter;
	num--; //reset to follow c++ iteration rules
	COUT << ENDL;

	for (iter = 0; iter < 45; iter++) { COUT << "-"; } //header for the display "box"
	COUT << ENDL << "\t" << players[num].player_name << "\'s Known Information" << ENDL;
	for (iter = 0; iter < 15; iter++) { COUT << "- -"; }
	COUT << ENDL;

	// display the characters information for the player
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

	//display the weapons information for the player
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

	//display the rooms information for the player
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

//print_category function:
void print_category(MAP<STRING, int> & master, VECTOR<Player> & players, int num, int player_count, VECTOR<STRING> & thecharacters, VECTOR<STRING> & theweapons, VECTOR<STRING> & therooms) {
	MAP<STRING, int>::iterator i;
	bool playersHand = false; //will turn if the card is found in a player's category map(s)
	bool inMiddle = false; //will turn if a player has the specific card while checking the player's category maps
	//bool unknownCard = false; //will turn if the card is found in a player's category map(s)
	//bool playersName = false; //if the player's name is printed then this flag will make sure "extra card" is not also printed
	//bool extraCard = false;
	int display;
	//int extraCardCount = 0; //a counter -- if all of the players have 3 and this count = player_count --> will display which are the extra cards

	COUT << ENDL;

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

			else if (i != master.end() && i->second == 1) {
				for (int jter = 0; jter < player_count; jter++) { //iterate through each of the players to check
					for (auto x : players[jter].characters) {

						if (i->first == x.first && x.second == 3) {
							inMiddle = true;
						}
						else if (i->first == x.first && x.second == 1) { //item is found in the player's cards so it can't be an extra card
							playersHand = true;
							//playersName = true;
							COUT << ENDL << "playersHand in else if: " << playersHand << ENDL;
							inMiddle = false;
							break;
						}

					}
					if ((playersHand == true) && (inMiddle == false)) {
						COUT << "\t--> " << players[jter].player_name << ENDL;
						COUT << ENDL << "playersHand in printout: " << playersHand << ENDL;
						break;
					} 
					else if (inMiddle == true) { 
						playersHand = false;
						COUT << ENDL << "playersHand in middle if: " << playersHand << ENDL;
						break; 
					}
				}
				COUT << ENDL << "playersHand after player loop: " << playersHand << ENDL;
				if ((playersHand == false) && (inMiddle == true)) {
					COUT << "\t--> Extra card" << ENDL; //or if the card is unavailable but not with a player - display that it's in the middle
				}
			}
			//reinitialize the flags
			playersHand = false;
			inMiddle = false;
			//unknownCard = false;
			//playersName = false;
			
		}
/*
	} else if (num == 2) {

		COUT << "WEAPONS:" << ENDL; //title
		for (int jter = 0; jter <= 8; jter++) { COUT << "-"; } 
		COUT << ENDL;

		for (int iter = 0; iter < 6; iter++) {
			COUT << theweapons[iter];
			i = master.find(theweapons[iter]);

			for (int jter = 0; jter < player_count; jter++) { //iterate through each of the players to check
				for (auto x : players[jter].weapons) {
					if (i->first == x.first && x.second == 1) { //item is found in the player's cards so it can't be an extra card
						playersHand = true;
						inMiddle = false;
						unknownCard = false;
					}
					else if ((i->first == x.first && x.second == 0) || (i->first == x.first && x.second == 2)) {
						playersHand = false;
						inMiddle = false;
						unknownCard = true;
					}
					else if (i->first == x.first && x.second == 3) {
						playersHand = false;
						inMiddle = true;
						unknownCard = false;
					}
				}

				if (playersHand) {
					COUT << "\t--> " << players[jter].player_name << ENDL;
				}
			}
			if (!playersHand && !unknownCard && inMiddle) {
				COUT << "\t--> Extra card" << ENDL; //or if the card is unavailable but not with a player - display that it's in the middle
			} else if (!playersHand && unknownCard && !inMiddle) {

			}
		}


	} else if (num == 3) {

		COUT << "ROOMS:" << ENDL; //title
		for (int jter = 0; jter <= 6; jter++) { COUT << "-"; } 
		COUT << ENDL;

		for (int iter = 0; iter < 6; iter++) {
			COUT << therooms[iter];
			i = master.find(therooms[iter]);

			for (int jter = 0; jter < player_count; jter++) { //iterate through each of the players to check
				for (auto x : players[jter].rooms) {
					if (i->first == x.first && x.second == 1) { //item is found in the player's cards so it can't be an extra card
						playersHand = true;
						inMiddle = false;
						unknownCard = false;
					}
					else if ((i->first == x.first && x.second == 0) || (i->first == x.first && x.second == 2)) {
						playersHand = false;
						inMiddle = false;
						unknownCard = true;
					}
					else if (i->first == x.first && x.second == 3) {
						playersHand = false;
						inMiddle = true;
						unknownCard = false;
					}
				}

				if (playersHand) {
					COUT << "\t--> " << players[jter].player_name << ENDL;
				}
			}
			if (!playersHand && !unknownCard && inMiddle) {
				COUT << "\t--> Extra card" << ENDL; //or if the card is unavailable but not with a player - display that it's in the middle
			}
		}
	}
	*/

	for (display = 0; display < 45; display++) { COUT << "-"; } //display ending
		COUT << ENDL;
}

//solver function:
bool solver(MAP<STRING, int> & master) {

	int zeros = 0;	//integer to count the number of 0s in the master
	MAP <STRING, int>::iterator i = master.begin();
	int whichItem = 0;
	STRING cardOne;
	STRING cardTwo;
	STRING cardThree;

	//iterate through the master list
	//and count the 0s in the list with
	//the "zeros" variable
	while (i != master.end()) {
		if (i->second == 0)	 {
			zeros++;	
			if (whichItem == 0) { 
				cardOne  = i->first;	//save the unknown card 
			}
			else if (whichItem == 1) { 
				cardTwo = i->first;		//save the unknown card
			}
			else { 
				cardThree = i->first;	//save the unknown card
			}
			whichItem++;
		}
		i++;		
	}

	//if exactly three 0s were found... a solution has been found!
	if (zeros == 3) {
		COUT << "Game is solvable!!!!!!!!\n";
		COUT << "The correct cards are " << cardOne << ", " << cardTwo << ", and " << cardThree << "! dun dun DUNNNNN\n";	//print the solution
		return true;
	
	//otherwise, a solution has not yet been found :(
	} else {
		COUT << "Puzzle not currently solvable. :( \n";
		return false;
	}


}

//check_num_knowns function:
void check_num_knowns(VECTOR<Player> & players, int curr_player, int cards_per_player) {

	if (players[curr_player].num_knowns >= cards_per_player) { //if we know what all of the cards are for a player...
			COUT << "All cards for player " << curr_player + 1 << " have been found. Updating info to reflect...\n";
			MAP <STRING, int>::iterator c = players[curr_player].characters.begin();
		
			//change all unknown info for the player to definitely does not have (3)
			//for all 3 maps in the player struct
			while (c != players[curr_player].characters.end()) {
				if (c->second != 1) {
					c->second = 3;
				}
				c++;
			}
			MAP <STRING, int>::iterator r = players[curr_player].rooms.begin();
			while (r != players[curr_player].rooms.end()) {
				if (r->second != 1) {
					r->second = 3;
				}
				r++;
			}
			MAP <STRING, int>::iterator w = players[curr_player].weapons.begin();
			while (w != players[curr_player].weapons.end()) {
				if (w->second != 1) {
					w->second = 3;
				}
				w++;
			}

	}
}
