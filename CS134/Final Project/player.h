#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include"Sprite.h"
#include"AnimationData.h"
#include"GameConstants.h"
#include"BackgroundDef.h"
#include"game_data.h"

/*
* Frank Mock CS134
* This is a class that represents the player's character.
*/

class Player : public Sprite{
public:
	Player():Sprite(){}
	Player(int, int, int, int, AnimationData &animData, BackgroundDef *background, Game_Data &aGameData);
	~Player();
	// All of the animation data (includes image files and frame data
	AnimationData animData;
	// Reference to background
	BackgroundDef *background;
	Game_Data *gameData;
	// Hit Points
	int hp;
	// The direction the character is facing
	int direction;
	// If x and y velocity is 0 player has stopped moving
	bool stopped;
	// True when hit by any enemy
	bool isHit;
	// True when shooting
	bool isShooting;
	// True when collided with a background tile
	bool backgroundTileCollision;
	// The particular animation that is active
	int animNum;
	// The previous animation
	int prevAnim;
	//The frame number of the active animation that's being displayed
	int frameNum;
	// The amount of time the current frame has been displayed
	float frameTime;
	// The FPS the animation is running at (24 FPS by default)
	float animFPS;
	void updateAnim(float deltaTime);
	void changeAnim(int num);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stop();
	void collision(Sprite &sprite);
	int getDirection();
	int prev_change_x;
	int prev_change_y;
	std::string to_string() const;
};

#endif