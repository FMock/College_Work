#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<GL/glew.h>
#include<stdio.h>
#include<cstdlib>
#include<string>
#include<assert.h>
#include"GameConstants.h"
#include"DrawUtils.h"
#include"Sprite.h"
#include"player.h"
#include"skeleton.h"
#include"skeleton_red.h"
#include"bullet.h"
#include"hit.h"
#include"camera.h"
#include"BackgroundDef.h"
#include"AnimFrameData.h"
#include"AnimationData.h"
#include"AABB.h"
#include<vector>
#include"timer.h"
#include"game_data.h"
#include<stdio.h>
#include<time.h>
#include"game_state.h"
#include"KeyStates.h"
#include<fmod.hpp> // For Sound Functionality
#include"score.h"
#include"lives.h"
#include"gems.h"
#include"pumpkin.h"
#include"gem.h"
#include"level.h"


/*
	Frank Mock CS134 Spring 2017
*/
typedef GameConstants GC;

// Set this to true to make the game loop exit.
char shouldExit = 0;

// The previous frame's keyboard state.
unsigned char kbPrevState[SDL_NUM_SCANCODES] = { 0 };

// The current frame's keyboard state.
const unsigned char* kbState = NULL;

// Size of the sprite.
int spriteSize[2];

std::vector<GLuint> images;
std::vector<AnimFrameData> frameInfo;
AnimationData animData; //player animation data
Player player;
int spriteWidth = 32;
int spriteHeight = 64;

Game_Data gameData;

std::vector<GLuint> imagesSkeleton;
std::vector<AnimFrameData> frameInfoSkeleton;
AnimationData animDataSkeleton; //skeleton animation data

std::vector<GLuint> imagesSkeletonRed;
std::vector<AnimFrameData> frameInfoSkeletonRed;
AnimationData animDataSkeletonRed; //Red skeleton animation data

std::vector<GLuint> imagesHit;
std::vector<AnimFrameData> frameInfoHit;
AnimationData animDataHit; //Hit animation data

std::vector<GLuint> imagesPumpkin;
std::vector<AnimFrameData> frameInfoPumpkin;
AnimationData animDataPumpkin; //Pumpkin animation data

std::vector<GLuint> imagesGem;
std::vector<AnimFrameData> frameInfoGem;
AnimationData animDataGem; //Gem animation data

int NUM_GEMS = 14;
int MAX_GEMS = NUM_GEMS;
int NUM_PUMPKINS = 10;
int MAX_PUMPKINS = NUM_PUMPKINS;
int NUM_SKELETONS = 10;
int MAX_SKELETONS = NUM_SKELETONS;
int NUM_SKELETONS_RED = 8;
int MAX_SKELETONS_RED = NUM_SKELETONS_RED;

std::vector<Gem *> gemsVector = std::vector<Gem *>();
std::vector<Pumpkin *> pumpkins = std::vector<Pumpkin *>();
std::vector<Skeleton *> skeletons = std::vector<Skeleton *>();
std::vector<Skeleton_Red *> skeletons_red = std::vector<Skeleton_Red *>();

std::vector<Bullet *> bullets = std::vector<Bullet *>();
bool bulletFired = false;

std::vector<Hit *> hits = std::vector<Hit *>();

enum playerFacing{ LEFT, RIGHT, UP, DOWN };
enum currentAnimation{WALK_LEFT, WALK_RIGHT, WALK_UP, WALK_DOWN, LEFT_STOPPED, RIGHT_STOPPED, UP_STOPPED, DOWN_STOPPED};

// Timer to help game objects keep track of time in seconds
Timer timer;

int startGameTime = 10;

// To regulate frame rate
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0.0f;

float currentFiredTime = 0.0f;
float previousFiredTime = 0.0f;
float firedTime = 0.0f;

float currentHitTime = 0.0f;
float previousHitTime = 0.0f;

float currentEndTime = 0.0f;
float previousEndTime = 0.0f;

// To get keyboard state
const Uint8 *keyState;

// Camera
Camera *camera;
int speedX = 100;
int speedY = 100;

bool AABBIntersect(AABB, AABB);
bool PlayerIntersect(AABB, AABB);

// Keyboard tracking and Game State tracking
GameState gameState;
KeyStates keyStates;

// Image Overlays for game states such as Pause and End
int imgOverlayPos[2] = {0, 0};
int imgOverlaySize[2];
GLuint pauseOverlayTex;
GLuint endOverlayTex;

// For Sound
FMOD::System *fmod_sys;
FMOD::Sound *shoot; // For the shoot sound
FMOD::Sound *score_sound; // For the shoot sound
FMOD::Sound *ouch_sound; // sounds when player is hit
FMOD::Sound *gem_sound; // sounds when player collects gem
FMOD::Sound *level_up_sound; // sounds when player collects 20 gems

// Points of enemies
int gemPoints = 50;
int pumpkinPoints = 5;
int whiteSkeletonPoints = 10;
int redSkeletonPoints = 15;

bool levelUp = false;

int main(void)
{
	// Sound Setup
	FMOD_RESULT fmodResult = System_Create(&fmod_sys);
	fmod_sys->init(400, FMOD_INIT_NORMAL, 0);
	fmod_sys->createSound("sounds/shoot_sound.wav", FMOD_DEFAULT, 0, &shoot);
	fmod_sys->createSound("sounds/score_sound.wav", FMOD_DEFAULT, 0, &score_sound);
	fmod_sys->createSound("sounds/ouch.wav", FMOD_DEFAULT, 0, &ouch_sound);
	fmod_sys->createSound("sounds/gem_collected.wav", FMOD_DEFAULT, 0, &gem_sound);
	fmod_sys->createSound("sounds/level_up.wav", FMOD_DEFAULT, 0, &level_up_sound);

	// To track important game data
	gameData = Game_Data();

	// Initialize a game_state object to track the game states
	gameState = GameState(gameData);
	gameData.currentGameState = gameState.START;

	// Initialize KeyState Object
	keyStates = KeyStates();

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialize SDL. ErrorCode=%s\n", SDL_GetError());
		return 1;
	}

	// timer helps game objects track time in seconds
	timer = Timer(SDL_GetTicks());

	// Create the window and OpenGL context.
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_Window* window = SDL_CreateWindow(
		"Spring 2017 CS134 Final Project by Frank Mock",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		GC::WINDOW_WIDTH, GC::WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);
	if (!window) {
		fprintf(stderr, "Could not create window. ErrorCode=%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext(window);


	// Make sure we have a recent version of OpenGL.
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		fprintf(stderr, "Could not initialize glew. ErrorCode=%s\n", glewGetErrorString(glewError));
		SDL_Quit();
		return 1;
	}
	if (GLEW_VERSION_2_0) {
		fprintf(stderr, "OpenGL 2.0 or greater supported: Version=%s\n",
			glGetString(GL_VERSION));
	}
	else {
		fprintf(stderr, "OpenGL max supported version is too low.\n");
		SDL_Quit();
		return 1;
	}

	// Setup OpenGL state.
	glViewport(0, 0, GC::WINDOW_WIDTH, GC::WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, GC::WINDOW_WIDTH, GC::WINDOW_HEIGHT, 0, 0, 100);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//******* Player Animation Data ********************
	frameInfo.push_back(AnimFrameData(0, 3)); // Animation #0 walking left
	frameInfo.push_back(AnimFrameData(3, 3)); // Animation #1 walking right
	frameInfo.push_back(AnimFrameData(6, 3)); // Animation #2 walking up
	frameInfo.push_back(AnimFrameData(9, 3)); // Animation #3 walking down
	frameInfo.push_back(AnimFrameData(1, 1)); // Animation #4 standing still facing left
	frameInfo.push_back(AnimFrameData(4, 1)); // Animation #5 standing still facing right
	frameInfo.push_back(AnimFrameData(7, 1)); // Animation #6 standing still facing up
	frameInfo.push_back(AnimFrameData(10, 1)); // Animation #7 standing still facing down
	frameInfo.push_back(AnimFrameData(12, 1)); // Animation #8 Player hit (red)
	frameInfo.push_back(AnimFrameData(13, 1)); // Animation #9 Player hit left (red)
	frameInfo.push_back(AnimFrameData(14, 1)); // Animation #10 Player hit back (red)
	frameInfo.push_back(AnimFrameData(15, 1)); // Animation #11 Player hit front (red)
	frameInfo.push_back(AnimFrameData(16, 3)); // Animation #12 walking left shooting
	frameInfo.push_back(AnimFrameData(19, 3)); // Animation #13 walking right shooting
	frameInfo.push_back(AnimFrameData(22, 3)); // Animation #14 walking down shooting

	images.push_back(glTexImageTGAFile("images/left01.tga", &spriteSize[0], &spriteSize[1]));  // #0
	images.push_back(glTexImageTGAFile("images/left02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/left03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/right01.tga", &spriteSize[0], &spriteSize[1])); // #3
	images.push_back(glTexImageTGAFile("images/right02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/right03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/back01.tga", &spriteSize[0], &spriteSize[1]));  // #6
	images.push_back(glTexImageTGAFile("images/back02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/back03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/front01.tga", &spriteSize[0], &spriteSize[1]));  // #9
	images.push_back(glTexImageTGAFile("images/front02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/front03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/player_hit.tga", &spriteSize[0], &spriteSize[1]));  // #12
	images.push_back(glTexImageTGAFile("images/player_hit_left.tga", &spriteSize[0], &spriteSize[1]));  // #13
	images.push_back(glTexImageTGAFile("images/player_hit_back.tga", &spriteSize[0], &spriteSize[1]));  // #14
	images.push_back(glTexImageTGAFile("images/player_hit_front.tga", &spriteSize[0], &spriteSize[1]));  // #15

	images.push_back(glTexImageTGAFile("images/left_shoot01.tga", &spriteSize[0], &spriteSize[1]));  // #16
	images.push_back(glTexImageTGAFile("images/left_shoot02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/left_shoot03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/right_shoot01.tga", &spriteSize[0], &spriteSize[1])); // #19
	images.push_back(glTexImageTGAFile("images/right_shoot02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/right_shoot03.tga", &spriteSize[0], &spriteSize[1]));

	images.push_back(glTexImageTGAFile("images/front_shoot01.tga", &spriteSize[0], &spriteSize[1]));  // #22
	images.push_back(glTexImageTGAFile("images/front_shoot02.tga", &spriteSize[0], &spriteSize[1]));
	images.push_back(glTexImageTGAFile("images/front_shoot03.tga", &spriteSize[0], &spriteSize[1]));

	//******* Skeleton Animation **********************************************************
	frameInfoSkeleton.push_back(AnimFrameData(0, 4)); // Animation #0 Skeleton walking down
	frameInfoSkeleton.push_back(AnimFrameData(4, 4)); // Animation #1 Skeleton walking up
	frameInfoSkeleton.push_back(AnimFrameData(8, 3)); // Animation #2 Skeleton walking left
	frameInfoSkeleton.push_back(AnimFrameData(11, 3)); // Animation #3 Skeleton walking right
	frameInfoSkeleton.push_back(AnimFrameData(14, 8)); // Animation #4 Skeleton stopped
	//frameInfoSkeleton.push_back(AnimFrameData(14, 10)); // Animation #5 Skeleton is hurt

	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_down01.tga", &spriteSize[0], &spriteSize[1])); // #0
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_down02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_down03.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_down04.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_up01.tga", &spriteSize[0], &spriteSize[1])); // #4
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_up02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_up03.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_up04.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_left01.tga", &spriteSize[0], &spriteSize[1])); // #8
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_left02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_left03.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_right01.tga", &spriteSize[0], &spriteSize[1])); // #11
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_right02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_right03.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still01.tga", &spriteSize[0], &spriteSize[1])); // 14
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still03.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still04.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still05.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still06.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still07.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeleton.push_back(glTexImageTGAFile("images/skeleton_stand_still08.tga", &spriteSize[0], &spriteSize[1]));


	//******* Red Skeleton Animations **********************************************************
	frameInfoSkeletonRed.push_back(AnimFrameData(0, 4)); // Animation #0 Skeleton walking down
	frameInfoSkeletonRed.push_back(AnimFrameData(4, 4)); // Animation #1 Skeleton walking up
	frameInfoSkeletonRed.push_back(AnimFrameData(8, 3)); // Animation #2 Skeleton walking left
	frameInfoSkeletonRed.push_back(AnimFrameData(11, 3)); // Animation #3 Skeleton walking right
	frameInfoSkeletonRed.push_back(AnimFrameData(1, 1)); // Animation #4 Skeleton stopped

	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_down_red01.tga", &spriteSize[0], &spriteSize[1])); // #0
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_down_red02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_down_red03.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_down_red04.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_up_red01.tga", &spriteSize[0], &spriteSize[1])); // #4
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_up_red02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_up_red03.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_up_red04.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_left_red01.tga", &spriteSize[0], &spriteSize[1])); // #8
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_left_red02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_left_red03.tga", &spriteSize[0], &spriteSize[1]));

	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_right_red01.tga", &spriteSize[0], &spriteSize[1])); // #11
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_right_red02.tga", &spriteSize[0], &spriteSize[1]));
	imagesSkeletonRed.push_back(glTexImageTGAFile("images/skeleton_right_red03.tga", &spriteSize[0], &spriteSize[1]));


	//******* Hit Animation **********************************************************
	frameInfoHit.push_back(AnimFrameData(0, 9)); // Animation #0 
	imagesHit.push_back(glTexImageTGAFile("images/hit_00.tga", &spriteSize[0], &spriteSize[1])); // #0
	imagesHit.push_back(glTexImageTGAFile("images/hit_01.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_02.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_03.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_04.tga", &spriteSize[0], &spriteSize[1])); // #4
	imagesHit.push_back(glTexImageTGAFile("images/hit_05.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_06.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_07.tga", &spriteSize[0], &spriteSize[1]));
	imagesHit.push_back(glTexImageTGAFile("images/hit_08.tga", &spriteSize[0], &spriteSize[1]));

		//******* Pumpkin Animation **********************************************************
	frameInfoPumpkin.push_back(AnimFrameData(0, 8)); // Animation #0 
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin01.tga", &spriteSize[0], &spriteSize[1])); // #0
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin02.tga", &spriteSize[0], &spriteSize[1]));
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin02.tga", &spriteSize[0], &spriteSize[1]));
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin02.tga", &spriteSize[0], &spriteSize[1]));
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin01.tga", &spriteSize[0], &spriteSize[1])); // #4
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin01.tga", &spriteSize[0], &spriteSize[1]));
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin01.tga", &spriteSize[0], &spriteSize[1]));
	imagesPumpkin.push_back(glTexImageTGAFile("images/pumpkin01.tga", &spriteSize[0], &spriteSize[1]));

	//******* Gem Animation **********************************************************
	frameInfoGem.push_back(AnimFrameData(0, 3)); // Animation #0 
	imagesGem.push_back(glTexImageTGAFile("images/gem01.tga", &spriteSize[0], &spriteSize[1])); // #0
	imagesGem.push_back(glTexImageTGAFile("images/gem02.tga", &spriteSize[0], &spriteSize[1]));
	imagesGem.push_back(glTexImageTGAFile("images/gem03.tga", &spriteSize[0], &spriteSize[1]));


	animData = AnimationData(images, frameInfo);
	animDataSkeleton = AnimationData(imagesSkeleton, frameInfoSkeleton);
	animDataSkeletonRed = AnimationData(imagesSkeletonRed, frameInfoSkeletonRed);
	animDataHit = AnimationData(imagesHit, frameInfoHit);
	animDataPumpkin = AnimationData(imagesPumpkin, frameInfoPumpkin);
	animDataGem = AnimationData(imagesGem, frameInfoGem);

	//*************** Load Image Overlays *****************************************************
	pauseOverlayTex = glTexImageTGAFile("images/game_paused.tga", &spriteSize[0], &spriteSize[1]);
	endOverlayTex = glTexImageTGAFile("images/game_over.tga", &spriteSize[0], &spriteSize[1]);
	
	//gameData = Game_Data();
	gameData.numberOfSkeletons = NUM_SKELETONS;
	gameData.numberOfRedSkeletons = NUM_SKELETONS_RED;
	gameData.numberOfPumpkins = NUM_PUMPKINS;
	gameData.numberOfGems = NUM_GEMS;

	camera = new Camera(0.0f, 0.0f);
	// Fill the background
	BackgroundDef *background = new BackgroundDef(camera, gameData);
	player = Player(0, 0, spriteWidth, spriteHeight, animData, background, gameData);
	Score *score = new Score(camera, gameData);
	Lives *lives = new Lives(gameData);
	Gems *gems = new Gems(gameData);
	Level *level = new Level(gameData);

	srand (time(NULL));
	// Dynamically create skeletons and place in vector
	for(int i = 0; i < NUM_SKELETONS; i++){
		int xpos = rand() % 1150 + 50;
		int ypos = rand() % 1150 + 50;

		skeletons.push_back(new Skeleton(xpos, ypos, spriteWidth, spriteHeight, animDataSkeleton, timer, gameData));
	}

	// Dynamically create Red skeletons and place in vector
	for(int i = 0; i < NUM_SKELETONS_RED; i++){
		int xpos = rand() % 1150 + 50;
		int ypos = rand() % 1150 + 50;
		int moveDir = rand() % 4;
		skeletons_red.push_back(new Skeleton_Red(xpos, ypos, spriteWidth, spriteHeight, animDataSkeletonRed, moveDir));
	}

	// Dynamically create pumpkins and place in vector
	for(int i = 0; i < NUM_PUMPKINS; i++){
		int xpos = rand() % 1150 + 50;
		int ypos = rand() % 1150 + 50;

		pumpkins.push_back(new Pumpkin(xpos, ypos, spriteWidth, spriteHeight, animDataPumpkin, timer, gameData));
	}

	// Dynamically create gems and place in vector
	for(int i = 0; i < NUM_GEMS; i++){
		int xpos = rand() % 1150 + 50;
		int ypos = rand() % 1150 + 50;

		gemsVector.push_back(new Gem(xpos, ypos, spriteWidth, spriteHeight, animDataGem, timer, gameData));
	}


	//****** THE GAME LOOP  **********************************************************

	kbState = SDL_GetKeyboardState(NULL);
	while (!shouldExit) {

		// Find out how many seconds have past since last loop iteration
		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f;

		assert(glGetError() == GL_NO_ERROR);
		memcpy(kbPrevState, kbState, sizeof(kbPrevState));

		// Handle OS message pump.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {


			if(event.type == SDL_KEYDOWN){
					switch(event.key.keysym.sym){
						case SDLK_RETURN:
							// Do something when Return key is pressed
							break;
						case SDLK_p:
							keyStates.states[SDL_SCANCODE_P] += 1;
							break;
						default:
							break;
					}
			}
			if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        //doStuff = 0;
                        break;
					case SDLK_p:
						// Reset back to zero when key is released
						keyStates.states[SDL_SCANCODE_P] = 0;
						break;
                    default:
                        break;
                }
        }



			switch (event.type) {
			case SDL_QUIT:
				shouldExit = 1;
			}
		}


		//*********  Do Updates  ********************************************


		// ********  If Game is not paused **********************************
		if(gameState.getGameState() == gameState.PLAY){

			fmod_sys->update();

			timer.update(SDL_GetTicks()); // Track time for all objects with timer reference to use

			// update the player
			player.updateAnim(deltaTime);

			// update gems
			for(int i = 0; i < NUM_GEMS; i++){
				if(!gemsVector.at(i)->isDead)
					gemsVector.at(i)->updateAnim(deltaTime);
			}

			// update pumpkins
			for(int i = 0; i < NUM_PUMPKINS; i++){
				if(!pumpkins.at(i)->isDead)
					pumpkins.at(i)->updateAnim(deltaTime);
			}


			// update skeletons
			for(int i = 0; i < NUM_SKELETONS; i++){
				if(!skeletons.at(i)->isDead)
					skeletons.at(i)->updateAnim(deltaTime);
			}

			// update Red skeletons
			for(int i = 0; i < NUM_SKELETONS_RED; i++){
				if(!skeletons_red.at(i)->isDead)
					skeletons_red.at(i)->updateAnim(deltaTime);
			}

			// update bullets
			for(int i = 0; i < bullets.size(); i++){
				bullets.at(i)->update(deltaTime);
			}

			// update hits
			for(int i = 0; i < hits.size(); i++){
				hits.at(i)->updateAnim(deltaTime);
			}

			camera->update(deltaTime);
		}// END IF GAME NOT PAUSED ****************************************************

		/***************  KEYBOARD CHECKING ***********************************/

		keyState = SDL_GetKeyboardState(NULL); // We want status of all the keys

		// Take action if any of arrowkeys are pushed
		if (keyState[SDL_SCANCODE_RIGHT]) {
			if(player.direction != RIGHT || player.stopped)
				player.changeAnim(WALK_RIGHT);
			player.moveRight();
			camera->centerOnPlayer(player.getXPos(), player.getYPos(), deltaTime);
		}
		else if (keyState[SDL_SCANCODE_LEFT]) {
			if(player.direction != LEFT || player.stopped )
				player.changeAnim(WALK_LEFT);
			player.moveLeft();
			camera->centerOnPlayer(player.getXPos(), player.getYPos(), deltaTime);
		}
		else if (keyState[SDL_SCANCODE_UP]) {
			if(player.direction != UP || player.stopped)
				player.changeAnim(WALK_UP);
			player.moveUp();
			camera->centerOnPlayer(player.getXPos(), player.getYPos(), deltaTime);
		}
		else if (keyState[SDL_SCANCODE_DOWN]) {
			if(player.direction != DOWN || player.stopped)
				player.changeAnim(WALK_DOWN);
			player.moveDown();
			camera->centerOnPlayer(player.getXPos(), player.getYPos(), deltaTime);
		}
		else if (keyState[SDL_SCANCODE_P]) {
			// If it only equals 1, then is was just pushed. Ignore if not 1
			if(keyStates.states[SDL_SCANCODE_P] == 1){
				
				//Pause / Unpause the game
				if(gameState.getGameState() == gameState.PLAY){
					gameState.changeState(gameState.PAUSE);
					gameData.currentGameState = gameState.PAUSE;
				}else{
					gameState.changeState(gameState.PLAY);
					gameData.currentGameState = gameState.PLAY;
				}
			}
		}
		else if (keyState[SDL_SCANCODE_A]) {
			//move the camera right
			camera->move(-speedX, 0, deltaTime);
		}
		else if (keyState[SDL_SCANCODE_D]) {
			// move the camera right
			camera->move(speedX, 0, deltaTime);
		}
		else if (keyState[SDL_SCANCODE_W]) {
			// move the camera up
			camera->move(0, -speedY, deltaTime);
		}
		else if (keyState[SDL_SCANCODE_S]) {
			// move the camera down
			//camera->move(0, speedY, deltaTime);
				
				//Restart Game
				if(gameState.getGameState() == gameState.END){
					lives->increaseLives(3);
					gameData.lives_remaining = lives->lives_remaining;

					player.isHit = false;
					player.hp = 50;

					gems->gem_count = 0;
					gameData.gem_count = gems->gem_count;

					level->level = 1;
					gameData.level = level->level;

					score->score = 0;
					gameData.score = 0;

					//****** Replace any missing skeletons *******************//
					int remaingSkeletons = MAX_SKELETONS - NUM_SKELETONS;
					for(int i = 0; i < remaingSkeletons; i++){
						int xpos = rand() % 1150 + 50;
						int ypos = rand() % 1150 + 50;
						skeletons.push_back(new Skeleton(xpos, ypos, spriteWidth, spriteHeight, animDataSkeleton, timer, gameData));
					}

					NUM_SKELETONS = MAX_SKELETONS;
					Skeleton::numSkeletons = MAX_SKELETONS;
					gameData.numberOfSkeletons = MAX_SKELETONS;

					//****** Replace any missing Red skeletons *******************//
					int remaingRedSkeletons = MAX_SKELETONS_RED - NUM_SKELETONS_RED;
					for(int i = 0; i < remaingRedSkeletons; i++){
						int xpos = rand() % 1150 + 50;
						int ypos = rand() % 1150 + 50;
						int moveDir = rand() % 4;
						skeletons_red.push_back(new Skeleton_Red(xpos, ypos, spriteWidth, spriteHeight, animDataSkeletonRed, moveDir));
					}

					NUM_SKELETONS_RED = MAX_SKELETONS_RED;
					Skeleton_Red::numRedSkeletons = MAX_SKELETONS_RED;
					gameData.numberOfRedSkeletons = MAX_SKELETONS_RED;

					//****** Replace any missing Pumpkins (aka scarescrows) *******************//
					int remaingPumpkins = MAX_PUMPKINS - NUM_PUMPKINS;
					for(int i = 0; i < remaingPumpkins; i++){
						int xpos = rand() % 1150 + 50;
						int ypos = rand() % 1150 + 50;
						pumpkins.push_back(new Pumpkin(xpos, ypos, spriteWidth, spriteHeight, animDataPumpkin, timer, gameData));
					}

					NUM_PUMPKINS = MAX_PUMPKINS;
					Pumpkin::numPumpkins = MAX_PUMPKINS;
					gameData.numberOfPumpkins = MAX_PUMPKINS;

					//****** Replace any missing gems *******************//
					int remaingGems = MAX_GEMS - NUM_GEMS;
					for(int i = 0; i < remaingGems; i++){
						int xpos = rand() % 1150 + 50;
						int ypos = rand() % 1150 + 50;
						gemsVector.push_back(new Gem(xpos, ypos, spriteWidth, spriteHeight, animDataGem, timer, gameData));
					}

					NUM_GEMS = MAX_GEMS;
					Gem::numGems = MAX_GEMS;
					gameData.numberOfGems = MAX_GEMS;


					gameState.changeState(gameState.PLAY);
					gameData.currentGameState = gameState.PLAY;
				}
		}
		else if (keyState[SDL_SCANCODE_SPACE]) {
			// Play shoot sound
			fmod_sys->playSound(shoot, 0, false, NULL);

			player.isShooting = true;

			// Determine how long it's been since last bullwt was shot
			previousFiredTime = currentFiredTime;
			currentFiredTime = SDL_GetTicks();
			float sinceLastFired = (currentFiredTime - previousFiredTime) / 1000.0f;
			
			bulletFired = false;

			// Fire bullets at a steady rate (To prevent bullets looking like a lazerbeam)
			if(sinceLastFired > 0.1){
				bullets.push_back(new Bullet("images/bullet.tga", 
					              player.getXPos() + camera->getXOffSet(), 
								  player.getYPos() + camera->getYOffSet() + player.getBox().h / 2));
				bullets.back()->setWidth(8);
				bullets.back()->setHeight(8);
				bullets.back()->initialize(player.getDirection(), 500); // set the direction and speed of the bullet
				bulletFired = true;
			}
		}
		
		else{
			player.stop();
			if(player.direction == LEFT)
				player.changeAnim(LEFT_STOPPED);
			if(player.direction == RIGHT)
				player.changeAnim(RIGHT_STOPPED);
			if(player.direction == UP)
				player.changeAnim(UP_STOPPED);
			if(player.direction == DOWN)
				player.changeAnim(DOWN_STOPPED);

			camera->stop();
		}

		// Game logic goes here.
		if (kbState[SDL_SCANCODE_ESCAPE]) {
			shouldExit = 1;
		}


		/******* Check for collisions with background items and with other sprites *******************/
		AABB box = player.getBox();
		bool collision = background->playerBackgroundCollsion(box);
		if(collision){
			player.backgroundTileCollision = true;
		}

		// Check collision between skeletons and background tiles
		for(int i = 0; i < NUM_SKELETONS; i++){
			AABB box = skeletons.at(i)->getBox();
			bool collision = background->collision(box);
			if(collision){
				skeletons.at(i)->backgroundTileCollision = true;
			}

			int nextIndex = i + 1;
			// Check if a skeleton has collided with another skeleton
			if(nextIndex < NUM_SKELETONS){

				// Check for collision with skeleton with an index greater than itself
				for(; nextIndex < NUM_SKELETONS; nextIndex++){
						if(AABBIntersect(skeletons.at(i)->getBox(), skeletons.at(nextIndex)->getBox())){
						    skeletons.at(i)->collieded = true;
						    skeletons.at(nextIndex)->collieded = true;
					}
				}

				if(i > 0){
				
				    // Check for collision with skeleton with an index less than itself
				    for(int m = i - 1; m < 0; m--){
						if(AABBIntersect(skeletons.at(i)->getBox(), skeletons.at(m)->getBox())){
						    skeletons.at(i)->collieded = true;
						    skeletons.at(m)->collieded = true;
					    }
				    }
				}
			}

			// Check for collsions with red skeletons
			for(int c = 0; c < NUM_SKELETONS_RED; c++){
				if(AABBIntersect(skeletons.at(i)->getBox(), skeletons_red.at(c)->getBox())){
					skeletons.at(i)->collieded = true;
					skeletons_red.at(c)->collieded = true;
				}
			}

			// Check for collsions with pumpkins (aka scarecrows)
			for(int c = 0; c < NUM_PUMPKINS; c++){
				if(AABBIntersect(skeletons.at(i)->getBox(), pumpkins.at(c)->getBox())){
					skeletons.at(i)->collieded = true;
					pumpkins.at(c)->collieded = true;
				}
			}

			// Check for collsions with gems
			for(int c = 0; c < NUM_GEMS; c++){
				if(AABBIntersect(skeletons.at(i)->getBox(), gemsVector.at(c)->getBox())){
					skeletons.at(i)->collieded = true;
					gemsVector.at(c)->collieded = true;
				}
			}

			// Flag any skeletons that somehow get out of bounds for removal from game
			if(skeletons.at(i)->getXPos() > 1243 || skeletons.at(i)->getYPos() > 1200){
				skeletons.at(i)->isHit = true;
			}
		}

		// Check collision between red skeletons and background tiles
		for(int i = 0; i < NUM_SKELETONS_RED; i++){
			AABB box = skeletons_red.at(i)->getBox();
			bool collision = background->collision(box);
			if(collision){
				skeletons_red.at(i)->backgroundTileCollision = true;
			}

			// Check if a red skeleton has collided with another red skeleton
			int nextIndex = i + 1;
			if(nextIndex < NUM_SKELETONS_RED){

				// Check for collision with red skeletons with an index greater than itself
				for(; nextIndex < NUM_SKELETONS_RED; nextIndex++){
					if(AABBIntersect(skeletons_red.at(i)->getBox(), skeletons_red.at(nextIndex)->getBox())){
						  skeletons_red.at(i)->collieded = true;
						  skeletons_red.at(nextIndex)->collieded = true;
					}
				}

				if(i > 0){
				
				    // Check for collision with red skeleton with an index less than itself
				    for(int m = i - 1; m < 0; m--){
						if(AABBIntersect(skeletons_red.at(i)->getBox(), skeletons_red.at(m)->getBox())){
						    skeletons_red.at(i)->collieded = true;
						    skeletons_red.at(m)->collieded = true;
					    }
				    }
				}
			}

			// Check for collsions with pumpkins (aka scarecrows)
			for(int c = 0; c < NUM_PUMPKINS; c++){
				if(AABBIntersect(skeletons_red.at(i)->getBox(), pumpkins.at(c)->getBox())){
					skeletons_red.at(i)->collieded = true;
					pumpkins.at(c)->collieded = true;
				}
			}

			// Check for collsions with gems
			for(int c = 0; c < NUM_GEMS; c++){
				if(AABBIntersect(skeletons_red.at(i)->getBox(), gemsVector.at(c)->getBox())){
					skeletons_red.at(i)->collieded = true;
					gemsVector.at(c)->collieded = true;
				}
			}

			// Flag red skeletons that somehow get out of bounds for removal from game
			if(skeletons_red.at(i)->getXPos() > 1223 || skeletons_red.at(i)->getYPos() > 1200){
				skeletons_red.at(i)->isDead = true;
			}
		}

		/********* End background tile and skeleton collision checking ********************/

		

		/*
		****** Check if any of the bullets have hit a skeleton *********************
		*/
		for(int i = 0; i < bullets.size(); i++){
			for(int j = 0; j < skeletons.size(); j++){
				if(AABBIntersect(bullets.at(i)->getBox(), skeletons.at(j)->getBox())){
					skeletons.at(j)->isHit = true;

					// create a hit animation object
					hits.push_back(new Hit(skeletons.at(j)->getXPos(), skeletons.at(j)->getYPos(), 64, 64, animDataHit, 0));

					// set isHit to true so update will flag it to be deleted
					bullets.at(i)->isHit = true;
				}
			}
		}
		

		/*
		***** Check if any of the bullets have hit a Red skeleton *********************
		*/
		for(int i = 0; i < bullets.size(); i++){
			for(int j = 0; j < skeletons_red.size(); j++){
				if(AABBIntersect(bullets.at(i)->getBox(), skeletons_red.at(j)->getBox())){
					skeletons_red.at(j)->isHit = true;

					// create a hit animation object
					hits.push_back(new Hit(skeletons_red.at(j)->getXPos(), skeletons_red.at(j)->getYPos(), 64, 64, animDataHit, 0));

					// set isHit to true so update will flag it to be deleted
					bullets.at(i)->isHit = true;
				}
			}
		}


		/*
		****** Check if any of the bullets have hit a pumpkin (aka scarescrow) *********************
		*/
		for(int i = 0; i < bullets.size(); i++){
			for(int j = 0; j < pumpkins.size(); j++){
				if(AABBIntersect(bullets.at(i)->getBox(), pumpkins.at(j)->getBox())){
					pumpkins.at(j)->isHit = true;

					// create a hit animation object
					hits.push_back(new Hit(pumpkins.at(j)->getXPos(), pumpkins.at(j)->getYPos(), 64, 64, animDataHit, 0));

					// set isHit to true so update will flag it to be deleted
					bullets.at(i)->isHit = true;
				}
			}
		}

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//******  Game drawing goes here **********************
		background->draw();

		// DRAW IF NOT START OR END
		if(gameState.getGameState() == gameState.PLAY || gameState.getGameState() == gameState.PAUSE || gameState.getGameState() == gameState.END){
			lives->draw();
			score->draw();
			gems->draw();
			level->draw();
		}// END DRAW IF NOT PAUSED OR END

		// Draw Game Pause Image Overlay
		if(gameState.getGameState() == gameState.PAUSE){

			glDrawSprite(pauseOverlayTex, imgOverlayPos[0], imgOverlayPos[1], 650, 650);
		}

		// Draw End of Game Image Overlay
		if(gameState.getGameState() == gameState.END){

			glDrawSprite(endOverlayTex, imgOverlayPos[0], imgOverlayPos[1], 650, 650);
		}


		// DRAW IF NOT PAUSED OR END
		if(gameState.getGameState() == gameState.PLAY){

			//Only draw gems in camera's view AND if not dead (isDead == false)
			for(int j = 0; j < NUM_GEMS; j++){
				if(!gemsVector.at(j)->isDead && AABBIntersect(camera->getBox(), gemsVector.at(j)->getBox()))
					gemsVector.at(j)->draw(camera->getX(), camera->getY());
			}

			//Only draw pumpkins in camera's view AND if not dead (isDead == false)
			for(int j = 0; j < NUM_PUMPKINS; j++){
				if(!pumpkins.at(j)->isDead && AABBIntersect(camera->getBox(), pumpkins.at(j)->getBox()))
					pumpkins.at(j)->draw(camera->getX(), camera->getY());
			}

			//Only draw skeletons in camera's view AND if not dead (isDead == false)
			for(int i = 0; i < NUM_SKELETONS; i++){
				if(!skeletons.at(i)->isDead && AABBIntersect(camera->getBox(), skeletons.at(i)->getBox()))
					skeletons.at(i)->draw(camera->getX(), camera->getY());
			}

			//Only draw Red skeletons in camera's view AND if not dead (isDead == false)
			for(int i = 0; i < NUM_SKELETONS_RED; i++){
				if(!skeletons_red.at(i)->isDead && AABBIntersect(camera->getBox(), skeletons_red.at(i)->getBox()))
					skeletons_red.at(i)->draw(camera->getX(), camera->getY());
			}
		}// END DRAW IF NOT PAUSED OR END

		//**********  Set gem's isHit to true if collision with player  ***********
		for(int i = 0; i < NUM_GEMS; i++){
			if(PlayerIntersect(player.getBox(), gemsVector.at(i)->getBox())){
				gemsVector.at(i)->collision(player);
				player.collision(*gemsVector.at(i));
				gemsVector.at(i)->isHit = true;
				gems->increaseGemCount(1);
				fmod_sys->playSound(gem_sound, 0, false, NULL);
			}
		}

		//**********  Set player's isHit to true if collision with pumpkin  ***********
		for(int i = 0; i < NUM_PUMPKINS; i++){
			if(PlayerIntersect(player.getBox(), pumpkins.at(i)->getBox())){
				pumpkins.at(i)->collision(player);
				player.collision(*pumpkins.at(i));
				player.isHit = true;
				fmod_sys->playSound(ouch_sound, 0, false, NULL);
			}
		}


		//**********  Set skeleton and player isHit to true if they collide  ***********
		for(int i = 0; i < NUM_SKELETONS; i++){
			if(PlayerIntersect(player.getBox(), skeletons.at(i)->getBox())){
				skeletons.at(i)->collision(player);
				player.collision(*skeletons.at(i));
				player.isHit = true;
				fmod_sys->playSound(ouch_sound, 0, false, NULL);
			}
		}


		//**********  Set Red skeleton and player isHit to true if they collide  ***********
		for(int i = 0; i < NUM_SKELETONS_RED; i++){
			if(PlayerIntersect(player.getBox(), skeletons_red.at(i)->getBox())){
				skeletons_red.at(i)->collision(player);
				player.collision(*skeletons_red.at(i));
				player.isHit = true;
				fmod_sys->playSound(ouch_sound, 0, false, NULL);
			}
		}
		
		if(player.isHit){
			// Determine how long it's been since last hit
			previousHitTime = currentHitTime;
			currentHitTime = SDL_GetTicks();
			float sinceLastHit = (currentHitTime - previousHitTime) / 1000.0f;
			
			if(sinceLastHit > 0.1){
				lives->decreaseLives(1);
			}
		}
		
		if(lives->lives_remaining == 0){
			gameState.changeState(gameState.END);
		}
		
		/*****  Draw bullets  *****/
		for(int i = 0; i < bullets.size(); i++){
			bullets.at(i)->draw(camera->getX(), camera->getY());
		}

		/*****  Draw hits  *****/
		for(int i = 0; i < hits.size(); i++){
			hits.at(i)->draw(camera->getX(), camera->getY());
		}

		player.draw(); // Player is always in camera's view

		// Present the most recent frame.
		SDL_GL_SwapWindow(window);


		//****** Remove skeletons that are dead ;) *******************//
		for(int i = 0; i < NUM_SKELETONS; i++){
			if(skeletons.at(i)->isDead){
				score->increaseScore(whiteSkeletonPoints);
				fmod_sys->playSound(score_sound, 0, false, NULL);
				skeletons.erase(skeletons.begin() + i);
				NUM_SKELETONS -= 1;
				Skeleton::numSkeletons -= 1;
				gameData.numberOfSkeletons = Skeleton::numSkeletons;
			}
		}

		//****** Remove Red skeletons that are dead ;) *******************//
		for(int i = 0; i < NUM_SKELETONS_RED; i++){
			if(skeletons_red.at(i)->isDead){
				score->increaseScore(redSkeletonPoints);
				fmod_sys->playSound(score_sound, 0, false, NULL);
				skeletons_red.erase(skeletons_red.begin() + i);
				NUM_SKELETONS_RED -= 1;
				Skeleton_Red::numRedSkeletons -= 1;
				gameData.numberOfRedSkeletons = Skeleton_Red::numRedSkeletons;
			}
		}

		//****** Remove Pumpkins that are dead ;) *******************//
		for(int i = 0; i < NUM_PUMPKINS; i++){
			if(pumpkins.at(i)->isDead){
				score->increaseScore(pumpkinPoints);
				fmod_sys->playSound(score_sound, 0, false, NULL);
				pumpkins.erase(pumpkins.begin() + i);
				NUM_PUMPKINS -= 1;
				Pumpkin::numPumpkins -= 1;
				gameData.numberOfPumpkins = Pumpkin::numPumpkins;
			}
		}

		//**************  LEVEL UP - Replenish enemies and Gems  ****************************************8
		if(levelUp){
			//****** Replace any missing gems *******************//
			int remaingGems = MAX_GEMS - NUM_GEMS;
			for(int i = 0; i < remaingGems; i++){
				int xpos = rand() % 1150 + 50;
				int ypos = rand() % 1150 + 50;
				gemsVector.push_back(new Gem(xpos, ypos, spriteWidth, spriteHeight, animDataGem, timer, gameData));
			}

			NUM_GEMS = MAX_GEMS;
			Gem::numGems = MAX_GEMS;
			gameData.numberOfGems = MAX_GEMS;

			//****** Replace any missing skeletons *******************//
			int remaingSkeletons = MAX_SKELETONS - NUM_SKELETONS;
			for(int i = 0; i < remaingSkeletons; i++){
				int xpos = rand() % 1150 + 50;
				int ypos = rand() % 1150 + 50;
				skeletons.push_back(new Skeleton(xpos, ypos, spriteWidth, spriteHeight, animDataSkeleton, timer, gameData));
			}

			NUM_SKELETONS = MAX_SKELETONS;
			Skeleton::numSkeletons = MAX_SKELETONS;
			gameData.numberOfSkeletons = MAX_SKELETONS;

			//****** Replace any missing Red skeletons *******************//
			int remaingRedSkeletons = MAX_SKELETONS_RED - NUM_SKELETONS_RED;
			for(int i = 0; i < remaingRedSkeletons; i++){
				int xpos = rand() % 1150 + 50;
				int ypos = rand() % 1150 + 50;
				int moveDir = rand() % 4;
				skeletons_red.push_back(new Skeleton_Red(xpos, ypos, spriteWidth, spriteHeight, animDataSkeletonRed, moveDir));
			}

			NUM_SKELETONS_RED = MAX_SKELETONS_RED;
			Skeleton_Red::numRedSkeletons = MAX_SKELETONS_RED;
			gameData.numberOfRedSkeletons = MAX_SKELETONS_RED;

			//****** Replace any missing Pumpkins (aka scarescrows) *******************//
			int remaingPumpkins = MAX_PUMPKINS - NUM_PUMPKINS;
			for(int i = 0; i < remaingPumpkins; i++){
				int xpos = rand() % 1150 + 50;
				int ypos = rand() % 1150 + 50;
				pumpkins.push_back(new Pumpkin(xpos, ypos, spriteWidth, spriteHeight, animDataPumpkin, timer, gameData));
			}

			NUM_PUMPKINS = MAX_PUMPKINS;
			Pumpkin::numPumpkins = MAX_PUMPKINS;
			gameData.numberOfPumpkins = MAX_PUMPKINS;

			levelUp = false;

		} //********  END LEVEL UP  ****************************************************************

		

		//****** Remove gems that have been collected *******************//
		for(int i = 0; i < NUM_GEMS; i++){
			if(gemsVector.at(i)->isDead){
				if(gameData.gem_count % 20 == 0 && gameData.score != 0){
					fmod_sys->playSound(level_up_sound, 0, false, NULL);
					level->level += 1;
					levelUp = true;
					gameData.level = level->level;
				}
				score->increaseScore(gemPoints);
				fmod_sys->playSound(score_sound, 0, false, NULL);
				gemsVector.erase(gemsVector.begin() + i);
				NUM_GEMS -= 1;
				Gem::numGems -= 1;
				gameData.numberOfGems = Gem::numGems;
			}
		}

		//******* Remove bullets that are out of the Game world ********//
		for(int i = 0; i < bullets.size(); i++){
			if(bullets.at(i)->outOfGameWorld == true)
				bullets.erase(bullets.begin() + i);
		}

		//******* Remove hits that have finished playing ********//
		for(int i = 0; i < hits.size(); i++){
			if(hits.at(i)->finished == true)
				hits.erase(hits.begin() + i);
		}
		

		//*************** Zero All Keys Before Next Frame *******************************
		keyStates.zeroAllKeyStates();


		//******** For Troubleshooting ***********************
		//printf(player.to_string().c_str());
		//printf(background->to_string().c_str());
		//printf(camera->to_string().c_str());
		//if(!bullets.empty())
			//printf(bullets.at(0)->to_string().c_str());
		//if(!skeletons.empty())
			//printf(skeletons.at(0)->to_string().c_str());
		 //if(!skeletons_red.empty())
			//printf(skeletons_red.at(0)->to_string().c_str());
		//printf(timer.to_string().c_str());
		//printf(gameData.to_string().c_str());
		//printf(gameState.to_string().c_str());
		//printf(keyStates.to_string().c_str());
		//printf(score->to_string().c_str());

	}//End Game Loop

	SDL_Quit();

	return 0;
}

/*
* Checks AABB/AABB collisions
* Works for all game sprites except the player
*/
bool AABBIntersect(AABB box1, AABB box2){
	//box1 to the right
	if(box1.x > box2.x + box2.w){
		return false;
	}

	// box1 top the left
	if(box1.x + box1.w < box2.x){
		return false;
	}

	// box1 below
	if(box1.y > box2.y + box2.h){
		return false;
	}

	// box1 above
	if(box1.y + box1.h < box2.y){
		return false;
	}
	
	return true;
}

// Checks for AABB/AABB collisions against the player and another sprite
bool PlayerIntersect(AABB box1, AABB box2){
	bool test = ((box1.x + box1.w/2)*2 < box2.x) ||   //box1 is to left of box2
		        (box2.x + box2.w < box1.x * 2 + 5) || //box1 is to right of box2
		        ((box1.y + box1.h/2)*2 < box2.y) ||   //box1 is above box2
				(box2.y + box2.h < box1.y * 2);       //box1 is below box2
	return !test;
}