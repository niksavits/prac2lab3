#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../structures/include/list.h"
#include "../structures/include/timer.h"

Timer timer;

BOOST_AUTO_TEST_SUITE(testSinglyLinkedList)

    BOOST_AUTO_TEST_CASE(test_push_front) {
        SinglyLinkedList<int> nums;
        nums.push_front(1);
        nums.push_front(2);
        nums.push_front(3);

        BOOST_CHECK_EQUAL(nums.get_size(), 3);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(4));
    }

    BOOST_AUTO_TEST_CASE(test_push_back) {
        SinglyLinkedList<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);

        BOOST_CHECK_EQUAL(nums.get_size(), 3);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(4));
    }

    BOOST_AUTO_TEST_CASE(test_pop_front) {
        SinglyLinkedList<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);

        nums.pop_front();
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(1));
    }

    BOOST_AUTO_TEST_CASE(test_pop_back) {
        SinglyLinkedList<int> nums;

        nums.push_back(1);
        nums.pop_back();
        BOOST_CHECK_EQUAL(nums.get_size(), 0);
        BOOST_CHECK(!nums.find(1));

        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.pop_back();
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(!nums.find(3));
    }

    BOOST_AUTO_TEST_CASE(test_remove) {
        SinglyLinkedList<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);

        nums.remove(2);
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(2));
    }

    BOOST_AUTO_TEST_CASE(test_empty) {
        SinglyLinkedList<int> nums;

        BOOST_CHECK_EQUAL(nums.get_size(), 0);
        BOOST_CHECK(!nums.find(1));
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(testDoublyLinkedList)

    BOOST_AUTO_TEST_CASE(test_push_front) {
        DoublyLinkedList<int> nums;
        nums.push_front(1);
        nums.push_front(2);
        nums.push_front(3);

        BOOST_CHECK_EQUAL(nums.get_size(), 3);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(4));
    }

    BOOST_AUTO_TEST_CASE(test_push_back) {
        DoublyLinkedList<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);

        BOOST_CHECK_EQUAL(nums.get_size(), 3);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(4));
    }

    BOOST_AUTO_TEST_CASE(test_pop_front) {
        DoublyLinkedList<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);

        nums.pop_front();
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(1));
    }

    BOOST_AUTO_TEST_CASE(test_pop_back) {
        DoublyLinkedList<int> nums;

        nums.push_back(1);
        nums.pop_back();
        BOOST_CHECK_EQUAL(nums.get_size(), 0);
        BOOST_CHECK(!nums.find(1));

        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.pop_back();
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(2));
        BOOST_CHECK(!nums.find(3));
    }

    BOOST_AUTO_TEST_CASE(test_remove) {
        DoublyLinkedList<int> nums;

        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.remove(1); // голова
        nums.remove(3); // хвост
        BOOST_CHECK_EQUAL(nums.get_size(), 1);
        BOOST_CHECK(!nums.find(1));
        BOOST_CHECK(!nums.find(3));
        BOOST_CHECK(nums.find(2));
        nums.pop_back();

        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.remove(2);
        BOOST_CHECK_EQUAL(nums.get_size(), 2);
        BOOST_CHECK(nums.find(1));
        BOOST_CHECK(nums.find(3));
        BOOST_CHECK(!nums.find(2));
    }

    BOOST_AUTO_TEST_CASE(test_empty) {
        DoublyLinkedList<int> nums;

        BOOST_CHECK_EQUAL(nums.get_size(), 0);
        BOOST_CHECK(!nums.find(1));
    }

BOOST_AUTO_TEST_SUITE_END()
