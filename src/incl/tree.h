#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void insert(int value);
    bool search(int value);
    bool isComplete();
    void print();

    void serializeText(const string& filename);
    void deserializeText(const string& filename);
    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value);
    };

    Node* root;
    int size;

    Node* insertRec(Node* node, int value);
    bool searchRec(Node* node, int value);
    int countNodes(Node* node);
    bool isCompleteRec(Node* node, int index, int numberNodes);
    void printTreeRec(Node* node, int depth);
    void destroyTree(Node* node);

    void serializeRec(Node* node, ofstream& ofs);
    Node* deserializeRec(ifstream& ifs);
    void serializeBinaryRec(Node* node, ofstream& ofs);
    Node* deserializeBinaryRec(ifstream& ifs);
};

#include "../src/tree.cpp" // Включаем реализацию шаблона

#endif
