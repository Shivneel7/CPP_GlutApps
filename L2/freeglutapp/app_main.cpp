#include <iostream>
#include <math.h>
#include <vector>
#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;


// Store the width and height of the window
int width = 640, height = 640;

vector<Rect*> grid;
vector<Rect*> menuButtons;

//0 = player 1s turn, 1 = player 2's turn
bool player = 0;

//Single player = 0, 2 player = 1;
bool mode = 0;

//currently on the menu screen?
bool menu = 1;

bool win = 0, draw = 0;

//start and end position of the win line
int win1, win2;

//used to count draws
int moveCount = 0;

char winner = ' ';


//checks for a Win
void checkWin(){
	//each col check
	for(int j = 0; j < 3; j ++){
		if(!grid[j*3]->isBlank() && grid[j*3]->mark == grid[j*3+1]->mark && grid[j*3]->mark == grid[j*3+2]->mark){
			win = true;
			winner = grid[j*3]->mark;
			cout << (char)(winner - 32) << " is the winner" << endl;
			cout << "Restart game to play again!"<<endl;			
			win1 = j*3;
			win2 = j*3+2;
			return;
		}
	}

	//each row check
	for(int i = 0; i < 3; i ++){
		if(!grid[i]->isBlank() && grid[i]->mark == grid[i+3]->mark && grid[i]->mark == grid[i+6]->mark){
			win = true;
			winner = grid[i]->mark;
			cout << (char)(winner - 32) << " is the winner!" << endl;
			cout << "Restart game to play again!"<<endl;			
			win1 = i;
			win2 = i + 6;
			return;
		}
	}

	//Diagonal check
	if(!grid[4]->isBlank()){
		//Top left to bottom right
		if(grid[4]->mark == grid[0]->mark && grid[4]->mark == grid[8]->mark){
			win = true;
			winner = grid[4]->mark;
			cout << (char)(winner - 32) << " is the winner!" << endl;
			cout << "Restart game to play again!"<<endl;
			win1 = 0;
			win2 = 8;
			return;
		}
		//Top right to bottom left
		if(grid[4]->mark == grid[6]->mark && grid[4]->mark == grid[2]->mark){
			win = true;
			winner = grid[4]->mark;
			cout << (char)(winner - 32) << " is the winner!" << endl;
			cout << "Restart game to play again!"<<endl;
			win1 = 2;
			win2 = 6;
			return;
		}
	}
	if(moveCount == 9){
		draw = 1;
		cout << "The game ended in a draw." << endl;
		cout << "Restart to play again!" << endl;
	}
}

//returns the square the AI will pick
Rect* pickSquare(){
	int ran = rand() % 9;
	for(int i = 0; i < 8; i ++){
		Rect* r = grid[(ran + i)%9];
		if(r->isBlank()){
			return r;
		}
	}

	// for(Rect* r : grid){
	// 	if(r->isBlank()){
	// 		return r;
	// 	}
	// }
}

void drawWin(){
		glLineWidth(15);

		glColor3f(0,1,0);
		glBegin(GL_LINES);

		glVertex3f(grid[win1]->x + grid[win1]->w/2, grid[win1]->y - grid[win1]->h/2,.1);
		glVertex3f(grid[win2]->x + grid[win1]->w/2, grid[win2]->y - grid[win1]->h/2,.1);

		glEnd();
}

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(menu){
		for(Rect* r : menuButtons){
			r->draw();
		}
	}else{
		for(Rect* r : grid){
			r->draw();
		}
		if(win){
			drawWin();
		}
	}

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...
	if(!s && !win && !draw){//only calls on mouse down, not when the mouse button goes back up
		if(menu){
			for(Rect* r : menuButtons){
				if(r->contains(mx,my)){
					if(r->mark == '1'){
						mode = 0;
					}else{
						mode = 1;
					}
					menu = 0;
				}
			}
		}else{
			for(Rect* r : grid){
				if(r->contains(mx,my) && r->isBlank()){
					if(!mode){//one player AI mode
						r->select('x');
						moveCount++;
						checkWin();
						if(!win && !draw){
							pickSquare()->select('o');
							moveCount++;
							checkWin();
						}
					}else{
						//2 player mode
						if(player){
							r->select('o');
						}else{
							r->select('x');
						}
						moveCount++;
						checkWin();
						player = !player;
					}
				}
			}
		}
	}

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {	
		// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;
		// More cases here if you need...
	//1 player
	case '1':
		if(menu){
			mode = 0;
			menu = 0;
		}
		break;
	//2 player
	case '2':
		if(menu){
			mode = 1;
			menu = 0;
		}
		break;
	}
	// After all the state changes, redraw the scene
	glutPostRedisplay();
}

void appKeyboardUpFunc(unsigned char key, int x, int y) {

}

void idle(){

}


int main(int argc, char** argv) {

	//creates the grid
	for(int i = 0; i < 3; i ++){
		for(int j = 0; j < 3; j ++){
			grid.push_back(new Rect(-1 + i * .7, 1 - .7  * j - .01, .6, .6, ' '));
		}
	}
	
	menuButtons.push_back(new Rect(-.5,.7,1,.3, 0, 1, 1, '1'));
	menuButtons.push_back(new Rect(-.5,-.2,1,.3, 0, 1, 1, '2'));

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	// Start with a slightly smaller window (bug in macOS Catalina)
	glutInitWindowSize(width-1, height-1);

	// Create the window
	glutCreateWindow("Shivneel Chand's Tic Tac Toe");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// This gets triggered when we release a keyboard key
	glutKeyboardUpFunc(appKeyboardUpFunc);
    
	// Resize your window to the desired size (bug in macOS Catalina)
    glutReshapeWindow(width, height);

	// Set the idle function. It gets called repeatedly all the time
	glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
