#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

//������� ���������� ��������� (1-�� �������)
void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j;
        float key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

//��������������� ������� ��� ������ ��������� �������
void swap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}

//��������������� ������� ��� ���������� ������� �� ��� ����� ������������ ���������� �������� ��������
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; //�� ������� ������� ������� ��������� ������� �������
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

//������� ������� ���������� ����� (2-�� �������)
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//������� ��������� ������ (3-� �������)
int binarySearch(float arr[], int low, int high, float searchable) {
    while (low <= high) {
        int mid = low + (high - low) / 2; //������� ������������ �������� �������

        if (arr[mid] == searchable)
            return mid;  //������� ������, ���������� ��� ������
        else if (arr[mid] < searchable)
            low = mid + 1;  //������� ������� ��������� � ������ ��������
        else
            high = mid - 1;  //������� ������� ��������� � ����� ��������
    }

    return -1;  //������� �� ������
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int size = 5;

    //1-�� �������
    float array1[] = { 12.5f, 11.0f, 13.2f, 5.8f, 6.4f };
    std::cout << "������� 1:" << std::endl << "����������� ������: ";
    for (int i = 0; i < size; i++)
        std::cout << array1[i] << " ";
    std::cout << std::endl;

    insertionSort(array1, size);

    std::cout << "��������������� ������ ����� ���������� ���������: ";
    for (int i = 0; i < size; i++)
        std::cout << array1[i] << " ";
    std::cout << std::endl << std::endl;

    //2-�� �������
    float array2[] = { -5.4f, 6.2f, 122.0f, 0.1f, -10.5f };
    std::cout << "������� 2:" << std::endl << "����������� ������: ";
    for (int i = 0; i < size; i++)
        std::cout << array2[i] << " ";
    std::cout << std::endl;

    quickSort(array2, 0, size - 1);

    std::cout << "��������������� ������ ����� ������� ����������: ";
    for (int i = 0; i < size; i++)
        std::cout << array2[i] << " ";
    std::cout << std::endl << std::endl;

    //3-� �������
    float array3[] = { -4.8f, -1.5f, 0.4f, 4.5f, 5.4f };
    float searchable = 4.5f;
    std::cout << "������� 3:" << std::endl << "����������� ������: ";
    for (int i = 0; i < size; i++)
        std::cout << array3[i] << " ";
    std::cout << std::endl;

    int indexOfSearchable = binarySearch(array3, 0, size - 1, searchable);

    if (indexOfSearchable != -1)
        std::cout << "������� " << searchable << " ��������� �� ������� " << indexOfSearchable << std::endl << std::endl;
    else
        std::cout << "�������� " << searchable << " ��� � �������!" << std::endl << std::endl;

    //4-�� �������
    std::vector<float> array4 = { 10.2f, -5.9f, 0.3f, -2.2f, -11.0f };
    std::cout << "������� 4:" << std::endl << "����������� ������: ";
    for (float num : array4)
        std::cout << num << " ";
    std::cout << std::endl;

    //���������� ������� � ������� ��������� std::sort
    std::sort(array4.begin(), array4.end());

    std::cout << "��������������� ������ ����� ���������� std::sort: ";
    for (float num : array4)
        std::cout << num << " ";
    std::cout << std::endl;

    searchable = 0.3f;
    bool found = std::binary_search(array4.begin(), array4.end(), searchable);
    if (found)
        std::cout << "������� " << searchable << " ������ � �������" << std::endl;
    else
        std::cout << "�������� " << searchable << " ��� � �������!" << std::endl;

    return 0;
}