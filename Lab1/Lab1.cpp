#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

//функция сортировки вставками (1-ое задание)
void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j;
        float key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

//вспомогательная функция для обмена элементов местами
void swap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}

//вспомогательная функция для разделения массива на две части относительно выбранного опорного элемента
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; //за опорный элемент берется последний элемент массива
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

//функция быстрой сортировки Хоара (2-ое задание)
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//функция бинарного поиска (3-е задание)
int binarySearch(float arr[], int low, int high, float searchable) {
    while (low <= high) {
        int mid = low + (high - low) / 2; //смотрим относительно середины массива

        if (arr[mid] == searchable)
            return mid;  //элемент найден, возвращаем его индекс
        else if (arr[mid] < searchable)
            low = mid + 1;  //искомый элемент находится в правой половине
        else
            high = mid - 1;  //искомый элемент находится в левой половине
    }

    return -1;  //элемент не найден
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int size = 5;

    //1-ое задание
    float array1[] = { 12.5f, 11.0f, 13.2f, 5.8f, 6.4f };
    std::cout << "Задание 1:" << std::endl << "Изначальный массив: ";
    for (int i = 0; i < size; i++)
        std::cout << array1[i] << " ";
    std::cout << std::endl;

    insertionSort(array1, size);

    std::cout << "Отсортированный массив после сортировки вставками: ";
    for (int i = 0; i < size; i++)
        std::cout << array1[i] << " ";
    std::cout << std::endl << std::endl;

    //2-ое задание
    float array2[] = { -5.4f, 6.2f, 122.0f, 0.1f, -10.5f };
    std::cout << "Задание 2:" << std::endl << "Изначальный массив: ";
    for (int i = 0; i < size; i++)
        std::cout << array2[i] << " ";
    std::cout << std::endl;

    quickSort(array2, 0, size - 1);

    std::cout << "Отсортированный массив после быстрой сортировки: ";
    for (int i = 0; i < size; i++)
        std::cout << array2[i] << " ";
    std::cout << std::endl << std::endl;

    //3-е задание
    float array3[] = { -4.8f, -1.5f, 0.4f, 4.5f, 5.4f };
    float searchable = 4.5f;
    std::cout << "Задание 3:" << std::endl << "Изначальный массив: ";
    for (int i = 0; i < size; i++)
        std::cout << array3[i] << " ";
    std::cout << std::endl;

    int indexOfSearchable = binarySearch(array3, 0, size - 1, searchable);

    if (indexOfSearchable != -1)
        std::cout << "Элемент " << searchable << " находится по индексу " << indexOfSearchable << std::endl << std::endl;
    else
        std::cout << "Элемента " << searchable << " нет в массиве!" << std::endl << std::endl;

    //4-ое задание
    std::vector<float> array4 = { 10.2f, -5.9f, 0.3f, -2.2f, -11.0f };
    std::cout << "Задание 4:" << std::endl << "Изначальный массив: ";
    for (float num : array4)
        std::cout << num << " ";
    std::cout << std::endl;

    //сортировка вектора с помощью алгоритма std::sort
    std::sort(array4.begin(), array4.end());

    std::cout << "Отсортированный массив после сортировки std::sort: ";
    for (float num : array4)
        std::cout << num << " ";
    std::cout << std::endl;

    searchable = 0.3f;
    bool found = std::binary_search(array4.begin(), array4.end(), searchable);
    if (found)
        std::cout << "Элемент " << searchable << " найден в векторе" << std::endl;
    else
        std::cout << "Элемента " << searchable << " нет в векторе!" << std::endl;

    return 0;
}