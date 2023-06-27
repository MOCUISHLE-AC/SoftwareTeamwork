#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Sudoku {	
public:
	//答案
	char** answer;
	//题目
	char** question;
	//是否合法
	bool isLegal = false;
	//初始化
	Sudoku();
	Sudoku(char** board);
	//解数独
	bool SolveDfs(int layer,char** temp);
	//打印
	void PrintBoard(char** board);
	//检验函数
	bool validate(char** board, int row, int col, char num);
	//创建数独（通过交换）
	void CreatBoard(char** board,int SwapTimes=10, int BlankNUM = 20);
};

Sudoku::Sudoku()
{
	question = new char* [9];
	answer = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		question[i] = new char[9];
		answer[i] = new char[9];
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			question[i][j] = '$';
	memcpy(answer, question, 81);
	//初始化一个有解的数组
	SolveDfs(0, question);
	PrintBoard(question);
	//对其进行交换和挖空
	CreatBoard(question,10,20);
	//对answer进行初始化
	memcpy(answer, question, 81);
}

Sudoku::Sudoku(char** board)
{
	question = new char* [9];
	answer = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		question[i] = new char[9];
		answer[i] = new char[9];
	}
	memcpy(question, board, 81);
	//对answer进行初始化
	memcpy(answer, question, 81);
}

bool Sudoku::validate(char** board, int row, int col, char num)
{
	//检查行是否重复
	for (int i = 0; i < 9; i++)
	{
		if (board[row][i] == num)
			return false;
	}
	//检查列是否重复
	for (int j = 0; j < 9; j++)
	{
		if (board[j][col] == num)
			return false;
	}
	//检查宫内是否重复
	//9 3*3
	int x = row / 3;
	int y = col / 3;
	for (int i = 3 * x; i < 3 * x + 3; i++)
		for (int j = 3 * y; j < 3 * y + 3; j++)
		{
			if (num == board[i][j])
				return false;
		}
	return true;
}

bool Sudoku::SolveDfs(int layer, char** board)
{
	bool flag = false;
	//已经解完
	if (layer == 81)
		return true;
	else 
	{
		//当前位置
		int x = layer / 9;
		int y = layer % 9;
		if (board[x][y] == '$')
		{
			for (int solve = 1; solve <= 9; solve++)
			{
				if (validate(board, x, y, solve + '0'))
				{
					board[x][y] = solve + '0';
					flag = SolveDfs(layer + 1, board);
					//回溯
					if (!flag)
					{
						board[x][y] = '$';
					}
				}
			}
		}
		//当前位置已经给好
		else
		{
			flag = SolveDfs(layer + 1, board);
		}
		return flag;
	}
}

/*
	根据数独的特性，在同一个小九宫格中的行和行之间交换位置，列与列之间交换位置，数独依然成立
*/
void Sudoku::CreatBoard(char** board, int SwapTimes,int BlankNUM)
{
	//小九宫格中的行和列交换，有以下９种交换方式
	int choices[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
	srand(time(NULL));//设置动态种子
	for (int time = 0; time < SwapTimes; time++)
	{
		//选取交换方式
		int choice = rand() % 9;
		//行交换
		int row1 = choices[choice][0];
		int row2 = choices[choice][1];
		for (int i = 0; i < 9; i++)
		{
			char temp = board[row1][i];
			board[row1][i] = board[row2][i];
			board[row2][i] = temp;
		}
		//列交换
		int col1 = choices[choice][0];
		int col2 = choices[choice][1];
		for (int i = 0; i < 9; i++)
		{
			char temp = board[i][col1];
			board[i][col1] = board[i][col2];
			board[i][col2] = temp;
		}
		cout << "交换的行（列）下标:" << row1 << " " << row2 << endl;
		PrintBoard(board);
	}
	//随机挖空
	for (int i = 0; i < BlankNUM; i++)
	{
		int row = rand() % 9;
		int col = rand() % 9;
		if (board[row][col] != '$')
		{
			board[row][col] = '$';
		}
		else
		{
			//重新挖空
			i--;
		}
	}
}

void Sudoku::PrintBoard(char** board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	//自动生成数独测试
	Sudoku test;
	cout << "生成的数独如下所示：" << endl;
	test.PrintBoard(test.question);
	cout << "答案如下：" << endl;
	bool flag = test.SolveDfs(0, test.answer);
	if (flag)
	{
		test.PrintBoard(test.answer);
	}
	else
	{
		cout << "无解" << endl;
	}

	//手动输入测试
	char** test2;
	test2 = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		test2[i] = new char[9];
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			cin >> test2[i][j];
	Sudoku newtest(test2);
	cout << "数独如下所示：" << endl;
	newtest.PrintBoard(newtest.question);
	newtest.SolveDfs(0, newtest.answer);
	cout << "答案如下：" << endl;
	newtest.PrintBoard(newtest.question);
}