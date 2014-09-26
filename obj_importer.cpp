#include"obj_importer.h"

/*
 * init all the number member
 * */
obj_importer::obj_importer(string obj_filename): obj_filename(obj_filename){
	fstream obj_file(obj_filename.c_str());
	//assert(obj_file);
	vertice_number = 0;
	face_number = 0;
	if(!obj_file){
		cerr << "error: unable to open obj file:"
			<< obj_filename << endl;
		return;
	}
	string line;
	while(getline(obj_file, line)){
		// Vertice
		if(line[0] == 'v' && line[1] == ' ')
			vertice_number++;
		// Face
		else if(line[0] == 'f' && line[1] == ' ')
			face_number++;
		// Normal
		else if(line[0] == 'v' && line[1] == 'n');
		// Parameter space vertice
		else if(line[0] == 'v' && line[1] == 'p');
	}
	// 此处可能的改进：将文件流设为一个类成员，每次用完将其定位到特定位置
	obj_file.close();
	//cout << vertice_number << endl << face_number << endl;
	
	vertices.resize(vertice_number);
}


int main(){
	obj_importer o(string("/home/simon/obj_importer/data.obj"));

	return 0;
}
