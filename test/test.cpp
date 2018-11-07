#define BOOST_TEST_MODULE TaskSysUnitTest

#include <memory>
#include <thread>

#include <boost/test/included/unit_test.hpp>

#include "task_queue.hpp"
#include "task.hpp"

#include "simulator.hpp"

using namespace std;
using namespace TaskSys;

// 队列析构函数测试
BOOST_AUTO_TEST_CASE( destructor_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    // 手动触发析构
    task_queue.reset();

    BOOST_TEST(true);
}

// 基本测试
BOOST_AUTO_TEST_CASE( basic_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    vector<thread> producers;
    for(int i = 0; i < 3; ++i)
        producers.emplace_back(run_task_producer_random, task_queue, 10);

    vector<thread> consumers;
    for(int i = 0; i < 6; ++i)
        consumers.emplace_back(run_task_consumer, task_queue);

    std::this_thread::sleep_for(std::chrono::seconds(20));

    task_queue->shutdown();

    for(thread& t: producers) {
        t.join();
    }
    for(thread& t: consumers) {
        t.join();
    }

    BOOST_TEST(true);
}

// 测试Task Retry。
BOOST_AUTO_TEST_CASE( task_retry_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    thread producer(run_task_producer, task_queue, 1, 0, 5);
    thread consumer(run_task_consumer, task_queue);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    task_queue->shutdown();

    producer.join();
    consumer.join();

    BOOST_TEST(true);
}

// 测试有线程在等待条件变量时，任务队列shutdown。
BOOST_AUTO_TEST_CASE( destory_taskqueue_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    thread consumer(run_task_consumer, task_queue);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    task_queue->shutdown();

    consumer.join();

    BOOST_TEST(true);
}

// 测试有线程在处理Task时，任务队列shutdown。
BOOST_AUTO_TEST_CASE( destory_taskqueue_while_processing_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    thread producer(run_task_producer, task_queue, 1, 20, 0);
    thread consumer(run_task_consumer, task_queue);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    task_queue->shutdown();

    producer.join();
    consumer.join();

    BOOST_TEST(true);
}