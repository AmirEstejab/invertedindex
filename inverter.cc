#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cctype>
using namespace std;

map<string, set<int>> invertedIndex;

void processFile(const string& fname, int id) { //reads the file and creates the inverted index
    fstream file(fname);

    //error catching 
    if(!file.is_open()) {
        cout << "Can't open" << fname << endl;
        return;
    }

    string word;
    char c;

    //go through the file finding each new word 
    while(file >> noskipws >> c) {

        //checks each iterating character is alpha  
        if(isalpha(c)) {
            word += c;
        }
        //once complete word is made either ads to the existing key or create new key 
        else {
            if(!word.empty()) {
                invertedIndex[word].insert(id);
                word.clear(); //resets word
            }
        }
    }

    //if EOF is reached word is still not in the map
    if(!word.empty()) {
        invertedIndex[word].insert(id);
    }

    file.close();
}

void printResults() {
    for (const auto& entry : invertedIndex) {
        cout << entry.first << ": ";
        for (int id: entry.second) {
            cout << id << " ";
        }
        cout << endl;
    }
}

int main() {
    fstream listFile("inputs.txt");   

    if (!listFile.is_open()) {
        cout << "Could not open inputs.txt" << endl;
        return 1;
    }

    string fname; //independent files to be read
    int id = 0; //document ID
    while (listFile >> fname) {        // read each filename
        processFile(fname, id);
        id++;
    }

    listFile.close();
    printResults();
    return 0;
}