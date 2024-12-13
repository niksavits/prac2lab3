#include "../include/hashtable.h"

template<typename T>
HashTable<T>::HashTable() : sizetable(0) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

template<typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        KeyValuePair* current = table[i];
        while (current) {
            KeyValuePair* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

template<typename T>
int HashTable<T>::hashFunction(const string& key) {
    hash<string> hashFn;
    return hashFn(key) % TABLE_SIZE;
}

template<typename T>
void HashTable<T>::insert(const string& key, T value) {
    int index = hashFunction(key);
    KeyValuePair* newPair = new KeyValuePair{key, value, nullptr};

    if (!table[index]) {
        table[index] = newPair; // Если ячейка пустая, добавляем новый элемент
        sizetable++;
    } else {
        KeyValuePair* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ существует
                delete newPair; // Удаляем временный элемент
                return; // Не увеличиваем sizetable
            }
            if (!current->next) { // Если достигли конца цепочки
                current->next = newPair; // Добавляем новый элемент в конец цепочки
                sizetable++;
                return;
            }
            current = current->next;
        }
    }
}

template<typename T>
bool HashTable<T>::get(const string& key, T& value) {
    int index = hashFunction(key);
    KeyValuePair* current = table[index];
    while (current) {
        if (current->key == key) {
            value = current->value; // Возвращаем значение
            return true;
        }
        current = current->next;
    }
    return false; // Ключ не найден
}

template<typename T>
bool HashTable<T>::remove(const string& key) {
    int index = hashFunction(key);
    KeyValuePair* current = table[index];
    KeyValuePair* previous = nullptr;

    while (current) {
        if (current->key == key) {
            if (previous) {
                previous->next = current->next; // Удаляем элемент из цепочки
            } else {
                table[index] = current->next; // Если это первый элемент в цепочке
            }
            delete current; // Освобождаем память
            sizetable--;
            return true; // Успешное удаление
        }
        previous = current;
        current = current->next;
    }
    return false; // Ключ не найден
}

template<typename T>
void HashTable<T>::serializeText(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        KeyValuePair* current = table[i];
        while (current) {
            ofs << current->key << ":" << current->value << endl;
            current = current->next;
        }
    }

    ofs.close();
}

template<typename T>
void HashTable<T>::deserializeText(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string key;
        T value;

        if (getline(iss, key, ':') && (iss >> value)) {
            insert(key, value);
        }
    }

    ifs.close();
}

template<typename T>
void HashTable<T>::serializeBinary(const string& filename) {
    ofstream ofs(filename, ios::binary);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        KeyValuePair* current = table[i];
        while (current) {
            size_t keyLength = current->key.size();
            ofs.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength)); // Записываем длину ключа
            ofs.write(current->key.c_str(), keyLength); // Записываем ключ
            ofs.write(reinterpret_cast<const char*>(&current->value), sizeof(current->value)); // Записываем значение
            current = current->next;
        }
    }

    ofs.close();
}

// Десериализация из бинарного формата
template<typename T>
void HashTable<T>::deserializeBinary(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    while (true) {
        size_t keyLength;
        if (!ifs.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength))) break; // Читаем длину ключа

        string key(keyLength, '0'); // Создаем строку нужной длины
        if (!ifs.read(&key[0], keyLength)) break; // Читаем ключ

        T value;
        if (!ifs.read(reinterpret_cast<char*>(&value), sizeof(value))) break; // Читаем значение

        insert(key, value); // Вставляем пару в хеш-таблицу
    }

    ifs.close();
}
