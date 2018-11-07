#ifndef _TASKSYS_TASK_QUEUE_HPP_
#define _TASKSYS_TASK_QUEUE_HPP_

#include <set>
#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace TaskSys {

    // 前置声明避免include过多头文件
    class Task;

    class TaskQueue {

    public:

        static std::shared_ptr<TaskQueue> new_task_queue();

        ~TaskQueue();

        void add(std::shared_ptr<Task>);

        int len() const;

        // 在TaskQueue先于Task析构的情况下，Task可能仍然被其他线程持有，
        // 无法由TaskQueue完成析构，所以使用shared_ptr来保证析构。
        std::shared_ptr<Task> get();
        void done(std::shared_ptr<Task>);

        void shutdown();
        bool is_closed() const;

    private:
        // TaskQueue可能由创建线程在其他持有该对象的线程结束之前销毁，
        // 所以由shared_ptr完成析构。这里强制使用new_task_queue来生成TaskQueue，
        // 保证TaskQueue由shared_ptr持有。
        // **但是这种做法要求创建线程退出前调用shutdown，否则可能会导致无限等待。

        TaskQueue();

        bool closed_;

        std::mutex queue_lock_;
        std::condition_variable queue_cond_;
        std::deque<std::shared_ptr<Task>> queue_;

        std::mutex task_in_processing_set_lock_;
        std::set<std::shared_ptr<Task>> task_in_processing_;

    };

}


#endif //_TASKSYS_TASK_QUEUE_HPP——
