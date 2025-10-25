#include<iostream>
using namespace std;

//ʵ��ջ�Ļ������� 
class Stack
{
private:
    char data[45];
    int top;
    
public:
	Stack() { top = -1; }
	~Stack() {};
	bool isEmpty() { return top == -1; }
	void push(char value) { data[++top] = value; }
	char pop() { return data[top--]; }
	char peek() { return data[top]; }
};

// �Աȷ������ȼ���a���ȼ�����b�򷵻�true��С�ڵ���b�򷵻�false 
bool Priority_Check(char a, char b)
{
	if(a == '*' || a == '/')
	{
		if(b == '+' || b == '-')
			return true;
	}
	return false;
}

// ����Ƿ������������������򷵻�true�����򷵻�false 
bool Sign_Check(const char *inex, int i)
{ 
	if(inex[i + 1] == ' ' && (inex[i] == '+' || inex[i] == '-' || inex[i] == '*' || inex[i] == '/'))
		return true;
	else
		return false; 
}

void Solution(const char *inex, char *outex)
{
	Stack S;
	int j = 0;
	for(int i = 0; inex[i] != '\0'; i++)
	{
		if(inex[i] == ' ')
			continue;
		if(Sign_Check(inex, i))
		{
			//����ջ����������ȼ����ϸ��������������ջֱ��ջ�ջ�������Ϊֹ 
			while(!S.isEmpty() && S.peek() != '(' && !Priority_Check(inex[i], S.peek()))
			{
				outex[j++] = S.pop();
				outex[j++] = ' ';
			}
			S.push(inex[i]);
		}
		else if(inex[i] == '(')
		{
			S.push(inex[i]);
		}
		else if(inex[i] == ')')
		{
			//�������ţ����ջ��������Ϊֹ 
			while(S.peek() != '(')
			{
				outex[j++] = S.pop();
				outex[j++] = ' ';
			}
			S.pop();									// ɾ�������� 
		}
		else
		{
			if(inex[i] == '+')							// ���Ų���� 
				i++;
			while(inex[i] != ' ' && inex[i] != '\0')
			{
				outex[j++] = inex[i++];
			}
			outex[j++] = ' ';
			i--;
		}
	}
	while(!S.isEmpty())
	{
		outex[j++] = S.pop();
		outex[j++] = ' ';
	}
	if (j > 0)
		outex[j - 1] = '\0';							// ɾ����β����ո� 
}

int main()
{
	char inex[41], outex[41];
	cin.getline(inex, 41);
	Solution(inex, outex);
	cout << outex << endl;
	system("pause"); 
	return 0;
}
