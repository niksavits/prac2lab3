#include <iostream>
#include "../structures/include/tree.h"

using namespace std;

int main() {

    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    cout << "Текстовый формат:" << endl;
    tree.serializeText("files/tree.txt");
    BinaryTree newTree;
    newTree.deserializeText("files/tree.txt");
    newTree.print();

    cout << "Бинарный формат:" << endl;
    tree.serializeBinary("files/tree.bin");
    BinaryTree anotherTree;
    anotherTree.deserializeBinary("files/tree.bin");
    anotherTree.print();

    return 0;
}
