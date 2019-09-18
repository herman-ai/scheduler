#ifndef _scheduler_hpp_
#define _scheduler_hpp_
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <queue>

using namespace std;
typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> MyTimePoint;

struct job {
    function<void(int)> f;
    MyTimePoint t; //The time at which to execute
    int id;
    job(function<void(int)> f, MyTimePoint t, int id) : f(f), t(t), id(id) {}
    ~job(){}
    friend bool operator<(const job & lhs, const job & rhs);
};

class scheduler {
    bool done = false;
    priority_queue<job> jobs;
    thread looper_thread;

    void looper();

    public:
        void schedule_call(function<void(int)> f, int n, int id);
        scheduler();
        ~scheduler();
        void stop() {done = true;}
};
#endif