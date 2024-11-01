//
// Created by Devam Shah on 6/25/24.
//
#pragma once
#ifndef LETTERBOXED_PRINTER_H
#define LETTERBOXED_PRINTER_H
#include "wurd.h"

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
        cout << "printing new letter: " << i+1 << endl;
    }
    cout << "printed " << c << " total words" << endl;
}

void printer(vector<vector<Wurd> >v){
    int c = 0;
    cout << "called printer2d" << endl;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            v[i][j].print();
            c++;
        }
        cout << "printing new letter: " << i+1 << endl;
    }
    cout << "printed " << c << " total words" << endl;
}


void printer(vector<double> v){
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
}

void printer(vector<Wurd> v){
    for (int j = 0; j < v.size(); ++j) {
        v[j].print();
    }
}

#endif //LETTERBOXED_PRINTER_H
