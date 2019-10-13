#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <math.h>
#include <string>
#include "particle.h"
using std::vector;
float oldx=0,oldy=0;
bool pausee = true;
int sizee = 0;
float xx = 0,yy = 0;
bool StartInertia = false;
bool life = false;
bool clickstart = false;
int height = 600;
vector<particle> points;
vector<int> pointaa;

float mymatrix[16]={2,0,0,1,
                    0,2,0,1,
                    0,0,2,1,
                    0,0,0,1};
void CreateParticle(void){
    for (int i = 0; i < 500; i++){
    	particle point;
    	points.push_back(point);
    }
}
//Writes text on the screen.
//Refrence: https://www.youtube.com/watch?v=elE__Nouv54
void drawText(const char *text, int length, int x, int y){
	glColor3f(0,1,0);
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0,600,0,600,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x,y);
	for(int i =0; i< length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void drawPoint(float x, float y) {
    glBegin(GL_POINTS);
    	glVertex3f(x, y, 0.0f);
    glEnd();
    
}
//FPS from tutorial 2 code
void FPS(int val){
    if (pausee){
        glutPostRedisplay();
    }
    glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}
//Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glPopMatrix();
    glPushMatrix();
    //If user has clicked once, the texts disappear
    if(clickstart == false){
    	std::string WelcomeMessage = "Welcome to the world";
    	std::string WelcomeMessage2 = "where inertia does not exist always.";
    	std::string WelcomeMessage3 = "CLICK TO START";
    	drawText(WelcomeMessage.data(),WelcomeMessage.size(), 200,350);
    	drawText(WelcomeMessage2.data(),WelcomeMessage2.size(), 140,300);
    	drawText(WelcomeMessage3.data(),WelcomeMessage3.size(), 214,250);
    }
    else{
	    for(int i = 0; i< (int)points.size(); i++){
	    	//Drawing the points
	    	glPointSize(points[i].size);
	    	glColor3f(points[i].c1, points[i].c2, points[i].c3);
	    	drawPoint(points[i].PX, points[i].PY);
	    	//if l is pressed, life will be true	
	    	if(life == true){	
	    		StartInertia = false;//no inertia when particles are alive.
	    		points[i].life -= 0.0000000000001;
	    		if(points[i].life == 0){
	    			points.erase(points.begin() + i);//Erases the points
					particle point;
	    			points.push_back(point);//Adds a new point.	
	    	}
	    	}
	    }
	    glPushMatrix();
	    //Inertia
	    if(StartInertia == true){
	    	//int arrsize = sizeof(pointsI)/sizeof(*pointsI);
	    	for (int i =0; i< (int)pointaa.size(); i++){
		    	for(int j = 0; j < 1000; j++){
		    		points[pointaa[i]].PX += (xx/555) * points[pointaa[i]].speed;
		  		 	points[pointaa[i]].PY += (yy/555) * points[pointaa[i]].speed;
		    	}
		}
	    }
	    glPopMatrix();
    
   }
  	glPopMatrix();
    glutSwapBuffers();
}
//Returns the distance between two points.
float distanceTo(float mx, float my, float pointx, float pointy){
	return sqrt(pow((mx - pointx),2) + pow((my - pointy),2));
}
void keyboard(unsigned char key, int xIn, int yIn)
{
	float newx = (((float)(xIn-300)/10)/3);
	float newy = ((float)((height - 300)-yIn)/10)/3;
    
    switch (key){
    	//Adds a new partcile at the current cursor.
    	case 'a':
    	{
    		particle newpoint;
			newpoint.PX = newx;
    		newpoint.PY = newy;
    		points.push_back(newpoint);
    		break;
    	}
    	//Removes the partcle close to the cursor
    	case 'd':
    	{
    		StartInertia = false;
    		int j = 0;
    		float tempdistance = 50;
    		if((int)points.size() > 0){
	    		for (int i = 0; i< (int)points.size(); i++){
	    			float distance = distanceTo(newx, newy, points[i].PX, points[i].PY);
	    			if(distance<tempdistance){
	    				j = i;
	    				tempdistance = distance;
	    			}
	    		}
	    		points.erase(points.begin() + j);
	    	}
    		break;
    	}
    	//Increases the range
    	case '+':
    	{
    		for (int i = 0; i< (int)points.size(); i++){
    				points[i].range++;
    		}
    		break;
    	}
    	//Decreases the range
    	case '-':
    	{
    		for (int i = 0; i< (int)points.size(); i++){
    				points[i].range--;
    		}
    		break;
    	}
    	//reset
    	case 'r':
    	{
    		StartInertia = false;
    		points.clear();
    		for (int i = 0; i< 500; i++){
    				particle point;
    				points.push_back(point);
    		}
    		break;
    	}
    	//Exit
    	case 'q':
    		exit(0);
    		break;
    	//Exit
    	case 27:
    		exit(0);
    		break;
    	//Stops/Runs the animation
    	case ' ':
    		pausee = !pausee;
    		break;
    	//Starts partcles life span and crease new ones
    	case 'l':
    		life = !life;
    		break;
    	//Swaps x and y of a partcle(closes to to the mouse)
    	case 's':
			for (int i =0; i< (int)points.size(); i++){
			  float distancee = distanceTo(newx, newy, points[i].PX, points[i].PY);
	  		  if(distancee < 1){
	    		float temp = points[i].PX;//swaping x and ys.
	    		points[i].PX = points[i].PY;
	    		points[i].PY = temp;
			   }
			}
    		break;
    }
}
void specialKeys(int key ,int x, int y){
	switch(key){
		//Increase the speed.
		//if up arrow is pressed
		case GLUT_KEY_UP:{
			for (int i = 0; i< (int)points.size(); i++){
    				points[i].speed++;
    		}
    		break;
		}
		//if down arrow is pressed
		case GLUT_KEY_DOWN:{
			for (int i = 0; i< (int)points.size(); i++){
    				points[i].speed--;
    		}
    		break;
		}
	}
}
//Left mouse button
void motionFuncLeft(int x, int y){
	StartInertia = false;
	//New x and y based on the window size
	float newx = (((float)(x-300)/10)/3);
	float newy = ((float)((height - 300)-y)/10)/3;
	xx = newx - oldx;//change in x
	yy = newy - oldy;//change in y
	oldx = newx;
	oldy = newy;
	pointaa.clear();//deletes all the points in pointaa
	//mover = mover + 0.01;
	for (int i =0; i< (int)points.size(); i++){
		int distance = distanceTo(newx, newy, points[i].PX, points[i].PY);
	    if(distance <= points[i].range){ 
	   		points[i].PX += (xx * points[i].speed);
	  	 	points[i].PY += (yy * points[i].speed);
	  	 	pointaa.push_back(i);//Used later for inertia
	  	 	newx -= (xx * points[i].speed);
	  	 	newy -= (yy * points[i].speed);
	   }
	}
	
}
//Right mouse button
void motionFuncRight(int x, int y){
	//New x and y based on the windows size.
	float newx = (((float)(x-300)/10)/3);
	float newy = ((float)((height - 300)-y)/10)/3;
	float smootherx = newx/30;//makes the animation smoother.
	float smoothery = newy/30; 
	for (int i =0; i< (int)points.size(); i++){
		int distance = distanceTo(newx, newy, points[i].PX, points[i].PY);
	    if(distance <= points[i].range){
	   		points[i].PX += (smootherx * points[i].speed);
	  	 	points[i].PY += (smoothery * points[i].speed);
	  	 	newx += (xx * points[i].speed);
	  	 	newy += (yy * points[i].speed);
	   }
	}
	}
//Tag for inertia animation in the display function
void inertia(void){
	StartInertia = true;
}

void mouseClicks(int button, int state, int x, int y){
	//StartInertia = false;
	//If clicked, the text disappears.
	clickstart = true;
	//If left mouse button is pressed
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			glutMotionFunc(motionFuncLeft);
		}
		//If the left mouse button is released do this
		else if(state == GLUT_UP){
			inertia();
		}
	}
	//if the right mouse button is pressed, call the motion function
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		glutMotionFunc(motionFuncRight);
	}
}
//passive motion function
void pass(int x, int y){
	float newx = (((float)(x-300)/10)/3);
	float newy = ((float)((height - 300)-y)/10)/3;
	for (int i =0; i< (int)points.size(); i++){
		float distancee = distanceTo(newx, newy, points[i].PX, points[i].PY);
	    if(distancee < 0.5){
	    //change the color
	    	points[i].c1 = 1;
	    	points[i].c2 = 0;
	    	points[i].c3 = 0;
	   }
	}
}
//Reshape function. Gets the changed height.
void shaped(int w, int h){
	height = h;
}
void instruction(void){
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		"INSTRUCTION", "Whenever mouse hits a particle, its color changes to red.", "Left mouse button attracts particles", "Right mouse button repels particle",
		"Key = a -> Adds a new particle at the current cursor location.", "Key = d -> Removes the particle close to the cursor",
		"Key = +/- -> Increases/decrease the range", "Key = up/down -> increase/decrease the speed", "Key = space bar -> Stops/runs the animation", "Key = r -> reset",
		"Key = q or Escape -> exit", "Key = l(smalll L) -> starts particle life span", "key = s -> Swaps x and y of a particle close to the cursor.");
}
//main function - program entry point 
int main(int argc, char** argv)
{
	srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("2D Particle Flockign System");
	glMatrixMode(GL_PROJECTION);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    CreateParticle();
    glutDisplayFunc(display);
    glutTimerFunc(0, FPS, 0);
    gluOrtho2D(-10,10,-10,10);
    glutMouseFunc(mouseClicks);
    glutPassiveMotionFunc(pass);
    glutReshapeFunc(shaped);
    instruction();
    glutMainLoop();
    return 0;
}
