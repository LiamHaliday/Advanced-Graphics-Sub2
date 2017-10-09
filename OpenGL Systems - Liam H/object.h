// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: object.h
// Description	: object class
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "Dependencies\FMOD\fmod.hpp"

#include "ShaderLoader.h"

#include "camera.h"


#include <vector>
#include <string>

#include <stdlib.h>    
#include <time.h>  


class object
{
public:

	object();

	void render(float one, float two, float three, bool moving, camera tryingCamera);
	void createObj(GLfloat *vert, int vertSize, GLuint *ind, int indSize); //GLfloat vertices, GLuint indices

	void setImage(const char* image);
	void setImage(const char* image, const char* image2);

private:



	GLuint program;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint texture;

	int pointsToRender;

	const char* imageLoc = NULL;
	const char* imageLoc2 = NULL;

};

#endif