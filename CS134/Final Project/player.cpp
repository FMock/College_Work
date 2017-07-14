#include "player.h"
#include"GameConstants.h"


// Frank Mock CS134
// Player is the main sprite of the game

using std::ostringstream;
typedef GameConstants GC;

enum facing{LEFT, RIGHT, UP, DOWN };

Player::Player(int x, int y, int w, int h, AnimationData &aData, BackgroundDef *background, Game_Data &aGameData):Sprite(x, y, w, h){
	type = "player";
	hp = 20;
	box.setW(characterSize[0]);
	box.setH(characterSize[1]);
	animFPS = 8.0f;
	direction = 0;
	stopped = true;
	isShooting = false;
	backgroundTileCollision = false;
	animData = aData;
	background = background;
	prevAnim = 0;
	gameData = &aGameData;
	gameData->player_hp = hp;
	gameData->player_direction = direction;
	isHit = false;
}

Player::~Player(){}

void Player::updateAnim(float deltaTime){
	if(isShooting && direction == 0)
		changeAnim(12); // shooting and facing left
	if(isShooting && direction == 1)
		changeAnim(13); // shooting and facing right
	if(isShooting && direction == 3)
		changeAnim(14); // shooting and facing down (front facing)

	if(isHit){
		hp -= 1;
		gameData->player_hp = hp;
		// Do something to react to hit
		if(direction == RIGHT)
			changeAnim(8); // #8 is the right hit animation
		else if(direction == LEFT)
			changeAnim(9); // #9 is the left hit animation
		else if(direction == UP)
			changeAnim(10); // #10 is the back facing (aka UP) hit animation
		else if(direction == DOWN)
			changeAnim(11); // #11 is the front facing (aka DOWN) hit animation
	}

	// Deal with collisions with background tiles
	if(backgroundTileCollision){
		if(direction == RIGHT){
			prev_change_x = change_x;
			change_x = 0; //stop player from going out of bounds right
			characterPos[0] -= 1;
		}else if(direction == LEFT){
			prev_change_x = change_x;
			change_x = 0; //stop player from going out of bounds left
			characterPos[0] += 1;
		}else if(direction == UP){
			prev_change_y = change_y;
			change_y = 0; //stop player from going out of bounds up
			characterPos[1] += 1;
		}else{
			prev_change_y = change_y;
			change_y = 0; //stop player from going out of bounds down
			characterPos[1] -= 1;
		}
	}

	isHit = false;
	isShooting = false;
	backgroundTileCollision = false;

	if(characterPos[0] >  GC::WINDOW_WIDTH - characterSize[0]){
		prev_change_x = change_x;
		change_x = 0; //stop player from going out of bounds right
		characterPos[0] -= 1;
	}

	if(characterPos[0] < 0){
		prev_change_x = change_x;
		change_x = 0; //stop player from going out of bounds left
		characterPos[0] += 1;
	}

	if(characterPos[1] < 0){
		prev_change_y = change_y;
		change_y = 0; //stop player from going out of bounds up
		characterPos[1] += 1;
	}

	if(characterPos[1] > GC::WINDOW_HEIGHT - characterSize[1]){
		prev_change_y = change_y;
		change_y = 0; //stop player from going out of bounds down
		characterPos[1] -= 1;
	}

	characterPos[0] += change_x * deltaTime;
	box.setX(characterPos[0]);
	characterPos[1] += change_y * deltaTime;
	box.setY(characterPos[1]);

	// Make player's info available to others
	gameData->recordPlayersXPos(characterPos[0]);
	gameData->recordPlayersYPos(characterPos[1]);
	gameData->recordPlayerDirection(direction);


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
}

void Player::changeAnim(int num){
	animNum = num;
	// The active animation is now at from 0 and 0.0f time
	frameNum = 0;
	frameTime = 0.0f;
	// Set active image, which is just the starting frame
	int imageNum = animData.frameInfo.at(animNum).startFrame;
	image = animData.images.at(imageNum);
}


void Player::moveLeft(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0; 
	change_x = -speedX;
	direction = LEFT;
}

void Player::moveRight(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0; 
	prev_change_x = change_x;
	change_x = speedX;
	direction = RIGHT;
}

void Player::moveUp(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = -speedY;
	direction = UP;
}

void Player::moveDown(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = speedY;
	direction = DOWN;
}

void Player::stop(){
	stopped = true;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = 0;
}

void Player::collision(Sprite &sprite){
	if(sprite.type == "skeleton"){
		if(direction == LEFT){
			prev_change_x = change_x;
			change_x = speedX;
		}
		if(direction == RIGHT){
			prev_change_x = change_x;
			change_x = -speedX;
		}
		if(direction == UP){
			prev_change_y = change_y;
			change_y = speedY;
		}
		if(direction == DOWN){
			prev_change_y = change_y;
			change_y = -speedY;
		}
	}else if(sprite.type == "pumpkin"){
			if(direction == LEFT){
			prev_change_x = change_x;
			change_x = speedX;
		}
		if(direction == RIGHT){
			prev_change_x = change_x;
			change_x = -speedX;
		}
		if(direction == UP){
			prev_change_y = change_y;
			change_y = speedY;
		}
		if(direction == DOWN){
			prev_change_y = change_y;
			change_y = -speedY;
		}
	}
}

int Player::getDirection(){
	return direction;
}


std::string Player::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "Sprite Type = " <<  type << "\n"
		<< "backgroundTileCollision = " << backgroundTileCollision << "\n"
		<< "isShooting = " << isShooting << "\n"
		<< "Direction = " << direction << "\n"
		<< "Stopped = " << stopped << "\n"
		<< "isHit = " << isHit << "\n"
		<< "AABB x = " << box.x << "\n"
		<< "AABB y = " << box.y << "\n"
		<< "AABB w = " << box.w << "\n"
		<< "AABB h = " << box.h << "\n"
		<< "xPos = " << getXPos() << "\n"
		<< "YPos = " << getYPos() << "\n"
		<< "hp = " << hp << "\n"
		<< "*************************\n";
	return oss.str();
}
