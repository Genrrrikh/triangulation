#include "Graphics.h"
#include "functions.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>
#include <algorithm>
#include <cmath>

#define RAD_GRAD 57.32484076433121
double X = 1, Y = 1, Z = 0, dZ = 0.75, topZ = 0.1;	//zero point
double _forward = 0, _sideways = 0;
double dforward = 0, dsideways = 0;
 double Anglefi = 0, Angleksy = 0;	//spherical coordinates (where the camera is looking)45
double dAnglefi = 0, dAngleksy = 0;
 double zoom = 3, dzoom = 0;
int view_mode = 0;

 clock_t _time = 0, old_time = 0;
double dtime = 0;
 int MouseX = -1, MouseY = -1;

  vector < triangle > *trian_vect_pointer;
   void
InitializationGLUT (int *argc, char **argv, int param, int flag,
		    vector < triangle > *trian_pointer,
		    void *pointer_to_points)
{
     trian_vect_pointer = trian_pointer;
     
	//setZeroPosition(pointer_to_points);
	glutInit (argc, argv);
     switch (param) {
    case LL:
	glutInitWindowSize (640, 480);	//window size
	glutInitWindowPosition (300, 100);	//window position
	break;
     case LO:
	glutInitWindowSize (800, 600);	//window size
	glutInitWindowPosition (300, 100);	//window position
	break;
     case LHD:
	glutInitWindowSize (1024, 720);	//window size
	glutInitWindowPosition (0, 0);	//window position
	break;
     case LFHD:
	glutInitWindowSize (1920, 1080);
	glutInitWindowPosition (0, 0);
	break;
     case LFK:
	glutInitWindowSize (4096, 3072);
	glutInitWindowPosition (0, 0);
	break;
     default:
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (300, 100);
	break;
    }
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_ACCUM
			    | GLUT_DEPTH);
    glutCreateWindow ("TRIANGULATOR");	//title
     glEnable (GL_DEPTH_TEST);	//DEPTH TEST
    glDepthFunc (GL_LEQUAL);	//Set the type of depth-test
    glShadeModel (GL_SMOOTH);	// Enable smooth shading
    glClearColor (0.53, 0.81, 0.98, 1);	//background color - sky blue
    glutDisplayFunc (display);	//set rendering function
    glutReshapeFunc (changeSize);	//set function to change size
    glutIdleFunc (display);	//!!!
    glutKeyboardFunc (pressNormalKeys);	//set fnc to press key x4
    glutSpecialFunc (pressSpecialKey);
    glutSpecialUpFunc (releaseSpecialKey);
    glutKeyboardUpFunc (releaseNormalKey);
     glutMouseFunc (pressMouseButton);
    glutMotionFunc (mouseMove);
    
	//glutMouseWheelFunc();//1111111111111111111111111
	glutIgnoreKeyRepeat (1);	//for smooth movement
     if (flag == FULL_SCREEN) {
	glutFullScreen ();
    }
     glutMainLoop ();		//GLUT main loop
};

 void
display ()
{
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();		//clr matrix
    _time = clock ();
    dtime = (_time - old_time) * 15.0 / CLOCKS_PER_SEC + 0.0000000000001;
    old_time = _time;
     Anglefi += dAnglefi * dtime;
    Angleksy += dAngleksy * dtime;
     if (Angleksy > 0) {
	Angleksy = 0;
    }
    if (Angleksy < -87) {
	Angleksy = -87;
    }
     if (Anglefi > 360) {
	Anglefi = 0;
    }
    if (Anglefi < -360) {
	Anglefi = 0;
    }
     _forward += dforward * dtime * zoom;
    _sideways += dsideways * dtime * zoom;
     zoom += zoom * dzoom * dtime;
      glRotated (Anglefi, 0, 0, 1);
    
	//rotation
	glRotated (Angleksy, cos (Anglefi / RAD_GRAD),
		   -sin (Anglefi / RAD_GRAD), 0);
       glTranslated (-_sideways * cos (Anglefi / RAD_GRAD),
			 _sideways * sin (Anglefi / RAD_GRAD), 0.0);
     glTranslated (-_forward * sin (Anglefi / RAD_GRAD),
		     -_forward * cos (Anglefi / RAD_GRAD), 0.0);
     glTranslated (-sin (Angleksy / RAD_GRAD) * sin (Anglefi / RAD_GRAD) *
		     zoom,
		     -sin (Angleksy / RAD_GRAD) * cos (Anglefi / RAD_GRAD) *
		     zoom, -cos (Angleksy / RAD_GRAD) * zoom);
      glTranslated (-X, -Y, -Z);
     int triangles_vector_size = 0, counter = 0;
    double red = 0, green = 0, blue = 0, delta = 0;

      
	//glutWireTorus(0.5, 2.5, 5, 5);
	triangles_vector_size = (*trian_vect_pointer).size ();
     glBegin (GL_TRIANGLES);
    for (counter = 0; counter < triangles_vector_size; counter++) {
	
/*
if (counter % 7 == 0){
           
                glColor3d(255, 0, 0);
		glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
	//	glColor3d(0, 1, 0);
           	glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
	//	glColor3d(0, 0, 1);
            	glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
			(*trian_vect_pointer)[counter].uzel[2]->z);
} 


else if (counter % 7 == 1){

                glColor3d(0, 255, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}
               
else if (counter % 7 == 2){

                glColor3d(0, 0, 255);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}

else if (counter % 7 == 3){

                glColor3d(255, 255, 255);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}

else if (counter % 7 == 4){

                glColor3d(255, 255, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}

else if (counter % 7 == 5){

                glColor3d(255, 0, 255);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}

else if (counter % 7 == 6){

                glColor3d(0, 0, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[0]->x,
                        (*trian_vect_pointer)[counter].uzel[0]->y,
                        (*trian_vect_pointer)[counter].uzel[0]->z);
        //      glColor3d(0, 1, 0);
                glVertex3d((*trian_vect_pointer)[counter].uzel[1]->x,
                        (*trian_vect_pointer)[counter].uzel[1]->y,
                        (*trian_vect_pointer)[counter].uzel[1]->z);
        //      glColor3d(0, 0, 1);
                glVertex3d((*trian_vect_pointer)[counter].uzel[2]->x,
                        (*trian_vect_pointer)[counter].uzel[2]->y,
                        (*trian_vect_pointer)[counter].uzel[2]->z);
}
*/ 
	     glColor3d (255, 0, 0);
	glVertex3d ((*trian_vect_pointer)[counter].uzel[0]->x, 
		     (*trian_vect_pointer)[counter].uzel[0]->y, 
		     (*trian_vect_pointer)[counter].uzel[0]->z);
	glColor3d (0, 255, 0);
	glVertex3d ((*trian_vect_pointer)[counter].uzel[1]->x, 
		     (*trian_vect_pointer)[counter].uzel[1]->y, 
		     (*trian_vect_pointer)[counter].uzel[1]->z);
	glColor3d (0, 0, 255);
	glVertex3d ((*trian_vect_pointer)[counter].uzel[2]->x, 
		     (*trian_vect_pointer)[counter].uzel[2]->y, 
		     (*trian_vect_pointer)[counter].uzel[2]->z);
                  }
             glEnd ();
     glFlush ();
    glutSwapBuffers ();
};

 void
changeSize (int w, int h)
{
    if (h == 0 || w == 0) {
	h = 1;
	w = 1;
    }
     float ratio = w * 1.0 / h;

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glViewport (0, 0, w, h);
    gluPerspective (45.0, ratio, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
};

 void
pressNormalKeys (unsigned char key, int x, int y)
{
     switch ((char) key) {
    case 27:
	exit (0);
	break;
    case 'w':
    case 'W':
    case 'ö':
    case 'Ö':
	dforward = 0.2;
	break;
    case 's':
    case 'S':
    case 'û':
    case 'Û':
	dforward = -0.2;
	break;
    case 'â':
    case 'Â':
    case 'd':
    case 'D':
	dsideways = 0.2;
	break;
    case 'a':
    case 'A':
    case 'ô':
    case 'Ô':
	dsideways = -0.2;
	break;
     case 'ê':
    case 'Ê':
    case 'r':
    case 'R':
	_forward = _sideways = 0;
	Anglefi = Angleksy = 0;
	zoom = 3;
	break;
     case 'i':
    case 'I':
    case 'ø':
    case 'Ø':
	dzoom = -0.2;
	break;
     case 'o':
    case 'O':
    case 'ù':
    case 'Ù':
	dzoom = 0.2;
	break;
     case ' ':
	 view_mode++;
	 if (view_mode > 3) {
	    view_mode = 0;
	}
	 switch (view_mode) {
	case 0:
	    Anglefi = 0;
	    Angleksy = 0;
	    break;
	case 1:
	    Anglefi = 0;
	    Angleksy = -60;
	    break;
	case 2:
	    Anglefi = 120;
	    Angleksy = -60;
	    break;
	case 3:
	    Anglefi = 240;
	    Angleksy = -60;
	    break;
	}
	break;
    }
};

 void
pressSpecialKey (int key, int x, int y)
{
     switch (key) {
    case GLUT_KEY_LEFT:
	dAnglefi = 50;
	break;
    case GLUT_KEY_RIGHT:
	dAnglefi = -50;
	break;
    case GLUT_KEY_UP:
	dAngleksy = 20;
	break;
    case GLUT_KEY_DOWN:
	dAngleksy = -20;
	break;
    }
};

 void
releaseSpecialKey (int key, int x, int y)
{
     switch (key) {
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
	dAnglefi = 0.0;
	break;
     case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
	dAngleksy = 0.0;
	break;
    }
};

 void
releaseNormalKey (unsigned char key, int x, int y)
{
     switch ((char) key) {
    case 27:
	exit (0);
	break;
     case 'w':
    case 'W':
    case 'ö':
    case 'Ö':
    case 's':
    case 'S':
    case 'û':
    case 'Û':
	dforward = 0.0;
	break;
    case 'â':
    case 'Â':
    case 'd':
    case 'D':
    case 'a':
    case 'A':
    case 'ô':
    case 'Ô':
	dsideways = 0.0;
	break;
     case 'i':
    case 'I':
    case 'ø':
    case 'Ø':
    case 'ù':
    case 'Ù':
    case 'o':
    case 'O':
	dzoom = 0.0;
	break;
    }
};

 
/*void setZeroPosition(void *pointer_to_points){

    int point_vector_size=0, counter=0;
    double Xmax=0, Xmin=0, Ymax=0, Ymin=0, Zmax=0, Zmin=0;

    //point_vector_size=(*main_pointer).size();

    Xmax=Xmin=(*pointer_to_points)[0].x;
    Ymax=Ymin=(*pointer_to_points)[0].y;
    Zmax=Zmin=(*pointer_to_points)[0].z;


    for(counter=0;counter<point_vector_size;counter++){
        if((*pointer_to_points)[counter].x > Xmax){Xmax=(*pointer_to_points)[counter].x;}
        if((*pointer_to_points)[counter].x < Xmin){Xmin=(*pointer_to_points)[counter].x;}
        if((*pointer_to_points)[counter].y > Ymax){Ymax=(*pointer_to_points)[counter].y;}
        if((*pointer_to_points)[counter].y < ymin){Ymin=(*pointer_to_points)[counter].y;}
        if((*pointer_to_points)[counter].z > Zmax){Zmax=(*pointer_to_points)[counter].z;}
        if((*pointer_to_points)[counter].z < Zmin){Zmin=(*pointer_to_points)[counter].z;}
    }

    X=(Xmax-Xmin)/2.0;
    Y=(Ymax-Ymin)/2.0;
    dZ=(Zmax-Zmin);
    if(0==dZ){dZ=1;}
    Z=Zmax+dZ/10.0;
    topZ=Zmax;
};         */ 
    void
pressMouseButton (int button, int state, int x, int y)
{
     if (button == GLUT_LEFT_BUTTON) {	//when we pushed left button, allow movement
	if (state == GLUT_UP) {
	    MouseX = MouseY = -1;
	}
	
	else {			// state = GLUT_DOWN, allow movement
	    MouseX = x;
	    MouseY = y;
	}
    }
     if (button == 3) {
	zoom -= zoom * 0.2;
    }
    if (button == 4) {
	zoom += zoom * 0.2;
    }
 };

 void
mouseMove (int x, int y)
{
    if ((MouseX >= 0) && (MouseY >= 0)) {	//when movement allowed
	Anglefi += (x - MouseX) * 0.1;
	Angleksy += (y - MouseY) * 0.1;
	MouseX = x;
	MouseY = y;
    }
};

 void
mouseWheel (int wheel, int direction, int x, int y)
{
    if (direction > 0) {
	zoom -= zoom * 0.1;
    }
    if (direction < 0) {
	zoom += zoom * 0.1;
    }
}


