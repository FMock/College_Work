#include "bullet.h"

// Frank Mock CS134

typedef GameConstants GC;

enum Direction{LEFT, RIGHT, UP, DOWN };

void Bullet::update(float deltaTime){

	box.setX(abs(characterPos[0]));
	box.setY(abs(characterPos[1]));

	if(direction == 0){
		characterPos[0] -= speedX * deltaTime;
		characterPos[1] += speedY;
	}else if(direction == 1){
		characterPos[0] += speedX * deltaTime;
		characterPos[1] += speedY;
	}else if(direction == 2){
		characterPos[0] += speedX;
		characterPos[1] -= speedY * deltaTime;
	}else{
		characterPos[0] += speedX;
		characterPos[1] += speedY * deltaTime;
	}

	// Check if the bullet is out of the game world
	if(characterPos[0] < 0 || characterPos[0] > GC::WORLD_WIDTH || 
	   characterPos[1] < 0 || characterPos[1] > GC::WORLD_HEIGHT)
		outOfGameWorld = true;
	if(isHit)
		outOfGameWorld = true;
}


// x and y should be the camera's x and y
void Bullet::draw(int x, int y){
	glDrawSprite(image,  characterPos[0] - x, characterPos[1] - y, characterSize[0], characterSize[1]);
}

void Bullet::initialize(int direction, int speed){
	outOfGameWorld = false;
	isHit = false;
	this->direction = direction;

	if(direction == LEFT || direction == RIGHT){
		this->speedX = speed;
		this->speedY = 0;
	}else{
		this->speedX = 0;
		this->speedY = speed;
	}
}

void Bullet::setDirection(int d){
	this->direction = d;
}


std::string Bullet::to_string() const{
	std::ostringstream oss;
	oss << "Bullet*************\n"
		<< "Direction = " << direction << "\n"
		<< "outOfGameWorld = " << outOfGameWorld << "\n"
		<< "AABB x = " << box.x << "\n"
		<< "AABB y = " << box.y << "\n"
		<< "AABB w = " << box.w << "\n"
		<< "AABB h = " << box.h << "\n"
		<< "xPos = " << getXPos() << "\n"
		<< "YPos = " << getYPos() << "\n"
		<< "END Bullet*********\n";
	return oss.str();
}