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

neural *netx;
neural *nety;

float bx;
float by;

float vx;
float vy;

float maxx =  0.8;
float maxy =  0.5;

float minx = -0.8;
float miny = -0.5;

float net_p_x = -0.8;
float human_p_x = 0.8;

float net_p_y;
float human_p_y;
float net_p_y_tmp;

int net_miss   = 0; 
int human_miss = 0;
int net_hits   = 0;
int human_hits = 0;

int tim = 30;

bool p = false;

using namespace std;


void print_s(){
	cout << (char)27 << "[2K";

	cout << "\rcomputer: (miss= " << net_miss << " hits= " << net_hits << ")";
	cout << ", human : (miss= " << human_miss << " hits= " << human_hits << ")";
	cout << ", t :" << tim ;
	cout.flush();
}

void print_header(){
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "                                                                  " << endl;
	cout << "		           pong playing neural network      	           " << endl;
	cout << "               --------------------------------                   " << endl;
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
		vx = (float)(rand() % 10) / 100.0 - 0.04;  
	}while(vx == 0);
	if(vx >= 0) vx += 0.01;
	else vx -= 0.01;
	do{
		vy = (float)(rand() % 10) / 100.0 - 0.04;  
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
	par(net_p_x + 0.01, net_p_x - 0.02, net_p_y + 0.15, net_p_y - 0.15, 0.0);
	par(human_p_x + 0.02, human_p_x - 0.01, human_p_y + 0.15, human_p_y - 0.15, 0.0);
	
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
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}else if((char)key == 'z'){
		tim++;
	}else if((char)key == 'x'){
		if(tim > 0) tim--;
	}else if((char)key == 'k'){
		start();
	}else if((char)key == 'p'){
		p = !p;
	}else if((char)key == 'r'){
		net_hits = human_hits = net_miss = human_miss = 0;
		print_s();
		start();
	}
}
void mouse( int x, int y){
	human_p_y = -1*((y)/400.0f) + maxy;
	if(human_p_y > maxy - 0.10) human_p_y = maxy - 0.10;
	if(human_p_y < miny + 0.12) human_p_y = miny + 0.12;
	if(!p) glutPostRedisplay();
}
void update(){
	float input[5];
	input[0] = bx;
	input[1] = by;
	input[2] = vx;
	input[3] = vy;
	
	float *out;
	if(vx <= 0){
		input[0] = -bx;
		input[2] = -vx;
		net_p_y_tmp = input[4] = net_p_y;
		out = netx -> feed(input);
		net_p_y += (out[0] - 0.5) ;
		if(net_p_y > maxy - 0.10) net_p_y = maxy - 0.10;
		if(net_p_y < miny + 0.12) net_p_y = miny + 0.12;
	}
}
void frame(int a) {
	if(!p){
		update();
		move();
		
		if(by <= miny || by >= maxy)
			turny();
		if(bx <= minx){
			if(net_p_y + 0.15 > by && net_p_y - 0.15 < by){ 
				turnx();
				net_hits++;
			}else{
				net_miss++;
				float in[1];
				in[0] = (by - net_p_y_tmp)  + 0.5;
				netx -> learn(in);	
				start();
			}
			print_s();
		}else if(bx >= maxx){	
			if(human_p_y + 0.15 > by && human_p_y - 0.15 < by){ 
				turnx();
				human_hits++;
			}else{
				human_miss++;;
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
	netx = new neural(5, 1, 3, 10, 0.2, 0.0);
	netx -> init();
	int num = netx -> get_num_weights();
	float *weights = (float *)malloc(sizeof(float) * num);
	
	FILE *fp = fopen("p1.data", "r");
	if(fp == NULL){
		cout << "file read error !!! \n" << endl;
		exit(0);
	}
	for(int i = 0; i < netx -> get_num_weights(); i++){
		fscanf(fp, "%f\n", &weights[i]);
	}
	netx -> put_weights(weights);
	print_header();
	print_s();
	start();
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("neural pong");
	
	init();
	glutTimerFunc(200, frame, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
}


