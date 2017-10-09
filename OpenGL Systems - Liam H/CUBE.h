#pragma once

#include "object.h"
#include "Text.h"

class cube
{
public:

	cube();

	void render(camera tryingCamera);

	void init(); //GLfloat vertices, GLuint indices

	void update();

	void setImage(const char* image);
	void setXYZ(glm::vec3 loc) { location = loc; };

private:


	GLuint program;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint texture;


	glm::vec3 location = { 0.0f, 0.0f, 0.0f};

	//int pointsToRender;

	const char* imageLoc = "Assets/images/jumper.png";
	//const char* imageLoc2 = NULL;

};