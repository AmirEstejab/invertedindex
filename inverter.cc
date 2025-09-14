#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cctype>
using namespace std;

map<string, set<int>> invertedIndex;

void createIndex(const string& file_name, int id) { //reads the file and creates the inverted index
    fstream file(file_name);

    //error catching 
    if(!file.is_open()) {
        cout << "Can't open" << file_name << endl;
        return;
    }

    string text;
    char c;

    //go through the file finding each new word 
    while(file >> noskipws >> c) {

        //checks each iterating character is alpha  
        if(isalpha(c)) {
            text += c;
        }
        //once complete word is made either ads to the existing key or create new key 
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
        cout << key.first << ": ";
        for (int id: key.second) {
            cout << id << " ";
        }
        cout << endl;
    }
}

int main() {
    fstream file_list("inputs.txt");   

    if (!file_list.is_open()) {
        cout << "Could not open inputs.txt" << endl;
        return 1;
    }

    string file_name; //independent files to be read
    int id = 0; //document ID
    while (file_list >> file_name) {  // read each filename
        createIndex(file_name, id);
        id++;
    }

    file_list.close();
    printResults();
    return 0;
}