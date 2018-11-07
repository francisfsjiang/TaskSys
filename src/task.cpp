#include "../include/task.hpp"

#include <thread>
#include <chrono>

namespace TaskSys{

    TaskSys::Task::Task(int processing_time, int fail_time) :
        id_(static_cast<int>((long long)(this))), processing_time_(processing_time), fail_time_(fail_time)
    {

    }

    TaskSys::Task::Task(int id, int processing_time, int fail_time) :
            id_(id), processing_time_(processing_time), fail_time_(fail_time)
    {

    }

    TaskSys::Task::~Task() {

    }

    int TaskSys::Task::get_id() {
        return id_;
    }

    int Task::process() {

        if(fail_time_ > 0) {
            --fail_time_;
            return -1;
        }

        if(processing_time_ > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(processing_time_));
        }

        return 0;
    }

}

