#include"camera.h"

// Frank Mock CS134

typedef GameConstants GC;

Camera::Camera(){}

Camera::Camera(float xOffSet, float yOffSet){
	x = int(xOffSet);
	y = int(yOffSet);
	change_x = 0;
	change_y = 0;
	speedX = 1;
	speedY = 1;
	this->xOffSet = xOffSet;
	this->yOffSet = yOffSet;
	box = AABB();
	box.setX(this->x);
	box.setY(this->y);
	box.setW(GC::WINDOW_WIDTH);
	box.setH(GC::WINDOW_HEIGHT);
}

int Camera::getX(){
	return x;
}

int Camera::getY(){
	return y;
}

float Camera::getXOffSet(){
	return xOffSet;
}

float Camera::getYOffSet(){
	return yOffSet;
}

void Camera::setXOffSet(float f){
	this->xOffSet = f;
}

void Camera::setYOffSet(float f){
	this->yOffSet = f;
}

void Camera::moveLeft(){
	change_y = 0;
	change_x = -speedX;
}

void Camera::moveRight(){
	change_y = 0;
	change_x = speedX;
}

void Camera::moveUp(){
	change_y = -speedY;
	change_x = 0;
}

void Camera::moveDown(){
	change_y = speedY;
	change_x = 0;
}

void Camera::stop(){
	change_y = 0;
	change_x = 0;
}

void Camera::update(float deltaTime){
	this->x += change_x * deltaTime;
	this->y += change_y * deltaTime;
}

void Camera::move(float xAmt, float yAmt, float deltaTime){
	this->xOffSet += xAmt * deltaTime;
	this->yOffSet += yAmt * deltaTime;
}

/* Keep the player in the center of the camera
*  x is the x position of the player
*  y is the y position of the player
*/
void Camera::centerOnPlayer(float x, float y, float dt){
	this->x = x;
	this->y = y;
	box.x = this->x;
	box.y = this->y;
	this->xOffSet = x;
	this->yOffSet = y;
}

AABB Camera::getBox(){
	return box;
}

std::string Camera::to_string() const{
	std::ostringstream oss;
	oss << "Camera\n"
		<< "AABB x val = " << box.x << "\n"
		<< "AABB y val = " << box.y << "\n"
		<< "AABB w val = " << box.w << "\n"
		<< "AABB h val = " << box.h << "\n"
		<< "xPos = " << x << "\n"
		<< "YPos = " << y << "\n";
	return oss.str();
}