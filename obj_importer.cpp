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
	
	vertices.reserve(vertice_number * 3);
	//faces.reverse(face_number * 3);
}

vector<string> obj_importer::line_parser(string line){
	int space_pos = line.find(" ");
	// 删除开头的字段类型标记
	line.erase(0, space_pos + 1);

	vector<string> result;
	// 用空格将line分割开
	while((space_pos = line.find(" ")) != -1){
		result.push_back(line.substr(0, space_pos));
		line.erase(0, space_pos + 1);
	}
	if(line.length())
		result.push_back(line);

	for(unsigned i = 0; i < result.size(); i++)
		cout << result[i] << endl;
	return result;
}

// 将obj文件中的各种信息存储到obj_importer类中
void obj_importer::file_parser(void){
	fstream obj_file(obj_filename.c_str());
	if(!obj_file){
		cerr << "error: unable to open obj file:"
			<< obj_filename << endl;
		return;
	}
	string line;
	vector<string> tmp;
	vertice vtmp;
	vector<int> ftmp;
	while(getline(obj_file, line)){
		// Vertice
		if(line[0] == 'v' && line[1] == ' '){
			tmp = line_parser(line);
			vtmp.x = (float)atof(tmp[0].c_str());
			vtmp.y = (float)atof(tmp[1].c_str());
			vtmp.z = (float)atof(tmp[2].c_str());
			vertices.push_back(vtmp);
		}
		// Face，暂时只支持三个index值
		else if(line[0] == 'f' && line[1] == ' '){
			ftmp.clear();
			tmp = line_parser(line);
			for (unsigned i = 0; i < tmp.size(); i++){
				ftmp.push_back(atoi(tmp[i].c_str()));
			}
			faces.push_back(ftmp);
		}
		// Normal
		else if(line[0] == 'v' && line[1] == 'n');
		// Parameter space vertice
		else if(line[0] == 'v' && line[1] == 'p');
	}

	obj_file.close();
}

int main(){
	obj_importer o(string("C:\\Users\\Administrator\\Documents\\GitHub\\obj_importer\\data.obj"));
	o.line_parser(string("v 0.006636 -0.001313 2.447146"));	
	return 0;
}

