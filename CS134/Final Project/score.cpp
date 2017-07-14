#include "score.h"


Score::Score(Camera *cam, Game_Data &aGameData):camera(*cam){
	gameData = &aGameData;
	gameData->score = 0;
	score = 0;
	scoreWidth = 95;
	scoreHeight = 22;
	scoreXPos = 350;
	scoreYPos = 32;
	digitWidth = 22;
	digitsYPos = 32;
	digit5XPos = 460;
	digit4XPos = digit5XPos + digitWidth;
	digit3XPos = digit4XPos + digitWidth;
	digit2XPos = digit3XPos + digitWidth;
	digit1XPos = digit2XPos + digitWidth;
	scoreTex = glTexImageTGAFile("images/score.tga", &scoreWidth, &scoreHeight);
	loadImages();
}

void Score::increaseScore(int amt){
	if(amt > 0){
		score += amt;
		gameData->score = score;
	}
}

void Score::loadImages(){
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

void Score::draw(){
	glDrawSprite(scoreTex, scoreXPos, scoreYPos, scoreWidth, scoreHeight);

	if(score > 9999){
		// Draw digit in ten thousandths place (digit 5)
		glDrawSprite(numbers.at(getDigitFive()), digit5XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw digit in thousandths place (digit 4)
		glDrawSprite(numbers.at(getDigitFour()), digit4XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw hundredths place (digit 3)
		glDrawSprite(numbers.at(getDigitThree()), digit3XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit2XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit1XPos, digitsYPos, digitWidth, scoreHeight);
	}else if(score > 999){
		// Draw digit in thousandths place (digit 4)
		glDrawSprite(numbers.at(getDigitFour()), digit5XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw hundredths place (digit 3)
		glDrawSprite(numbers.at(getDigitThree()), digit4XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit3XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit2XPos, digitsYPos, digitWidth, scoreHeight);
	}else if(score > 99){
		// Draw digit in hundredths place (digit 3)
		glDrawSprite(numbers.at(getDigitThree()), digit5XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit4XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit3XPos, digitsYPos, digitWidth, scoreHeight);
	}else if(score > 9){
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit5XPos, digitsYPos, digitWidth, scoreHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit4XPos, digitsYPos, digitWidth, scoreHeight);
	} else{
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit5XPos, digitsYPos, digitWidth, scoreHeight);
	}
}

// Given a score, returns the integer in the ones place
int Score::getDigitOne(){
	return score % 10;
}

// Given a score, returns the integer in the tens place
int Score::getDigitTwo(){
	return (score % 100) / 10;
}

// Given a score, returns the integer in the hundredths place
int Score::getDigitThree(){
	return (score % 1000) / 100;
}

// Given a score, returns the integer in the thousandths place
int Score::getDigitFour(){
	return (score % 10000) / 1000;
}

// Given a score, returns the integer in the thousandths place
int Score::getDigitFive(){
	return score / 10000;
}

std::string Score::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "score = " << score << "\n";

	return oss.str();
}