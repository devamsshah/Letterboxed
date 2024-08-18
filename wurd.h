//
// Created by Devam Shah on 6/25/24.
//

#ifndef LETTERBOXED_WURD_H
#define LETTERBOXED_WURD_H

using namespace std;
class Wurd {
private:
    string w; // the word
    double p; // the guesses rating
    vector<Wurd> vec; //next guesses in order
    double sumBelow; //sum of the p of the highest wurds in the vec
public:
    Wurd(const string& str, double dbl) : w(str), p(dbl) {}

    string getW() const {
        return w;
    }

    void setW(const string& str) {
        w = str;
    }

    double getP() const {
        return p;
    }

    void setP(double dbl) {
        p = dbl;
    }

    vector<Wurd> getVec(){
        return vec;
    }

    void setVec(vector<Wurd> v){
        vec = v;
    }

    double getSumBelow(){
        return sumBelow;
    }

    void setSumBelow(double dbl){
        sumBelow = dbl;
    }
    void print() const{
        if(!vec.empty()){
            cout << w << ": " << p << "\t\t\t";
            vec[0].print();
        }else {
            cout << w << ": " << p << endl;
        }
    }
};

///example usage
//int main() {
//    Wurd word("example", 3.14);
//    return 0;
//}



#endif //LETTERBOXED_WURD_H
