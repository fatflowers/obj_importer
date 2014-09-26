#include"obj_importer.h"

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
		switch(line[0]){
			case 'v':
				vertice_number++;
				break;
			case 'f':
				face_number++;
				break;
		}
	}
	
	obj_file.close();
	cout << vertice_number << endl << face_number << endl;
}


int main(){
	obj_importer o(string("/home/simon/obj_importer/hirestoutatis.obj"));

	return 0;
}
