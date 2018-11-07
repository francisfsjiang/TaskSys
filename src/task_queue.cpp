#include <iostream>
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
        shutdown();

        queue_.clear();
        task_in_processing_.clear();
    }

    void TaskQueue::add(std::shared_ptr<Task> task) {
        unique_lock<mutex> lock(queue_lock_);
        if (closed_) return;

        queue_.push_back(task);

        // 此时如果有线程等待在条件变量上，那么在释放锁之后会被唤醒。
        // 如果没有，下一个线程在获取锁之后会先检查状态，不需要等待条件变量。
        queue_cond_.notify_one();

        // 非必要，函数结束，lock析构时同样会释放锁
        lock.unlock();
    }

    int TaskQueue::len() const {
        return static_cast<int>(queue_.size());
    }

    std::shared_ptr<Task> TaskQueue::get() {
        unique_lock<mutex> lock(queue_lock_);

        // 获取锁之后，先判断条件，再等待信号量，避免信号量丢失的情况。
        // while循环避免spurious wakeup
        while(queue_.empty() && !closed_) {
            queue_cond_.wait(lock, [this]{return !this->queue_.empty() || this->closed_;});
        }

        if (closed_) return nullptr;
        std::shared_ptr<Task> task = queue_.front();
        queue_.pop_front();

        // 这里如果不unlock，直接去lock task_in_processing_set_lock_，
        // 可能会导致死锁。
        lock.unlock();

        unique_lock<mutex> set_lock(task_in_processing_set_lock_);
        task_in_processing_.insert(task);
        set_lock.unlock();

        return task;
    }

    void TaskQueue::done(std::shared_ptr<Task> task) {
        unique_lock<mutex> set_lock(task_in_processing_set_lock_);
        // TODO check return value
        task_in_processing_.erase(task);
        set_lock.unlock();
    }

    void TaskQueue::shutdown() {
        unique_lock<mutex> lock(queue_lock_);
        cout << "Shutting down." << endl;
        closed_ = true;
        queue_cond_.notify_all();
    }

    bool TaskQueue::is_closed() const {
        return closed_;
    }


}