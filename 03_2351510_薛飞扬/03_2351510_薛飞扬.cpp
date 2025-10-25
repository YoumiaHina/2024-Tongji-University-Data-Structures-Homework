#include<iostream>
using namespace std;

const int MAXSIZE = 101;

struct coordinate
{
	int x;
	int y;
};

class LNode								// 链表节点类，用于存储路径 
{
	friend class Maze;
	coordinate data;
	LNode *next;
	LNode()
	{
		data = {0, 0};
		next = NULL;
	}
	~LNode() {};
};

class Maze
{
public:
    Maze();
    ~Maze() { };
    void setMazeData(int predefinedMaze[][7], int mrow_size, int mcol_size, coordinate mstart, coordinate mend);	// 设置迷宫数据 
    bool TraverseMaze();	// 使用深度优先搜索找到从起点到终点的路径
    void showMap();							// 显示带路径的地图 
    void showTrace();						// 显示找到的路径
private:
	int row_size, col_size;
    coordinate start;
    coordinate end;
    coordinate current;
    int map[MAXSIZE][MAXSIZE];
    int move_x[4] = {1, 0, -1, 0};			// 向上下左右四种方向走时，x坐标的变化量
    int move_y[4] = {0, 1, 0, -1};			// 向上下左右四种方向走时，y坐标的变化量
	LNode *T;								// 用于存储路径的链表 
};

Maze::Maze()
{
	for(int i = 0; i < MAXSIZE; i++)
	{
		for(int j = 0; j < MAXSIZE; j++)
		{
			map[i][j] = 0;
		}
	}
	T = NULL;
	row_size = 0; col_size = 0;
	start = {0,0}; end = {0,0};
}

void Maze::setMazeData(int predefinedMaze[][7], int mrow_size, int mcol_size, coordinate mstart, coordinate mend)
{
	for (int i = 0; i < mrow_size; i++) 
    {
        for (int j = 0; j < mcol_size; j++) 
        {
        	map[i][j] = predefinedMaze[i][j];
		}
    }
    row_size = mrow_size;
    col_size = mcol_size;
    start = mstart;
    end = mend;
    current = start;
}

bool Maze::TraverseMaze()
{
	if(current.x == end.x && current.y == end.y)
	{
		T = new LNode;
		T->data = current;
		T->next = NULL;
		map[current.x][current.y] = 2;
		return true;						// 已找到路径，返回真 
	}
	for(int i = 0; i < 4; i++)
	{
		if(map[current.x+move_x[i]][current.y+move_y[i]] == 0)
		{
			map[current.x][current.y] = 2;
			current.x += move_x[i];
			current.y += move_y[i];
			if(TraverseMaze())
			{	
				current.x -= move_x[i];
				current.y -= move_y[i];
				LNode *temp = new LNode;
				temp->data = current;
				temp->next = T;
				T = temp;					//利用头插法将坐标插入路径链表 
				return true;
			}
			current.x -= move_x[i];
			current.y -= move_y[i];
			map[current.x][current.y] = 0;
		}
	}
	return false;
}

void Maze::showMap()
{
	cout << "迷宫地图：" << endl;
	cout << "\t";
	for(int j = 0; j < col_size; j++)
	{
		cout << j << "列" << "\t";
	}
	cout << endl;
	for(int i = 0; i < row_size; i++)
	{
		cout << i << "行" << "\t";
		for(int j = 0; j < col_size; j++)
		{
			switch(map[i][j])
			{
				case 0:
					cout << 0 << "\t";
					break;
				case 1:
					cout << "#" << "\t";
					break;
				case 2:
					cout << "x" << "\t";
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::showTrace()
{
	LNode *temp = T;
	cout << "迷宫路径：" << endl;
	cout << "(" << temp->data.x << "," << temp->data.y << ")";
	temp = temp->next;
	while(temp != NULL)
	{
		cout<< " ---> (" << temp->data.x <<"," << temp->data.y << ")";
		temp = temp->next;
	}
	cout << endl; 
}

int main()
{
	int row_size = 7, col_size = 7;
	int predefinedMaze[7][7] = 
    {
		{1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
	};
	coordinate start = {1,1};
	coordinate end = {5,5};
	Maze myMaze;
	myMaze.setMazeData(predefinedMaze, row_size, col_size, start, end);
	if(myMaze.TraverseMaze())
	{
		myMaze.showMap();
		myMaze.showTrace();
	}
	else
	{
		cout << "迷宫无解！" << endl;
	}
	system("pause"); 
	return 0;
}
