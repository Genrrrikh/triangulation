#ifndef GRAPH_H
#define GRAPH_H

#include "GL/glut.h"
#include <cmath>
#include <vector>
#include <ctime>



#define LL 0           //640*480
#define LO 1           //800*600
#define LHD 2          //HD
#define LFHD 3         //FullHD
#define LFK 4          //4K
#define FULL_SCREEN 1
#define NO_FULL_SCREEN 0


void display();                                      //funct to render image
void changeSize(int, int);                           //funct to set projection matrix (when user changed size of the window)
void pressNormalKeys(unsigned char, int, int);     //processing of clicks x4
void pressSpecialKey(int, int, int);
void releaseSpecialKey(int, int, int);
void releaseNormalKey(unsigned char, int, int);

//void setZeroPosition(void*);                             //fnc to find center lol

void InitializationGLUT(int *, char **, int, int, vector<triangle>*, void *);        //fnc to init window and draw
/*1st is pointer to argc, 2nd - char** argv (param to main)
3d is window size in pixels and the 4th is full_screen flag
void* is pointer to triangles vector, 2nd void * is pointer to points vector;
you must use fork or thread to use my library*/

#endif
