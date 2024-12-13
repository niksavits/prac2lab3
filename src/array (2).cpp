#include <iostream>
#include "../structures/include/array.h"

using namespace std;

int main() {

    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(4);

    cout << "Текстовый формат: ";
    arr.serializeText("files/array.txt");
    Array<int> newArr;
    newArr.deserializeText("files/array.txt");
    newArr.print();

    cout << "Бинарный формат: ";
    arr.serializeBinary("files/array.bin");
    Array<int> anotherArr;
    anotherArr.deserializeBinary("files/array.bin");
    anotherArr.print();

    return 0;
}
