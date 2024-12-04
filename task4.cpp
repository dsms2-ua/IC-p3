#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int max = 0;
    int min = 1000;

    #pragma omp parallel for
    for(int i = 1000; i >= 0; i--){
        #pragma omp critical
        {
            if(i > max) max = i;
        }

        #pragma omp critical
        {
            if(i < min) min = i;
        }
    }

    cout << "Max: " << max << ", Min: " << min << endl;
}