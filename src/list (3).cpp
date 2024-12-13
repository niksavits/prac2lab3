#include <iostream>
#include "../structures/include/list.h"

using namespace std;

int main() {

    cout << "Односвязный список: " << endl;
    SinglyLinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(5);

    cout << "Текстовый формат: ";
    list1.serializeText("files/list.txt");
    SinglyLinkedList<int> newList1;
    newList1.deserializeText("files/list.txt");
    newList1.print();

    cout << "Бинарный формат: ";
    list1.serializeBinary("files/list.bin");
    SinglyLinkedList<int> binaryList1;
    binaryList1.deserializeBinary("files/list.bin");
    binaryList1.print();


    cout << endl << "Двухсвязный список: " << endl;
    DoublyLinkedList<int> list2;
    list2.push_back(3);
    list2.push_back(2);
    list2.push_back(3);

    cout << "Текстовый формат: ";
    list2.serializeText("files/list.txt");
    SinglyLinkedList<int> newList2;
    newList2.deserializeText("files/list.txt");
    newList2.print();

    cout << "Бинарный формат: ";
    list2.serializeBinary("files/list.bin");
    SinglyLinkedList<int> binaryList2;
    binaryList2.deserializeBinary("files/list.bin");
    binaryList2.print();

    return 0;
}
