#include "../include/list.h"

template<typename T>
SinglyLinkedList<T>::Node::Node(T value) : data(value), next(nullptr) {}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    while (head) {
        pop_front();
    }
}

template<typename T>
void SinglyLinkedList<T>::push_front(T value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push_back(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template<typename T>
void SinglyLinkedList<T>::pop_front() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}

template<typename T>
void SinglyLinkedList<T>::pop_back() {
    if (head == nullptr) return;
    if (!head->next) { // если только 1 элемент
        delete head;
        head = nullptr;
        size--;
        return;
    }
    Node* current = head;
    while (current->next && current->next->next) {
        current = current->next;
    }
    delete current->next; // Удаляем последний элемент
    current->next = nullptr; // Обнуляем указатель
    size--;
}

template<typename T>
void SinglyLinkedList<T>::remove(T value) {
    Node* current = head;
    Node* previous = nullptr;
    while (current) {
        if (current->data == value) {
            previous->next = current->next; // Пропускаем текущий узел
            delete current; // Освобождаем память
            size--;
            return; // Выход после удаления первого найденного элемента
        }
        previous = current;
        current = current->next;
    }
}

template<typename T>
bool SinglyLinkedList<T>::find(T value) const {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return true; // Элемент найден
        }
        current = current->next;
    }
    return false; // Элемент не найден
}

template<typename T>
void SinglyLinkedList<T>::print() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
int SinglyLinkedList<T>::get_size() const {
    return size;
}

template<typename T>
void SinglyLinkedList<T>::serializeText(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        outFile << current->data << " ";
        current = current->next;
    }
    outFile.close();
}

template<typename T>
void SinglyLinkedList<T>::deserializeText(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return;
    }

    // Очистка текущего списка
    while (head) {
        pop_front();
    }

    T value;
    while (inFile >> value) {
        push_back(value);
    }
    inFile.close();
}

template<typename T>
void SinglyLinkedList<T>::serializeBinary(const string& filename) const {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        outFile.write(reinterpret_cast<const char*>(&current->data), sizeof(T));
        current = current->next;
    }
    outFile.close();
}

template<typename T>
void SinglyLinkedList<T>::deserializeBinary(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return;
    }

    // Очистка текущего списка
    while (head) {
        pop_front();
    }

    T value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(T))) {
        push_back(value);
    }
    inFile.close();
}


template<typename T>
DoublyLinkedList<T>::Node::Node(T value) : data(value), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        pop_front();
    }
}

template<typename T>
void DoublyLinkedList<T>::push_front(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // Список стал пустым
    }
    delete temp;
    size--;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (tail == nullptr) return; // Список пуст
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // Список стал пустым
    }
    delete temp;
    size--;
}

template<typename T>
void DoublyLinkedList<T>::remove(T value) {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next; // Удаляем голову
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev; // Удаляем хвост
            }
            delete current;
            size--;
            return; // Выход после удаления первого найденного элемента
        }
        current = current->next;
    }
}

template<typename T>
bool DoublyLinkedList<T>::find(T value) const {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return true; // Элемент найден
        }
        current = current->next;
    }
    return false; // Элемент не найден
}

template<typename T>
void DoublyLinkedList<T>::print() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
int DoublyLinkedList<T>::get_size() const {
    return size;
}

template<typename T>
void DoublyLinkedList<T>::serializeText(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        outFile << current->data << " ";
        current = current->next;
    }
    outFile.close();
}

template<typename T>
void DoublyLinkedList<T>::deserializeText(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    while (head) { // Очищаем текущий список
        pop_front();
    }

    string line;
    if (getline(inFile, line)) {
        istringstream iss(line);
        T value;
        while (iss >> value) {
            push_back(value);
        }
    }
    inFile.close();
}

template<typename T>
void DoublyLinkedList<T>::serializeBinary(const string& filename) const {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        outFile.write(reinterpret_cast<const char*>(&current->data), sizeof(T));
        current = current->next;
    }
    outFile.close();
}

template<typename T>
void DoublyLinkedList<T>::deserializeBinary(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return;
    }

    // Очистка текущего списка
    while (head) {
        pop_front();
    }

    T value;
    while (inFile >> value) {
        push_back(value);
    }
    inFile.close();
}
