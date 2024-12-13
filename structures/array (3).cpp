#include "../include/array.h"

template<typename T>
Array<T>::Array() : capacity(10), size(0) {
    data = new T[capacity];
}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
void Array<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i]; // Копируем старые данные
    }
    delete[] data; // Освобождаем старый массив
    data = newData; // Указываем на новый массив
}

template<typename T>
void Array<T>::add(T value) {
    if (size == capacity) {
        resize(); // Увеличиваем массив, если он заполнен
    }
    data[size++] = value;
}

template<typename T>
void Array<T>::addAt(size_t index, T value) {
    if (index > size) {
        cout << "Индекс выходит за размеры массива!" << endl;
        return;
    }
    if (size == capacity) {
        resize(); // если заполнен - увеличить
    }
    for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1]; // Сдвигаем элементы вправо
    }
    data[index] = value;
    ++size;
}

template<typename T>
T Array<T>::get(size_t index) const {
    if (index >= size) {
        cout << "Индекс выходит за размеры массива!" << endl;
        return -1;
    }
    return data[index];
}

template<typename T>
void Array<T>::remove(size_t index) {
    if (index >= size) {
        cout << "Индекс выходит за размеры массива!" << endl;
        return;
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1]; // Сдвигаем элементы влево
    }
    --size; // уменьшаем размер
}

template<typename T>
void Array<T>::replace(size_t index, T value) {
    if (index >= size) {
        cout << "Индекс выходит за размеры массива!" << endl;
        return;
    }
    data[index] = value; // Заменяем элемент по индексу
}

template<typename T>
size_t Array<T>::length() const {
    return size;
}

template<typename T>
void Array<T>::print() const {
    for (size_t i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

template<typename T>
void Array<T>::serializeText(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    outFile << size << endl; // Сначала записываем размер массива
    for (size_t i = 0; i < size; ++i) {
        outFile << data[i] << endl; // Записываем каждый элемент
    }
    outFile.close();
}

template<typename T>
void Array<T>::deserializeText(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    size_t newSize;
    inFile >> newSize; // Читаем размер массива
    for (size_t i = 0; i < newSize; ++i) {
        T value;
        inFile >> value; // Читаем каждый элемент
        add(value); // Добавляем элемент в массив
    }
    inFile.close();
}

template<typename T>
void Array<T>::serializeBinary(const string& filename) const {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Записываем размер
    outFile.write(reinterpret_cast<const char*>(data), sizeof(T) * size); // Записываем данные
    outFile.close();
}

template<typename T>
void Array<T>::deserializeBinary(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size)); // Читаем размер
    // Увеличиваем массив до нужного размера
    while (capacity < size) {
        resize();
    }
    inFile.read(reinterpret_cast<char*>(data), sizeof(T) * size); // Читаем данные
    inFile.close();
}
