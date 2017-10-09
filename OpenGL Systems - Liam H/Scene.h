#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "object.h"
#include "Text.h"
#include "CUBE.h"

struct objectStruct
{
	object object;
	float xCoord;
	float yCoord;
	float zCoord;

	float mag;
	float dir;

	int direction;
};


class Scene
{
public:

	Scene();

	void Setsquare();
	void SetFloor();
	void SetCamObjThings();

	void SetBlendBox();


	FMOD::System* audioMgr;
	FMOD::Sound* hitSound;
	FMOD::Sound* bgMusic;

	bool InitFmod()
{

	FMOD_RESULT result;

	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK) return false;

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) return false;

	return true;
}

	const bool LoadAudio()
{
	FMOD_RESULT result;

	result = audioMgr->createSound("Assets/audio/click.wav", FMOD_DEFAULT, 0, &hitSound);

	result = audioMgr->createSound("Assets/audio/backGroud.wav", FMOD_LOOP_NORMAL, 0, &bgMusic);

	bgMusic->setMode(FMOD_LOOP_NORMAL);

	return true;
}

	camera mainCam;

	float adjacent;
	float opposite;

	void init();
	void render();

	void update(unsigned char *keyState, unsigned int *ArrowKeyState, 
		GLfloat yaw, GLfloat pitch, GLfloat lastX, GLfloat lastY);


private:
	
	//object* enemy = new object();

	float inOut = 2.0f;

	camera* camPoint;

	cube cubeForClass;

	//text
	TextLabel* label;
	TextLabel* endlabel;
	TextLabel* EnterToRestart;
	TextLabel* FPS;

	objectStruct player;
	objectStruct mainMenuObject;

	object floor;
	object floor2;
	object BlendBox;
	object camLookObj;

	object end;
	bool lost = false;

	bool buletStart = false;

	//bullets 
	std::vector<objectStruct> bullets;
	int bulletsInUse;

	std::vector<objectStruct> pinkEnemys;
	std::vector<objectStruct> greenEnemys;

	glm::vec2 whiteBoxVec;

	//keyboard bits
	unsigned char keyState[255];
	float Bulletspeed = 0.55f;
	float Playerspeed = 0.1f;
	float pinkySpeed = 0.01;

	glm::vec3 camLoc {0, 1.0, 0};
	glm::vec3 camLook{ 0,0,0 };
	glm::vec3 front{ 0,0,0 };
	glm::vec3 frontChange{ 0,0,0 };

	// deltaTime
	float deltaTime;
	float currentFrame;
	float lastFrame;

	float CurrentFPS;
};

#endif