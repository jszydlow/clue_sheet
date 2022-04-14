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
	int personInt = -1;
	int categoryInt = -1;
	MAP <STRING, int>::iterator i;
	STRING item;

	COUT << ENDL << ENDL << "Which player information would you like to update? Please enter a number." << ENDL;
		for (int iter = 0; iter < player_count; iter++) {
			COUT << "(" << iter + 1 << ") " << players[iter].player_name << ENDL;
		}
	CIN >> personInt;

	COUT << "Which category would you like to update? Please enter a number." << ENDL;
	COUT << "(1) Characters" << ENDL << "(2) Weapons" << ENDL << "(3) Rooms" << ENDL;
	CIN >> categoryInt;

	COUT << "Pleade input the item name: ";

	switch(categoryInt) {
		case 1: //Characters
			GETLINE(CIN >> WS, item);
			/*
			for (int jter = 0; jter < TOTALCHARACTERS; jter++) {
				i = players[personInt].characters.find(item);
				if (i == players[jter].characters.end()) {
					i->second = 1; //this user definitely has the card
				}
			}
			*/
			for(auto n:master) { //iterate through and update the master list once we have a definite (1) value
        		if (n.first == item) {
					n.second = 1;
					//COUT<<"Key (character) - "<<n.first<<" "<<" Value (1/0) - "<<n.second << ENDL;
        		}
    		}

		case 2: //Weapons
			GETLINE(CIN >> WS, item);

			for(auto n:master) { //iterate through and update the master list once we have a definite (1) value
        		if (n.first == item) {
					n.second = 1;
        		}
    		}
		}

		case 3: //Rooms
			GETLINE(CIN >> WS, item);

			for(auto n:master) { //iterate through and update the master list once we have a definite (1) value
        		if (n.first == item) {
					n.second = 1;
        		}
    		}
		}


	
}
