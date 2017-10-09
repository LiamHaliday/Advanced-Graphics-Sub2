#include "camera.h"

/****************************************************/
// Filename: camera.cpp
// Created: Liam Haliday
// Description: draws the object from an angle
/****************************************************/
void camera::draw(GLuint program, GLfloat currentThime, bool spin, float one, float two, float three)
{


	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);//get current time.
	currentTime = currentTime / 1000;//convert millisecond to seconds

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	// Set value to the parameter
	glUniform1f(currentTimeLocation, currentTime);// set value

	//cameraPos =	glm::vec3(0.0f, 0.5f, 0.5f); // where the camera is 
	//cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // what the camera is looking at
	//cameraUp =	glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 newPositonObj = glm::vec3(one, two, -three);
	glm::mat4 translation;
	translation = glm::translate(glm::mat4(), newPositonObj);

	GLfloat radius = 4.0f;
	GLfloat camX = sin(currentTime) * radius;
	GLfloat camZ = cos(currentTime) * radius;

	glm::mat4 world;
	glm::vec3 newPositon = glm::vec3(0.0f, 0.0f, 0.0f);
	world = glm::translate(glm::mat4(), newPositon);

	view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	model = glm::translate(glm::mat4(), newPositonObj) * glm::rotate(glm::mat4(), -0.0f / 100, glm::vec3(0.0f, 1.0f, 0.0f)); // TRANS WAS HERE 
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 10.0f);


	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint worldLoc = glGetUniformLocation(program, "world");


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));


	GLuint transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translation));



};

/****************************************************/
// Filename: camera.cpp
// Created: Liam Haliday
// Description: draws the object strate down (for the main menu)
/****************************************************/
void camera::drawflat(GLuint program, GLfloat currentThime, bool spin, float one, float two, float three)
{


	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);//get current time.
	currentTime = currentTime / 1000;//convert millisecond to seconds

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	// Set value to the parameter
	glUniform1f(currentTimeLocation, currentTime);// set value

	cameraPos = glm::vec3(0.0f, 5.76f, 0.0f); // where the camera is 
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // what the camera is looking at
	cameraUp = glm::vec3(0.0f, 1.0f, camerafront);

	glm::vec3 newPositonObj = glm::vec3(one, two, -three);
	glm::mat4 translation;
	translation = glm::translate(glm::mat4(), newPositonObj);

	GLfloat radius = 4.0f;
	GLfloat camX = sin(currentTime) * radius;
	GLfloat camZ = cos(currentTime) * radius;

	glm::mat4 world;
	glm::vec3 newPositon = glm::vec3(0.0f, 0.0f, 0.0f);
	world = glm::translate(glm::mat4(), newPositon);

	view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	model = glm::translate(glm::mat4(), newPositonObj) * glm::rotate(glm::mat4(), -0.0f / 100, glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 10.0f);


	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint worldLoc = glGetUniformLocation(program, "world");


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));


	GLuint transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translation));



};


void camera::movingCam(glm::vec3 pasloc, glm::vec3 paslook, glm::vec3 pasUp)
{
	
	cameraPos = pasloc; // where the camera is 
	cameraFront = paslook; // what the camera is looking at
	cameraUp = pasUp;

}