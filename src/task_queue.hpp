#ifndef _TASKSYS_TASK_QUEUE_HPP_
#define _TASKSYS_TASK_QUEUE_HPP_

#include <deque>
#include <mutex>
#include <condition_variable>

namespace TaskSys {

    class Task;

    class TaskQueue {

    public:
        TaskQueue();
        ~TaskQueue();

        void add(Task*);
        int len() const;
        Task* get();
        void done(Task*);
        void shutdown();
        bool is_closed() const;

    private:

        bool closed_;

        std::mutex queue_lock_;

        std::condition_variable queue_cond_;

        std::deque<Task*> queue_;

    };

}


#endif //_TASKSYS_TASK_QUEUE_HPP——
