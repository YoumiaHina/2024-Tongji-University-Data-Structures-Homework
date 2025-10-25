#include<iostream>
using namespace std;

//实现栈的基本功能 
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

// 对比符号优先级，a优先级大于b则返回true，小于等于b则返回false 
bool Priority_Check(char a, char b)
{
	if(a == '*' || a == '/')
	{
		if(b == '+' || b == '-')
			return true;
	}
	return false;
}

// 检查是否是运算符，是运算符则返回true，否则返回false 
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
			//遇到栈中运算符优先级不严格递增的情况，则出栈直到栈空或左括号为止 
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
			//遇右括号，则出栈至左括号为止 
			while(S.peek() != '(')
			{
				outex[j++] = S.pop();
				outex[j++] = ' ';
			}
			S.pop();									// 删除左括号 
		}
		else
		{
			if(inex[i] == '+')							// 正号不输出 
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
		outex[j - 1] = '\0';							// 删除结尾多余空格 
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
