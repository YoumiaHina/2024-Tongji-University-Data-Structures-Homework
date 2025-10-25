#include<iostream>
using namespace std;

// ʵ�ֶ��й���
class Queue
{
private:
	int* data;		// ��������
    int front;		// ��ͷ
    int rear;		// ��β
    int capacity;	// ��������
    
public:
	Queue(); 		// ���캯�� 
    ~Queue() { };	// ��������
    bool isEmpty();	// �п� 
    bool EnQueue(int x);	// ��� 
    int DeQueue();			// ���� 
    int peek();				//������Ԫ�� 
};

Queue::Queue()
{
	capacity = 1005;
    data = new int[capacity];
    front = 0;
    rear = 0;
}

bool Queue::isEmpty()
{
	if(rear == front)
		return true;
	else
		return false;
}

bool Queue::EnQueue(int x)
{
	if((rear + 1) % capacity == front)	// �������� 
		return false;
	data[rear] = x;
	rear = (rear + 1) % capacity;
	return true;
}

int Queue::DeQueue()
{
	if(isEmpty())						// �ӿձ��� 
		return -1;
	int val = data[front];
	front = (front + 1) % capacity;
	return val; 
}

int Queue::peek()
{
	if(isEmpty())						// �ӿձ��� 
		return -1;
	return data[front];
}

void Solution(int n, int *cus)
{
	Queue A, B;
	// �Ƚ���AB������Ա�ּ�
	for(int i = 0; i < n; i++)
	{
		if (cus[i] % 2 == 1)
			A.EnQueue(cus[i]);
		else 
			B.EnQueue(cus[i]);
	}
	// ����ҵ�����˳������
	int i = 0;
	int *ans = new int[n];
	while (!A.isEmpty() && !B.isEmpty())
	{
		ans[i++] = A.DeQueue();
		if(!A.isEmpty())
			ans[i++] = A.DeQueue();
		ans[i++] = B.DeQueue();
	}
	while(!A.isEmpty())
	{
		ans[i++] = A.DeQueue();
	}
	while(!B.isEmpty())
	{
		ans[i++] = B.DeQueue();
	}
	// ���
	for(int i = 0; i < n-1; i++)
		cout << ans[i] << " ";
	cout << ans[n-1] << endl;
}

int main()
{
	int n;
	int *cus;
	cin >> n;
	cus = new int[n]; 
	for(int i = 0; i < n; i++)
		cin >> cus[i];
	Solution(n, cus);
	system("pause"); 
	return 0;
}
