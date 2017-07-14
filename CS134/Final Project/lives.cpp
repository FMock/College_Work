#include "lives.h"


Lives::Lives(Game_Data &aGameData){
	gameData = &aGameData;
	lives_remaining = 3;
	gameData->lives_remaining = lives_remaining;
	livesWidth = 95;
	livesHeight = 22;
	livesXPos = 150;
	livesYPos = 60;
	numWidth = 19;
	numHeight = 22;
	digitWidth = 19;
	digitsYPos = livesYPos;
	digit2XPos = 260;
	digit1XPos = digit2XPos + digitWidth;
	livesTex = glTexImageTGAFile("images/lives.tga", &livesWidth, &livesHeight);
	loadImages();
}

void Lives::loadImages(){
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

void Lives::draw(){
	glDrawSprite(livesTex, livesXPos, livesYPos, livesWidth, livesHeight);

	if(lives_remaining > 9){
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit2XPos, digitsYPos, digitWidth, livesHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit1XPos, digitsYPos, digitWidth, livesHeight);
	} else{
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit2XPos, digitsYPos, digitWidth, livesHeight);
	}
}

void Lives::increaseLives(int amt){
	if(amt > 0){
		lives_remaining += amt;
		gameData->lives_remaining = lives_remaining;
	}
}

void Lives::decreaseLives(int amt){
	if(amt > 0){
		int n = lives_remaining - amt;
		if(n >= 0){
			lives_remaining = n;
			gameData->lives_remaining = n;
		}else{
			lives_remaining = 0;
			gameData->lives_remaining = 0;	
		}
	}
}

// With regards to lives_remaining, returns the integer in the ones place
int Lives::getDigitOne(){
	return lives_remaining % 10;
}

// With regards to lives_remaining, returns the integer in the tens place
int Lives::getDigitTwo(){
	return (lives_remaining % 100) / 10;
}

std::string Lives::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "Lives Remaining = " << lives_remaining << "\n";

	return oss.str();
}