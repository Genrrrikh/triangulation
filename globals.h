#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>

using namespace std;


FILE* input=fopen("input.txt","r");     //file containing information about points
point mass_of_points[10000];    //array of points
int vector_pointer = 0; //structure counter
int tr_pointer = 0;     //triangles counter
//KOLYAN LIKES IT 

