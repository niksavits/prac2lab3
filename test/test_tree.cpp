#define BOOST_TEST_MODULE TreeTest
#include <boost/test/included/unit_test.hpp>
#include "../structures/include/tree.h"

#include "../structures/include/timer.h"

Timer timer;

BOOST_AUTO_TEST_CASE(test_insert) {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(6);

    BOOST_CHECK(tree.search(5));
    BOOST_CHECK(tree.search(4));
    BOOST_CHECK(tree.search(6));
    BOOST_CHECK(!tree.search(10));
}

BOOST_AUTO_TEST_CASE(test_isComplete) {
    BinaryTree tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);
    BOOST_CHECK(tree.isComplete());

    tree.insert(6);
    BOOST_CHECK(!tree.isComplete());

    tree.insert(4);
    BOOST_CHECK(tree.isComplete());

    tree.print();
}

BOOST_AUTO_TEST_CASE(test_ser) {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.serializeText("tree.txt");
    BinaryTree newTree;
    newTree.deserializeText("tree.txt");
    BOOST_CHECK(newTree.search(5));
    BOOST_CHECK(newTree.search(10));
    BOOST_CHECK(newTree.search(15));

    tree.serializeBinary("tree.bin");
    BinaryTree anotherTree;
    anotherTree.deserializeBinary("tree.bin");
    BOOST_CHECK(anotherTree.search(5));
    BOOST_CHECK(anotherTree.search(10));
    BOOST_CHECK(anotherTree.search(15));
}
