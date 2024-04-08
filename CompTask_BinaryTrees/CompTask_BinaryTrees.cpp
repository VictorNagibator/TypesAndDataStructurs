#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <windows.h>

using namespace std;

//����� ��� ������������� ��������� ������
class BinaryTree {
private:
    //���������, ����������� ���� ������
    struct Node {
        int data;
        Node* left;
        Node* right;
    };

    //���� ������ ������
    Node* root; 

    //����������� ����� ��� ���������� �������� � ������
    Node* insert(Node* node, int data) {
        if (node == nullptr)
        {
            node = new Node;
            node->data = data;
            node->left = node->right = nullptr;
        }

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        return node;
    }

    //��������������� ����������� ������� ��� ���������� ��������� ���������� ����� ������
    void fillSet(Node* node, unordered_set<int>& s) {
        if (node == nullptr)
            return;

        s.insert(node->data);
        fillSet(node->left, s);
        fillSet(node->right, s);
    }

    //������ ��������� ������ � ���� ������ ����������� �� -90 ��������
    void printTree(Node* node, int level) {
        if (node == nullptr)
            return;

        printTree(node->right, level + 1);
        for (int i = 0; i < level; ++i)
            cout << "\t";
        cout << node->data << endl;

        printTree(node->left, level + 1);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    //����� ��� ���������� �������� � ������
    void insert(int data) {
        root = insert(root, data);
    }

    //����� ��� ��������, �������� �� ��� ������ ���������� ��������
    bool areEquivalent(BinaryTree& other) {
        unordered_set<int> set1, set2;
        fillSet(root, set1);
        fillSet(other.root, set2);

        for (int val : set1) {
            if (set2.find(val) == set2.end())
                return false;
        }
        for (int val : set2) {
            if (set1.find(val) == set1.end())
                return false;
        }
        return true;
    }

    //������ ��������� ������ � ���� ������ ����������� �� -90 ��������
    void print() {
        printTree(root, 0);
    }

    //���������� ��� ������������ ������, ���������� ��� ������
    ~BinaryTree() {
        deleteTree(root);
    }

    //����������� ������� ��� ������������ ������, ���������� ��� ������
    void deleteTree(Node* node) {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("input.dat");
    ofstream outputFile("output.dat");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "������: �� ���������� ������� �����!" << endl;
        return 1;
    }

    BinaryTree tree1, tree2;
    int value;
    string line;

    //��������� ������ ������ �� ����� � ��������� �������� � ������ ������
    if (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> value) {
            tree1.insert(value);
        }
    }

    //��������� ������ ������ �� ����� � ��������� �������� �� ������ ������
    if (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> value) {
            tree2.insert(value);
        }
    }

    //������� ������� � ��������� �����
    cout << "������ ������:" << endl;
    tree1.print();
    cout << endl << "������ ������:" << endl;
    tree2.print();
    cout << endl;

    //��������� �������������� ��������������� ��������
    bool equivalent = tree1.areEquivalent(tree2);

    //������� ��������� �� ����� � ���������� � ����
    if (equivalent) {
        cout << "��� ������ ������������� ������������." << endl;
        outputFile << "��� ������ ������������� ������������." << endl;
    }
    else {
        cout << "��� ������ �� ������������� ������������." << endl;
        outputFile << "��� ������ �� ������������� ������������." << endl;
    }

    //��������� �����
    inputFile.close();
    outputFile.close();

    return 0;
}
