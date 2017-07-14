#ifndef CAMERA_H
#define CAMERA_H
#include<string>
#include<sstream>
#include"GameConstants.h"
#include"AABB.h"
// Frank Mock CS134
class Camera{

public:
	AABB box;
	AABB getBox();
	int x;
	int y;
	int getX();
	int getY();
	float xOffSet;
	float yOffSet;
	Camera();
	Camera(float xOffSet, float yOffSet);
	void update(float deltaTime);
	void move(float xAmt, float yAmt, float deltaTime);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stop();
	int change_x;
	int change_y;
	// speed of the sprite Pixels/Sec
	float speedX;
	float speedY;
	void centerOnPlayer(float x, float y, float dt);
	float getXOffSet();
	float getYOffSet();
	void setXOffSet(float);
	void setYOffSet(float);
	std::string to_string() const;
};

#endif