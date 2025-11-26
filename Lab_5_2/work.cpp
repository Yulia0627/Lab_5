#include <syncstream>
#include<thread>
#include<iostream>
#include<chrono>
#include<future>

using namespace std;

void slow_and_quick(const string& name, int time) {
    this_thread::sleep_for(chrono::seconds(time));
    osyncstream (cout) << name << endl;
}

void work() {
    using namespace std;

    auto start = chrono::high_resolution_clock::now();

    auto fB = async(launch::async, [] {
        slow_and_quick("B1", 1);
        slow_and_quick("B2", 1);
        slow_and_quick("B3", 7);  
    });

    slow_and_quick("A1", 7);
    slow_and_quick("A2", 1);
    slow_and_quick("A3", 1);

    fB.get(); 

    slow_and_quick("C", 1);

    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration<double>(end - start).count();

    osyncstream(cout) << "Total time: " << seconds << " s\n" << "Work is done!";
}


int main()
{
    work();
}