#include<iostream>

using namespace std;

class ArcNode
{
public:
	int headvex, tailvex;
	ArcNode *hlink, *tlink;
	int cost;
	
	ArcNode()
	{
		headvex = 0;
		tailvex = 0;
		hlink = NULL;
		tlink = NULL;
		cost = 0;
	}
	~ArcNode() { }
};

class VNode
{
public:
	int indegree;		// 入度 
	int outdegree;		// 出度 
	ArcNode *firstout;	// 出边链表 
	ArcNode *firstin;	// 入边链表 
	VNode()
	{
		indegree = 0;
		outdegree = 0;
		firstout = NULL;
		firstin = NULL;
	}
	~VNode() { }
};

// 实现栈的功能 
class Stack_int
{
private:
	int data[105];
    int top;
    
public:
	Stack_int() { top = -1; }
	~Stack_int() {}
	bool isEmpty() { return top == -1; }
	void push(int value) { data[++top] = value; }
	int pop() { return data[top--]; }
	int peek() { return data[top]; }
};
class Stack_ArcNode
{
private:
	ArcNode *data[5000];
    int top;
    
public:
	Stack_ArcNode() { top = -1; }
	~Stack_ArcNode() {}
	bool isEmpty() { return top == -1; }
	void push(ArcNode *value) { data[++top] = value; }
	ArcNode *pop() { return data[top--]; }
	ArcNode *peek() { return data[top]; }
};

class Solution
{
private:
	int n, m;
	VNode *g;
	
	int *order;
	int *ve, *vl;
	int *e, *l;
public:
	Solution()
	{
		n = 0;
		m = 0;
		g = NULL;
		order = NULL;
		ve = NULL;
		vl = NULL;
		e = NULL;
		l = NULL;
	}
	~Solution() { }
	void input();
	bool Topological_Sort();
	void Critical_Path();
};

void Solution::input()
{
	cin >> n >> m;
	g = new VNode[n+1];
	int head, tail, cost;
	for(int i = 0; i < m; i++)
	{
		cin >> head >> tail >> cost;
		ArcNode *p = new ArcNode;
		p->headvex = head;
		p->tailvex = tail;
		p->cost = cost;
		
		if (g[head].firstout == NULL)
		{
			g[head].firstout = p;
		}
		else
		{
			ArcNode *q = g[head].firstout;
			while(q->tlink != NULL)
				q = q->tlink;
			q->tlink = p;
		}
		if (g[tail].firstin == NULL)
		{
			g[tail].firstin = p;
		}
		else
		{
			ArcNode *q = g[tail].firstin;
			while(q->hlink != NULL)
				q = q->hlink;
			q->hlink = p;
		}
		g[tail].indegree++;
		g[head].outdegree++;
	}
}

bool Solution::Topological_Sort()
{
	Stack_int S;
	order = new int[n];			// order用于存放拓扑序列 
	int i;
	for(i = 1; i <= n; i++)
	{
		if (g[i].indegree == 0)
			S.push(i);
	}
	int count = 0;
	ArcNode *p = NULL;
	while (!S.isEmpty())
	{
		i = S.pop();
		order[count++] = i;
		for(p = g[i].firstout; p != NULL; p = p->tlink)
		{
			int v = p->tailvex;
			if(!(--g[v].indegree))
				S.push(v);
		}
	}
	if(count < n)
		return false;
	else
		return true;
}

void Solution::Critical_Path()
{
	ve = new int[n+1]; 
	vl = new int[n+1];
	for(int i = 1; i <= n; i++)
		ve[i] = 0;
	for(int i = 0; i < n; i++)
	{
		ArcNode *p = NULL;
		for(p = g[order[i]].firstout; p != NULL; p = p->tlink)
		{
			if(ve[order[i]] + p->cost > ve[p->tailvex])
				ve[p->tailvex] = ve[order[i]] + p->cost;
		}
	}
	
	for(int i = 1; i <= n; i++)
		vl[i] = ve[order[n-1]];
	for(int i = n-1; i >= 0; i--)
	{
		ArcNode *p = NULL;
		for(p = g[order[i]].firstin; p != NULL; p = p->hlink)
		{
			if(vl[order[i]] - p->cost < vl[p->headvex])
				vl[p->headvex] = vl[order[i]] - p->cost;
		}
	}
	
	e = new int[m];
	l = new int[m];
	ArcNode **arc = new ArcNode*[m];
	Stack_ArcNode S;
	int count = 0;
	for(int i = 1; i <= n; i++)
	{
		ArcNode *p = g[i].firstout;
		while(p != NULL)
		{
			S.push(p);
			p = p->tlink;
		}
		while(!S.isEmpty())
		{
			p = S.pop();
			arc[count] = p;
			e[count] = ve[p->headvex];
			l[count] = vl[p->tailvex] - p->cost;
			count++;
		}
	}
	
	cout << ve[order[n-1]] << endl;
	for(int i = 0; i < m; i++)
	{
		if(e[i] == l[i])
		{
			cout << arc[i]->headvex << "->" << arc[i]->tailvex << endl;
		}
	}
}

int main()
{
	Solution sol;
	sol.input();
	if (!sol.Topological_Sort())
		cout << 0 << endl;
	else
		sol.Critical_Path();
	system("pause");
	return 0;
}
