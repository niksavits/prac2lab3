#ifndef STACK_H
#define STACK_H

#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class Stack {
public:
    Stack(int size); // конструктор
    ~Stack(); // деструктор

    void push(T value); // добавление элемента
    void pop(); // удаление элемента
    T peek(); // вывод вершины стека
    bool isEmpty(); // проверка на пустоту
    int size(); // размер

    void serializeText(const string& filename);
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);
private:
    T* data;        // Указатель на массив данных
    int top;        // Индекс верхнего элемента
    int capacity;   // Вместимость стека
};

#include "../src/stack.cpp" // Включаем реализацию шаблона

#endif
