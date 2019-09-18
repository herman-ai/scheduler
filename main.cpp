#include <iostream>
#include "scheduler.hpp"

using namespace std;

void f(int id) {
    auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    cout << "Executing function [" << id << "] at :" << now.count() << endl;
}

int main() {
    cout << "Hello world" << endl; 
    scheduler s;
    // function<void(int)> f = func;
    f(0);
    s.schedule_call(f, 10, 10);
    s.schedule_call(f, 1000, 1000);
    s.stop();
    s.schedule_call(f, 1000, 1000);
}