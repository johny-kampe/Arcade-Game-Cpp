#include "Map.h"

#include <iostream>
#include <fstream>

Map::Map(char * map){
	// string file_path = "/home/kampe/Desktop/Cpp/Final_Project/";  // the path of my project
	string file_path = map;  // conctenating map's file name in the path

	ifstream read_file; 
	string line;


	read_file.open(file_path);
	int count = 0;  // counting rows
	if(read_file.is_open()){  // check if the file is open
		while ( !read_file.eof() ){  // if the file is open find the number of rows and columns by getting every line of the file
			getline(read_file, line);

			if(count == 0){  // find the size of one line (getting the amount of columns)
				columns = line.size();
			}
			line+= '\n';  // maybe for debbuging reasons, 
			
			the_map.push_back(line);
			count++;
		}
		rows = count - 1;
	}
	read_file.close();
}

vector<string> Map::getMap() const{ 
    return the_map;
}

int Map::getRows() const {
	return rows;
}

int Map::getColumns() const {
	return columns;
}
