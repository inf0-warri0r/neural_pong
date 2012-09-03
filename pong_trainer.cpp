/*
*Author :Tharindra Galahena
*Project:pong game playing neural network (AI)
*Date   :02/09/2012
*License:
* 
*     Copyright 2012 Tharindra Galahena
*
* This program is free software: you can redistribute it and/or modify it under the terms of 
* the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version. This program is distributed
* in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with This program. 
* If not, see http://www.gnu.org/licenses/.
*
*/


#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "neural_net.h"

neural *net_left;
neural *net_right;

float bx;
float by;

float vx;
float vy;

float maxx =  0.8;
float maxy =  0.5;

float minx = -0.8;
float miny = -0.5;

float p_left_x  = -0.8;
float p_right_x = 0.8;

float p_left_y;
float p_right_y;
float p_left_y_tmp;
float p_right_y_tmp;

int left_miss  = 0; 
int right_miss = 0;
int left_hits  = 0;
int right_hits = 0;

int tim = 20;

bool p = false;
using namespace std;

void print_s(){
	cout << (char)27 << "[2K";
	cout << "\rAI 1 :(miss= " << left_miss << " hits= " << left_hits << ")";
	cout << ", AI 2 :(miss= " << right_miss << " hits= " << right_hits << ")";
	cout << ", t :" << tim ;
	cout.flush();
}
void print_header(){
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "                                                                  " << endl;
	cout << "		         pong playing neural network trainer     	       " << endl;
	cout << "             -----------------------------------------            " << endl;
	cout << "                                                                  " << endl;
	cout << " * Created By : Tharindra Galahena ( inf0_warri0r )               " << endl;
	cout << " * Blog       : http://www.inf0warri0r.blogspot.com               " << endl; 		
	cout << "                                                                  " << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
}
void move(){
	bx += vx;
	by += vy;
}
void start(){
	bx = 0.0;
	by = 0.0;
	do{
		vx = (float)(rand() % 10) / 100.0 - 0.05;  
	}while(vx == 0);
	if(vx >= 0) vx += 0.01;
	else vx -= 0.01;
	do{
		vy = (float)(rand() % 10) / 100.0 - 0.05;  
	}while(vy == 0.0);
	if(vy >= 0) vy += 0.01;
	else vy -= 0.01;
}
void turnx(){
	vx *= -1.0;
}
void turny(){
	vy *= -1.0; 
}
void border(float x1, float y1, float z1, float w, float h){
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	
	glVertex3f(x1            , y1 + 0.04, z1);
	glVertex3f(x1 - 2*w + 0.1, y1 + 0.04, z1);
	glVertex3f(x1 - 2*w + 0.1, y1 + 0.05, z1);
	glVertex3f(x1            , y1 + 0.05, z1);

	glEnd();

	glBegin(GL_QUADS);
	
	glVertex3f(x1            , y1 + 2*h - 0.04, z1);
	glVertex3f(x1 - 2*w + 0.1, y1 + 2*h - 0.04, z1);
	glVertex3f(x1 - 2*w + 0.1, y1 + 2*h - 0.05, z1);
	glVertex3f(x1            , y1 + 2*h - 0.05, z1);

	glEnd();

	glBegin(GL_QUADS);
	
	glVertex3f(x1       , y1 + 0.05      , z1);
	glVertex3f(x1 + 0.01, y1 + 0.05      , z1);
	glVertex3f(x1 + 0.01, y1 + 2*h - 0.05, z1);
	glVertex3f(x1       , y1 + 2*h - 0.05, z1);

	glEnd();

	glBegin(GL_QUADS);
	
	glVertex3f(x1 - 2*w +  0.1, y1 + 0.05      , z1);
	glVertex3f(x1 - 2*w + 0.11, y1 + 0.05      , z1);
	glVertex3f(x1 - 2*w + 0.11, y1 + 2*h - 0.05, z1);
	glVertex3f(x1 - 2*w +  0.1, y1 + 2*h - 0.05, z1);

	glEnd();
}
void par(float x1, float x2, float y1, float y2, float z1){
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);

	glEnd(); 
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef(0.0, 0.0, -2.0);
	
	par(bx  + 0.01, bx  - 0.01, by  + 0.01, by  - 0.01, 0.0);
	par(p_left_x + 0.01, p_left_x - 0.02, p_left_y + 0.15, p_left_y - 0.15, 0.0);
	par(p_right_x + 0.02, p_right_x - 0.01, p_right_y + 0.15, p_right_y - 0.15, 0.0);
	
	border(minx - 0.05, maxy + 0.01, 0.0, minx, miny);
	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);

}
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(45.0, (double)w/(double)h, 0.1, 200.0);
	
}
void wright_weights(){
	FILE *f1 = fopen("p1.data", "w");
	float *weights_x = net_left -> get_weights();
	for(int i = 0; i < net_left -> get_num_weights(); i++){
			fprintf(f1, "%f\n", weights_x[i]);
	}
	fclose(f1);
	FILE *f2 = fopen("p2.data", "w");
	float *weights_y = net_right -> get_weights();
	for(int i = 0; i < net_right -> get_num_weights(); i++){
		fprintf(f2, "%f\n", weights_y[i]);
	}
	fclose(f2);
	
	cout << (char)27 << "[2K";	
	cout << "\rweights are recorded !!! " << endl;
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}else if((char)key == 'z'){
		tim++;
	}else if((char)key == 'x'){
		if(tim > 0) tim--;
	}else if((char)key == 'r'){
		start();
	}else if((char)key == 'w'){
		wright_weights();
	}else if((char)key == 'p'){
		p = !p;
	}
}
void update(){
	float input[5];
	input[0] = bx;
	input[1] = by;
	input[2] = vx;
	input[3] = vy;
	
	float *out;
	if(vx > 0){
		p_right_y_tmp = input[4] = p_right_y;
		out = net_right -> feed(input);
		p_right_y += (out[0] - 0.5) ;
		if(p_right_y > maxy - 0.10) p_right_y = maxy - 0.10;
		if(p_right_y < miny + 0.12) p_right_y = miny + 0.12;
	}else{
		input[0] = -bx;
		input[2] = -vx;
		p_left_y_tmp = input[4] = p_left_y;
		out = net_left -> feed(input);
		p_left_y += (out[0] - 0.5) ;
		if(p_left_y > maxy - 0.10) p_left_y = maxy - 0.10;
		if(p_left_y < miny + 0.12) p_left_y = miny + 0.12;
	}
	
}
void frame(int a) {
	if(!p){
		update();
		move();
		if(by <= miny || by >= maxy)
			turny();
		if(bx <= minx){
			if(p_left_y + 0.15 > by && p_left_y - 0.15 < by){ 
				turnx();
				left_hits++;
			}else{
				left_miss++;
				float in[1];
				in[0] = (by - p_left_y_tmp)  + 0.5;
				net_left -> learn(in);	
				start();
			}
			print_s();
		}else if(bx >= maxx){
			
			if(p_right_y + 0.15 > by && p_right_y - 0.15 < by){ 
				turnx();
				right_hits++;
			}else{
				right_miss++;
				float in[1];
				in[0] = (by - p_right_y_tmp)  + 0.5;
				net_right -> learn(in);
				start();
			}
			print_s();
		}
		glutPostRedisplay();	
	}
		
	glutTimerFunc(tim, frame, 0);
}

int main(int argc, char **argv){
	
	srand(time(0));
	net_left = new neural(5, 1, 3, 10, 0.2, 0.0);
	net_left -> init();

	net_right = new neural(5, 1, 3, 10, 0.2, 0.0);
	net_right -> init();
	
	print_header();
	
	start();
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("neural pong trainer");
	init();
	glutTimerFunc(200, frame, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	
	glutMainLoop();
}

