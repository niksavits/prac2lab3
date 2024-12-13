#include <iostream>
#include "../structures/include/stack.h"

using namespace std;

int main() {

    Stack<int> stack(10);
    stack.push(1);
    stack.push(2);
    stack.push(5);

    cout << "Текстовый формат: ";
    stack.serializeText("files/stack.txt");
    Stack<int> newStack(10);
    newStack.deserializeText("files/stack.txt");
    while (!newStack.isEmpty()) {
        cout << newStack.peek() << " ";
        newStack.pop();
    }
    cout << endl;

    cout << "Бинарный формат: ";
    stack.serializeBinary("files/stack.bin");
    Stack<int> anotherStack(10);
    anotherStack.deserializeBinary("files/stack.bin");
    while (!anotherStack.isEmpty()) {
        cout << anotherStack.peek() << " ";
        anotherStack.pop();
    }
    cout << endl;

    return 0;
}
