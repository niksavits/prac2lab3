#ifndef QUEUE_H
#define QUEUE_H

#include <fstream>

using namespace std;

template <typename T>
class Queue {
public:
    Queue(int cap); // конструктор
    ~Queue(); // деструктор

    void push(T value); // ф-ия добавления элемента в конец очереди
    void pop(); // ф-ия удаления элемента с начала очереди и его возврат
    T peek(); // ф-ия вывода элемента в начале очереди
    bool isEmpty(); // ф-ия проверки очереди на пустоту
    int Size(); // ф-ия получения размера очереди

    void serializeText(const string& filename);
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);
private:
    T* data;        // Указатель на массив данных
    int front;      // Индекс первого элемента
    int rear;       // Индекс последнего элемента
    int capacity;   // Вместимость очереди
    int size;       // Текущий размер очереди
};

#include "../src/queue.cpp" // Включаем реализацию шаблона

#endif
