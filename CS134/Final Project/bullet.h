#pragma once
#ifndef BULLET_H
#define BULLET_H
#include"Sprite.h"
#include"GameConstants.h"

// Frank Mock CS134

class Bullet : public Sprite{
public:
	Bullet():Sprite(){}
	Bullet(std::string path, int x, int y): Sprite(path, x, y){}
	void initialize(int direction, int speed);
	bool outOfGameWorld;
	bool isHit;
	int direction;
	void setDirection(int);
	void update(float deltaTime);
	void draw(int x, int y); // x and y is the camera's x and y
	std::string to_string() const;
};

#endif