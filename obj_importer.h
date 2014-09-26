/**
 * Import an obj file into class obj_importer.
 * Simon 2014-09-26
 *
 *
 *
 *
 *
 * */


#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;

struct vertice{
	float x;
	float y;
	float z;
};

class obj_importer{
public:
	obj_importer(string obj_filename);

private:
	vector<vertice> vertices;	
	int vertice_number;
	int face_number;
	const string obj_filename;
};
