#include<iostream>
using namespace std;

class PriorityQueue
{
private:
	int* data;				// �洢ľͷ���ȵ�����
	int size;				// ������Ԫ�صĸ���
	int capacity;			// ���е�����
public:
	PriorityQueue();		// ���캯��
	~PriorityQueue() {};	// ��������
	int pop();
	bool push(int x);
	int getSize();
};

PriorityQueue::PriorityQueue()
{
	capacity = 10005;
	data = new int[capacity];
	size = 0;
}

int PriorityQueue::pop()
{
	if (size == 0)
		return -1;
	int min = data[0], minindex = 0;
	for (int i = 0; i < size; i++)
	{
		if (data[i] < min)
		{
			minindex = i;
			min = data[i];
		}
	}
	data[minindex] = data[size-1];
	size -= 1;
	return min;
}

bool PriorityQueue::push(int x)
{
	if (size >= capacity)
		return false;
	data[size++] = x;
	return true;
}

int PriorityQueue::getSize()
{
	return size;
}

int Solution(int n, int *wlength)
{
	PriorityQueue Q;
	for(int i = 0; i < n; i++)
		Q.push(wlength[i]);
	int ans = 0, tem = 0;
	while(Q.getSize() > 1)
	{
		tem = Q.pop();
		tem += Q.pop();
		Q.push(tem);
		ans += tem;
	}
	return ans;
}

int main()
{
	int n;
	int wlength[10005];
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> wlength[i];
	cout << Solution(n, wlength) << endl;
	system("pause");
	return 0;
}
