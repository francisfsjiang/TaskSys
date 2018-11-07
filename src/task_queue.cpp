
#include <task_queue.hpp>

#include "../include/task_queue.hpp"

using namespace std;

namespace TaskSys {

    shared_ptr<TaskQueue> TaskQueue::new_task_queue() {
        return shared_ptr<TaskQueue>(new TaskQueue());
    }

    TaskQueue::TaskQueue() {
        closed_ = false;
    }

    TaskQueue::~TaskQueue() {
        closed_ = true;
        queue_cond_.notify_all();

        queue_.clear();
        task_in_processing_.clear();
    }

    void TaskQueue::add(std::shared_ptr<Task> task) {
        unique_lock<mutex> lock(queue_lock_);
        if (closed_) return;

        queue_.push_back(task);

        queue_cond_.notify_one();

        lock.unlock();
    }

    int TaskQueue::len() const {
        return static_cast<int>(queue_.size());
    }

    std::shared_ptr<Task> TaskQueue::get() {
        unique_lock<mutex> lock(queue_lock_);

        while(queue_.empty() && !closed_) {
            queue_cond_.wait(lock, [this]{return !this->queue_.empty() || this->closed_;});
        }

        if (closed_) return nullptr;
        std::shared_ptr<Task>& task = queue_.front();
        queue_.pop_front();
        task_in_processing_.insert(task);

        lock.unlock();
        return task;
    }

    void TaskQueue::done(std::shared_ptr<Task> task) {
        // TODO check return value
        task_in_processing_.erase(task);
    }

    void TaskQueue::shutdown() {
        unique_lock<mutex> lock(queue_lock_);
        closed_ = true;
        queue_cond_.notify_all();
    }

    bool TaskQueue::is_closed() const {
        return closed_;
    }


}