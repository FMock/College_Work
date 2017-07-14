#include "gem.h"
#include"GameConstants.h"

/*
* Gem.cpp - Frank Mock CS134
*/

using std::ostringstream;
typedef GameConstants GC;

enum facing{LEFT, RIGHT, UP, DOWN };
enum behavior{NO_MOVE, ROAM, ATTACK};

// Definition of static member variable
int Gem::numGems = 0;

Gem::Gem(int x, int y, int w, int h, 
	                       AnimationData &aData, Timer &atimer, Game_Data &aGameData):Sprite(x, y, w, h){
	type = "gem";
	collieded = false;
	backgroundTileCollision = false;
	isDead = false;
	isHit = false;
	timeReset = false;
	box.setW(characterSize[0]);
	box.setH(characterSize[1]);
	animFPS = 8.0f;
	direction = 4; // Move direction is re-assigned by one of the movement methods
	stopped = true;
	animData = aData;
	behaviorChangeDuration = 18; // units are seconds
	timer = &atimer;
	gameData = &aGameData;
	time = timer->getElapsedTime();
	endTime = time + behaviorChangeDuration;
	choiceTime = 0; // time the next choice will be made
	choiceInterval = 2; // choice interval in seconds for attack behavior
	changeAnim(0);
	prevAnim = 0;
	changeBehavior(); // Sets currentBehavior
	characterSize[0] = 32;
	characterSize[1] = 32;
	Gem::numGems += 1;
}

Gem::~Gem(){
	//Gem::numGems -= 1; // Decrementing not working, why?
}

// x and y should be the camera's x and y
void Gem::draw(int x, int y){
	glDrawSprite(image,  characterPos[0] - x, characterPos[1] - y, characterSize[0], characterSize[1]);
}

void Gem::updateAnim(float deltaTime){
	// Advance the time
	clockTick();

	// Possibly change behavior
	if(time > endTime){
		changeBehavior(); // Randomly selects another behavior - it may be current behavior
		choiceTime = time + choiceInterval;
		// reset timer
		resetTimer();
	}
	
	// Only make new attack behavior movement choice at a regular interval in seconds - NOT EVERY FRAME!
	if(currentBehavior == ATTACK){
		if(time > choiceTime){
			attack();
			choiceTime = time + choiceInterval;
		}
	}

	if(isHit){
		// Do something like reduce hit points, change animation, or kill Skelton
		isDead = true;
	}
	isHit = false;


	collieded = false;
	backgroundTileCollision = false;

	//**** Prevent Gem from leaving game world **********

	if(characterPos[0] >  GC::WORLD_WIDTH - characterSize[0]){
		prev_change_x = change_x;
		change_x = 0; //stop Gem from going out of bounds right
		characterPos[0] -= 1;
		moveLeft();
	}

	if(characterPos[0] < 0){
		prev_change_x = change_x;
		change_x = 0; //stop Gem from going out of bounds left
		characterPos[0] += 1;
		moveRight();
	}

	if(characterPos[1] < 0){
		prev_change_y = change_y;
		change_y = 0; //stop Gem from going out of bounds up
		characterPos[1] += 1;
		moveDown();
	}

	if(characterPos[1] > GC::WORLD_HEIGHT - characterSize[1]){
		prev_change_y = change_y;
		change_y = 0; //stop Gem from going out of bounds up
		characterPos[1] -= 1;
		moveUp();
	}

	characterPos[0] += change_x * deltaTime;
	box.setX(characterPos[0]);
	characterPos[1] += change_y * deltaTime;
	box.setY(characterPos[1]);


	// update how long the current frame has been displayed
	frameTime += deltaTime;
	
	// This check determines if it is time ito change to the next frame
	if(frameTime > (1/animFPS)){
		// The number of frames to increment is the integral result of
		// frametime / (1 / animFPS), which is frameTime * animFPS
		frameNum += frameTime * animFPS;

		// Check if we've advanced past the last frame and must wrap
		if(frameNum >= animData.frameInfo.at(animNum).numFrames){
			frameNum = frameNum % animData.frameInfo.at(animNum).numFrames;
		}

		// Update the active image
		int imageNum = animData.frameInfo.at(animNum).startFrame + frameNum;
		image = animData.images.at(imageNum);

		frameTime = fmod(frameTime, 1 / animFPS);
	}

	timeReset = false;
}

/*
* Randonmly selects another behavior. More likley to pick some behaviors over others
* Three behaviors, each with an assigned percentage
* NO_MOVE = 15%, ROAM = 5%, ATTACK = 80%
*/
void Gem::changeBehavior(){

	// generate random int between 0 and 99
	int randInt = rand() % 100;
	
	if(randInt < 99){
		// Hold current position
		currentBehavior = NO_MOVE;
		stop();
	}else if(randInt > 99){
		// Attack
		currentBehavior = ATTACK; // Attack is really just move towards player
		attack();

	}else{
		//Random Roam
		currentBehavior = ROAM;
		int i = rand() % 4;

		if(i == 0){
			moveLeft();
		}else if(i == 1){
			moveRight();
		}else if(i == 2){
			moveUp();
		}else if(i == 3){
			moveDown();
		}
	}
}

void Gem::setTime(int t){
	time = t;
}

void Gem::clockTick(){
	time = timer->getElapsedTime();
}

void Gem::resetTimer(){
	time = timer->getElapsedTime();
	endTime = time + behaviorChangeDuration;
	timeReset = true;
}

void Gem::changeAnim(int num){
	animNum = num;
	// The active animation is now at from 0 and 0.0f time
	frameNum = 0;
	frameTime = 0.0f;
	// Set active image, which is just the starting frame
	int imageNum = animData.frameInfo.at(animNum).startFrame;
	image = animData.images.at(imageNum);
}

// Attack is moving the Gem in the general direction
// of the player
void Gem::attack(){
		

}


void Gem::moveLeft(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0;
	prev_change_x = change_x;
	change_x = -speedX;
	direction = LEFT;
	changeAnim(0);
}

void Gem::moveRight(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0;
	prev_change_x = change_x;
	change_x = speedX;
	direction = RIGHT;
	changeAnim(0);
}

void Gem::moveUp(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = -speedY;
	direction = UP;
	changeAnim(0);
}

void Gem::moveDown(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = speedY;
	direction = DOWN;
	changeAnim(0);
}

void Gem::stop(){
	stopped = true;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = 0;
	changeAnim(0);
}

void Gem::collision(Sprite &sprite){
	collieded = true;
	if(sprite.type == "player"){
		if(direction == LEFT){
			characterPos[0] += 2;
		}
		if(direction == RIGHT){
			characterPos[0] -= 2;
		}
		if(direction == UP){
			characterPos[1] += 2;
		}
		if(direction == DOWN){
			characterPos[1] -= 2;
		}
	}
}


std::string Gem::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "backgroundTileCollision = " << backgroundTileCollision << "\n"
		<< "collided = " << collieded << "\n" 
		<< "Sprite Type = " << type << "\n"
		<< "numGems = " << Gem::numGems << "\n"
		<< "isDead = " << isDead << "\n"
		<< "Direction = " << direction << "\n"
		<< "isHit = "  << isHit << "\n"
		<< "AABB x = " << box.x << "\n"
		<< "AABB y = " << box.y << "\n"
		<< "AABB w = " << box.w << "\n"
		<< "AABB h = " << box.h << "\n"
		<< "xPos = " << getXPos() << "\n"
		<< "YPos = " << getYPos() << "\n"
		<< "timeReset = " << timeReset << "\n"
		<< "time = " << time << "\n"
		<< "endTime = " << endTime << "\n"
		<< "currentBehavior = " << currentBehavior << "\n"
		<< "************************\n";
	return oss.str();
}
