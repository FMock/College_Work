#ifndef LEVEL_H
#define LEVEL_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include"DrawUtils.h"
#include"game_data.h"

class Level{
public:
	Level(Game_Data &aGameData);
	Game_Data *gameData;
	int level;
	GLuint LevelTex;
	int LevelWidth;
	int LevelHeight;
	int LevelXPos;
	int LevelYPos;
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
	void increaseLevelCount(int);
	void decreaseLevelCount(int);
	std::string to_string() const;
};

#endif

