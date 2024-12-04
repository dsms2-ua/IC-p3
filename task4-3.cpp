#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

int main(){
    int size = 10000000;
    //default initialization and add elements with push_back
    auto start = chrono::high_resolution_clock::now();

    vector<int> v1;

    #pragma omp parallel for
    for(int i = 0; i < size; i++){
        #pragma omp critical
        v1.push_back(i);
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Default initialization of " << v1.size() << " elements: " << elapsed.count() << "ms" << endl;

    //initialized with required size and add elements with direct access
    start = chrono::high_resolution_clock::now();

    vector<float> v2(size);
    #pragma omp parallel for
    for(int i = 0; i < size; i++){
        v2[i] = i;
    }

    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Initialization with required size of " << v2.size() << " elements: " << elapsed.count() << "ms" << endl;
}