#include<iostream>
#include<cstring>
#include<cstdlib>
#include<limits>
using namespace std;

// 用左孩子右兄弟方法存储树，定义二叉树节点类 
class TNode
{
    friend class Family;
private:
    char Name[50];
    TNode *firstChild, *nextSibling;
public:
    TNode() {
        strcpy(Name, "\0");
        firstChild = NULL;
        nextSibling = NULL;
    }
    ~TNode() {}
};

// 实现栈的功能 
class Stack
{
private:
    TNode * data[100];
    int top;
    
public:
	Stack() { top = -1; }
	~Stack() {};
	bool isEmpty() { return top == -1; }
	void push(TNode * value) { data[++top] = value; }
	TNode * pop() { return data[top--]; }
	TNode * peek() { return data[top]; };
};

class Family
{
    TNode* ancestor;
    TNode* InOrderTraverse(char* name); 
public:
    Family() { ancestor = new TNode; }
    ~Family() {	}
    void Generate();
    void Consummate();
    void Add();
    void Dissolve();
    void Modify();
    void SelectMode();
};

TNode* Family::InOrderTraverse(char* name)
{
	Stack S;
	TNode* p = ancestor;
	S.push(p);
	while(!S.isEmpty() || p != NULL)
	{
		while(p != NULL)
		{
			S.push(p);
			p = p->firstChild;
		}
		p = S.pop();
		if(p != NULL && strcmp(p->Name, name) == 0)
			return p;
		p = p->nextSibling;
	}
	return NULL;
}

void Family::Generate()
{
    char name[50];

    cout << "首先请建立一个家谱！" << endl;
    cout << "请输入祖先的姓名：";
    cin >> name;
    strcpy(ancestor->Name, name);
    cout << "此家谱的祖先是：" << name << endl;
    cout << endl;
}

void Family::Consummate()
{
	char parentName[50], childName[50];
	int childNum;
	TNode *p;
	
	cout << "请输入要建立家庭的人的姓名：";
	cin >> parentName;
	p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "不存在此人，请重新输入！" << endl;
		cout << "请输入要建立家庭的人的姓名：";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
	if(p->firstChild != NULL)
	{
		cout << "此人已有家庭，无法再建立家庭！" << endl << endl;
		return;
	}
	
	cout << "请输入" << parentName << "的儿女人数："; 
	cin >> childNum;
	
	cout << "请依次输入" << parentName << "的儿女的姓名：";
	cin >> childName;
	TNode *fc = new TNode;
	strcpy(fc->Name, childName);
	p->firstChild = fc;
	TNode *current = fc;
	for(int i = 1; i < childNum; i++)
	{
		cin >> childName;
		TNode *ns = new TNode;
		strcpy(ns->Name, childName);
		current->nextSibling = ns;
		current = current->nextSibling;
	}
	
	cout << parentName << "的第一代子孙是：";
	current = fc;
	while(current != NULL)
	{
		cout << current->Name << "\t";
		current = current->nextSibling;
	}
	cout << endl << endl;
}

void Family::Add()
{
	char parentName[50], childName[50];
	TNode *p, *current;
    cout << "请输入要添加儿子（或女儿）的人的姓名：";
    cin >> parentName;
    p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "不存在此人，请重新输入！" << endl;
		cout << "请输入要添加儿子（或女儿）的人的姓名：";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
	cout << "请输入" << parentName << "新添加的儿子（或女儿）的姓名：";
	cin >> childName;
	
	TNode *c = new TNode;
	strcpy(c->Name, childName);
	if(p->firstChild == NULL)
	{
		p->firstChild = c;
	}
	else
	{
		current = p->firstChild;
		while(current->nextSibling != NULL)
			current = current->nextSibling;
		current->nextSibling = c;
	}
	
	cout << parentName << "的第一代子孙是：";
	current = p->firstChild;
	while(current != NULL)
	{
		cout << current->Name << "\t";
		current = current->nextSibling;
	}
	cout << endl << endl;
}

void Family::Dissolve()
{
    char parentName[50];
    TNode *p; 
    cout << "请输入要解散家庭的人的姓名：";
    cin >> parentName;
    p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "不存在此人，请重新输入！" << endl;
		cout << "请输入要解散家庭的人的姓名：";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
    cout << "要解散家庭的人是：" << p->Name << endl;
    TNode *current = p->firstChild;
    // 若无子孙则返回 
    if(current == NULL)
    {
    	cout << p->Name << "没有子孙！" << endl << endl;
    	return;
	}
	// 输出第一代子孙 
	cout << p->Name << "的第一代子孙是：" ;
	while(current != NULL)
	{
		cout << current->Name << "\t";
		current = current -> nextSibling;
	}
	
	// 执行左子树删除操作 
	current = p->firstChild;
	Stack S;
	while(current != NULL)
	{
		if(current->firstChild != NULL)
		{
			S.push(current);
			current = current->firstChild;
		}
		else if(current->nextSibling != NULL)
		{
			TNode *temp = current;
			current = current->nextSibling;
			delete temp;
		}
		else
		{
			TNode *temp = current;
			if (!S.isEmpty())
				current = S.pop();
			else
				current = NULL;
			delete temp;
		}
	}
	p->firstChild = NULL;
	cout << endl << endl;
}

void Family::Modify()
{
    char oriName[50], newName[50];
    TNode *p; 
    cout << "请输入要更改姓名的人的目前姓名：";
    cin >> oriName;
    p = InOrderTraverse(oriName);
	while(p == NULL)
	{
		cout << "不存在此人，请重新输入！" << endl;
		cout << "请输入要更改姓名的人的目前姓名：";
		cin >> oriName;
		p = InOrderTraverse(oriName);
	}
	
	cout << "请输入更改后的姓名：";
	cin >> newName;
	strcpy(p->Name, newName);
	cout << oriName << "已更名为" << newName;
	cout << endl << endl;
}

void Family::SelectMode()
{
    char mode = '0';

    while (true)
	{
        cout << "请选择要执行的操作：" ;
        cin >> mode;
        if (cin.fail() || mode < 'A' || mode > 'E')
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入错误，请重新输入！" << endl;
        }
		else
		{
            break;
        }
    }

    while (mode != 'E')
	{
        switch (mode)
		{
            case 'A':
                Consummate();
                break;
            case 'B':
                Add();
                break;
            case 'C':
                Dissolve();
                break;
            case 'D':
                Modify();
                break;
            case 'E':
                break;
            default:
                break;
        }

        while (true)
		{
            cout << "请选择您要进行的操作：";
            cin >> mode;
            if (cin.fail() || mode < 'A' || mode > 'E')
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "输入错误，请重新输入！" << endl;
            }
			else
			{
                break;
            }
        }
    }
}

int main() {
    Family* T = new Family;
    cout << "**                    家谱管理系统                    **" << endl
    	 << "========================================================" << endl
    	 << "**                 请选择要执行的操作 ：              **" << endl
		 << "**                    A --- 完善家谱                  **" << endl
		 << "**                    B --- 添加家庭成员              **" << endl
		 << "**                    C --- 解散局部家庭              **" << endl
		 << "**                    D --- 更改家庭成员姓名          **" << endl
		 << "**                    E --- 退出程序                  **" << endl
		 << "========================================================" << endl; 
    T->Generate();
    T->SelectMode();
    cout << "操作结束！" << endl;
    delete T;
    system("pause"); 
    return 0;
}

