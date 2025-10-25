#include<iostream>
#include<cstring>
#include<cstdlib>
#include<limits>
using namespace std;

// ���������ֵܷ����洢��������������ڵ��� 
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

// ʵ��ջ�Ĺ��� 
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

    cout << "�����뽨��һ�����ף�" << endl;
    cout << "���������ȵ�������";
    cin >> name;
    strcpy(ancestor->Name, name);
    cout << "�˼��׵������ǣ�" << name << endl;
    cout << endl;
}

void Family::Consummate()
{
	char parentName[50], childName[50];
	int childNum;
	TNode *p;
	
	cout << "������Ҫ������ͥ���˵�������";
	cin >> parentName;
	p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "�����ڴ��ˣ����������룡" << endl;
		cout << "������Ҫ������ͥ���˵�������";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
	if(p->firstChild != NULL)
	{
		cout << "�������м�ͥ���޷��ٽ�����ͥ��" << endl << endl;
		return;
	}
	
	cout << "������" << parentName << "�Ķ�Ů������"; 
	cin >> childNum;
	
	cout << "����������" << parentName << "�Ķ�Ů��������";
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
	
	cout << parentName << "�ĵ�һ�������ǣ�";
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
    cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
    cin >> parentName;
    p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "�����ڴ��ˣ����������룡" << endl;
		cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
	cout << "������" << parentName << "����ӵĶ��ӣ���Ů������������";
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
	
	cout << parentName << "�ĵ�һ�������ǣ�";
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
    cout << "������Ҫ��ɢ��ͥ���˵�������";
    cin >> parentName;
    p = InOrderTraverse(parentName);
	while(p == NULL)
	{
		cout << "�����ڴ��ˣ����������룡" << endl;
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> parentName;
		p = InOrderTraverse(parentName);
	}
	
    cout << "Ҫ��ɢ��ͥ�����ǣ�" << p->Name << endl;
    TNode *current = p->firstChild;
    // ���������򷵻� 
    if(current == NULL)
    {
    	cout << p->Name << "û�����" << endl << endl;
    	return;
	}
	// �����һ������ 
	cout << p->Name << "�ĵ�һ�������ǣ�" ;
	while(current != NULL)
	{
		cout << current->Name << "\t";
		current = current -> nextSibling;
	}
	
	// ִ��������ɾ������ 
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
    cout << "������Ҫ�����������˵�Ŀǰ������";
    cin >> oriName;
    p = InOrderTraverse(oriName);
	while(p == NULL)
	{
		cout << "�����ڴ��ˣ����������룡" << endl;
		cout << "������Ҫ�����������˵�Ŀǰ������";
		cin >> oriName;
		p = InOrderTraverse(oriName);
	}
	
	cout << "��������ĺ��������";
	cin >> newName;
	strcpy(p->Name, newName);
	cout << oriName << "�Ѹ���Ϊ" << newName;
	cout << endl << endl;
}

void Family::SelectMode()
{
    char mode = '0';

    while (true)
	{
        cout << "��ѡ��Ҫִ�еĲ�����" ;
        cin >> mode;
        if (cin.fail() || mode < 'A' || mode > 'E')
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "����������������룡" << endl;
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
            cout << "��ѡ����Ҫ���еĲ�����";
            cin >> mode;
            if (cin.fail() || mode < 'A' || mode > 'E')
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "����������������룡" << endl;
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
    cout << "**                    ���׹���ϵͳ                    **" << endl
    	 << "========================================================" << endl
    	 << "**                 ��ѡ��Ҫִ�еĲ��� ��              **" << endl
		 << "**                    A --- ���Ƽ���                  **" << endl
		 << "**                    B --- ��Ӽ�ͥ��Ա              **" << endl
		 << "**                    C --- ��ɢ�ֲ���ͥ              **" << endl
		 << "**                    D --- ���ļ�ͥ��Ա����          **" << endl
		 << "**                    E --- �˳�����                  **" << endl
		 << "========================================================" << endl; 
    T->Generate();
    T->SelectMode();
    cout << "����������" << endl;
    delete T;
    system("pause"); 
    return 0;
}

