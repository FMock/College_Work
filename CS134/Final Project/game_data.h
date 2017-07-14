#pragma once
#ifndef GAME_DATA_H
#define GAME_DATA_H
#include<string>
#include<sstream>

/* All objects with a reference to Game_Data can track important game
* information to use with game control or response */

using std::ostringstream;

struct Game_Data{
public:
	inline Game_Data::Game_Data():currentGameState(0),player_x(0), player_y(0){}

	enum state {START, PLAY, PAUSE, END};

	// General Game Info
	int currentGameState;
	int score;
	int lives_remaining;
	int gem_count;
	int level;

	// Player Info
	int player_x;
	int player_y;
	int player_direction; // LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3
	int player_hp;
	
	// Skeleton Info
	int numberOfSkeletons;
	int numberOfRedSkeletons;
	int numberOfPumpkins;
	int numberOfGems;

	inline void recordPlayersXPos(int x){ player_x = x * 2; }
	inline void recordPlayersYPos(int y){ player_y = y * 2; }
	inline void recordPlayerDirection(int d) {player_direction = d; }

	inline int getPlayerXPos(){ return player_x; }
	inline int getPlayerYPos(){ return player_y; }

	inline std::string Game_Data::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "score = " << score << "\n"
		<< "level = " << level << "\n"
		<< "lives remaining = " << lives_remaining << "\n"
		<< "gem_count = " << gem_count << "\n"
		<< "Player's X pos. = " <<  player_x << "\n"
		<< "Player's Y pos. = " <<  player_y << "\n"
		<< "Player's HP = " << player_hp << "\n"
		<< "currentGameState = " << currentGameState << "\n"
		<< "numberOfSkeletons = " << numberOfSkeletons << "\n"
		<< "numberOfRedSkeletons = " << numberOfRedSkeletons << "\n"
		<< "numberOfPumpkins = " << numberOfPumpkins << "\n"
		<< "Player's Direction = " <<  player_direction << "\n";
		return oss.str();
	}
};
#endif