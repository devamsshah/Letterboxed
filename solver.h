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
#include "math.h"
#include "sorter.h"
using namespace std;
#ifndef LETTERBOXED_SOLVER_H
#define LETTERBOXED_SOLVER_H

//find on which side the letter belongs to and return the side number
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

//checks if the previous letter is on the same side or not
//returns false if the letter is not on the same side
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

//checks if the given word is possible as an input to the given set of letterboxed
bool possible(const vector<string>& set, string word, vector<bool>& b){
    for (int i = 0; i < word.size(); ++i) {
        if(isOnSameSide(b, word[i], set))
            return false;
    }
    return true;
}

//counts the number of unique characters in the given string
int countUniqueCharacters(const string& input, unordered_set<char>& uniqueChars){
    int a = uniqueChars.size();
    for (char ch : input) {
        uniqueChars.insert(ch);
    }
    return uniqueChars.size()-(a);
}

//given a word, finds the ratio of unique letters vs avg word size of the second guess
double ratUnique(string og, string curr, double avgWordSize){
    unordered_set<char> uniqueChars;
    countUniqueCharacters(og, uniqueChars);
    double s = countUniqueCharacters(curr, uniqueChars);
    if(s == 0){
        return -1;
    }
    return s/avgWordSize;
}

//gives the frequency and likelihood of the next letter
double ratPoss(vector<int> numWordsForEachAlph, Wurd word, int totWords){
    char c = word.getW()[word.getW().size()-1];
    int a = static_cast<int>(c)-97;
    double s = numWordsForEachAlph[a];
    return s/(totWords/12);
}

//combines the two ratios (ratUnique and ratPoss) and gives out the final ration
int addRat(vector<vector<Wurd> >& words2D, double numGuess, vector<double> avgSizeWords, int totWords, vector<int> numWordsForEachAlph){
    for (int i = 0; i < words2D.size(); ++i) {
        for (int j = 0; j < words2D[i].size(); ++j) {
            int c = static_cast<int>(words2D[i][j].getW()[(words2D[i][j].getW().size()-1)])-97;
            double m = ratUnique("", words2D[i][j].getW(), avgSizeWords[c]);
            if(m == -1){
                return -1;
            }
            double n = ratPoss(numWordsForEachAlph, words2D[i][j], totWords);
            words2D[i][j].setP(weight(numGuess, m, n));
        }
    }
    return 0;
}


//Adds ratios to a 1d vector of words given that some of the characters are already used
int addRat(vector<Wurd>& words1D, double numGuess, vector<double> avgSizeWords, int totWords, vector<int> numWordsForEachAlph, string og){
    for (int i = 0; i < words1D.size(); ++i) {
        int lastCharInd = static_cast<int>(words1D[i].getW()[(words1D[i].getW().size()-1)])-97;
        double m = ratUnique(og, words1D[i].getW(), avgSizeWords[lastCharInd]);
        if(m == -1){
            return -1;
        }
        double n = ratPoss(numWordsForEachAlph, words1D[i], totWords);
        words1D[i].setP(weight(numGuess, m, n));
    }
    return 0;
}

//finds the average size of words for each start letter and modifies the totatl number of words
vector<double> avgSize(vector<vector<Wurd> > w, int &totalNumWords, vector<int> &numAlphWords){
    vector<double> avg;
    totalNumWords=0;
    for (int i = 0; i < w.size(); ++i) {
        double a = 0;
        totalNumWords+=w[i].size();
        numAlphWords[i] = w[i].size();
        for (int j = 0; j < w[i].size(); ++j) {
            a+=w[i][j].getW().size();
        }
        double b = a/w[i].size();
        avg.push_back(b);
    }
    return avg;
}

//goes through the list of words and checks if each word is possible or not
vector<vector<Wurd> > processWords(const vector<string>& set) {
    ifstream inputFile("words.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
    }
    string word;
    vector<vector<Wurd> > wordVec(26);
    int ind;
    while (getline(inputFile, word)) {
        vector<bool> b(4, false);
        if (word.size() > 2 && possible(set, word, b) ) {
            ind = static_cast<int>(word[0]) - 97;
            Wurd w(word, 0.0);
            wordVec[ind].push_back(w);
        }
    }
    inputFile.close();
    return wordVec;
}

int nextGuessPossPerWord(vector<vector<Wurd> > words2D, Wurd &word, vector<int> numWordsForEachAlph, double quadraturePointx, vector<double> avgWordSizePerAlph, int totWords){
    char lastChar = word.getW()[word.getW().size()-1];
    int indLastChar = static_cast<int>(lastChar)-97;
    vector<Wurd> words1Dnew = words2D[indLastChar];
    int indicator = addRat(words1Dnew, quadraturePointx, avgWordSizePerAlph, totWords, numWordsForEachAlph, word.getW());
    bubbleSort(words1Dnew);
    word.setVec(words1Dnew);
    if(indicator == -1){
        return -1;
    }
    return 0;
}

int nextGuess(vector<Wurd> & flatVec, vector<vector<Wurd> > words2D, vector<int> numWordsForEachAlph, double quadraturePointx, vector<double> avgWordSizePerAlph, int totWords, int limit){
    for(int i = 0; i < flatVec.size(); i++) {
        int indicator = nextGuessPossPerWord(words2D, flatVec[i], numWordsForEachAlph, quadraturePointx, avgWordSizePerAlph, totWords);
        if (indicator == -1) {
            return -1;
        }
    }
    return 0;
}



void solver(const int limit){
    cout << "enter the 12 characters in 3 <newline> 3... format"<< endl;
    string one, two, three, four;
    vector<string> set;
    cin >> one >> two >> three >> four;
    set.push_back(one);
    set.push_back(two);
    set.push_back(three);
    set.push_back(four);
    vector<vector<Wurd> > pWords = processWords(set);
    vector<double> r = quadrature(limit);
    int totWords = 0;
    vector<int> numWordsForEachAlph(26, 0);
    vector<double> avgSizeWords = avgSize(pWords, totWords, numWordsForEachAlph);
    addRat(pWords, 1, avgSizeWords, totWords, numWordsForEachAlph);
    vector<Wurd> flatVec = sortAndFlatten(pWords);
    printer(flatVec);
    for (int i = 2; i <= limit; i++){
        int indicator = nextGuess(flatVec, pWords, numWordsForEachAlph, i,avgSizeWords, totWords, limit);
    }
    printer(flatVec);
}
#endif //LETTERBOXED_SOLVER_H

//git add .
//git commit -m "added comments and made the code faster and space efficient for solver by scanning and loading and saving poss words together in the solver case "
//git push -u origin main

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

//a
//4
//par
//inc
//lwt
//ous

//a
//4
//lin
//ade
//htb
//ucr

//a
//6
//ygt
//xun
//oaq
//rsb


//a
//6
//bpe
//cua
//syl
//rmt

//a
//6
//tif
//grl
//ncu
//dhm

//a
//6
//ite
//dsa
//vxc
//mpo


//a
//6
//can
//wit
//jep
//lrx

//a
//4
//tyo
//eil
//cgn
//vra

//a
//5
//cib
//lhm
//ank
//oup

//a
//4
//frn
//tsl
//dia
//oku

//a
//5
//ceo
//str
//mxu
//big

//a
//4
//ohn
//tel
//caw
//rim

//a
//5
//xer
//abc
//kim
//hsn

//a
//4
//pea
//glo
//rnt
//mvu

//a
//5
//rxt
//fal
//pci
//eym

//a
//5
//afi
//wvs
//der
//ock

//a
//5
//jth
//bge
//niu
//awo

//a
//5
//aio
//bnr
//chz
//eml

//a
//5
//nai
//row
//eud
//gfb

//a
//6
//sic
//qht
//erz
//upn

//a
//4
//tca
//beo
//ipy
//snw
