#include"BackgroundDef.h"
#include<cmath>

// **** Frank Mock CS134  Spring 2017 ****

using std::ostringstream;

enum TileIDs { GRASS_00, GRASS_01, GRASS_02, GRASS_03, GRASS_04, 
			   GRASS_05, GRASS_06, GRASS_07, GRASS_08, GRASS_09,
			   GRASS_10, FLOWER_GRASS, BOULDER, ROCKS, GRASS_14,
			   GRASS_15, GRASS_16, GRASS_17, GRASS_18, GRASS_19,
			   ROCK_20, PILLAR_21, PILLAR_22, TOPLEFTCORNER};

BackgroundDef::BackgroundDef(Camera *cam, Game_Data &aGameData):camera(*cam){
	gameData = &aGameData;
	x = 0;
	y = 0;
	xStart = 0;
	xEnd = 40;
	yStart = 0;
	yEnd = 40;
	tileWidth = 32;
	tileHeight = 32;
	width = 40;  // tilemap width
	height = 40; // tilemap height
	worldWidth = tileWidth * width;
	worldHeight = tileHeight * height;
	tiles = new int[width * height](); // initialize with all zeros
	loadMap();
	loadImages();
	startScreenWidth = 650;
	startScreenHeight = 650;

	startScreenTex = glTexImageTGAFile("images/start_screen.tga", &startScreenWidth, &startScreenWidth);
}

void BackgroundDef::loadImages(){

	GLuint imageTex5 = glTexImageTGAFile("images/gr05.tga", &tileWidth, &tileHeight);  // 0
	imageTexList.push_back(imageTex5);
	GLuint imageTex10 = glTexImageTGAFile("images/gr10.tga", &tileWidth, &tileHeight); // 1
	imageTexList.push_back(imageTex10);
	GLuint imageTex11 = glTexImageTGAFile("images/gr11.tga", &tileWidth, &tileHeight); // 2
	imageTexList.push_back(imageTex11);
	GLuint imageTex12 = glTexImageTGAFile("images/gr12.tga", &tileWidth, &tileHeight); // 3
	imageTexList.push_back(imageTex12);
	GLuint imageTex13 = glTexImageTGAFile("images/gr13.tga", &tileWidth, &tileHeight); // 4
	imageTexList.push_back(imageTex13);
	GLuint imageTex14 = glTexImageTGAFile("images/gr14.tga", &tileWidth, &tileHeight); // 5
	imageTexList.push_back(imageTex14);
	GLuint imageTex15 = glTexImageTGAFile("images/gr15.tga", &tileWidth, &tileHeight); // 6
	imageTexList.push_back(imageTex15);
	GLuint imageTex16 = glTexImageTGAFile("images/gr16.tga", &tileWidth, &tileHeight); // 7
	imageTexList.push_back(imageTex16);
	GLuint imageTex17 = glTexImageTGAFile("images/gr17.tga", &tileWidth, &tileHeight); // 8
	imageTexList.push_back(imageTex17);
	GLuint imageTex18 = glTexImageTGAFile("images/gr18.tga", &tileWidth, &tileHeight); // 9
	imageTexList.push_back(imageTex18);
	GLuint imageTex04 = glTexImageTGAFile("images/gr04.tga", &tileWidth, &tileHeight); // 10
	imageTexList.push_back(imageTex04);
	GLuint flowers = glTexImageTGAFile("images/flowers.tga", &tileWidth, &tileHeight); // 11
	imageTexList.push_back(flowers);
	GLuint boulder = glTexImageTGAFile("images/boulder.tga", &tileWidth, &tileHeight); // 12
	imageTexList.push_back(boulder);
	GLuint rocks = glTexImageTGAFile("images/rocks.tga", &tileWidth, &tileHeight); // 13
	imageTexList.push_back(rocks);
}

/*
* tile_width = tile_height = 32 px
*
* x = floor( x_pos / tile_width )
* y = floor( y_pos / tile_height )
* width = width in tiles = 40
* returns a code value from the tiles array
* This method calculates an array index using the parameters passed 
* which are a calculated x and y
*/
int BackgroundDef::getTileCode(int x, int y){
	return tiles[y * width + x];
}


// Load the tile map 40 x 40 grid of tiles
void BackgroundDef::loadMap(){

	   // level 1
	   int data [] =   //5                //10                //15                //20                //25                //30                //35                //40
	   {2310, 1311, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1311, 1311, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211, 1211,
        1330,  100,  200,  200,  200,  200,  300, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1211, 1311, 1311, 1211, 1211, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1330,  400,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1211, 1311, 1211, 1211, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231,  400,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1211, 1211, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231,  700,  800,  800,  800,  800,  900, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  100,  200,  200,  300, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500, 1000,  200,  200,  200,  300, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500, 1000,  200,  200,  200,  300, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
        1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
        1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00,  700,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  900, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1221,
        1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1321,
		1331, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1321,
		1331, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1221,
		1231, 1241, 00, 00, 00,  100,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  200,  300, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
        1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00,  400,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  500,  600, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
        1231, 00, 00, 00, 00,  700,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  800,  900, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
        1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  100,  200,  200,  200,  200,  300, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  400,  500,  500,  500,  500,  600, 1221,
		1231, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241,  400,  500,  500,  500,  500,  600, 1221,
        1231, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1241, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1241, 1241,  400,  500,  500,  500,  500,  600, 1221,
		1331, 1241, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1301, 1301, 1241, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1241, 1341, 1341, 1241,  700,  800,  800,  800,  800,  900, 1221,
        1301, 1301, 1201, 1201,1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1301, 1301, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1301, 1301, 1301, 1201, 1201, 1201, 1201, 1201, 1201, 1201, 1221};

	   int size = 1600;

	   for (int i = 0; i < size; ++i)
		{
			tiles[i] = data[i];
		}

}

void BackgroundDef::draw(){

	if(gameData->currentGameState == gameData->START){
		glDrawSprite(startScreenTex, 0, 0, startScreenWidth, startScreenHeight);
	}else{

	int tile_width = 32; // Each tile is 32 pixels wide
	int tile_height = 32; // Each tile is 32 pixels high
	int tile_x = int(floor(float(camera.getX()/tile_width)));  // The x position of first tile to draw
	int tile_y = int(floor(float(camera.getY()/tile_height))); // The y position of first tile to draw
	int camWidthInTiles = 22;  // The Camera width in tiles
	int camHeightInTiles = 22; // The Camera height in tiles

	// Only draw tiles in camera's view
	for(int x = tile_x; x < tile_x + camWidthInTiles; x++){
		for(int y = tile_y; y < tile_y + camHeightInTiles; y++){
			int tile_code = getTileCode(x, y);
			int id = getTileID(tile_code);
			switch(id){
			case GRASS_00:
				glDrawSprite(imageTexList.at(GRASS_00), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_01:
				glDrawSprite(imageTexList.at(GRASS_01), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_02:
				glDrawSprite(imageTexList.at(GRASS_02), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_03:
				glDrawSprite(imageTexList.at(GRASS_03), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_04:
				glDrawSprite(imageTexList.at(GRASS_04), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_05:
				glDrawSprite(imageTexList.at(GRASS_05), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_06:
				glDrawSprite(imageTexList.at(GRASS_06), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_07:
				glDrawSprite(imageTexList.at(GRASS_07), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_08:
				glDrawSprite(imageTexList.at(GRASS_08), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_09:
				glDrawSprite(imageTexList.at(GRASS_09), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case GRASS_10:
				glDrawSprite(imageTexList.at(GRASS_10), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case FLOWER_GRASS:
				glDrawSprite(imageTexList.at(FLOWER_GRASS), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case BOULDER:
				glDrawSprite(imageTexList.at(BOULDER), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case ROCKS:
				glDrawSprite(imageTexList.at(ROCKS), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			case TOPLEFTCORNER:
				this->x = x * tile_width - this->camera.getXOffSet();
				this->y = y * tile_height - this->camera.getYOffSet();
				glDrawSprite(imageTexList.at(ROCKS), x * tile_width - this->camera.getXOffSet(), y * tile_height - this->camera.getYOffSet(), tileWidth, tileHeight);
				break;
			default:
				break;
			}
		}
	}
	}
}

/* Extracts and returns a tile ID from a given tile code
*  The tile ID are the left most digits of the code
*
*  Examples: for a code of 2311, 23 is the Tile ID and 11 is the collidable info
*            for a code of 500, 5 is the Tile ID and 00 is the collidable info
*/
int BackgroundDef::getTileID(int tile_code){
	int a =  int(floor(float((tile_code / 1000))));
	int b = tile_code % 1000;
	int c = int(floor(float(b / 100)));

	return (a * 10) + c;
}

// Extracts the collidable direction from a code
int BackgroundDef::getCollidableDirection(AABB box){
	int x = (box.x)*2;
	int y = (box.y)*2;
	int code = getTileCode(x/32, y/32);
	int a = code % 100;
	return int(a/10);
}

/* For a given tile code returns true if it's collidable
*  false otherwise.
*  For a any tile code, the right-most digit is identifies the tile as collidable
*  1 = collidable
*  0 = not collidable
*/
bool BackgroundDef::collidableTile(int code){
	if(code % 10 == 1)
		return true;
	else
		return false;
}

/* Takes an AABB box and indentifies if there is a collision
*  with a collidable background tile
*/
bool BackgroundDef::collision(AABB box){
	int code1 = getTopLeftTileCode(box, "sprite");     // check top left
	int code2 = getTopRightTileCode(box, "sprite");    // check top right
	int code3 = getBottomLeftTileCode(box, "sprite");  // check bottom left
	int code4 = getBottomRightTileCode(box, "sprite"); // check bottom right

	if(collidableTile(code1) || collidableTile(code2) || collidableTile(code3)  || collidableTile(code4))
		return true;
	else
		return false;
}

/* Takes the player's AABB box and indentifies if there is a collision
*  with a collidable background tile
*/
bool BackgroundDef::playerBackgroundCollsion(AABB box){

	int code1 = getTopLeftTileCode(box, "player");     // check top left
	int code2 = getTopRightTileCode(box, "player");    // check top right
	int code3 = getBottomLeftTileCode(box, "player");  // check bottom left
	int code4 = getBottomRightTileCode(box, "player"); // check bottom right

	if(collidableTile(code1) || collidableTile(code2) || collidableTile(code3)  || collidableTile(code4))
		return true;
	else
		return false;
}

// Returns the overlap of sprite box and tile
int BackgroundDef::getBottomY_Overlap(AABB box){
	int playerY = (box.y)*2;
	int tileY = int(playerY/32)*32;
	int a = playerY - tileY;
	return tileHeight - a;
}

/*
* Returns the tile code of the tile a sprites top left corner is intersecting
* x = floor( x_pos / tile_width )
* y = floor( y_pos / tile_height )
* width = width in tiles = 40
*/
int BackgroundDef::getTopLeftTileCode(AABB box, std::string type){
	int overlap = 45; // Amount sprites are allowed to overlap tile
	int x_overlap = 10;
	if(type == "player"){
		// *** player's x and y are half of all other sprites
		return tiles[int((floor(float((box.y * 2 + overlap)/tileWidth)) * width + int(floor(float((box.x * 2 + x_overlap)/tileWidth)))))];
	}else{
		return tiles[int((floor(float((box.y + overlap)/tileWidth)) * width + int(floor(float((box.x + x_overlap) / tileWidth)))))];
	}
}

/*
* Returns the tile code of the tile a sprites top right corner is intersecting
* x = floor( x_pos / tile_width )
* y = floor( y_pos / tile_height )
* width = width in tiles = 40
*/
int BackgroundDef::getTopRightTileCode(AABB box, std::string type){
	int overlap = 45; // Amount sprites are allowed to overlap tile
	int x_overlap = 10;
	if(type == "player"){
		// *** player's x and y are half of all other sprites
		return tiles[int((floor(float((box.y * 2 + overlap)/tileWidth)) * width + int(floor(float((box.x * 2 - x_overlap)/tileWidth))))) + 1];
	}else{
		return tiles[int((floor(float((box.y + overlap)/tileWidth)) * width + int(floor(float((box.x - x_overlap)/ tileWidth))))) + 1];
	}
}

/*
* Returns the tile code of the tile a sprites bottom right corner is intersecting
* x = floor( x_pos / tile_width )
* y = floor( y_pos / tile_height )
* width = width in tiles = 40
*/
int BackgroundDef::getBottomRightTileCode(AABB box, std::string type){
	int overlap = 10; // Amount sprites are allowed to overlap tile
	if(type == "player"){
		// *** player's x and y are half of all other sprites
		return tiles[int((floor(float((box.y * 2 + box.h)/tileWidth)) * width + int(floor(float((box.x * 2 - overlap)/tileWidth))))) + 1];
	}else{
		return tiles[int((floor(float((box.y + box.h)/tileWidth)) * width + int(floor(float((box.x - overlap) / tileWidth))))) + 1];
	}
}

/*
* Returns the tile code of the tile a sprites bottom left corner is intersecting
* x = floor( x_pos / tile_width )
* y = floor( y_pos / tile_height )
* width = width in tiles = 40
*/
int BackgroundDef::getBottomLeftTileCode(AABB box, std::string type){
	int overlap = 10; // Amount sprites are allowed to overlap tile
	if(type == "player"){
		// *** player's x and y are half of all other sprites
		return tiles[int((floor(float((box.y * 2 + box.h)/tileWidth)) * width + int(floor(float((box.x * 2 + overlap)/tileWidth)))))];
	}
	else{
		return tiles[int((floor(float((box.y + box.h)/tileWidth)) * width + int(floor(float(box.x/tileWidth)))))];
	}
}


int BackgroundDef::getBackgroundX() const{
	return this->x;
}

int BackgroundDef::getBackgroundY() const{
	return this->y;
}

std::string BackgroundDef::to_string() const{
	ostringstream oss;
	oss << "Background x = " << x << "\n"
		<< "Background y = " << y << "\n";
	return oss.str();
}