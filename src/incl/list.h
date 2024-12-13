#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    void push_front(T value); // добавление элемента в начало
    void push_back(T value); // добавление элемента в конец
    void pop_front(); // удаление элемента с начала
    void pop_back(); // удаление элемента с конца
    void remove(T value); // удаление элемента по значению
    bool find(T value) const; // поиска элемента по значению
    void print() const; // вывод списка
    int get_size() const;

    void serializeText(const string& filename) const;
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename) const;
    void deserializeBinary(const string& filename);
private:
    struct Node {
        T data;
        Node* next;

        Node(T value); // конструктор узла
    };

    Node* head;
    int size;
};

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(T value); // добавление элемента в начало
    void push_back(T value); // добавление элемента в конец
    void pop_front(); // удаление элемента в начале
    void pop_back(); // удаление элемента в конце
    void remove(T value); // удаление элемента по значению
    bool find(T value) const; // поиска элемента по значению
    void print() const; // вывод списка
    int get_size() const;

    void serializeText(const string& filename) const;
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename) const;
    void deserializeBinary(const string& filename);
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value);
    };

    Node* head;
    Node* tail;
    int size;
};



#include "../src/list.cpp"

#endif
