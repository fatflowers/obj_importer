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
private:
	vector<vertice> vertices;	
	int vertice_number;
	int face_number;
	const string obj_filename;
};


vector<string> obj_importer::line_parser(string line){
	int space_pos = line.find(" ");
	// 删除开头的字段类型标记
	line.erase(0, space_pos + 1);

	vector<string> result;
	while(space_pos = line.find(" ")){
		result.push_back(line.substr(0, space_pos));
		line.erase(0, space_pos + 1);
	}
	if(line.length())
		result.push_back(line);

	for(int i = 0; i < result.size(); i++)
		cout << result[i] << endl;
	return result;
}


