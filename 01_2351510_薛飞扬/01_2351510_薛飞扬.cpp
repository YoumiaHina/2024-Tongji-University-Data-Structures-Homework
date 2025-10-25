#include<iostream>
#include<cstring>
#include<cstdlib>
#include<limits>
#include<iomanip>
using namespace std;

class Student
{
private:
    int Id;             // 用于存储学号
    char Name[50];      // 用于存储姓名
    char Gender[10];    // 用于存储性别
    int Age;            // 用于存储年龄
    char Category[50];  // 用于存储专业

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

    cout << "首先请建立考生信息系统！" << endl;
    cout << "请输入考生人数：";

    while (true)
	{
        cin >> snum;
        if (cin.fail() || snum <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请输入一个正整数！" << endl;
        }
		else
		{
            break;
        }
    }

    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
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
                cout << "输入无效，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
            }
			else if (find(Id))
			{
				cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "考号已存在，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
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
    cout << "请输入你要插入的考生的位置：";

    while (true)
	{
        cin >> loc;
        if (cin.fail() || loc < 1)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请输入一个正整数！" << endl;
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
        p = p->next;  // 找到要插入的结点的前驱 

    if (p == NULL)
	{
        cout << "插入位置有误！" << endl << endl;
        return;
    }
    
    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
    while (true)
	{
        cin >> Id >> Name >> Gender >> Age >> Category;
        if (cin.fail() || Age <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
        }
        else if (find(Id))
		{
			cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "考号已存在，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
		}
		else
		{
            break;
        }
    }

    LNode* q = new LNode;	// 存储要插入的结点 
    q->data.SetStudent(Id, Name, Gender, Age, Category);
    
    if (p->next == NULL)	// 若是尾结点
	{
    	p->next = q;
    }
	else
	{
        q->next = p->next;
        p->next = q;
    }

    cout << "操作成功！" << endl;
    cout << endl;
}

void LinkList::Delete()
{
    int target;
    cout << "请输入要删除的考生的考号：";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入考生的考号！" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head;
    
    while (p->next != NULL && p->next->data.getId() != target)  // 找到目标结点的前驱 
        p = p->next;
	
	LNode *q = p->next;
    if (q == NULL)
	{
        cout << "该考生不存在！" << endl << endl;
        return;
    }
	else
	{
        p->next = q->next;
    }

    delete q;
    cout << "操作成功！" << endl;
    cout << endl;
}

void LinkList::Search()
{
    int target;
    cout << "请输入要查找的考生的考号：";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入考生的考号！" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head->next;
    
    while (p != NULL && p->data.getId() != target)  // 找到目标结点 
        p = p->next;

    if (p == NULL)
	{
        cout << "该考生不存在！" << endl << endl;
        return;
    }

    cout << left << setw(10) << "考号"
         << setw(10) << "姓名" 
    	 << setw(10) << "性别"
         << setw(10) << "年龄" 
         << setw(20) << "报考类别" << endl;
    cout << left << setw(10) << p->data.getId() 
         << setw(10) << p->data.getName() 
         << setw(10) << p->data.getGender() 
         << setw(10) << p->data.getAge() 
         << setw(20) << p->data.getCategory() << endl;
    cout << "操作成功！" << endl;
    cout << endl;
}

void LinkList::Modify()
{
    int target;
    cout << "请输入要修改的考生的考号：";
    
    while (true)
	{
        cin >> target;
        if (cin.fail())
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入考生的考号！" << endl;
        }
		else
		{
            break;
        }
    }

    LNode* p = this->head->next;
    
    while (p != NULL && p->data.getId() != target)  // 找到目标结点 
        p = p->next;

    if (p == NULL)
	{
        cout << "该考生不存在！" << endl << endl;
        return;
    }
    p->data.SetId(-1);      // Id置-1便于输入错误处理

    int Id, Age;
    char Name[50], Gender[10], Category[50];
    cout << "请依次输入修改后的考生的考号，姓名，性别，年龄及报考类别！" << endl;

    while (true) {
        cin >> Id >> Name >> Gender >> Age >> Category;
        if (cin.fail() || Age <= 0)
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
        }
        else if (find(Id))
		{
			cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "考号已存在，请重新输入考号，姓名，性别，年龄及报考类别！" << endl;
		}
		else
		{
            break;
        }
    }

    p->data.SetStudent(Id, Name, Gender, Age, Category);
    cout << "操作成功！" << endl;
    cout << endl;
}

void LinkList::Output()
{
    LNode* p = this->head->next;
    int totalNum = 0, maleNum = 0, femaleNum = 0;

    cout << left << setw(10) << "考号"
         << setw(10) << "姓名" 
    	 << setw(10) << "性别"
         << setw(10) << "年龄" 
         << setw(20) << "报考类别" << endl;

    while (p != NULL)
	{
	    cout << left << setw(10) << p->data.getId() 
	         << setw(10) << p->data.getName() 
	         << setw(10) << p->data.getGender() 
	         << setw(10) << p->data.getAge() 
	         << setw(20) << p->data.getCategory() << endl;

        if (strcmp(p->data.getGender(), "男") == 0)
            maleNum++;
        else if (strcmp(p->data.getGender(), "女") == 0)
            femaleNum++;

        p = p->next;
        totalNum++;
    }

    cout << "总人数：" << totalNum << endl;
    cout << "男性人数：" << maleNum << endl;
    cout << "女性人数：" << femaleNum << endl;
    cout << endl;
}

void LinkList::SelectMode() {
    int mode = 0;
    cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;

    while (true)
	{
        cout << "请选择您要进行的操作：";
        cin >> mode;
        if (cin.fail() || mode < 0 || mode > 5)
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
            cout << "请选择您要进行的操作：";
            cin >> mode;
            if (cin.fail() || mode < 0 || mode > 5)
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
    LinkList* L = new LinkList;
    L->Generate();
    L->SelectMode();
    cout << "操作结束！" << endl;
    delete L;
    system("pause"); 
    return 0;
}

