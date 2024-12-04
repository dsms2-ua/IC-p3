#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int task(int id, int millis){
    this_thread::sleep_for(std::chrono::milliseconds(millis));
    cout << "Task " << id << " completed" << endl;
    return id;
}

int main(){
    auto start = chrono::high_resolution_clock::now();

    future<int> task1 = async(launch::deferred, task, 1, 2000);
    future<int> task2 = async(launch::deferred, task, 2, 3000);

    task1.wait();
    int taskId = task2.get();

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Completed in: " << elapsed.count() << "ms" << endl;
}