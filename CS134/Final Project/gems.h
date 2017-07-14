#ifndef GEMS_H
#define GEMS_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include"DrawUtils.h"
#include"game_data.h"

class Gems{
public:
	Gems(Game_Data &aGameData);
	Game_Data *gameData;
	int gem_count;
	GLuint gemsTex;
	int gemsWidth;
	int gemsHeight;
	int gemsXPos;
	int gemsYPos;
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
	void increaseGemCount(int);
	void decreaseGemCount(int);
	std::string to_string() const;
};

#endif

