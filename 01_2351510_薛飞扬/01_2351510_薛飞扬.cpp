#include<iostream>
#include<cstring>
#include<cstdlib>
#include<limits>
#include<iomanip>
using namespace std;

class Student
{
private:
    int Id;             // ���ڴ洢ѧ��
    char Name[50];      // ���ڴ洢����
    char Gender[10];    // ���ڴ洢�Ա�
    int Age;            // ���ڴ洢����
    char Category[50];  // ���ڴ洢רҵ

public:
    Student() {
        Id = 0;
        strcpy(Name, "0");
        strcpy(Gender, "0");
        Age = 0;
        strcpy(Category, "0");
    }
    
    void SetStudent(int id, const char* name, const char* gender, int age, const char* category) {
        Id = id;
        strcpy(Name, name);
        strcpy(Gender, gender);
        Age = age;
        strcpy(Category, category);
    }
    void SetId(int id) { Id = id; }
    
    ~Student() {}
    
    int getId() { return Id; }
    const char* getName() { return Name; }
    const char* getGender() { return Gender; }
    int getAge() { return Age; }
    const char* getCategory() { return Category; }
};

class LNode
{
    friend class LinkList;
public:
    Student data;
    LNode* next;
    
    LNode() {
        data = Student();
        next = NULL;
    }
    
    ~LNode() {}
};

class LinkList
{
    LNode* head;
public:
    LinkList() { head = new LNode; }
    ~LinkList();
    bool find(int num); 
    void Generate();
    void Insert();
    void Delete();
    void Search();
    void Modify();
    void Output();
    void SelectMode();
};

LinkList::~LinkList()
{
    LNode* current = head;
    while (current) {
        LNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool LinkList::find(int num)
{
	LNode *p = head->next;
	while(p != NULL)
	{
		if (p->data.getId() == num)
			return true;
		p = p->next;
	}
	return false;
}

void LinkList::Generate()
{
    int snum;
    int Id, Age;
    char Name[50], Gender[10], Category[50];

    cout << "�����뽨��������Ϣϵͳ��" << endl;
    cout << "�����뿼��������";

    while (true)
	{
        cin >> snum;
        if (cin.fail() || snum <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч��������һ����������" << endl;
        }
		else
		{
            break;
        }
    }

    cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
    LNode* p = this->head;

    while (snum--)
	{
        p->next = new LNode;

        while (true)
		{
            cin >> Id >> Name >> Gender >> Age >> Category;
            if (cin.fail() || Age <= 0)
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������Ч�����������뿼�ţ��������Ա����估�������" << endl;
            }
			else if (find(Id))
			{
				cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�����Ѵ��ڣ����������뿼�ţ��������Ա����估�������" << endl;
			}
			else
			{
                break;
            }
        }
		p->next->data.SetStudent(Id, Name, Gender, Age, Category);
        p = p->next;
    }
    cout << endl;
}

void LinkList::Insert()
{
    int loc;
    cout << "��������Ҫ����Ŀ�����λ�ã�";

    while (true)
	{
        cin >> loc;
        if (cin.fail() || loc < 1)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч��������һ����������" << endl;
        }
		else
		{
            break;
        }
    }

    int Id, Age;
    char Name[50], Gender[10], Category[50];
    LNode* p = this->head;

    while (p != NULL && --loc) 
        p = p->next;  // �ҵ�Ҫ����Ľ���ǰ�� 

    if (p == NULL)
	{
        cout << "����λ������" << endl << endl;
        return;
    }
    
    cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
    while (true)
	{
        cin >> Id >> Name >> Gender >> Age >> Category;
        if (cin.fail() || Age <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч�����������뿼�ţ��������Ա����估�������" << endl;
        }
        else if (find(Id))
		{
			cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����Ѵ��ڣ����������뿼�ţ��������Ա����估�������" << endl;
		}
		else
		{
            break;
        }
    }

    LNode* q = new LNode;	// �洢Ҫ����Ľ�� 
    q->data.SetStudent(Id, Name, Gender, Age, Category);
    
    if (p->next == NULL)	// ����β���
	{
    	p->next = q;
    }
	else
	{
        q->next = p->next;
        p->next = q;
    }

    cout << "�����ɹ���" << endl;
    cout << endl;
}

void LinkList::Delete()
{
    int target;
    cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч�����������뿼���Ŀ��ţ�" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head;
    
    while (p->next != NULL && p->next->data.getId() != target)  // �ҵ�Ŀ�����ǰ�� 
        p = p->next;
	
	LNode *q = p->next;
    if (q == NULL)
	{
        cout << "�ÿ��������ڣ�" << endl << endl;
        return;
    }
	else
	{
        p->next = q->next;
    }

    delete q;
    cout << "�����ɹ���" << endl;
    cout << endl;
}

void LinkList::Search()
{
    int target;
    cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч�����������뿼���Ŀ��ţ�" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head->next;
    
    while (p != NULL && p->data.getId() != target)  // �ҵ�Ŀ���� 
        p = p->next;

    if (p == NULL)
	{
        cout << "�ÿ��������ڣ�" << endl << endl;
        return;
    }

    cout << left << setw(10) << "����"
         << setw(10) << "����" 
    	 << setw(10) << "�Ա�"
         << setw(10) << "����" 
         << setw(20) << "�������" << endl;
    cout << left << setw(10) << p->data.getId() 
         << setw(10) << p->data.getName() 
         << setw(10) << p->data.getGender() 
         << setw(10) << p->data.getAge() 
         << setw(20) << p->data.getCategory() << endl;
    cout << "�����ɹ���" << endl;
    cout << endl;
}

void LinkList::Modify()
{
    int target;
    cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч�����������뿼���Ŀ��ţ�" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head->next;
    
    while (p != NULL && p->data.getId() != target)  // �ҵ�Ŀ���� 
        p = p->next;

    if (p == NULL)
	{
        cout << "�ÿ��������ڣ�" << endl << endl;
        return;
    }
    p->data.SetId(-1);      // Id��-1�������������

    int Id, Age;
    char Name[50], Gender[10], Category[50];
    cout << "�����������޸ĺ�Ŀ����Ŀ��ţ��������Ա����估�������" << endl;

    while (true) {
        cin >> Id >> Name >> Gender >> Age >> Category;
        if (cin.fail() || Age <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч�����������뿼�ţ��������Ա����估�������" << endl;
        }
        else if (find(Id))
		{
			cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����Ѵ��ڣ����������뿼�ţ��������Ա����估�������" << endl;
		}
		else
		{
            break;
        }
    }

    p->data.SetStudent(Id, Name, Gender, Age, Category);
    cout << "�����ɹ���" << endl;
    cout << endl;
}

void LinkList::Output()
{
    LNode* p = this->head->next;
    int totalNum = 0, maleNum = 0, femaleNum = 0;

    cout << left << setw(10) << "����"
         << setw(10) << "����" 
    	 << setw(10) << "�Ա�"
         << setw(10) << "����" 
         << setw(20) << "�������" << endl;

    while (p != NULL)
	{
	    cout << left << setw(10) << p->data.getId() 
	         << setw(10) << p->data.getName() 
	         << setw(10) << p->data.getGender() 
	         << setw(10) << p->data.getAge() 
	         << setw(20) << p->data.getCategory() << endl;

        if (strcmp(p->data.getGender(), "��") == 0)
            maleNum++;
        else if (strcmp(p->data.getGender(), "Ů") == 0)
            femaleNum++;

        p = p->next;
        totalNum++;
    }

    cout << "��������" << totalNum << endl;
    cout << "����������" << maleNum << endl;
    cout << "Ů��������" << femaleNum << endl;
    cout << endl;
}

void LinkList::SelectMode() {
    int mode = 0;
    cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;

    while (true)
	{
        cout << "��ѡ����Ҫ���еĲ�����";
        cin >> mode;
        if (cin.fail() || mode < 0 || mode > 5)
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

    while (mode != 0)
	{
        switch (mode)
		{
            case 1:
                Insert();
                break;
            case 2:
                Delete();
                break;
            case 3:
                Search();
                break;
            case 4:
                Modify();
                break;
            case 5:
                Output();
                break;
            default:
                break;
        }

        while (true)
		{
            cout << "��ѡ����Ҫ���еĲ�����";
            cin >> mode;
            if (cin.fail() || mode < 0 || mode > 5)
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
    LinkList* L = new LinkList;
    L->Generate();
    L->SelectMode();
    cout << "����������" << endl;
    delete L;
    system("pause"); 
    return 0;
}

