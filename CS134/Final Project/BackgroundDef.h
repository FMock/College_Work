#ifndef BACKGROUNDDEF_H
#define BACKGROUNDDEF_H

#include<GL/glew.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include"DrawUtils.h"
#include"camera.h"
#include"AABB.h"
#include"game_data.h"

class BackgroundDef{

public:
	BackgroundDef(Camera *cam, Game_Data &aGameData);
	Camera &camera;
	Game_Data *gameData;
	GLuint startScreenTex;
	int startScreenWidth;
	int startScreenHeight;
	int getTileID(int); // Extracts the tile ID from a tile code
	int getCollidableDirection(AABB);
	bool collidableTile(int);
	bool collision(AABB box);
	bool playerBackgroundCollsion(AABB);
	int getBottomY_Overlap(AABB);
	int getTileCode(int x, int y);

	// These are for tile collison detection 
	int getTopLeftTileCode(AABB, std::string);
	int getTopRightTileCode(AABB, std::string);
	int getBottomRightTileCode(AABB box, std::string);
	int getBottomLeftTileCode(AABB box, std::string);

	void draw();
	void loadMap();
	void loadImages();
	int x, y;
	int xStart, xEnd, yStart, yEnd;
	int getBackgroundX() const;
	int getBackgroundY() const;
	int width;
	int height;
	int *tiles;
	int tileWidth;
	int tileHeight;
	int worldWidth;
	int worldHeight;
	std::vector<GLuint> imageTexList;
	std::string to_string() const;

};

#endif