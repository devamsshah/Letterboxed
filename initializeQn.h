//
// Created by Devam Shah on 6/13/24.
//

#include <vector>
#ifndef LETTERBOXED_INITIALIZEQN_H
#define LETTERBOXED_INITIALIZEQN_H
using namespace std;


void individualFrequency(const vector<string>& words){
    vector<int> frequency(26,0);
    long long int totalChar = 0;
    int ind;
    for(auto & word : words){
        for (char j : word) {
            totalChar++;
            ind = static_cast<int>(j) - 97;
            frequency[ind]++;
        }
    }
    vector<long double> prob;
    prob.reserve(frequency.size());
    long double temp;
    for (int i: frequency) {
        temp = static_cast<double>(i) / static_cast<double>(totalChar);
        prob.push_back(temp);
    }
}



void initializeQn(vector<char>& qn, int& n, const vector<string>& words){
    vector<char> nullVector(12, '\0');
    qn = nullVector;
    n = 1;
    individualFrequency(words);
}


#endif //LETTERBOXED_INITIALIZEQN_H
