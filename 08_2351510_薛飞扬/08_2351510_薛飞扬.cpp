#include<iostream>
#include<limits>

using namespace std;

const int MAXINT = 100000000;

class EdgeNode
{
	friend class Power_grid;
private:
	int tail, head;
	float cost;
public:
	EdgeNode()
	{
		tail = 0;
		head = 0;
		cost = 0;
	}
	~EdgeNode() { }
};

class Power_grid
{
private:
	int n;
	float *lowcost;
	int *nearvex;
	float **edge;
	char *vertexName;
	EdgeNode *T;			// �߽���������ڴ����С������ 
	
public:
	Power_grid();
	~Power_grid() { }
	void CreateVertex();
	void setGraph();
	void AddEdge();
	int FindIndex(char v);
	void Prim();
	void Print_Tree();
	void ModeSelect();
	
};

Power_grid::Power_grid()
{
	n = 0;
	lowcost = NULL;
	nearvex = NULL;
	edge = NULL;
	vertexName = NULL;
	T = NULL;
}

void Power_grid::CreateVertex()
{
	cout << "�����붥��ĸ�����";
	cin >> n;
	vertexName = new char[n];
	cout << "�������������������ƣ�" << endl ;
	for(int i = 0; i < n; i++)
		cin >> vertexName[i];
	setGraph();
	cout << endl;
}

void Power_grid::setGraph()
{
	lowcost = new float[n];
	nearvex = new int[n];
	edge = new float*[n];
	for(int i = 0; i < n; i++)
	{
		edge[i] = new float[n];
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			edge[i][j] = MAXINT;
		}
	}
	for(int i = 0; i < n; i++)
		edge[i][i] = 0;
}

void Power_grid::AddEdge()
{
	char headname, tailname;
	int headindex, tailindex;
	float cost;
	do
	{
		while (true)
		{
	        cout << "�������������㼰�ߣ�";
	        cin >> headname >> tailname >> cost;
	        headindex = FindIndex(headname);
	        tailindex = FindIndex(tailname);
	        if (headname == '?' && tailname == '?' && cost == 0)
	        {
	        	break;
			}
	        else if (cin.fail() || headindex == -1 || tailindex == -1 || headindex == tailindex || cost <= 0)
			{
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	            cout << "����������������룡" << endl;
	        }
	        else if (edge[headindex][tailindex] != MAXINT)
	        {
	        	cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        	cout << "�Ѵ��ڱߣ����������룡" << endl;
			}
			else
			{
	            break;
	        }
	    }
	    if(headindex != -1 && tailindex != -1)
	    {
			edge[headindex][tailindex] = cost;
	    	edge[tailindex][headindex] = cost;
		}
	    
	}while(headname != '?' || tailname != '?' || cost != 0);
	cout << endl;
}

int Power_grid::FindIndex(char v)
{
	for(int i = 0 ; i < n; i++)
	{
		if (vertexName[i] == v)
			return i;
	}
	return -1;
}

void Power_grid::Prim()
{
	char start;
	int startindex;
	while(true)
	{
		cout << "��������ʼ���㣺";
		cin >> start;
		startindex = FindIndex(start);
		if (cin.fail() || startindex == -1)
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
	
	for(int i = 0; i < n; i++)
	{
		lowcost[i] = edge[startindex][i];
		nearvex[i] = startindex;
	}
	nearvex[startindex] = -1;
	T = new EdgeNode[n-1];
	int Td = 0;						// ���б߽���ָ�� 
	for(int i = 1; i < n; i++)
	{
		float min = MAXINT;
		int v = -1;
		for(int j = 0; j < n; j++)
		{
			if (nearvex[j] != -1 && lowcost[j] < min)
			{
				v = j;
				min = lowcost[j];
			}
		}
		if(v != -1)
		{
			T[Td].head = nearvex[v];
			T[Td].tail = v;
			T[Td].cost = lowcost[v];
			Td++;
			nearvex[v] = -1;
			for(int j = 0; j < n; j++)
			{
				if(nearvex[j] != -1 && edge[v][j] < lowcost[j])
				{
					lowcost[j] = edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	cout << "����Prim��С��������" << endl << endl;
}

void Power_grid::Print_Tree()
{
	cout << "��С�������Ķ��㼰��Ϊ��" << endl << endl; 
	for(int i = 0; i < n-1; i++)
	{
		cout << vertexName[T[i].head] << "-(" << T[i].cost << ")->" << vertexName[T[i].tail] << "\t";
	}
	cout << endl << endl;
}

void Power_grid::ModeSelect()
{
	char mode = ' ';
	do
	{
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
	    
	    switch (mode)
		{
			case 'A':
				this->CreateVertex();
				break;
			case 'B':
				this->AddEdge();
				break;
			case 'C':
				this->Prim();
				break;
			case 'D':
				this->Print_Tree();
				break;
			case 'E':
				break; 
            default:
                break;
        }
        
        
	}while(mode != 'E');
}

int main()
{
	cout << "**             �������ģ��ϵͳ                  **" << endl
    	 << "===================================================" << endl
    	 << "**             A --- ������������                **" << endl
    	 << "**             B --- ��ӵ����ı�                **" << endl
    	 << "**             C --- ������С������              **" << endl
    	 << "**             D --- ��ʾ��С������              **" << endl
    	 << "**             E --- �˳�   ����                 **" << endl
    	 << "===================================================" << endl << endl; 
	
	Power_grid P;
	P.ModeSelect();
	system("pause");
	return 0;
}
