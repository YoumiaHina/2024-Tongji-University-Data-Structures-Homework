#include<iostream>
using namespace std;

const int MAXSIZE = 101;

struct coordinate
{
	int x;
	int y;
};

class LNode								// ����ڵ��࣬���ڴ洢·�� 
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
    void setMazeData(int predefinedMaze[][7], int mrow_size, int mcol_size, coordinate mstart, coordinate mend);	// �����Թ����� 
    bool TraverseMaze();	// ʹ��������������ҵ�����㵽�յ��·��
    void showMap();							// ��ʾ��·���ĵ�ͼ 
    void showTrace();						// ��ʾ�ҵ���·��
private:
	int row_size, col_size;
    coordinate start;
    coordinate end;
    coordinate current;
    int map[MAXSIZE][MAXSIZE];
    int move_x[4] = {1, 0, -1, 0};			// �������������ַ�����ʱ��x����ı仯��
    int move_y[4] = {0, 1, 0, -1};			// �������������ַ�����ʱ��y����ı仯��
	LNode *T;								// ���ڴ洢·�������� 
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
		return true;						// ���ҵ�·���������� 
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
				T = temp;					//����ͷ�巨���������·������ 
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
	cout << "�Թ���ͼ��" << endl;
	cout << "\t";
	for(int j = 0; j < col_size; j++)
	{
		cout << j << "��" << "\t";
	}
	cout << endl;
	for(int i = 0; i < row_size; i++)
	{
		cout << i << "��" << "\t";
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
	cout << "�Թ�·����" << endl;
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
		cout << "�Թ��޽⣡" << endl;
	}
	system("pause"); 
	return 0;
}
