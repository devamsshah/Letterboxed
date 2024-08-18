//
// Created by Devam Shah on 7/4/24.
//

#ifndef LETTERBOXED_SORTER_H
#define LETTERBOXED_SORTER_H

#endif //LETTERBOXED_SORTER_H


//helper function for bubble sort
void swap(Wurd& a, Wurd& b) {
    Wurd temp = a;
    a = b;
    b = temp;
}


//simple generic bubble sort function tailored to the data structure
void bubbleSort(vector<Wurd>& wurds) {
    bool swapped;
    int n = wurds.size();

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            if (wurds[j].getP() < wurds[j + 1].getP()) {
                swap(wurds[j], wurds[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by the inner loop, then the list is sorted
        if (!swapped) {
            break;
        }
    }
}

void bubbleSortSumBelow(vector<Wurd>& wurds) {
    bool swapped;
    int n = wurds.size();

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            if (wurds[j].getSumBelow() < wurds[j + 1].getSumBelow()) {
                swap(wurds[j], wurds[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by the inner loop, then the list is sorted
        if (!swapped) {
            break;
        }
    }
}

//generic sort for 1d vector
void sortWurds(vector<Wurd>& vec) {
    int n = vec.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (vec[j].getP() < vec[j+1].getP()) {
                swap(vec[j], vec[j+1]);
            }
        }
    }
}

//generic sort function for the 2d vector
void sort(vector<vector<Wurd> >& w){
    for(auto& vec : w) {
        sortWurds(vec);
    }
}


// Function to flatten and sort a 2D vector of Wurd
vector<Wurd> sortAndFlatten(vector<vector<Wurd> >& wurds) {
    vector<Wurd> flatList;
    sort(wurds);
    // Flatten the 2D vector into a 1D vector
    for (const auto& row : wurds) {
        for (const auto& wurd : row) {
            flatList.push_back(wurd);
        }
    }
    // Sort the 1D vector using the bubble sort function
    bubbleSort(flatList);
    return flatList;
}

