#ifndef SPRITE_H
#define SPRITE_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<cmath>
#include"DrawUtils.h"
#include"AABB.h"
#include"GameConstants.h"

// Frank Mock CS134

class Sprite{
public:
	Sprite();
	Sprite(int, int, int, int);
	Sprite(std::string, int, int);
	~Sprite();
	char *type;
	AABB box;
	AABB& getBox();
	GLuint image;
	virtual void draw();
	virtual void update(float);
	void setXPos(int);
	void setYPos(int);
	void setXSpeed(int);
	void setYSpeed(int);
	void setWidth(int);
	void setHeight(int);
	int getXPos() const;
	int getYPos() const;
	int x;
	int y;
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveUp();
	virtual void moveDown();
	virtual void stop();
	virtual std::string to_string() const;
protected:
	int *characterSize;
	float *characterPos;
	int change_x;
	int change_y;
	float speedX;
	float speedY;
};

#endif