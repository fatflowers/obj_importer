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
#include <limits>
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


	// 点的坐标值的最大值和最小值
	vertice m_vMax;
	vertice m_vMin;
	// obj文件中的所有点
	vector<vertice> vertices;
	// obj文件中的所有面
	vector<vector<int> > faces;
private:
	// obj文件中点的数量
	int vertice_number;
	// obj文件中面的数量
	int face_number;
	// obj文件名（路径）
	const string obj_filename;
	
};





