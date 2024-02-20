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

	int front() const; //возвращает первый элемент очереди, не извлекая его
	bool isEmpty() const; //проверка на пустоту очереди
private:
	int *queue; //динамический массив, отведенный под очередь
	int rpos = 0, spos = 0; //rpos - голова очереди, spos - хвост очереди

	int maxNum; //максимальное количество элементов в очереди
};

MyQueue::MyQueue(int n)
{
	queue = new int[n]; //выделяем динамически память под очередь
	maxNum = n; //и запоминаем максимальное количество элементов
}

MyQueue::~MyQueue()
{
	delete[] queue; 
}

void MyQueue::store(int element) //помещаем элемент в очередь
{
	if (spos == maxNum)
	{
		std::cout << "Очередь заполнена!" << std::endl;
		return;
	}

	queue[spos] = element;
	spos++;
}

bool MyQueue::isEmpty() const
{
	return rpos == spos;
}

int MyQueue::retrieve() //извлекаем элемент из очереди
{
	if (isEmpty())
	{
		std::cout << "Очередь пуста!" << std::endl;
		return -1;
	}

	rpos++;
	return queue[rpos - 1];
}

int MyQueue::front() const //возвращает первый элемент очереди, не извлекая его
{
	if (isEmpty())
	{
		std::cout << "Очередь пуста!" << std::endl;
		return -1;
	}

	return queue[rpos];
}

static void printUntilEven(MyQueue& queue) //выводит элементы очереди до первого четного (но этот четный элемент не извлекаем)
{
	bool isNoEven = true;
	std::cout << "Вывод элементов очереди до первого четного:" << std::endl;
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
		std::cout << "Элементы в очереди закончились, в ней нет четных элементов!" << std::endl;
}

static void printUntilEven(std::queue<int>& queue) //аналогичная функция, но для std::queue
{
	bool isNoEven = true;
	std::cout << "Вывод элементов очереди до первого четного:" << std::endl;
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
		std::cout << std::endl << "Элементы в очереди закончились, в ней нет четных элементов!" << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	int arr1[] = { 5, 1, 3, 5, 5, 5 }, arr2[] = { 5, 3, 2, 1, 4 };

	//1-ое задание
	std::cout << "1-ое задание:" << std::endl;
	
	MyQueue myqueue(100);
    for (int i = 0; i < 6; i++)
        myqueue.store(arr1[i]);
    printUntilEven(myqueue);
	
	//очистка очереди
	while (!myqueue.isEmpty())
		myqueue.retrieve();

	for (int i = 0; i < 5; i++)
		myqueue.store(arr2[i]);
	printUntilEven(myqueue);

	//2-ое задание
	std::cout << std::endl << "2-ое задание:" << std::endl;
	std::queue<int> queue;
	for (int i = 0; i < 6; i++)
		queue.push(arr1[i]);
	printUntilEven(queue);

	//очистка очереди
	while (!queue.empty())
		queue.pop();

	int arr3[] = { 5, 3, 1, 1, 4 };
	for (int i = 0; i < 5; i++)
		queue.push(arr3[i]);
	printUntilEven(queue);
}