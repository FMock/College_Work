#include "skeleton_red.h"
#include"GameConstants.h"

/* Frank Mock CS134 Spring 2017
 * Red Skeletons can take more damage and are faster than
 * regular skeletons.
 */

using std::ostringstream;
typedef GameConstants GC;

enum facing{LEFT, RIGHT, UP, DOWN};

// Definition of static member variable
int Skeleton_Red::numRedSkeletons = 0;

Skeleton_Red::Skeleton_Red(int x, int y, int w, int h, 
	                       AnimationData &aData, int moveDir):Sprite(x, y, w, h){
	type = "skeleton_red";
	setXSpeed(150); // Red skeletons are faster than regular skeletons
	setYSpeed(150); // Red skeletons are faster than regular skeletons
	hitPoints = 8;  // Red skeletons can take more damage than regular skeletons
	collieded = false;
	backgroundTileCollision = false;
	isDead = false;
	isHit = false;
	box.setW(characterSize[0]);
	box.setH(characterSize[1]);
	animFPS = 8.0f;
	direction = 1;
	stopped = true;
	animData = aData;
	changeAnim(0);
	prevAnim = 0;
	if(moveDir == 0)
		moveDown();
	else if(moveDir == 1)
		moveUp();
	else if(moveDir == 2)
		moveLeft();
	else if(moveDir == 3)
		moveRight();
	else
		stop();

	Skeleton_Red::numRedSkeletons += 1;
}

Skeleton_Red::~Skeleton_Red(){}

// x and y should be the camera's x and y
void Skeleton_Red::draw(int x, int y){
	glDrawSprite(image,  characterPos[0] - x, characterPos[1] - y, characterSize[0], characterSize[1]);
}

void Skeleton_Red::updateAnim(float deltaTime){
	
	if(isHit){
		hitPoints -= 1;
	}

	if(hitPoints < 0)
		isDead = true;

	isHit = false;

	// Deal with collisions with background tiles and other skeletons
	if(backgroundTileCollision || collieded){
		if(direction == RIGHT){
			prev_change_x = change_x;
			change_x = 0; //stop skeleton from going out of bounds right
			characterPos[0] -= 1;
			int randInt = rand() % 3; // Help make collsion reaction more random
			characterPos[1] += randInt;
			moveLeft();
		}else if(direction == LEFT){
			prev_change_x = change_x;
			change_x = 0; //stop skeleton from going out of bounds left
			characterPos[0] += 1;
			int randInt = rand() % 3; // Help make collsion reaction more random
			characterPos[1] += randInt;
			moveRight();
		}else if(direction == UP){
			prev_change_y = change_y;
			change_y = 0; //stop skeleton from going out of bounds up
			characterPos[1] += 1;
			int randInt = rand() % 3; // Help make collsion reaction more random
			characterPos[0] += randInt;
			moveDown();
		}else{
			prev_change_y = change_y;
			change_y = 0; //stop skeleton from going out of bounds down
			characterPos[1] -= 1;
			int randInt = rand() % 3; // Help make collsion reaction more random
			characterPos[0] += randInt;
			moveUp();
		}
	}

	collieded = false;
	backgroundTileCollision = false;

	if(characterPos[0] >  GC::WORLD_WIDTH - characterSize[0]){
		prev_change_x = change_x;
		change_x = 0; //stop skeleton from going out of bounds right
		characterPos[0] -= 1;
		moveLeft();
	}

	if(characterPos[0] < 0){
		prev_change_x = change_x;
		change_x = 0; //stop skeleton from going out of bounds left
		characterPos[0] += 1;
		moveRight();
	}

	if(characterPos[1] < 0){
		prev_change_y = change_y;
		change_y = 0; //stop skeleton from going out of bounds up
		characterPos[1] += 1;
		moveDown();
	}

	if(characterPos[1] > GC::WORLD_HEIGHT - characterSize[1]){
		prev_change_y = change_y;
		change_y = 0; //stop skeleton from going out of bounds down
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
}

void Skeleton_Red::changeAnim(int num){
	animNum = num;
	// The active animation is now at from 0 and 0.0f time
	frameNum = 0;
	frameTime = 0.0f;
	// Set active image, which is just the starting frame
	int imageNum = animData.frameInfo.at(animNum).startFrame;
	image = animData.images.at(imageNum);
}


void Skeleton_Red::moveLeft(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0;
	prev_change_x = change_x;
	change_x = -speedX;
	direction = LEFT;
	changeAnim(2);
}

void Skeleton_Red::moveRight(){
	stopped = false;
	prev_change_y = change_y;
	change_y = 0;
	prev_change_x = change_x;
	change_x = speedX;
	direction = RIGHT;
	changeAnim(3);
}

void Skeleton_Red::moveUp(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = -speedY;
	direction = UP;
	changeAnim(1);
}

void Skeleton_Red::moveDown(){
	stopped = false;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = speedY;
	direction = DOWN;
	changeAnim(0);
}

void Skeleton_Red::stop(){
	stopped = true;
	prev_change_x = change_x;
	change_x = 0;
	prev_change_y = change_y;
	change_y = 0;
}

void Skeleton_Red::collision(Sprite &sprite){
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


std::string Skeleton_Red::to_string() const{
	ostringstream oss;
	oss << "*************************\n"
		<< "Sprite Type = " << type << "\n"
		<< "backgroundTileCollision = " << backgroundTileCollision << "\n"
		<< "collieded = " << collieded << "\n"
		<< "numRedSkeletons = " << Skeleton_Red::numRedSkeletons << "\n"
		<< "isDead = " << isDead << "\n"
		<< "Direction = " << direction << "\n"
		<< "isHit = "  << isHit << "\n"
		<< "AABB x = " << box.x << "\n"
		<< "AABB y = " << box.y << "\n"
		<< "AABB w = " << box.w << "\n"
		<< "AABB h = " << box.h << "\n"
		<< "xPos = " << getXPos() << "\n"
		<< "YPos = " << getYPos() << "\n"
		<< "**************************\n";
	return oss.str();
}
