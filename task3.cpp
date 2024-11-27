#include <iostream>
#include <vector>
#include <random>
#include <omp.h>
#include <chrono>
#include <future>

using namespace std;

random_device os_seed;
const int seed = 1;

mt19937 generator(seed);
uniform_int_distribution<> distribute(0, 1000);

double average(const vector<double> &v){
    double sum = 0.0f;
    for(int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum / v.size();
}

double maximum(const vector<double> &v){
    double max = v[0];
    for(int i = 1; i < v.size(); i++){
        if(v[i] > max){
            max = v[i];
        }
    }
    return max;
}

double minimum(const vector<double> &v){
    double min = v[0];
    for(int i = 1; i < v.size(); i++){
        if(v[i] < min){
            min = v[i];
        }
    }
    return min;
}

int main(){
    int size = 100000000;
    vector<double> v(size);
    for(int i = 0; i < size; i++){
        v[i] = distribute(generator)/1000.0;
    }

    auto start = chrono::steady_clock::now();
    double min, max, avg;

    min = minimum(v);
    max = maximum(v);
    avg = average(v);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Elapsed: " << elapsed.count() << "s" << endl;
    cout << "Min: " << min << ", Max: " << max << ", Avg: " << avg << endl;
}