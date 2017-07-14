#pragma once
#ifndef GEM_H
#define GEM_H
#include"Sprite.h"
#include"AnimationData.h"
#include"GameConstants.h"
#include"timer.h"
#include"game_data.h"

/*
* Frank Mock CS134
* Gem - Player collects these to advance a level
*/

class Gem : public Sprite{
public:
	Gem():Sprite(){}
	Gem(int, int, int, int, AnimationData &animData, Timer &atimer, Game_Data &aGameData);
	~Gem();
	// All of the animation data (includes image files and frame data
	AnimationData animData;
	// Timer reference used to decide behavior changes
	Timer *timer;
	Game_Data *gameData;
	bool timeReset;
	int time;
	int endTime;
	int choiceTime; // time at which the next choice is made
	int choiceInterval; // time between choices
	int behaviorChangeDuration; // in seconds
	int currentBehavior; // an int that represents the behavior
	bool collieded;
	// True when collided with a background tile
	bool backgroundTileCollision;
	// The direction the character is facing
	int direction;
	// If x and y velocity is 0 player has stopped moving
	bool stopped;
	// True when hit by any enemy
	bool isHit;
	// If True remove Gem from game
	bool isDead;
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
	void setTime(int);
	void clockTick();
	void resetTimer();
	void changeBehavior();
	void updateAnim(float deltaTime);
	void draw(int, int);
	void changeAnim(int num);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stop();
	void attack();
	void collision(Sprite &sprite);
	std::string to_string() const;
	int prev_change_x;
	int prev_change_y;
	static int numGems;
};
#endif