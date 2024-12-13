#define BOOST_TEST_MODULE HashTableTest
#include <boost/test/included/unit_test.hpp>
#include "../structures/include/hashtable.h"
#include "../structures/include/timer.h"

Timer timer;

BOOST_AUTO_TEST_CASE(test_insert_and_get) {
    HashTable<int> ht;

    // Вставка элементов
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);

    int value;

    // Проверка получения значений
    BOOST_CHECK(ht.get("one", value));
    BOOST_CHECK_EQUAL(value, 1);

    BOOST_CHECK(ht.get("two", value));
    BOOST_CHECK_EQUAL(value, 2);

    BOOST_CHECK(ht.get("three", value));
    BOOST_CHECK_EQUAL(value, 3);

    // Проверка отсутствия ключа
    BOOST_CHECK(!ht.get("four", value));
}

BOOST_AUTO_TEST_CASE(test_update_value) {
    HashTable<int> ht;

    // Вставка элемента
    ht.insert("one", 1);

    // Обновление значения
    ht.insert("one", 10);

    int value;
    BOOST_CHECK(ht.get("one", value));
    BOOST_CHECK_EQUAL(value, 10); // Проверяем обновленное значение
}

BOOST_AUTO_TEST_CASE(test_remove) {
    HashTable<int> ht;

    // Вставка элементов
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("654321", 1);
    ht.insert("6543219", 2);

    // Удаление элемента
    BOOST_CHECK(ht.remove("one"));
    BOOST_CHECK(ht.remove("6543219"));

    int value;
    BOOST_CHECK(!ht.get("one", value)); // Проверяем, что элемент был удален
    BOOST_CHECK(ht.get("two", value));   // Проверяем, что другой элемент все еще доступен
    BOOST_CHECK(!ht.get("6543219", value)); // Проверяем, что элемент был удален
    BOOST_CHECK(ht.get("654321", value));   // Проверяем, что другой элемент все еще доступен
}

BOOST_AUTO_TEST_CASE(test_remove_non_existent) {
    HashTable<int> ht;

    // Удаление несуществующего элемента
    BOOST_CHECK(!ht.remove("nonexistent")); // Должно вернуть false
}

BOOST_AUTO_TEST_CASE(test_collision) {
    HashTable<int> ht;

    // Вставка элементов с потенциальными хеш-коллизиями
    ht.insert("654321", 1);
    ht.insert("6543219", 2);

    int value;

    // Проверка значений
    BOOST_CHECK(ht.get("654321", value));
    BOOST_CHECK_EQUAL(value, 1);

    BOOST_CHECK(ht.get("6543219", value));
    BOOST_CHECK_EQUAL(value, 2);
}
