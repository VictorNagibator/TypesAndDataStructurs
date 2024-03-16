#include <iostream>
#include <set>
#include <list>
#include <windows.h>

using namespace std;

//стуктура, описывающая узел связанного списка
struct Node
{
    int data;
    Node* next;
};

//класс, описывающий связанный список
class MyList
{
private:
    Node* head = nullptr; //указатель на начало списка

public:
    MyList() = default;
    ~MyList();

    void append(int data); //метод для добавления элемента в конец списка
    void remove(int data); //метод для удаления элемента из списка
    void print(); //метод для вывода списка на экран
    void leaveFirstOccurrences(); //метод для удаления всех повторяющихся элементов, кроме первого вхождения
};

//в деструкторе удаляем все узлы списка
MyList::~MyList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void MyList::append(int data) {
    //если список пуст, создаем первый элемент
    if (head == nullptr) {
        head = new Node();
        head->data = data;
    }
    //иначе добавляем элемент в конец списка
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node();
        current->next->data = data;
    }
}

void MyList::remove(int data) {
    if (head == nullptr) {
        return;
    }

    //если удаляемый элемент - первый в списке, то удаляем его и меняем указатель на начало списка
    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    //проходим по списку, пока не найдем элемент для удаления
    while (current->next != nullptr) {
        if (current->next->data == data) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

void MyList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void MyList::leaveFirstOccurrences() {
    if (head == nullptr) return;

    set<int> seen;
    Node* prev = nullptr;
    Node* curr = head;

    //проходим по списку, удаляем повторяющиеся элементы
    while (curr) {
        //если текущий элемент не встречался ранее, добавляем его в множество
        if (seen.find(curr->data) == seen.end()) {
            seen.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
        //если текущий элемент встречался ранее, удаляем его из списка
        else {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } 
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //1-ое задание
    cout << "1-ое задание" << endl;
    MyList mylist1, mylist2, mylist3;

    mylist1.append(1);
    mylist1.append(2);
    mylist1.append(3);
    mylist1.append(2);
    mylist1.append(2);
    mylist1.append(4);
    mylist1.append(5);
    mylist1.append(3);
    cout << "Список 1 до изменений: ";
    mylist1.print();
    mylist1.leaveFirstOccurrences();
    cout << "Список 1 после изменений: ";
    mylist1.print();

    mylist2.append(1);
    mylist2.append(2);
    mylist2.append(3);
    mylist2.append(4);
    cout << "Список 2 до изменений: ";
    mylist2.print();
    mylist2.leaveFirstOccurrences();
    cout << "Список 2 после изменений: ";
    mylist2.print();

    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    cout << "Список 3 до изменений: ";
    mylist3.print();
    mylist3.leaveFirstOccurrences();
    cout << "Список 3 после изменений: ";
    mylist3.print();
    cout << endl;

    //2-ое задание
    cout << "2-ое задание" << endl;
    list<int> stlList1 = { 1, 2, 3, 2, 2, 4, 5, 3 },
              stlList2 = { 1, 2, 3, 4 },
              stlList3 = { 4, 4, 4, 4, 4 };

    cout << "Список 1 до изменений: ";
    for (int i : stlList1) {
        cout << i << " ";
    }
    cout << endl;
    stlList1.sort();
    stlList1.unique();
    cout << "Список 1 после изменений: ";
    for (int i : stlList1) {
		cout << i << " ";
	}
    cout << endl;

    cout << "Список 2 до изменений: ";
    for (int i : stlList2) {
        cout << i << " ";
    }
    cout << endl;
    stlList2.sort();
    stlList2.unique();
    cout << "Список 2 после изменений: ";
    for (int i : stlList2) {
        cout << i << " ";
    }
    cout << endl;

    cout << "Список 3 до изменений: ";
    for (int i : stlList3) {
        cout << i << " ";
    }
    cout << endl;
    stlList3.sort();
    stlList3.unique();
    cout << "Список 3 после изменений: ";
    for (int i : stlList3) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}