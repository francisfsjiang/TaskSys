#include "simulator.hpp"

#include "task_queue.hpp"
#include "task.hpp"

#include <random>

using namespace std;
using namespace TaskSys;


void run_task_producer_random(shared_ptr<TaskQueue> task_queue, int num) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> processing_time_dis(0, 2);
    std::uniform_int_distribution<> fail_time_dis(0, 1);

    for(int i = 0; i < num; ++i) {
        int processing_time = processing_time_dis(gen);
        int fail_time = fail_time_dis(gen);
        task_queue->add(make_shared<Task>(processing_time, fail_time));
    }
}

void run_task_producer(shared_ptr<TaskQueue> task_queue, int num, int processing_time, int fail_time) {
    for(int i = 0; i < num; ++i) {
        task_queue->add(make_shared<Task>(processing_time, fail_time));
    }

}

void run_task_producer_list(shared_ptr<TaskQueue> task_queue, const vector<Task>& list)
{
    for(auto const task: list) {
        task_queue->add(shared_ptr<Task>(new Task(task)));
    }

}

void run_task_consumer(shared_ptr<TaskQueue> task_queue) {

    while (!task_queue->is_closed()) {
        shared_ptr<Task> task = task_queue->get();
        if(!task) continue;

        int ret = task->process();
        if(ret != 0) {
            task_queue->add(task);
        }
        else {
            task_queue->done(task);
        }

    }

}