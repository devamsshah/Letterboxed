//
// Created by Devam Shah on 6/25/24.
//

#ifndef LETTERBOXED_WURD_H
#define LETTERBOXED_WURD_H

using namespace std;
class Wurd {
private:
    string w;
    double p;
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

    void print() const{
        cout << w << ": " << p << endl;
    }
};

///example usage
//int main() {
//    Wurd word("example", 3.14);
//    return 0;
//}



#endif //LETTERBOXED_WURD_H
