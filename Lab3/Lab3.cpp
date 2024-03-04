#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //���� ����� �����
    string filename;
    cout << "������� ��� ���������� �����: ";
    cin >> filename;

    //�������� �����
    ifstream infile(filename);
    if (!infile) {
        cerr << "������ �������� �����!" << endl;
        return -1;
    }

    //��������� ��� �������� ���������� ����
    set<string> words;

    //���������� ���� �� �����
    string word;
    while (infile >> word) {
        //�������� ����� ���������� �� �����
        for (char c : word) {
            //����� � ����� �����������
            if (ispunct(c) && c != '-') {
                auto deletableChar = find(word.begin(), word.end(), c);
                word.erase(deletableChar);
            }
        }

        //�������������� ����� � ������� ��������
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        //���������� ����� � ���������
        words.insert(word);
    }

    // ����� ������ ���������� ����
    cout << "������ ���������� ����:" << endl;
    for (const string& word : words) {
        cout << word << endl;
    }

    return 0;
}