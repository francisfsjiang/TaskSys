#ifndef _TASKSYS_SIMULATOR_HPP_
#define _TASKSYS_SIMULATOR_HPP_

#include <initializer_list>
#include <vector>

namespace TaskSys {
    class Task;
    class TaskQueue;
}

class TaskProducer {
public:
    TaskProducer(int);
    TaskProducer(int, int, int);
    TaskProducer(std::initializer_list<TaskSys::Task>);

private:
    std::vector<std::shared_ptr<TaskSys::Task>> tasks_;
};

void run_task_consumer(std::shared_ptr<TaskSys::TaskQueue> task_queue);


#endif //_TASKSYS_SIMULATOR_HPP_
