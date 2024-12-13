#include "../include/stack.h"

template <typename T>
Stack<T>::Stack(int size) : top(-1), capacity(size) {
    data = new T[capacity];
}

template <typename T>
Stack<T>::~Stack() {
    delete[] data;
}

template <typename T>
void Stack<T>::push(T value) {
    if (top >= capacity - 1) {
        cout << "Стек переполнен!" << endl; // Проверка на переполнение
        return;
    }
    data[++top] = value; // Увеличение индекса и добавление элемента
}

template <typename T>
void Stack<T>::pop() {
    if (top < 0) {
        cout << "Стек пуст!" << endl; // Проверка на пустоту
        return;
    }
    data[--top]; // удаление верхнего элемента и уменьшение индекса
}

template <typename T>
T Stack<T>::peek() {
    if (top == -1) {
        cout << "Стек пуст!" << endl; // Проверка на пустоту
        return -1;
    }
    return data[top];
}

template <typename T>
bool Stack<T>::isEmpty() {
    return top < 0;
}

template <typename T>
int Stack<T>::size() {
    return top + 1;
}

template <typename T>
void Stack<T>::serializeText(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (int i = 0; i <= top; ++i) {
        ofs << data[i] << endl; // Записываем каждый элемент в файл
    }

    ofs.close();
}

template <typename T>
void Stack<T>::deserializeText(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    T value;
    while (ifs >> value) {
        push(value); // Добавляем элементы в стек
    }

    ifs.close();
}

template <typename T>
void Stack<T>::serializeBinary(const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    ofs.write(reinterpret_cast<char*>(&top), sizeof(top)); // Записываем размер стека
    ofs.write(reinterpret_cast<char*>(&capacity), sizeof(capacity)); // Записываем емкость стека
    ofs.write(reinterpret_cast<char*>(data), sizeof(T) * (top + 1)); // Записываем данные стека

    ofs.close();
}

template <typename T>
void Stack<T>::deserializeBinary(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    ifs.read(reinterpret_cast<char*>(&top), sizeof(top)); // Читаем размер стека
    ifs.read(reinterpret_cast<char*>(&capacity), sizeof(capacity)); // Читаем емкость стека

    delete[] data; // Удаляем старый массив
    data = new T[capacity]; // Создаем новый массив
    ifs.read(reinterpret_cast<char*>(data), sizeof(T) * (top + 1)); // Читаем данные стека

    ifs.close();
}
