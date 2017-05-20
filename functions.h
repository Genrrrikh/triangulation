#ifndef FUNCTIONS
#define FUNCTIONS
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>


using namespace std;
/*
FILE* input=fopen("input.txt","r");	//file containing information about points
point mass_of_points[10000];	//array of points
int vector_pointer = 0;	//structure counter
int tr_pointer = 0;	//triangles counter

*/

class line{
public:
        double k;       //сoefficient k of a straight line 
        double b;       //coefficient b of a straight line
};

class point{    //point
public:
        double x;       //x coordinate of point 
        double y;       //y coordinate of point
        double z;       //z coordinate of point
        int type;       //auxiliary parameter for the function find_bridges
};



class triangle{	//triangle
public:
	point* uzel[3];	//pointers to nodes of a triangle
	triangle* trian[3];	//pointers to the neighbors of the triangle
};

class point_group{	//group of points
public:
	int father;	//number of the group that generated this
	int amount;	//number of points in a group
	point** mass;	//array of pointers to points
	vector <point*> shell;	//vector of pointers to the points that make up the shell
	int tr_amount;	//number of triangles in a group
	int triang[1];	//triangles in a group //БУДЕТ ВЕКТОРОМ, А НЕ ТУПЫМ МАССИВОМ
	point* bridge[4];	//bridges in the group
	vector <point*> coast_1;
	vector <point*> coast_2;
	bool fath;
	
	point_group(int k){      
	this->amount = k;
	this->mass = new point*[k];
	this->tr_amount = 0;
	this->fath = 0;
	}

	void del(){		
	delete [] mass;
	}

};

int compare_x(const void* x1, const void* x2); //сomparison function for a function qsort that sorts the structure pointgroup along the x axis

int compare_y(const void* x1, const void* x2); //сomparison function for a function qsort that sorts the structure pointgroup along the x axis

line line_by_points(point* t_1, point* t_2); //builds a line on two points

int diagonal(point* p0, point* p1, point* p2, point* p3); //checks whether the line is diagonal

int is_it_type_1(point* p0, point* p1, point* p2, point* p3); //сhecks whether this triangulation consists of 3 triangles

int delanau(point* p1, point* p2, point* p3, point* p4); //checks whether triangulation of 3 triangles is a Delaunay triangulation

void starting_triangulate(vector <triangle>* p_tr, vector <point_group>* p_vect, int num); //Performs a triangulation of a group of points of 3 or 4 points

void razdel(vector <point_group>* p_vect, int num, int type_of_sort); //recursive function realizing the primary partition
void make_ls(vector <point_group>* p_vect, vector <triangle>* p_tr, int num, int st_1, int st_2, int fin_1, int fin_2);
void fill_the_gap(vector <point_group>* p_vect, vector <triangle>* p_tr, int num);
void do_shell(vector <point_group>* p_vect, int num);
void find_bridges(vector <point_group>* p_vect, int num);
#endif
