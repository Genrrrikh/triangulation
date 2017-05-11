#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>
#include "delanau.cpp"

using namespace std;
int main ()
{
int i,N,j,k;
vector <point_group> vect;
vector <point_group>::iterator p;
vector <point_group>* p_vect = &vect;
vector <triangle> triangles;
vector <triangle>* p_tr = &triangles;
cin >> N;

for (i=0; i<(2*N); i++)
{
	if (i<N) fscanf(input,"%lf",&mass_of_points[i].x);
	else fscanf(input,"%lf",&mass_of_points[i-N].y);
}

vect.push_back(point_group(N)); //с помощью конструктора выделяем память под первую структуру и сразу кладем ее в вектор
vect[0].father = -1;
p = vect.begin();

for (i=0; i<N; i++){
	(*p).mass[i] = &(mass_of_points[i]); //заполняем структуру
}

qsort((*p).mass, (*p).amount, sizeof(point*), compare_x); //сортируем структуру по х

razdel(p_vect, 0, 0);
for (i=0; i<=vector_pointer; i++){
	starting_triangulate(p_tr, p_vect, i);
}

for (i=0; i<triangles.size(); i++){
	cout <<"triangle #" << i << endl;
	for (j=0; j<3; j++){
		cout << (triangles[i].uzel[j]->x) << " " << (triangles[i].uzel[j]->y) << endl;
	}
}

for (i=0; i<vect.size(); i++){
	cout << "Triangulation #" << i << endl;
	cout << "Triangles amount=" << vect[i].tr_amount << endl;

	for (j=0; j<vect[i].tr_amount; j++)
	{
		for (k=0; k<3; k++){
			cout << triangles[vect[i].triang[j]].uzel[k]->x << " " << triangles[vect[i].triang[j]].uzel[k]->y << endl;	
		}
		cout << endl;
	}
}

for (i=0; i<vect.size(); i++){
	if (vect[i].amount <= 4) do_shell(p_vect, i);
}

for (i=0; i<vect.size(); i++){
	cout << "NUMBER=" << i << endl;
	for (j=0; j<vect[i].shell.size(); j++) cout << vect[i].shell[j]->x << " " << vect[i].shell[j]->y << endl;
	cout << "MY_FATHER=" << vect[i].father << endl;
}

//find_bridges(p_vect, 10);
//find_bridges(p_vect, 8);
find_bridges(p_vect, 6);
find_bridges(p_vect, 4);
find_bridges(p_vect, 2);

int fortune = 0; 


cout << endl << endl;
for (j=0; j<vect[fortune].shell.size(); j++) {
	cout << vect[fortune].shell[j]->x << " " << vect[fortune].shell[j]->y << endl;
}

cout << "SUKA" << endl;

cout << vect[fortune].bridge[0]->x << " " << vect[fortune].bridge[0]->y << endl << vect[fortune].bridge[1]->x << " " << vect[fortune].bridge[1]->y << endl;
cout << vect[fortune].bridge[2]->x << " " << vect[fortune].bridge[2]->y << endl << vect[fortune].bridge[3]->x << " " << vect[fortune].bridge[3]->y << endl;


cout << "B1" << endl;


for (i=0; i<vect[fortune].coast_1.size(); i++) {
	cout << vect[fortune].coast_1[i]->x << " " << vect[fortune].coast_1[i]->y << endl;
};
cout << "B2" << endl;
for (i=0; i<vect[fortune].coast_2.size(); i++) cout << vect[fortune].coast_2[i]->x << " " << vect[fortune].coast_2[i]->y << endl;



//(*p).del();
//vect.erase(p);

return 0;
}
