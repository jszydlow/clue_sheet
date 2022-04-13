/**************************************************************************************
 * Names: Juliette Liebov, Noor Achkar, Jenna Szydlowski, Monica Cichon
 * Emails: jliebov@nd.edu, nachkar@nd.edu, mjzydlow@nd.edu, mcichon@nd.edu
 * File Name: clue_headers.h
 * Date Created: 4/12/2022
 * File Contents: This file contains the function prototypes for the Cheers! Final Project
 ***************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define VECTOR std::vector
#define STRING std::string
#define GETLINE std::getline
#define WS std::ws
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream
#define MAP std::map

//Function Prototypes:

typedef struct Player {

	STRING player_name;

	MAP <STRING, int> characters = {{"Miss Scarlet", 0},
									{"Colonel Mustard", 0},
									{"Mrs. White", 0},
									{"Mr. Green", 0},
									{"Mrs. Peacock", 0},
									{"Professor Plum", 0}};
	
	MAP <STRING, int> weapons = { 	{"Revolver", 0},
									{"Knife", 0},
									{"Lead Pipe", 0},
									{"Rope", 0},
									{"Candlestick", 0},
									{"Wrench", 0}};

	MAP <STRING, int> rooms = {		{"Kitchen", 0},
									{"Hall", 0},
									{"Ballroom", 0},
									{"Conservatory", 0},
									{"Dining Room", 0},
									{"Cellar", 0},
									{"Billiard Room", 0},
									{"Library", 0},
									{"Lounge", 0},
									{"Study", 0}};
} Player;

int introduction();
void build_players_array(VECTOR<Player> & players, int player_count);
int update_initial_knowns(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master);
void input_user_cards(VECTOR<Player> & players, int cards_per_player, int player_count, MAP<STRING, int> & master);
void input_extra_cards(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master);
