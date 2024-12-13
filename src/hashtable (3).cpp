#include <iostream>
#include "../structures/include/hashtable.h"

using namespace std;

int main() {

    HashTable<int> table;
    table.insert("key1", 1);
    table.insert("key2", 2);
    table.insert("key3", 3);

    cout << "Текстовый формат: ";
    table.serializeText("files/hashtable.txt");
    HashTable<int> newTable;
    newTable.deserializeText("files/hashtable.txt");
    int value;
    newTable.get("key1", value);
    cout << "key1:" << value << " ";
    newTable.get("key2", value);
    cout << "key2:" << value << " ";
    newTable.get("key3", value);
    cout << "key3:" << value;
    cout << endl;

    cout << "Бинарный формат: ";
    table.serializeBinary("files/hashtable.bin");
    HashTable<int> anotherTable;
    anotherTable.deserializeBinary("files/hashtable.bin");
    anotherTable.get("key1", value);
    cout << "key1:" << value << " ";
    anotherTable.get("key2", value);
    cout << "key2:" << value << " ";
    anotherTable.get("key3", value);
    cout << "key3:" << value;
    cout << endl;

    return 0;
}
