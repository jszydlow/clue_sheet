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
#include <iomanip>
#include <cstdio>
#include <cstring>

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
#define setw std::setw
#define setfill std::setfill

#define TOTALCHARACTERS 6
#define TOTALWEAPONS 6
#define TOTALROOMS 10
#define TOTALITEMS 22

//Function Prototypes:

typedef struct Player {

	STRING player_name;
	int num_knowns;
	MAP <STRING, int> characters = {{"MISS SCARLET", 0},
									{"COLONEL MUSTARD", 0},
									{"MRS. WHITE", 0},
									{"MR. GREEN", 0},
									{"MRS. PEACOCK", 0},
									{"PROFESSOR PLUM", 0}};
	
	MAP <STRING, int> weapons = { 	{"REVOLVER", 0},
									{"KNIFE", 0},
									{"LEAD PIPE", 0},
									{"ROPE", 0},
									{"CANDLESTICK", 0},
									{"WRENCH", 0}};

	MAP <STRING, int> rooms = {		{"KITCHEN", 0},
									{"HALL", 0},
									{"BALLROOM", 0},
									{"CONSERVATORY", 0},
									{"DINING ROOM", 0},
									{"CELLAR", 0},
									{"BILLIARD ROOM", 0},
									{"LIBRARY", 0},
									{"LOUNGE", 0},
									{"STUDY", 0}};
} Player;

int introduction();
void toUpper(STRING &word);
bool errorCheck( VECTOR<Player> & players, STRING item, int categoryInt);
void build_players_array(VECTOR<Player> & players, int player_count);
int update_initial_knowns(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master);
void input_user_cards(VECTOR<Player> & players, int cards_per_player, int player_count, MAP<STRING, int> & master);
void input_extra_cards(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master);

void update_info(VECTOR<Player> & players, int player_count, MAP<STRING, int> & master, int cards_per_player);
int print_menu();
void print_all(VECTOR <Player> & players, int player_count);
void print_player(VECTOR<Player> & players, int num);
void print_category(MAP<STRING, int> & master, VECTOR<Player> & players, int num, int player_count, VECTOR<STRING> & thecharacters, VECTOR<STRING> & theweapons, VECTOR<STRING> & therooms);
bool solver(MAP<STRING, int> & master);
void check_num_knowns(VECTOR<Player> & players, int curr_player, int cards_per_player); 

