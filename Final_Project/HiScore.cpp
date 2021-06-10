#include "HiScore.h"

#include <iostream>
#include <fstream>
#include <string.h>

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
}

void HiScore::operator<<(Engine &engine){
	for(int i = 0; i < 5; i++){
		if(engine.getPlayerScore() > scores[i]){
			scores[i] = engine.getPlayerScore();
			strcpy(names[i], engine.getPlayerName());
			break;
		}
	}

	ofstream write_to_file("highscore.dat", ios::binary);
    if(!write_to_file) {
        cout << "Cannot open file!" << endl;
    }

    for(int i = 0; i < 5; i++){
        write_to_file.write((char *) &names[i], sizeof(names[i]));
        write_to_file.write((char *) &scores[i], sizeof(scores[i]));        
    }
    write_to_file.close();
}
