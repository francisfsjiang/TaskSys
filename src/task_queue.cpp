#include "task_queue.hpp"


namespace TaskSys {

    TaskQueue::TaskQueue() {

    }

    TaskQueue::~TaskQueue() {

    }

    void TaskQueue::add(Task *) {

    }

    int TaskQueue::len() const {
        return static_cast<int>(queue_.size());
    }

    Task *TaskQueue::get() {
        return nullptr;
    }

    void TaskQueue::done(Task *) {

    }

    void TaskQueue::shutdown() {

    }

    bool TaskQueue::is_closed() const {
        return closed_;
    }

}