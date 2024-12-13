#define BOOST_TEST_MODULE QueueTest
#include <boost/test/included/unit_test.hpp>
#include "../structures/include/queue.h"
#include "../structures/include/timer.h"

Timer timer;

BOOST_AUTO_TEST_CASE(test_push) {
    Queue<int> nums(10);

    nums.push(1);
    nums.push(2);
    nums.push(3);

    BOOST_CHECK_EQUAL(nums.Size(), 3);
    BOOST_CHECK_EQUAL(nums.peek(), 1);
}

BOOST_AUTO_TEST_CASE(test_pop) {
    Queue<int> nums(10);

    nums.push(1);
    nums.push(2);
    nums.push(3);
    nums.pop();

    BOOST_CHECK_EQUAL(nums.Size(), 2);
    BOOST_CHECK_EQUAL(nums.peek(), 2);
}

BOOST_AUTO_TEST_CASE(test_empty_and_full) {
    Queue<int> nums(5);

    nums.pop(); // очередь пуста
    BOOST_CHECK_EQUAL(nums.peek(), -1);
    BOOST_CHECK(nums.isEmpty());

    nums.push(1);
    nums.push(2);
    nums.push(3);
    nums.push(4);
    nums.push(5);
    BOOST_CHECK(!nums.isEmpty());

    nums.push(6); // не добавится из-за переполнения

    BOOST_CHECK_EQUAL(nums.Size(), 5);
    BOOST_CHECK_EQUAL(nums.peek(), 1);
}
