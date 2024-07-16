//
// Created by Devam Shah on 6/13/24.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "wurd.h"
#ifndef LETTERBOXED_SCAN_H
#define LETTERBOXED_SCAN_H

using namespace std;

void loadWords(vector<string> & words){
    ifstream inputFile("words.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string word;
    while (getline(inputFile, word)) {
        words.push_back(word);
    }

    inputFile.close();
}


#endif //LETTERBOXED_SCAN_H
