#include<iostream>
using namespace std;

// 实现队列功能
class Queue
{
private:
	int* data;		// 队列数组
    int front;		// 队头
    int rear;		// 队尾
    int capacity;	// 队列容量
    
public:
	Queue(); 		// 构造函数 
    ~Queue() { };	// 析构函数
    bool isEmpty();	// 判空 
    bool EnQueue(int x);	// 入队 
    int DeQueue();			// 出队 
    int peek();				//读队首元素 
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
	if((rear + 1) % capacity == front)	// 队满报错 
		return false;
	data[rear] = x;
	rear = (rear + 1) % capacity;
	return true;
}

int Queue::DeQueue()
{
	if(isEmpty())						// 队空报错 
		return -1;
	int val = data[front];
	front = (front + 1) % capacity;
	return val; 
}

int Queue::peek()
{
	if(isEmpty())						// 队空报错 
		return -1;
	return data[front];
}

void Solution(int n, int *cus)
{
	Queue A, B;
	// 先进行AB窗口人员分拣
	for(int i = 0; i < n; i++)
	{
		if (cus[i] % 2 == 1)
			A.EnQueue(cus[i]);
		else 
			B.EnQueue(cus[i]);
	}
	// 生成业务完成顺序序列
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
	// 输出
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
