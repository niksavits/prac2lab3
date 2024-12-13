#include "../include/tree.h"

BinaryTree::Node::Node(int value) : data(value), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr), size(0) {}

BinaryTree::~BinaryTree() {
    destroyTree(root);
}

void BinaryTree::insert(int value) {
    root = insertRec(root, value);
    size++;
}

bool BinaryTree::search(int value) {
    return searchRec(root, value);
}

bool BinaryTree::isComplete() {
    int nodeCount = countNodes(root);
    return isCompleteRec(root, 0, nodeCount);
}

void BinaryTree::print() {
    printTreeRec(root, 0);
    cout << endl;
}

BinaryTree::Node* BinaryTree::insertRec(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->data) {
        node->left = insertRec(node->left, value);
    } else {
        node->right = insertRec(node->right, value);
    }
    return node;
}

bool BinaryTree::searchRec(Node* node, int value) {
    if (node == nullptr) return false;
    if (node->data == value) return true;

    if (value < node->data) {
        return searchRec(node->left, value);
    } else {
        return searchRec(node->right, value);
    }
}

int BinaryTree::countNodes(Node* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

bool BinaryTree::isCompleteRec(Node* node, int index, int numberNodes) {
    if (node == nullptr) return true;
    if (index >= numberNodes) return false;

    return isCompleteRec(node->left, 2 * index + 1, numberNodes) &&
            isCompleteRec(node->right, 2 * index + 2, numberNodes);
}

void BinaryTree::printTreeRec(Node* node, int depth) {
    if (node == nullptr) return;

    // Сначала выводим правое поддерево
    printTreeRec(node->right, depth + 1);

    // Затем выводим текущий узел
    cout << setw(4 * depth) << " " << node->data << endl;

    // Затем выводим левое поддерево
    printTreeRec(node->left, depth + 1);
}

void BinaryTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);   // Освобождаем левое поддерево
        destroyTree(node->right);  // Освобождаем правое поддерево
        delete node;               // Освобождаем текущий узел
    }
}

void BinaryTree::serializeText(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    serializeRec(root, ofs);
    ofs.close();
}

void BinaryTree::serializeRec(Node* node, ofstream& ofs) {
    if (node == nullptr) {
        ofs << "#" << " "; // Используем '#' для обозначения пустого узла
        return;
    }
    ofs << node->data << " "; // Записываем значение узла
    serializeRec(node->left, ofs); // Рекурсивно сериализуем левое поддерево
    serializeRec(node->right, ofs); // Рекурсивно сериализуем правое поддерево
}

void BinaryTree::deserializeText(const string& filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    root = deserializeRec(ifs);

    ifs.close();
}

BinaryTree::Node* BinaryTree::deserializeRec(ifstream& ifs) {
    string value;
    if (!(ifs >> value)) return nullptr; // Если не удалось прочитать значение

    if (value == "#") return nullptr; // Пустой узел

    int data = stoi(value);
    Node* node = new Node(data); // Создаем новый узел
    node->left = deserializeRec(ifs); // Рекурсивно десериализуем левое поддерево
    node->right = deserializeRec(ifs); // Рекурсивно десериализуем правое поддерево
    return node;
}

void BinaryTree::serializeBinary(const string& filename) {
    ofstream ofs(filename, ios::binary); // Открываем файл в бинарном режиме
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи!" << endl;
    return;
    }
    serializeBinaryRec(root, ofs);
    ofs.close();
}

void BinaryTree::serializeBinaryRec(Node* node, ofstream& ofs) {
    if (node == nullptr) {
        // Используем -1 для обозначения пустого узла
        int marker = -1;
        ofs.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
        return;
    }

    // Записываем значение узла
    ofs.write(reinterpret_cast<const char*>(&node->data), sizeof(node->data));

    // Рекурсивно сериализуем левое и правое поддерево
    serializeBinaryRec(node->left, ofs);
    serializeBinaryRec(node->right, ofs);
}

void BinaryTree::deserializeBinary(const string& filename) {
    ifstream ifs(filename, ios::binary); // Открываем файл в бинарном режиме
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    root = deserializeBinaryRec(ifs);

    ifs.close();
}

BinaryTree::Node* BinaryTree::deserializeBinaryRec(ifstream& ifs) {
    int data;

    // Читаем значение узла
    if (ifs.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        if (data == -1) return nullptr; // Пустой узел

        Node* node = new Node(data); // Создаем новый узел

        // Рекурсивно десериализуем левое и правое поддерево
        node->left = deserializeBinaryRec(ifs);
        node->right = deserializeBinaryRec(ifs);

        return node;
    }

    return nullptr; // Если не удалось прочитать данные
}
