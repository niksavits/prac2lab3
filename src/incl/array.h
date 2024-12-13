#ifndef ARRAY_H
#define ARRAY_H

#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class Array {
public:
    Array(); // Конструктор
    ~Array(); // Деструктор

    void resize(); // Увеличение вместимости
    void add(T value); // Добавление элемента в конец массива
    void addAt(size_t index, T value); // Добавление элемента по индексу
    T get(size_t index) const; // Получение элемента по индексу
    void remove(size_t index); // Удаление элемента по индексу
    void replace(size_t index, T value); // Замена элемента по индексу
    size_t length() const; // Вывод размера массива
    void print() const; // Вывод массива

    void serializeText(const string& filename) const;
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename) const;
    void deserializeBinary(const string& filename);
private:
    T* data;       // Указатель на массив
    size_t capacity; // Вместимость массива
    size_t size;     // Текущий размер массива
};

#include "../src/array.cpp" // Включаем реализацию шаблона

#endif
