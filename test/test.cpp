#define BOOST_TEST_MODULE TaskSysUnitTest

#include <memory>

#include <boost/test/included/unit_test.hpp>

#include "task_queue.hpp"
#include "task.hpp"

using namespace std;
using namespace TaskSys;


BOOST_AUTO_TEST_CASE( destructor_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    // 手动触发析构
    task_queue.reset();
    BOOST_TEST(true);
}


BOOST_AUTO_TEST_CASE( basic_test )
{
    auto task_queue = TaskQueue::new_task_queue();

    // 手动触发析构
    task_queue.reset();
    BOOST_TEST(true);
}