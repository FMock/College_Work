#include"game_state.h"

using std::ostringstream;

GameState::GameState(){}

GameState::GameState(Game_Data &aGameData){
	gameData = &aGameData;
	currentState = START;
	gameData->currentGameState = currentState;
}

void GameState::changeState(int s){
	if(s > 0 && s < 4){
		currentState = s;
		gameData->currentGameState = currentState;
	}
}

int GameState::getGameState(){
	return currentState;
}

std::string GameState::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "CurrentState = " <<  currentState << "\n";
	return oss.str();
}