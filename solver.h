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

using namespace std;
#pragma once
#ifndef LETTERBOXED_SOLVER_H
#define LETTERBOXED_SOLVER_H
#include "printer.h"
#include "math.h"
#include "sorter.h"
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
    return s/avgWordSize;
}

//gives the frequency and likelihood of the next letter
double ratPoss(vector<int> numWordsForEachAlph, Wurd word, int totWords){
    char c = word.getW()[word.getW().size()-1];
    int a = static_cast<int>(c)-97;
    double s = numWordsForEachAlph[a];
    return s/(totWords/12);
}

double ratQual(vector<double> avgWordSize, Wurd word){
    double fin = 0;
    unordered_set<char> uniqueChars;
    for (char ch : word.getW()) {
        uniqueChars.insert(ch);
    }
    for (char ch : uniqueChars) {
        int a = static_cast<int>(ch)-97;
        fin+= (1/avgWordSize[a]);
    }
    return fin;
}

//combines the two ratios (ratUnique and ratPoss) and gives out the final ration
int addRat(vector<vector<Wurd> >& words2D, double numGuess, vector<double> avgSizeWords, int totWords, vector<int> numWordsForEachAlph, vector<double> quadratureVec){
    for (int i = 0; i < words2D.size(); ++i) {
        for (int j = 0; j < words2D[i].size(); ++j) {
            int c = static_cast<int>(words2D[i][j].getW()[(words2D[i][j].getW().size()-1)])-97;
            double m = ratUnique("", words2D[i][j].getW(), avgSizeWords[c]);
            double n = ratPoss(numWordsForEachAlph, words2D[i][j], totWords);
            double o = ratQual(avgSizeWords, words2D[i][j]);
            words2D[i][j].setP(weight(quadratureVec[numGuess], m, o));
        }
    }
    return 0;
}


//Adds ratios to a 1d vector of words given that some of the characters are already used
void addRat(vector<Wurd>& words1D, double numGuess, vector<double> avgSizeWords, int totWords, vector<int> numWordsForEachAlph, string og, vector<double> quadratureVec){
    for (int i = 0; i < words1D.size(); ++i) {
        int lastCharInd = static_cast<int>(words1D[i].getW()[(words1D[i].getW().size()-1)])-97;
        double m = ratUnique(og, words1D[i].getW(), avgSizeWords[lastCharInd]);
        double n = ratPoss(numWordsForEachAlph, words1D[i], totWords);
        double o = ratQual(avgSizeWords, words1D[i]);
        words1D[i].setP(weight(quadratureVec[numGuess], m, o));
    }
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


std::string to_lowercase(const std::string& str) {
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
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
        if (word.size() > 2 && possible(set, to_lowercase(word), b) ) {
            ind = static_cast<int>(to_lowercase(word)[0]) - 97;
            Wurd w(to_lowercase(word), 0.0);
            wordVec[ind].push_back(w);
        }
    }
    inputFile.close();
    return wordVec;
}

void nextGuessPossPerWord(vector<vector<Wurd> > words2D, Wurd &word, vector<int> numWordsForEachAlph, double quadraturePointx, vector<double> avgWordSizePerAlph, int totWords, vector<double> quadratureVec){
    char lastChar = word.getW()[word.getW().size()-1];
    int indLastChar = static_cast<int>(lastChar)-97;
    vector<Wurd> words1Dnew = words2D[indLastChar];
    addRat(words1Dnew, quadraturePointx, avgWordSizePerAlph, totWords, numWordsForEachAlph, word.getW(), quadratureVec);
    bubbleSort(words1Dnew);
    word.setVec(words1Dnew);
}

void nextGuess(vector<Wurd> & flatVec, vector<vector<Wurd> > words2D, vector<int> numWordsForEachAlph, double quadraturePointx, vector<double> avgWordSizePerAlph, int totWords, int limit, vector<double> quadratureVec){
    for(int i = 0; i < flatVec.size()*0.1; i++) {
        nextGuessPossPerWord(words2D, flatVec[i], numWordsForEachAlph, quadraturePointx, avgWordSizePerAlph, totWords, quadratureVec);
    }
}

vector<Wurd> solvedSet(vector<Wurd> flatvec, vector<string> set){
    string og = set[0] + set[1] + set[2] + set[3];
    vector<Wurd> winningWurd;
    for (int i = 0; i < flatvec.size()*0.1; ++i) {
        string curr = flatvec[i].getW() + flatvec[i].getVec()[0].getW();
        if(ratUnique(curr, og,  1) == 0){
            Wurd ww = flatvec[i];
            winningWurd.push_back(ww);
        }
    }
    return winningWurd;
}

vector<Wurd> setSumBelow(vector<Wurd> & flatVec, vector<string> set){
    for (int i = 0; i < flatVec.size(); ++i) {
        if (flatVec[i].getVec().size() == 0){
            flatVec[i].setSumBelow(flatVec[i].getP());
        }else {
            flatVec[i].setSumBelow(flatVec[i].getP() + flatVec[i].getVec()[1].getP());
        }
    }
    bubbleSortSumBelow(flatVec);
    return solvedSet(flatVec, set);
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
    vector<double> quadratureVec = quadrature(limit);
    int totWords = 0;
    vector<int> numWordsForEachAlph(26, 0);
    vector<double> avgSizeWords = avgSize(pWords, totWords, numWordsForEachAlph);
    addRat(pWords, 1, avgSizeWords, totWords, numWordsForEachAlph, quadratureVec);
    vector<Wurd> flatVec = sortAndFlatten(pWords);
    for (int i = 2; i <= 2; i++){
        nextGuess(flatVec, pWords, numWordsForEachAlph, i,avgSizeWords, totWords, limit, quadratureVec);
    }
    vector<Wurd> solvedVec = setSumBelow(flatVec, set);
    printer(solvedVec);
}
#endif //LETTERBOXED_SOLVER_H

//git add .
//git commit -m "added comments and made the code faster and space efficient for solver by scanning and loading and saving poss words together in the solver case "
//git push -u origin main

//a
//5
//kme
//cnd
//bur
//ail

//a
//6
//uta
//mln
//rzo
//iwc

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

//a
//5
//enr
//sxp
//tbl
//ioa
