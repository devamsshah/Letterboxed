//
// Created by Devam Shah on 6/13/24.
//
#include <random>
#include <string>
#include <iostream>
#ifndef LETTERBOXED_FEEDBACK_H
#define LETTERBOXED_FEEDBACK_H
using namespace std;


void patOnTheBack(){
    vector<string> pats;
    pats.push_back("Genius");  pats.push_back("Amazing"); pats.push_back("Awesome"); pats.push_back("Good"); pats.push_back("Fabulous"); pats.push_back("Great");
    int r = rand() % 6;
    cout << pats[r] << "!\n";
}

void finished(vector<string> userAnswer, int n){
    if(userAnswer.size() > n)
        cout << "CONGRATULATIONS, YOU SUCCESSFULLY COMPLETED THE GAME!" << endl;
    else
        cout << "CONGRATULATIONS, YOU SUCCESSFULLY SOLVED LETTERBOXED WITHIN " << n << (n==1? "WORD!": "WORDS!") << endl;

}

#endif //LETTERBOXED_FEEDBACK_H
