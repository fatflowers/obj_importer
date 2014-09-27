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
	vector<string> line_parser(string line);
	// 将obj文件中的各种信息存储到obj_importer类中
	void file_parser(void);
private:
	vector<vertice> vertices;	
	vector<vector<int> > faces;
	int vertice_number;
	int face_number;
	const string obj_filename;
	
};





