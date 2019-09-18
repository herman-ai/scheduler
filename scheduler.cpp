#include "scheduler.hpp"


void scheduler::looper() {
    while (true) {
        this_thread::sleep_for(chrono::microseconds(100));
        while (jobs.size() > 0) {
            job j = jobs.top();
            MyTimePoint now = chrono::time_point_cast<MyTimePoint::duration>(chrono::system_clock::now());
            if (now >= j.t) {
                jobs.pop();
                j.f(j.id);
            } else {
                break;
            }
        }
        if (done && jobs.size()==0) {
            break;
        }
    }
}

scheduler::scheduler(): looper_thread(thread(&scheduler::looper, this)) {
}

scheduler::~scheduler() {
    looper_thread.join();
}

void scheduler::schedule_call(function<void(int)> f, int n, int id) {
    if (done) {
        throw runtime_error("Stop called, can't add more!");
    }
    auto now = chrono::time_point_cast<MyTimePoint::duration>(chrono::system_clock::now());
    MyTimePoint execution_time = now + chrono::milliseconds(n);
    job j(f, execution_time, id);
    jobs.push(j);
}

bool operator<(const job & lhs, const job & rhs) {
    return (lhs.t > rhs.t);
}