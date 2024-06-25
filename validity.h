//
// Created by Devam Shah on 6/13/24.
//

#include <vector>
#include <string>
using namespace std;

#ifndef LETTERBOXED_VALIDITY_H
#define LETTERBOXED_VALIDITY_H

bool isinWords(const string& input, const vector<string>& words){
    for(const auto & word : words){
        if(input == word)
            return true;
    }
    return false;
}

bool isinQn(const string& input, const vector<char>& qn){
    for (char c : input) {
        if (find(qn.begin(), qn.end(), c) == qn.end()) {
            return false;
        }
    }
    return true;
}

bool isValidWord(const string& input, const vector<char>& qn, const vector<string>& words) {
    if(isinWords(input, words) && isinQn(input, qn) && input.size()>=3)
        return true;
    return false;
}


bool gameCondition(const vector<bool>& qnb){
    for (auto i : qnb)
        if(!i) {return false;}
    return true;
}

#endif //LETTERBOXED_VALIDITY_H
