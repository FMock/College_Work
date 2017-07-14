#ifndef LIVES_H
#define LIVES_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include"DrawUtils.h"
#include"game_data.h"

class Lives{
public:
	Lives(Game_Data &aGameData);
	Game_Data *gameData;
	int lives_remaining;
	GLuint livesTex;
	int livesWidth;
	int livesHeight;
	int livesXPos;
	int livesYPos;
	int numWidth;
	int numHeight;
	int digitWidth;
	int digitsYPos;
	int digit2XPos;
	int digit1XPos;
	int getDigitOne(); // ones place
	int getDigitTwo(); // tens place
	std::vector<GLuint> numbers;
	void loadImages();
	void draw();
	void increaseLives(int);
	void decreaseLives(int);
	std::string to_string() const;
};

#endif

