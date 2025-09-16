#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cctype>
using namespace std;

map<string, set<int>> invertedIndex;

void createIndex(const string& file_name, int id) { //reads the file and creates the inverted index
    ifstream file(file_name.c_str());

    //error catching 
    if(!file.is_open()) {
        //skip unreadable silently
        return; 
    }

    string text;
    char c;

    //go through the file finding each new word 
    while(file >> noskipws >> c) {

        //checks each iterating character is alpha  
        if(isalpha(static_cast<unsigned char>(c))) {
            text += c;
        }
        //once complete word is made either adds to the existing key or create new key 
        else {
            if(!text.empty()) {
                invertedIndex[text].insert(id);
                text.clear(); //resets word
            }
        }
    }

    //if EOF is reached word is still not in the map
    if(!text.empty()) {
        invertedIndex[text].insert(id);
    }

    file.close();
}

void printResults() {
    for (const auto& key: invertedIndex) {
        cout << key.first << ":";
        for (int id: key.second) {
            cout << " " << id;
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        //no extra output
        return 0; 
    }

    ifstream file_list(argv[1]);   

    if (!file_list.is_open()) {
        //exit silently
        return 0; 
    }

    string file_name; //independent files to be read
    int id = 0; //document ID
    while (file_list >> file_name) {  //read each filename
        ifstream test(file_name.c_str());
        if(!test.is_open()) {
            continue; //skip invalid file, do not increment id
        }
        test.close();
        createIndex(file_name, id);
        id++;
    }

    file_list.close();
    printResults();
    return 0;
}