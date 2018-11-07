#ifndef _TASKSYS_SIMULATOR_HPP_
#define _TASKSYS_SIMULATOR_HPP_

#include <initializer_list>
#include <memory>
#include <vector>

namespace TaskSys {
    class Task;
    class TaskQueue;
}

// 随机生成指定个数个Task
void run_task_producer_random(std::shared_ptr<TaskSys::TaskQueue>, int);

// 生成指定个数个Task，并且指定Task需要的处理时间和失败次数
void run_task_producer(std::shared_ptr<TaskSys::TaskQueue>, int, int, int);

// 根据Task列表生成Task
void run_task_producer_list(std::shared_ptr<TaskSys::TaskQueue>, std::vector<TaskSys::Task>);

void run_task_consumer(std::shared_ptr<TaskSys::TaskQueue> task_queue);


#endif //_TASKSYS_SIMULATOR_HPP_
