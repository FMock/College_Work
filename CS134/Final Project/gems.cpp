#include "gems.h"


Gems::Gems(Game_Data &aGameData){
	gameData = &aGameData;
	gem_count = 0;
	gameData->gem_count = gem_count;
	gemsWidth = 95;
	gemsHeight = 22;
	gemsXPos = 350;
	gemsYPos = 60;
	numWidth = 19;
	numHeight = 22;
	digitWidth = 19;
	digitsYPos = gemsYPos;
	digit2XPos = 460;
	digit1XPos = digit2XPos + digitWidth;
	gemsTex = glTexImageTGAFile("images/gems.tga", &gemsWidth, &gemsHeight);
	loadImages();
}

void Gems::loadImages(){
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

void Gems::draw(){
	glDrawSprite(gemsTex, gemsXPos, gemsYPos, gemsWidth, gemsHeight);

	if(gem_count > 9){
		// Draw tens place (digit 2)
		glDrawSprite(numbers.at(getDigitTwo()), digit2XPos, digitsYPos, digitWidth, numHeight);
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit1XPos, digitsYPos, digitWidth, numHeight);
	} else{
		// Draw ones place (digit 1)
		glDrawSprite(numbers.at(getDigitOne()), digit2XPos, digitsYPos, digitWidth, numHeight);
	}
}

void Gems::increaseGemCount(int amt){
	if(amt > 0){
		gem_count += amt;
		gameData->gem_count = gem_count;
	}
}

void Gems::decreaseGemCount(int amt){
	if(amt > 0){
		int n = gem_count - amt;
		if(n >= 0){
			gem_count = n;
			gameData->gem_count = n;
		}else{
			gem_count = 0;
			gameData->gem_count = 0;	
		}
	}
}

// With regards to gem_count, returns the integer in the ones place
int Gems::getDigitOne(){
	return gem_count % 10;
}

// With regards to gem_count, returns the integer in the tens place
int Gems::getDigitTwo(){
	return (gem_count % 100) / 10;
}

std::string Gems::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "gem_count = " << gem_count << "\n";

	return oss.str();
}