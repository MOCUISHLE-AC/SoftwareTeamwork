#include "sudoku.h"
using namespace std;

bool CompareBetween(char** a, char** b)
{
	bool flag=true;
	for (int i = 0; i < 9; i++)
	{
		if (strcmp(a[i], b[i]) == 0)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
}

Sudoku::Sudoku(int t_time, int t_blank)
{
	question = new char* [9];
	answer = new char* [9];
	remain = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		question[i] = new char[9];
		answer[i] = new char[9];
		remain[i] = new char[9];
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			question[i][j] = '$';
			answer[i][j] = '$';
			remain[i][j] = '$';
		}
	}
	//memcpy(answer, question, 81);
	//初始化一个有解的数组
	InitSolveDfs(0, question);
	PrintBoard(question);
	//对其进行交换和挖空
	CreatBoard(question,t_time,t_blank);
	//对answer进行初始化
	CopyBoard(answer, question);
	CopyBoard(remain, answer);
}

Sudoku::Sudoku(char** board)
{
	question = new char* [9];
	answer = new char* [9];
	remain = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		question[i] = new char[9];
		answer[i] = new char[9];
		remain[i] = new char[9];
	}
	CopyBoard(question, board);
	//对answer进行初始化
	CopyBoard(answer, question);
	CopyBoard(remain, answer);
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
	{
		AnswerNum++;
		//存储答案候选名单
		char** temp;
		temp =new char* [9];
		for (int i = 0; i < 9; i++)
		{
			temp[i] = new char[9];
		}
		//memcpy(temp, board, 81);黑人问号！！！！！
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				temp[i][j] = board[i][j];
		AnserSheet.push_back(temp);
		//PrintBoard(AnserSheet.back());
		return true;
	}
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
					bool flag1 = SolveDfs(layer + 1, board);
					//回溯
					board[x][y] = '$';
					if (flag1)
						flag = true;
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

bool Sudoku::InitSolveDfs(int layer, char** board)
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
					flag = InitSolveDfs(layer + 1, board);
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
			flag = InitSolveDfs(layer + 1, board);
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
	default_random_engine e;
	e.seed(time(0));
	uniform_int_distribution<int> u(0,8);
	for (int time = 0; time < SwapTimes; time++)
	{
		//选取交换方式
		int choice = u(e);
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
		//cout << "交换的行（列）下标:" << row1 << " " << row2 << endl;
		//PrintBoard(board);
	}
	//随机挖空
	for (int i = 0; i < BlankNUM; i++)
	{
		int row = u(e);
		int col = u(e);
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

bool Sudoku::GetAnswerNum()
{
	if (AnswerNum == 1)
		return true;
	return false;
}

bool Sudoku::SolveReat(int Trytimes)
{
	/*
		找的第一个与答案不同的位置，将其固定，重新选择'$'，如果超时，return false；
	*/
	for (int times = 0; times < Trytimes; times++)
	{
		if (!GetAnswerNum())
		{
			int state = 0;//记录第几个数不一样
			for (int i = 0; i < 9; i++)
			{
				bool flag = false;
				for (int j = 0; j < 9; j++)
				{
					//只比较 answer[0] answer[1]
					if (AnserSheet[0][i][j] != AnserSheet[1][i][j])
					{
						flag = true;
						break;
					}
					else
						state++;
				}
				if (flag)
					break;
			}
			//坐标
			int row = state / 9;
			int col = state % 9;
			//默认使用 AnserSheet[0]的答案
			answer[row][col] = AnserSheet[0][row][col];
			//blank数量减少
			this->blank--;
			//重置答案个数
			AnserSheet.clear();
			AnswerNum = 0;
			SolveDfs(0, answer);
		}
		else
		{
			//对answer赋值
			question = answer;
			answer = AnserSheet[0];
			return true;
		}
	}
	return false;
}

void Sudoku::LoadBoard(char** board)
{
	//memcpy(question, board, 81);
	//memcpy(answer, board, 81);
	CopyBoard(question, board);
	CopyBoard(answer, board);
}

void Sudoku::InitNum()
{
	AnswerNum = 0;
}

void CopyBoard(char** board1, char** board2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board1[i][j] = board2[i][j];
		}
	}
}
