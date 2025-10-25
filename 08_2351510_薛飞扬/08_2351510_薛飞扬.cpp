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
	EdgeNode *T;			// 边结点数组用于存放最小生成树 
	
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
	cout << "请输入顶点的个数：";
	cin >> n;
	vertexName = new char[n];
	cout << "请依次输入各顶点的名称：" << endl ;
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
	        cout << "请输入两个顶点及边：";
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
	            cout << "输入错误，请重新输入！" << endl;
	        }
	        else if (edge[headindex][tailindex] != MAXINT)
	        {
	        	cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        	cout << "已存在边，请重新输入！" << endl;
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
		cout << "请输入起始顶点：";
		cin >> start;
		startindex = FindIndex(start);
		if (cin.fail() || startindex == -1)
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
	
	for(int i = 0; i < n; i++)
	{
		lowcost[i] = edge[startindex][i];
		nearvex[i] = startindex;
	}
	nearvex[startindex] = -1;
	T = new EdgeNode[n-1];
	int Td = 0;						// 树中边结点的指针 
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
	cout << "生成Prim最小生成树！" << endl << endl;
}

void Power_grid::Print_Tree()
{
	cout << "最小生成树的顶点及边为：" << endl << endl; 
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
	cout << "**             电网造价模拟系统                  **" << endl
    	 << "===================================================" << endl
    	 << "**             A --- 创建电网顶点                **" << endl
    	 << "**             B --- 添加电网的边                **" << endl
    	 << "**             C --- 构建最小生成树              **" << endl
    	 << "**             D --- 显示最小生成树              **" << endl
    	 << "**             E --- 退出   程序                 **" << endl
    	 << "===================================================" << endl << endl; 
	
	Power_grid P;
	P.ModeSelect();
	system("pause");
	return 0;
}
