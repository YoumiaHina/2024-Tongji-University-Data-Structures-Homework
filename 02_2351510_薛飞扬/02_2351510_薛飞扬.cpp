#include<iostream>
using namespace std;

class LNode
{
	friend class LinkList;
public:
	int data;
	LNode *next;
	LNode()
	{
		data = 0;
		next = NULL;
	}
	~LNode() {} 
};

class LinkList
{
	LNode *head;
	
public:
	LinkList();
	~LinkList() {};
	void Input();								// 用于输入链表
	void Output();								// 用于输出链表
	void Intersect(LinkList L1, LinkList L2);	// 用于求交集，生成L1和L2的交集链表
};

LinkList::LinkList()
{
	head = new LNode;
}

void LinkList::Input()
{
	LNode *p = this->head;
	int num;
	while(cin >> num && num != -1)
	{
		p->next = new LNode;
		p->next->data = num;
		p = p->next;
	}
}

void LinkList::Output()
{
	LNode *p = this->head->next;
	if(p == NULL)
	{
		cout << "NULL" << endl;
		return;
	}
	while(p->next != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << p->data << endl;
}

void LinkList::Intersect(LinkList L1, LinkList L2)
{
	LNode *current = this->head;					//新链表的指针 
	LNode *p = L1.head->next, *q = L2.head->next;	//指针p扫描L1，指针q扫描L2 
	while(p != NULL && q != NULL)
	{
		if(p->data == q->data && p->data != current->data)
		{
			current->next = new LNode;
			current->next->data = p->data;
			current = current->next;
			p = p->next;
			q = q->next;
		}
		else if(p->data < q->data)
		{
			p = p->next;
		}
		else
		{
			q = q->next;
		}
	}
}

int main()
{
	LinkList L1, L2;
	L1.Input();
	L2.Input();
	LinkList L3;
	L3.Intersect(L1, L2);
	L3.Output();
	system("pause"); 
	return 0;
}
