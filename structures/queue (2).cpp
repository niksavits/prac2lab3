#include "../include/queue.h"

template<typename T>
Queue<T>::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
    data = new T[capacity];
}

template<typename T>
Queue<T>::~Queue() {
    delete[] data;
}

template<typename T>
void Queue<T>::push(T value) {
    if (size == capacity) {
        cout << "Очередь переполнена!" << endl; // Проверка на переполнение
        return;
    }
    rear = (rear + 1) % capacity; // Циклическое увеличение индекса
    data[rear] = value; // Добавление элемента
    size++; // Увеличение размера очереди
}

template<typename T>
void Queue<T>::pop() {
    if (size == 0) {
        cout << "Очередь пуста!" << endl; // Проверка на пустоту
        return;
    }
    front = (front + 1) % capacity; // Циклическое увеличение индекса
    size--; // Уменьшение размера очереди
}

template<typename T>
T Queue<T>::peek() {
    if (size == 0) {
        cout << "Очередь пуста" << endl; // Проверка на пустоту
        return -1;
    }
    return data[front];
}

template<typename T>
bool Queue<T>::isEmpty() {
    return size == 0;
}

template<typename T>
int Queue<T>::Size() {
    return size;
}

template <typename T>
void Queue<T>::serializeText(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    ofs << size << endl; // Сначала записываем размер очереди
    for (int i = 0; i < size; ++i) {
        ofs << data[(front + i) % capacity] << endl; // Записываем элементы очереди
    }

    ofs.close();
}

template <typename T>
void Queue<T>::deserializeText(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    int newSize;
    ifs >> newSize; // Читаем размер очереди
    if (newSize > capacity) {
        cerr << "Ошибка: размер очереди превышает емкость!" << endl;
        return;
    }

    // Очищаем текущую очередь
    front = 0;
    rear = -1;
    size = 0;

    T value;
    for (int i = 0; i < newSize; ++i) {
        ifs >> value; // Читаем элемент
        push(value); // Добавляем элемент в очередь
    }

    ifs.close();
}

template <typename T>
void Queue<T>::serializeBinary(const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    ofs.write(reinterpret_cast<char*>(&size), sizeof(size)); // Записываем размер очереди
    for (int i = 0; i < size; ++i) {
        ofs.write(reinterpret_cast<char*>(&data[(front + i) % capacity]), sizeof(T)); // Записываем элементы очереди
    }

    ofs.close();
}

template <typename T>
void Queue<T>::deserializeBinary(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    ifs.read(reinterpret_cast<char*>(&size), sizeof(size)); // Читаем размер очереди
    if (size > capacity) {
        cerr << "Ошибка: размер очереди превышает емкость!" << endl;
        return;
    }

    // Очищаем текущую очередь
    front = 0;
    rear = -1;

    T value;
    for (int i = 0; i < size; ++i) {
        ifs.read(reinterpret_cast<char*>(&value), sizeof(T)); // Читаем элемент
        push(value); // Добавляем элемент в очередь
    }

    ifs.close();
}
