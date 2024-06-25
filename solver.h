//
// Created by Devam Shah on 6/17/24.
//
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#ifndef LETTERBOXED_SOLVER_H
#define LETTERBOXED_SOLVER_H

struct wurd{
    string w;
    double p;
};

int findSide(vector<bool> b, char a, vector<string> set){
    for (int i = 0; i < set.size(); ++i) {
        for (int j = 0; j < set[i].size(); ++j) {
            if(set[i][j] == a){
                return i;
            }
        }
    }
    return -1;
}

bool isOnSameSide(vector<bool>& b, char a, vector<string> set){
    int c = findSide(b,a,set);
    if(c==-1 || b[c]){
        return true;
    }
    for (int i = 0; i < b.size(); ++i) {
        b[i] = false;
    }
    b[c]=true;
    return false;
}

bool possible(const vector<string>& set, string word, vector<bool>& b){
    for (int i = 0; i < word.size(); ++i) {
        if(isOnSameSide(b, word[i], set))
            return false;
    }
    return true;
}

vector<vector<string> > processWords(const vector<string>& words, const vector<string>& set) {
    vector<vector<string> > wordVec(26);
    int ind = 0;
    for (const auto& word : words) {
        vector<bool> b(4, false);
        if (possible(set, word, b)) {
            ind = static_cast<int>(word[0]) - 97;
            wordVec[ind].push_back(word);
        }
    }
    return wordVec;
}



//
//bool compareByLength(const std::string& a, const std::string& b) {
//    return a.size() < b.size();
//}
//
//vector<vector<string> > sorter(vector<vector<string> >& pWords) {
//    for (int i = 0; i < 26; ++i) {
//        sort(pWords[i].begin(), pWords[i].end(), compareByLength);
//    }
//    return pWords;
//}

void printer(vector<string> v){
    cout << "called printer" << endl;
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
}

void printer(vector<vector<string> >v){
    int c = 0;
    cout << "called printer2d" << endl;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            cout << v[i][j] << endl;
            c++;
        }
        cout << "printing new letter: " << i << endl;
    }
    cout << "printed " << c << " total words" << endl;
}

void solver(const vector<string>& words, const int limit){
    cout << "enter the 12 characters in 3 <newline> 3... format"<< endl;
    string one, two, three, four;
    cin >> one >> two >> three >> four;
    vector<string> set;
    set.push_back(one);
    set.push_back(two);
    set.push_back(three);
    set.push_back(four);
    printer(set);
    vector<vector<string> > pWords = processWords(words, set);
    printer(pWords);
}
#endif //LETTERBOXED_SOLVER_H
//a
//5
//nlb
//wca
//kge
//uro
