//
// Created by Devam Shah on 6/13/24.
//
#include <vector>

using namespace std;
#pragma once
#ifndef LETTERBOXED_GAMEPLAY_H
#define LETTERBOXED_GAMEPLAY_H

#include "scan.h"
#include "validity.h"
#include "feedback.h"
#include "initializeQn.h"



void loadAlphabets(vector<char> & alphabets){
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        alphabets.push_back(ch);
    }
}
void gameplay(vector<string> words){
    vector<bool> qnb(12, false);
    vector<char> alphabets;
    loadAlphabets(alphabets);
    vector<char> qn;
    int n;
    initializeQn(qn, n, words);
    vector<string> tries;

    while (gameCondition(qnb)){
        string word;
        cin >> word;
        if(isValidWord(word, qn, words)){
            patOnTheBack();
            tries.push_back(word);
            continue;
        }
    }

    finished(tries, n);
}

#endif //LETTERBOXED_GAMEPLAY_H
