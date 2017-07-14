#ifndef GAME_STATE_H
#define GAME_STATE_H

#include"game_data.h"
#include<string>
#include<sstream>


class GameState{
public:
	GameState();
	GameState(Game_Data &aGameData);
	Game_Data *gameData;
	enum state {START, PLAY, PAUSE, END};
	int currentState;
	void changeState(int);
	int getGameState();
	std::string to_string() const;
};

#endif