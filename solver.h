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

double ratUnique(vector<vector<Wurd> > w, Wurd word, double p){
    double s = countUniqueCharacters(word.getW());
    return s/p;
}


double weight(double x, double ratioUnique, double ratioPoss){
    return (x*ratioUnique)+((1-x)*ratioPoss);
}

int lett(vector<vector<Wurd> > w, string end){
    char c = end[end.size()-1];
    int a = static_cast<int>(c)-97;
    return w[a].size();
}

double ratPoss(vector<vector<Wurd> > w, Wurd word, int p){
    double s = lett(w, word.getW());
    return s/(p/12);
}

vector<double> quadrature(int lim){
    vector<double> points;
    for (int i = 0; i < lim; ++i) {
        points.push_back(f(static_cast<double>(i)/static_cast<double>(lim-1)));
    }
    return points;
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


void addRat(vector<vector<Wurd> >& word, double q, vector<double> avg, int t){
    for (int i = 0; i < word.size(); ++i) {
        for (int j = 0; j < word[i].size(); ++j) {
            int c = static_cast<int>(word[i][j].getW()[(word[i][j].getW().size()-1)])-97;
            double m = ratUnique(word, word[i][j], avg[c]);
            double n = ratPoss(word, word[i][j], t);
            word[i][j].setP(weight(q, m, n));
        }
    }
}


bool possible(const vector<string>& set, string word, vector<bool>& b){
    for (int i = 0; i < word.size(); ++i) {
        if(isOnSameSide(b, word[i], set))
            return false;
    }
    return true;
}
void swap(Wurd& a, Wurd& b) {
    Wurd temp = a;
    a = b;
    b = temp;
}

void sortWurds(std::vector<Wurd>& vec) {
    int n = vec.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (vec[j].getP() < vec[j+1].getP()) {
                swap(vec[j], vec[j+1]);
            }
        }
    }
}

void sort(vector<vector<Wurd> >& w){
    for(auto& vec : w) {
        sortWurds(vec);
    }
}

vector<double> avgSize(vector<vector<Wurd> > w, int &t){
    vector<double> avg;
    t=0;
    for (int i = 0; i < w.size(); ++i) {
        double a = 0;
        t+=w[i].size();
        for (int j = 0; j < w[i].size(); ++j) {
            a+=w[i][j].getW().size();
        }
        double b = a/w[i].size();
        avg.push_back(b);
    }
    return avg;
}


vector<vector<Wurd> > processWords(const vector<string>& words, const vector<string>& set) {
    vector<vector<Wurd> > wordVec(26);
    int ind = 0;
    for (const auto& word : words) {
        vector<bool> b(4, false);
        if (word.size() > 2 && possible(set, word, b) ) {
            ind = static_cast<int>(word[0]) - 97;
            Wurd w(word, 0.0);
            wordVec[ind].push_back(w);
        }
    }
    return wordVec;
}

void solver(vector<string> words, const int limit){
    cout << "enter the 12 characters in 3 <newline> 3... format"<< endl;
    string one, two, three, four;
    cin >> one >> two >> three >> four;
    vector<string> set;
    set.push_back(one);
    set.push_back(two);
    set.push_back(three);
    set.push_back(four);
    vector<vector<Wurd> > pWords = processWords(words, set);
    vector<double> r = quadrature(limit);
    int totWords = 0;
    vector<double> avg = avgSize(pWords, totWords);
    addRat(pWords, 1, avg, totWords);
    printer(pWords);
    sort(pWords);
}
#endif //LETTERBOXED_SOLVER_H

//a
//5
//nlb
//wca
//kge
//uro

//a
//5
//bsa
//zru
//gko
//eit

//a
//6
//jxz
//uel
//oin
//rca
