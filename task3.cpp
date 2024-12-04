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
    #pragma omp parallel for reduction(+: sum)
    for(int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum / v.size();
}

double maximum(const vector<double> &v){
    double max = v[0];
    #pragma omp parallel for reduction(max: max)
    for(int i = 1; i < v.size(); i++){
        if(v[i] > max){
            max = v[i];
        }
    }
    return max;
}

double minimum(const vector<double> &v){
    double min = v[0];
    #pragma omp parallel for reduction(min: min)
    for(int i = 1; i < v.size(); i++){
        if(v[i] < min){
            min = v[i];
        }
    }
    return min;
}

int main(){
    int size = 400000000;
    vector<double> v(size);
    for(int i = 0; i < size; i++){
        v[i] = distribute(generator)/1000.0;
    }

    auto start = chrono::steady_clock::now();
    double min, max, avg;

    future<double> f1 = async(minimum, ref(v));
    future<double> f2 = async(maximum, ref(v));
    future<double> f3 = async(average, ref(v));

    min = f1.get();
    max = f2.get();
    avg = f3.get();

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Elapsed: " << elapsed.count() << "s" << endl;
    cout << "Min: " << min << ", Max: " << max << ", Avg: " << avg << endl;
}