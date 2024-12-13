#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class HashTable {
public:
    HashTable(); // Конструктор
    ~HashTable(); // Деструктор

    void insert(const string& key, T value); // Вставка элемента
    bool get(const string& key, T& value); // Получение значения по ключу
    bool remove(const string& key); // Удаление элемента по ключу

    void serializeText(const string& filename);
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);
private:
    struct KeyValuePair {
        string key;
        T value;
        KeyValuePair* next;
    };

    static const int TABLE_SIZE = 100; // Размер таблицы
    KeyValuePair* table[TABLE_SIZE]; // Массив указателей на ключ-значение
    int sizetable; // Количество элементов в таблице

    int hashFunction(const string& key); // Хеш-функция
};

#include "../src/hashtable.cpp"

#endif
