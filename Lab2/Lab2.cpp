#include <iostream>
#include <queue>
#include <windows.h>

class MyQueue
{
public:
	MyQueue(int n);
	~MyQueue();

	void store(int element);
	int retrieve();

	int front() const; //���������� ������ ������� �������, �� �������� ���
	bool isEmpty() const; //�������� �� ������� �������
private:
	int *queue; //������������ ������, ���������� ��� �������
	int rpos = 0, spos = 0; //rpos - ������ �������, spos - ����� �������

	int maxNum; //������������ ���������� ��������� � �������
};

MyQueue::MyQueue(int n)
{
	queue = new int[n]; //�������� ����������� ������ ��� �������
	maxNum = n; //� ���������� ������������ ���������� ���������
}

MyQueue::~MyQueue()
{
	delete[] queue; 
}

void MyQueue::store(int element) //�������� ������� � �������
{
	if (spos == maxNum)
	{
		std::cout << "������� ���������!" << std::endl;
		return;
	}

	queue[spos] = element;
	spos++;
}

bool MyQueue::isEmpty() const
{
	return rpos == spos;
}

int MyQueue::retrieve() //��������� ������� �� �������
{
	if (isEmpty())
	{
		std::cout << "������� �����!" << std::endl;
		return -1;
	}

	rpos++;
	return queue[rpos - 1];
}

int MyQueue::front() const //���������� ������ ������� �������, �� �������� ���
{
	if (isEmpty())
	{
		std::cout << "������� �����!" << std::endl;
		return -1;
	}

	return queue[rpos];
}

static void printUntilEven(MyQueue& queue) //������� �������� ������� �� ������� ������� (�� ���� ������ ������� �� ���������)
{
	bool isNoEven = true;
	std::cout << "����� ��������� ������� �� ������� �������:" << std::endl;
	while (queue.front() != -1)
	{
		int temp = queue.front();
		std::cout << temp << " ";
		if (temp % 2 == 0)
		{
			isNoEven = false;
			std::cout << std::endl;
			break;
		}

		queue.retrieve();
	}

	if (isNoEven)
		std::cout << "�������� � ������� �����������, � ��� ��� ������ ���������!" << std::endl;
}

static void printUntilEven(std::queue<int>& queue) //����������� �������, �� ��� std::queue
{
	bool isNoEven = true;
	std::cout << "����� ��������� ������� �� ������� �������:" << std::endl;
	while (!queue.empty())
	{
		int temp = queue.front();
		std::cout << temp << " ";
		if (temp % 2 == 0)
		{
			isNoEven = false;
			std::cout << std::endl;
			break;
		}

		queue.pop();
	}

	if (isNoEven)
		std::cout << std::endl << "�������� � ������� �����������, � ��� ��� ������ ���������!" << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	int arr1[] = { 5, 1, 3, 5, 5, 5 }, arr2[] = { 5, 3, 2, 1, 4 };

	//1-�� �������
	std::cout << "1-�� �������:" << std::endl;
	
	MyQueue myqueue(100);
    for (int i = 0; i < 6; i++)
        myqueue.store(arr1[i]);
    printUntilEven(myqueue);
	
	//������� �������
	while (!myqueue.isEmpty())
		myqueue.retrieve();

	for (int i = 0; i < 5; i++)
		myqueue.store(arr2[i]);
	printUntilEven(myqueue);

	//2-�� �������
	std::cout << std::endl << "2-�� �������:" << std::endl;
	std::queue<int> queue;
	for (int i = 0; i < 6; i++)
		queue.push(arr1[i]);
	printUntilEven(queue);

	//������� �������
	while (!queue.empty())
		queue.pop();

	int arr3[] = { 5, 3, 1, 1, 4 };
	for (int i = 0; i < 5; i++)
		queue.push(arr3[i]);
	printUntilEven(queue);
}