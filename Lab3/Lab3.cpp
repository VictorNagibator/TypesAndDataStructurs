#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //Ввод имени файла
    string filename;
    cout << "Введите имя текстового файла: ";
    cin >> filename;

    //Открытие файла
    ifstream infile(filename);
    if (!infile) {
        cerr << "Ошибка открытия файла!" << endl;
        return -1;
    }

    //Множество для хранения уникальных слов
    set<string> words;

    //Считывание слов из файла
    string word;
    while (infile >> word) {
        //Удаление знака пунктуации из слова
        for (char c : word) {
            //Дефис в слове допускается
            if (ispunct(c) && c != '-') {
                auto deletableChar = find(word.begin(), word.end(), c);
                word.erase(deletableChar);
            }
        }

        //Преобразование слова к нижнему регистру
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        //Добавление слова в множество
        words.insert(word);
    }

    // Вывод списка уникальных слов
    cout << "Список уникальных слов:" << endl;
    for (const string& word : words) {
        cout << word << endl;
    }

    return 0;
}