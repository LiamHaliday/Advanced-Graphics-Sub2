#include "Scene.h"


#define BUTTON_UP   0 
#define BUTTON_DOWN 1
#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

unsigned char mouseState[3];
unsigned char keyState[255];
unsigned int ArrowKeyState[4];

void keyboard(unsigned char key, int x, int y){
	keyState[key] = BUTTON_DOWN;
}
void keyboard_up(unsigned char key, int x, int y){
	keyState[key] = BUTTON_UP;
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_DOWN;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_DOWN;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_DOWN;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_DOWN;
		break;
	}
}
void SpecialInput_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_UP;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_UP;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_UP;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_UP;
		break;
	}
}



void mouse(int button, int button_state, int x, int y) {

#define state ( (button_state== GLUT_DOWN) ? BUTTON_DOWN : BUTTON_UP )

	switch (button) {

	case GLUT_LEFT_BUTTON:
		mouseState[MOUSE_LEFT] = state; break;

	case GLUT_MIDDLE_BUTTON:
		mouseState[MOUSE_MIDDLE] = state; break;

	case GLUT_RIGHT_BUTTON:
		mouseState[MOUSE_RIGHT] = state; break;
	}
}

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = 1600 / 2.0;
GLfloat lastY = 1000 / 2.0;
bool firstMouse = true;

void mousePassiveMove(int x, int y) {

	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y; // Reversed since y-coordinates go from bottom to left
	lastX = x;
	lastY = y;
	GLfloat sensitivity = 0.4;//
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//camera->setCameraFront(glm::normalize(front));
}



camera* Cam;
Scene MainScene;

bool mainMenu = true;
bool gameInit = false;


void init()
{
	MainScene.init();
}


void render(void)
{
	MainScene.render();
	std::cout << "MouseX: " << lastX << " Mousey: " << lastY << std::endl;
}


void update() {
	// update game information.
	glutPostRedisplay();

	if (keyState[(unsigned char)'M'] == BUTTON_DOWN || keyState[(unsigned char)'m'] == BUTTON_DOWN) 
	{  
		glutSetCursor(GLUT_CURSOR_NONE);
		glutFullScreen();
	//	glutExit()
	}

	if (mouseState[MOUSE_LEFT] == BUTTON_DOWN)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_DESTROY);
	}
	
	MainScene.update(keyState, ArrowKeyState, yaw, pitch, lastX, lastY);


	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInput_up);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 16); // anti-aliasing

	glutInitWindowPosition(50, 5); glutInitWindowSize(1600, 1000);
	glutCreateWindow("OpenGL Tests");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutIdleFunc(update);
	 
	glutMouseFunc(mouse);

	glutMotionFunc(mousePassiveMove);
	glutPassiveMotionFunc(mousePassiveMove);

	glutMainLoop();
	return 0;
}

