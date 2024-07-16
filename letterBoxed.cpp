#include "gameplay.h"
#include "solver.h"
#include "scan.h"
using namespace std;
///IMPLEMENT BACKSPACE FUNCTION///

vector<string> words;

int main() {
    cout << "find answers or create a game?" << endl;
    char aorb;
    cin >> aorb;
    if(aorb == 'a') {
        int limit = 4; //default is 4
        cout << "How many words do you need to solve it in?" << endl;
        cin >> limit;
        solver(limit);
    }
    else {
        gameplay(words);
    }
    return 0;
}
