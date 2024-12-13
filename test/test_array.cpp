#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>
#include "../structures/include/array.h"
#include "../structures/include/timer.h"

Timer timer;

BOOST_AUTO_TEST_CASE(test_add_and_resize) {
    Array<int> nums;

    for (int i = 1; i <= 11; ++i) {
        nums.add(i);
    }
    BOOST_CHECK_EQUAL(nums.length(), 11);

    BOOST_CHECK_EQUAL(nums.get(0), 1);
    BOOST_CHECK_EQUAL(nums.get(5), 6);
    BOOST_CHECK_EQUAL(nums.get(10), 11);
}

BOOST_AUTO_TEST_CASE(test_addAT) {
    Array<int> nums;

    for (int i = 1; i <= 10; ++i) {
        nums.add(i);
    }
    nums.addAt(15, 5); // индекс выходит за размеры
    nums.addAt(1, 4);

    BOOST_CHECK_EQUAL(nums.length(), 11);
    BOOST_CHECK_EQUAL(nums.get(1), 4);
    BOOST_CHECK_EQUAL(nums.get(15), -1); // индекс выходит за размеры массива
}

BOOST_AUTO_TEST_CASE(test_remove) {
    Array<int> nums;

    nums.add(1);
    nums.add(2);
    nums.add(3);
    nums.remove(10); // индекс выходит за размеры массива
    nums.remove(1);

    BOOST_CHECK_EQUAL(nums.length(), 2);
    BOOST_CHECK_EQUAL(nums.get(1), 3);
}

BOOST_AUTO_TEST_CASE(test_replace) {
    Array<int> nums;

    nums.add(1);
    nums.add(2);
    nums.add(3);
    nums.replace(10, 5); // индекс выходит за размеры массива
    nums.replace(1, 6);

    BOOST_CHECK_EQUAL(nums.length(), 3);
    BOOST_CHECK_EQUAL(nums.get(1), 6);
}
