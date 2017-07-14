#ifndef SCORE_H
#define SCORE_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include"DrawUtils.h"
#include"camera.h"
#include"game_data.h"

class Score{
public:
	Score(Camera *cam, Game_Data &aGameData);
	Camera &camera;
	Game_Data *gameData;
	int score;
	GLuint scoreTex;
	int scoreWidth;
	int scoreHeight;
	int scoreXPos;
	int scoreYPos;
	int numWidth;
	int numHeight;
	int digitWidth;
	int digitsYPos;
	int digit5XPos;
	int digit4XPos;
	int digit3XPos;
	int digit2XPos;
	int digit1XPos;

	std::vector<GLuint> numbers;
	void loadImages();
	void draw();
	void increaseScore(int);
	int getDigitOne(); // ones place
	int getDigitTwo(); // tens place
	int getDigitThree(); // hundreds place
	int getDigitFour(); // Thousandths place
	int getDigitFive(); // Ten Thousandths place
	std::string to_string() const;
};

#endif