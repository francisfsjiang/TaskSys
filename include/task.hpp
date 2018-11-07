#ifndef _TASKSYS_TASK_HPP_
#define _TASKSYS_TASK_HPP_

namespace TaskSys {

    class Task {
    public:
        Task(int, int, int);
        Task(int, int);
        ~Task();

        int get_id();

        int process();
    private:

        int id_;
        int processing_time_;
        int fail_time_;

    };

}


#endif //_TASKSYS_TASK_HPP_
