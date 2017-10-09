// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Scene.cpp
// Description	: Scenes
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#include "Scene.h"
#//include <glm/gtc/matrix_transform.hpp>

#define BUTTON_UP   0 
#define BUTTON_DOWN 1
#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;



Scene::Scene()
{
	srand(time(NULL));
};



void Scene::init()
{

	FPS = new TextLabel("End score", "Assets/fonts/arial.ttf");
	FPS->setPosition(glm::vec2(10.0f, 950.0f));
	FPS->setColor(glm::vec3(1.0f, 1.0f, 0.0f));

	player.object.setImage("Assets/images/lava.jpg");
	Setsquare();	

	floor.setImage("Assets/images/Left2.png");
	floor2.setImage("Assets/images/Right2.png");
	SetFloor();

	camLookObj.setImage("Assets/images/red.png");
	SetCamObjThings();

	BlendBox.setImage("Assets/images/waterTile.png");
	SetBlendBox();

	player.xCoord = 0.50f;
	player.yCoord = 0.225f;
	player.zCoord = 0.50f;

	cubeForClass.init();
	cubeForClass.setXYZ(glm::vec3( 0.0f , 0.0f , 0.0f));
}


void Scene::render()
{
	glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	cubeForClass.render(mainCam);

	// _____________ STENCIL _____________

	glEnable(GL_STENCIL_TEST); 
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); 

	glStencilFunc(GL_ALWAYS, 1, 0xFF); 

	glStencilMask(0xFF);

	player.object.render(player.xCoord, player.yCoord, player.zCoord, true, mainCam);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF); glStencilMask(0x00); 
	
	camLookObj.render(player.xCoord, player.yCoord, player.zCoord, true, mainCam);

	glStencilMask(0xFF); 
	glDisable(GL_STENCIL_TEST);

	// _____________ SCISSOR _____________

	glEnable(GL_SCISSOR_TEST);	
	
	glScissor(0, 0, 800, 1000); // left 
	floor.render(0.0, -1.1, 0.0, true, mainCam);             
	
	glScissor(800, 0, 800, 1000); //right 
	floor2.render(0.0, -1.1, 0.0, true, mainCam);
	
	glDisable(GL_SCISSOR_TEST);

	// _____________ BLENDING _____________

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BlendBox.render(-0.50f, 0.255f, -0.50f, false, mainCam);

	glDisable(GL_BLEND);

	FPS->Render(); 
	
	glutSwapBuffers();
}


void Scene::update(unsigned char *keyState, unsigned int *ArrowKeyState,
	GLfloat yaw, GLfloat pitch, GLfloat lastX, GLfloat lastY)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000;

	//delta time
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	CurrentFPS = ((1 / deltaTime) * 1000);
	//std::cout << currentTime << std::endl;

	Playerspeed = 0.005f * deltaTime;

	std::string FPString = "FPS: ";
	FPString += std::to_string(int(CurrentFPS)).c_str();
	FPS->setText(FPString.c_str());


	// -------------------------------------- CAMERA ZONE --------------------------------------

	if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN) { inOut = 2.0f; }

	if (keyState[(unsigned char)'w'] == BUTTON_DOWN || keyState[(unsigned char)'W'] == BUTTON_DOWN) { camLoc += (front * 0.05f); }
	if (keyState[(unsigned char)'s'] == BUTTON_DOWN || keyState[(unsigned char)'S'] == BUTTON_DOWN) { camLoc -= (front * 0.05f); }
	

	//frontChange = glm::rotate(2.0f ,front);

	if (keyState[(unsigned char)'a'] == BUTTON_DOWN || keyState[(unsigned char)'A'] == BUTTON_DOWN) { camLoc += (frontChange * 0.05f); }
	if (keyState[(unsigned char)'d'] == BUTTON_DOWN || keyState[(unsigned char)'D'] == BUTTON_DOWN) { camLoc -= (frontChange * 0.05f); }
																												 
	if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN) { camLoc -= (front * 0.05f); }
	if (keyState[(unsigned char)'f'] == BUTTON_DOWN || keyState[(unsigned char)'F'] == BUTTON_DOWN) { camLoc += (front * 0.05f); }

	//if (keyState[(unsigned char)' '] == BUTTON_UP ) 
	//{ 
	//	camLoc.x = sin(currentTime) *  inOut;
	//	camLoc.y = 1.0f;
	//	camLoc.z = cos(currentTime) *  inOut;
	//
	//	camLook.x = 0.0f;
	//	camLook.y = 0.0f;
	//	camLook.z = 0.0f;
	//}
	//else
	//{
	//	camLoc.x = 0.0f;
	//	camLoc.y = 0.25f;
	//	camLoc.z = 0.0f;
	//
	//	camLook.x = sin(currentTime) *  0.50f;
	//	camLook.y = 0.25f;
	//	camLook.z = cos(currentTime) *  0.50f;
	//}

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	
	mainCam.movingCam(camLoc, front+camLoc, glm::vec3(0, 1, 0));
	//mainCam.movingCam(glm::vec3(0, 0, 0), front, glm::vec3(0, 1, 0));

	//mainCam.movingCam(front, camLook, glm::vec3(0, 1, 0));  // look 
}


void Scene::Setsquare()
{
	// square ver and ind
	GLfloat vertices[] = {
		//position				//color				//texture coord
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};


	GLfloat * testVert = vertices;
	GLuint * testInd = indices;

	
	player.object.createObj(testVert, sizeof(vertices), testInd, sizeof(indices));
}


void Scene::SetFloor()
{

	//floor vec ands ind
	GLfloat floorVertices[] = {
		//position				//color				//texture coord		 
		-1.00f, -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-1.00f,  0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 1.00f,   0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		 1.00f,  -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the b2ck face vertex data.							 
		-1.00f, -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		 1.00f,  -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 1.00f,   0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-1.00f,  0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		// Fill 1n the t2p face vertex data.							 
		-1.00f,  0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-1.00f,  0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 1.00f,   0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
	 	 1.00f,   0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the b2ttom face vertex data.							 
		-1.00f, -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		 1.00f,  -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 1.00f,  -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-1.00f, -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		// Fill 1n the l2ft face vertex data.							 
		-1.00f, -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-1.00f,  0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		-1.00f,  0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		-1.00f, -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 
		// Fill 1n the r2ght face vertex data.							 
		 1.00f,  -0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		 1.00f,   0.10f, -1.00f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 1.00f,   0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
		 1.00f,  -0.10f,  1.00f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,		
	};


	GLuint floorIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};


	GLfloat * testVert = floorVertices;
	GLuint * testInd = floorIndices;


	floor.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
	floor2.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
};


void Scene::SetCamObjThings()
{

	//floor vec ands ind
	GLfloat floorVertices[] = {
		//position				//color				//texture coord
		-0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		0.1325f, -0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.1325f, 0.1325f, -0.1325f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.1325f, 0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.1325f, -0.1325f, 0.1325f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};


	GLuint floorIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};


	GLfloat * testVert = floorVertices;
	GLuint * testInd = floorIndices;


	camLookObj.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
};


void Scene::SetBlendBox()
{
	// square ver and ind
	GLfloat vertices[] = {
		//position				//color				//texture coord
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the back face vertex data.
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the top face vertex data.
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the bottom face vertex data.
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		// Fill in the left face vertex data.
		-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// Fill in the right face vertex data.
		0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,

		// bottom
		12, 13, 14,
		12, 14, 15,
		// left
		16, 17, 18,
		16, 18, 19,
		// right
		20, 21, 22,
		20, 22, 23,
	};


	GLfloat * testVert = vertices;
	GLuint * testInd = indices;


	BlendBox.createObj(testVert, sizeof(vertices), testInd, sizeof(indices));
}