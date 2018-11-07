#include "../include/task.hpp"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

namespace TaskSys{

    TaskSys::Task::Task(int processing_time, int fail_time) :
        id_((unsigned long long)(this)), processing_time_(processing_time), fail_time_(fail_time)
    {

    }

    TaskSys::Task::Task(unsigned long long id, int processing_time, int fail_time) :
            id_(id), processing_time_(processing_time), fail_time_(fail_time)
    {

    }

    TaskSys::Task::~Task() {
        cout << "Task " << id_ << " destructing." << endl;
    }

    int TaskSys::Task::get_id() {
        return id_;
    }

    int Task::process() {

        cout << "Processing " << id_ << endl;

        if(fail_time_ > 0) {
            --fail_time_;
            return -1;
        }

        if(processing_time_ > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(processing_time_));
        }
        cout << "Processing " << id_ << " finished." << endl;

        return 0;
    }

}

