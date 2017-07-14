#include "level.h"


Level::Level(Game_Data &aGameData){
	gameData = &aGameData;
	level = 1;
	gameData->level = level;
	LevelWidth = 100;
	LevelHeight = 22;
	LevelXPos = 150;
	LevelYPos = 32;
	numWidth = 19;
	numHeight = 22;
	digitWidth = 19;
	digitsYPos = LevelYPos;
	digit2XPos = 260;
	digit1XPos = digit2XPos + digitWidth;
	LevelTex = glTexImageTGAFile("images/Level.tga", &LevelWidth, &LevelHeight);
	loadImages();
}

void Level::loadImages(){
	GLuint img0 = glTexImageTGAFile("images/num0.tga", &numWidth, &numHeight); // 0
	numbers.push_back(img0);
	GLuint img1 = glTexImageTGAFile("images/num1.tga", &numWidth, &numHeight); // 1
	numbers.push_back(img1);
	GLuint img2 = glTexImageTGAFile("images/num2.tga", &numWidth, &numHeight); // 2
	numbers.push_back(img2);
	GLuint img3 = glTexImageTGAFile("images/num3.tga", &numWidth, &numHeight); // 3
	numbers.push_back(img3);
	GLuint img4 = glTexImageTGAFile("images/num4.tga", &numWidth, &numHeight); // 4
	numbers.push_back(img4);
	GLuint img5 = glTexImageTGAFile("images/num5.tga", &numWidth, &numHeight); // 5
	numbers.push_back(img5);
	GLuint img6 = glTexImageTGAFile("images/num6.tga", &numWidth, &numHeight); // 6
	numbers.push_back(img6);
	GLuint img7 = glTexImageTGAFile("images/num7.tga", &numWidth, &numHeight); // 7
	numbers.push_back(img7);
	GLuint img8 = glTexImageTGAFile("images/num8.tga", &numWidth, &numHeight); // 8
	numbers.push_back(img8);
	GLuint img9 = glTexImageTGAFile("images/num9.tga", &numWidth, &numHeight); // 9
	numbers.push_back(img9);
}

void Level::draw(){
	glDrawSprite(LevelTex, LevelXPos, LevelYPos, LevelWidth, LevelHeight);

	if(level > 9){
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit2XPos, digitsYPos, digitWidth, numHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit1XPos, digitsYPos, digitWidth, numHeight);
	} else{
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit2XPos, digitsYPos, digitWidth, numHeight);
	}
}

void Level::increaseLevelCount(int amt){
	if(amt > 0){
		level += amt;
		gameData->level = level;
	}
}

void Level::decreaseLevelCount(int amt){
	if(amt > 0){
		int n = level - amt;
		if(n >= 0){
			level = n;
			gameData->level = n;
		}else{
			level = 0;
			gameData->level = 0;	
		}
	}
}

// With regards to level, returns the integer in the ones place
int Level::getDigitOne(){
	return level % 10;
}

// With regards to level, returns the integer in the tens place
int Level::getDigitTwo(){
	return (level % 100) / 10;
}

std::string Level::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "level = " << level << "\n";

	return oss.str();
}