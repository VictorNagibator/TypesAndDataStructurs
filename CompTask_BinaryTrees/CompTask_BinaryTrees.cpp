#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <windows.h>

using namespace std;

//Класс для представления бинарного дерева
class BinaryTree {
private:
    //Структура, описывающая узел дерева
    struct Node {
        int data;
        Node* left;
        Node* right;
    };

    //Узел корень дерева
    Node* root; 

    //Рекурсивный метод для добавления элемента в дерево
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

    //Вспомогательная рекурсивная функция для заполнения множества значениями узлов дерева
    void fillSet(Node* node, unordered_set<int>& set) {
        if (node == nullptr)
            return;

        set.insert(node->data);
        fillSet(node->left, set);
        fillSet(node->right, set);
    }

    //Печать бинарного дерева в виде дерева повернутого на -90 градусов
    void printTree(Node* node, int level, ostream& output) {
        if (node == nullptr)
            return;

        printTree(node->right, level + 1, output);
        for (int i = 0; i < level; ++i)
            output << "\t";
        output << node->data << endl;

        printTree(node->left, level + 1, output);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    //Метод для добавления элемента в дерево
    void insert(int data) {
        root = insert(root, data);
    }

    //Метод для проверки, содержат ли два дерева одинаковые значения
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

    //Печать бинарного дерева в виде дерева повернутого на -90 градусов
    void print(ostream& output = cout) {
        printTree(root, 0, output);
    }

    //Деструктор для освобождения памяти, выделенной под дерево
    ~BinaryTree() {
        deleteTree(root);
    }

    //Рекурсивная функция для освобождения памяти, выделенной под дерево
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
        cout << "Ошибка: не получилось открыть файлы!" << endl;
        return 1;
    }

    BinaryTree tree1, tree2;
    int value;
    string line;

    //Считываем первую строку из файла и добавляем значения в первое дерево
    if (getline(inputFile, line)) {
        //Создаем строковый поток из строки line
        istringstream iss(line);
        while (iss >> value) {
            tree1.insert(value);
        }
    }

    //Считываем вторую строку из файла и добавляем значения во второе дерево
    if (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> value) {
            tree2.insert(value);
        }
    }

    //Выводим деревья в табличной форме в консоль
    cout << "Первое дерево:" << endl;
    tree1.print();
    cout << endl << "Второе дерево:" << endl;
    tree2.print();
    cout << endl;

    //Записываем деревья в файл
    outputFile << "Первое дерево:" << endl;
    tree1.print(outputFile);
    outputFile << endl << "Второе дерево:" << endl;
    tree2.print(outputFile);
    outputFile << endl;

    //Проверяем информационную эквивалентность деревьев
    bool equivalent = tree1.areEquivalent(tree2);

    //Выводим результат на экран и записываем в файл
    if (equivalent) {
        cout << "Два дерева информационно эквивалентны." << endl;
        outputFile << "Два дерева информационно эквивалентны." << endl;
    }
    else {
        cout << "Два дерева информационно не эквивалентны." << endl;
        outputFile << "Два дерева информационно не эквивалентны." << endl;
    }

    //Закрываем файлы
    inputFile.close();
    outputFile.close();

    return 0;
}