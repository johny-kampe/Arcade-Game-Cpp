#include "HiScore.h"

#include <iostream>
#include <fstream>

HiScore::HiScore(char * hiscore_array){
	file = hiscore_array;

	ifstream read_binary; 
	read_binary.open(file, ios::binary);

	if(read_binary.is_open()){  // check if the file is open
		for(int i = 0; i < 5; i++){
        	read_binary.read((char *) &names[i], sizeof(names[i]));
        	read_binary.read((char *) &scores[i], sizeof(scores[i]));
		}
	}
	read_binary.close();

    if(!read_binary.good()) {
        cout << "Error occurred at reading time!" << endl;
        exit(1);
    }
    // for(int i=0; i < 5; i++) {
    //     cout << "Name: " << this->names[i] << endl;
    //     cout << "Score: " << this->scores[i] << endl;
    //     cout << endl;
    // }
}