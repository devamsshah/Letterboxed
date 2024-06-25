//
// Created by Devam Shah on 6/17/24.
//
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <unordered_set>
#include "printer.h"
using namespace std;
#ifndef LETTERBOXED_SOLVER_H
#define LETTERBOXED_SOLVER_H

int findSide(char a, vector<string> set){
    for (int i = 0; i < set.size(); ++i) {
        for (int j = 0; j < set[i].size(); ++j) {
            if(set[i][j] == a){
                return i;
            }
        }
    }
    return -1;
}

double f(double x){
    if(x<0){
        x = -1*x;
    }
    if(x>1){
        x = x-(static_cast<int>(x));
    }
    double innerCos = cos(M_PI * x);
    double outerCos = cos(innerCos + 2);
    double result = (((-outerCos + 1) / sqrt(2)) + 0.2) / 2;
    return result;
}

int countUniqueCharacters(const string& input) {
    unordered_set<char> uniqueChars;
    for (char ch : input) {
        uniqueChars.insert(ch);
    }
    return uniqueChars.size();
}

int nullfun(int a){
    return a;
}



double ratUnique(vector<vector<Wurd> > w, Wurd word){
    double s = countUniqueCharacters(word.getW());
    vector<Wurd> temp = w[static_cast<int>(word[word.getW()[0]])-97];
    int p = 0;
    for (int i = 0; i < temp.size(); ++i) {
        p+= temp[i].getW().size();
    }
    return s/p;
}


double weight(double x, double ratioUnique, double ratioPoss){
    return (x*ratioUnique)+((1-x)*ratioPoss);
}

double ratPoss(vector<vector<Wurd> > w, Wurd word){
    char c = word.getW()[word.getW().size()-1];
    int a = static_cast<int>(c)-97;
    double s = w[a].size();
    int p = 0;
    for (int i = 0; i < w.size(); ++i) {
        p += w[i].size();
    }
    return s/(p/12);
}



bool isOnSameSide(vector<bool>& b, char a, vector<string> set){
    int c = findSide(a,set);
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
//
//a
//5
//bsa
//zru
//gko
//eit
