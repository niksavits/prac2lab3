#include <iostream>
#include "../structures/include/queue.h"

using namespace std;

int main() {

    Queue<int> queue(10);
    queue.push(1);
    queue.push(2);
    queue.push(3);

    cout << "Текстовый формат: ";
    queue.serializeText("files/queue.txt");
    Queue<int> newQueue(10);
    newQueue.deserializeText("files/queue.txt");
    while (!newQueue.isEmpty()) {
        cout << newQueue.peek() << " ";
        newQueue.pop();
    }
    cout << endl;

    cout << "Бинарный формат: ";
    queue.serializeText("files/queue.bin");
    Queue<int> anotherQueue(10);
    anotherQueue.deserializeText("files/queue.bin");
    while (!anotherQueue.isEmpty()) {
        cout << anotherQueue.peek() << " ";
        anotherQueue.pop();
    }
    cout << endl;

    return 0;
}
