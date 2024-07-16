//
// Created by Devam Shah on 7/4/24.
//

#ifndef LETTERBOXED_MATH_H
#define LETTERBOXED_MATH_H
using namespace std;


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


vector<double> quadrature(int lim){
    vector<double> points;
    for (int i = 0; i < lim; ++i) {
        points.push_back(f(static_cast<double>(i)/static_cast<double>(lim-1)));
    }
    return points;
}

double weight(double x, double ratioUnique, double ratioPoss){
    return (x*ratioUnique)+((1-x)*ratioPoss);
}

#endif //LETTERBOXED_MATH_H
