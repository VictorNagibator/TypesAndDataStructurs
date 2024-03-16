#include <iostream>
#include <set>
#include <list>
#include <windows.h>

using namespace std;

//��������, ����������� ���� ���������� ������
struct Node
{
    int data;
    Node* next;
};

//�����, ����������� ��������� ������
class MyList
{
private:
    Node* head = nullptr; //��������� �� ������ ������

public:
    MyList() = default;
    ~MyList();

    void append(int data); //����� ��� ���������� �������� � ����� ������
    void remove(int data); //����� ��� �������� �������� �� ������
    void print(); //����� ��� ������ ������ �� �����
    void leaveFirstOccurrences(); //����� ��� �������� ���� ������������� ���������, ����� ������� ���������
};

MyList::~MyList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void MyList::append(int data) {
    if (head == nullptr) {
        head = new Node();
        head->data = data;
    }
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

    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
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

    while (curr) {
        if (seen.find(curr->data) == seen.end()) {
            seen.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
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

    //1-�� �������
    cout << "1-�� �������" << endl;
    MyList mylist1, mylist2, mylist3;

    mylist1.append(1);
    mylist1.append(2);
    mylist1.append(3);
    mylist1.append(2);
    mylist1.append(2);
    mylist1.append(4);
    mylist1.append(5);
    mylist1.append(3);
    cout << "������ 1 �� ���������: ";
    mylist1.print();
    mylist1.leaveFirstOccurrences();
    cout << "������ 1 ����� ���������: ";
    mylist1.print();

    mylist2.append(1);
    mylist2.append(2);
    mylist2.append(3);
    mylist2.append(4);
    cout << "������ 2 �� ���������: ";
    mylist2.print();
    mylist2.leaveFirstOccurrences();
    cout << "������ 2 ����� ���������: ";
    mylist2.print();

    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    mylist3.append(4);
    cout << "������ 3 �� ���������: ";
    mylist3.print();
    mylist3.leaveFirstOccurrences();
    cout << "������ 3 ����� ���������: ";
    mylist3.print();
    cout << endl;

    //2-�� �������
    cout << "2-�� �������" << endl;
    list<int> stlList1 = { 1, 2, 3, 2, 2, 4, 5, 3 },
              stlList2 = { 1, 2, 3, 4 },
              stlList3 = { 4, 4, 4, 4, 4 };

    cout << "������ 1 �� ���������: ";
    for (int i : stlList1) {
        cout << i << " ";
    }
    cout << endl;
    stlList1.sort();
    stlList1.unique();
    cout << "������ 1 ����� ���������: ";
    for (int i : stlList1) {
		cout << i << " ";
	}
    cout << endl;

    cout << "������ 2 �� ���������: ";
    for (int i : stlList2) {
        cout << i << " ";
    }
    cout << endl;
    stlList2.sort();
    stlList2.unique();
    cout << "������ 2 ����� ���������: ";
    for (int i : stlList2) {
        cout << i << " ";
    }
    cout << endl;

    cout << "������ 3 �� ���������: ";
    for (int i : stlList3) {
        cout << i << " ";
    }
    cout << endl;
    stlList3.sort();
    stlList3.unique();
    cout << "������ 3 ����� ���������: ";
    for (int i : stlList3) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}