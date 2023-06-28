#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include<iterator>
using namespace std;


//用于判断 char** 中的内容是否相同
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

class Sudoku {
private:
	int AnswerNum = 0;
public:
	//blank 数量
	int blank;
	//交换次数
	int swaptimes;
	//答案
	char** answer;
	//候选答案（解可能不唯一）
	vector<char**> AnserSheet;
	//题目
	char** question;
	//是否合法
	bool isLegal = false;
	//初始化
	Sudoku(int SwapTimes = 10, int BlankNUM = 20);
	Sudoku(char** board,int BlankNum);
	//解数独
	bool SolveDfs(int layer, char** board);
	bool InitSolveDfs(int layer, char** board);
	//打印
	void PrintBoard(char** board);
	//检验函数
	bool validate(char** board, int row, int col, char num);
	//创建数独（通过交换）
	void CreatBoard(char** board, int SwapTimes = 10, int BlankNUM = 20);
	//获取解的个数
	bool GetAnswerNum();
	//解决多个解的问题
	bool SolveReat(int Trytimes=10);
};

Sudoku::Sudoku(int SwapTimes, int BlankNUM)
{
	//balnk 和 swaptimes 先赋值
	blank = BlankNUM;
	this->swaptimes = SwapTimes;
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
	InitSolveDfs(0, question);
	//对其进行交换和挖空
	CreatBoard(question, swaptimes, blank);
	//对answer进行初始化
	memcpy(answer, question, 81);
}

Sudoku::Sudoku(char** board, int BlankNum)
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
	//blank
	this->blank = BlankNum;
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
			flag = SolveDfs(layer + 1, board);
		}
		return flag;
	}
}


/*
	根据数独的特性，在同一个小九宫格中的行和行之间交换位置，列与列之间交换位置，数独依然成立
*/
void Sudoku::CreatBoard(char** board, int SwapTimes, int BlankNUM)
{
	this->blank = BlankNUM;
	//小九宫格中的行和列交换，有以下９种交换方式
	int choices[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
	srand(clock());//设置动态种子
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
		/*cout << "交换的行（列）下标:" << row1 << " " << row2 << endl;
		PrintBoard(board);*/
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
			question = answer;
			answer = AnserSheet[0];
			return true;
		}
	}
	return false;
}
int main()
{
	vector <Sudoku> SudokuList;
	//生成1000个
	while (SudokuList.size()<1000)
	{
		srand(clock());//设置动态种子
		int swaptemp = rand() % 10 + 10;
		int blanktemp = rand() % 35 + 20;

		Sudoku test(swaptemp,blanktemp);
		cout << "生成的数独如下所示：" << endl;
		test.PrintBoard(test.question);
		//有解
		if (test.SolveDfs(0, test.answer))
		{
			cout << "解的个数：" << test.AnserSheet.size() << endl;
		}
		else
			continue;
		//答案不唯一
		if (!test.GetAnswerNum())
		{
			cout << "答案不唯一" << endl;
			if (test.SolveReat())
			{
				test.PrintBoard(test.question);
				test.PrintBoard(test.answer);
				cout << "解决成功" << endl;
				SudokuList.push_back(test);
			}
			else
				cout << "解决失败" << endl;
		}
		else
		{
			SudokuList.push_back(test);
		}
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
	Sudoku newtest(test2,4);
	cout << "数独如下所示：" << endl;
	newtest.PrintBoard(newtest.question);
	//有解
	if (newtest.SolveDfs(0, newtest.answer))
	{
		cout << "答案如下：" << endl;
		for (int i = 0; i < newtest.AnserSheet.size(); i++)
		{
			newtest.PrintBoard(newtest.AnserSheet[i]);
		}
	}
	//答案不唯一
	if (!newtest.GetAnswerNum())
	{
		cout << "答案不唯一" << endl;
		if (newtest.SolveReat())
		{
			newtest.PrintBoard(newtest.question);
			newtest.PrintBoard(newtest.answer);
			cout << "解决成功" << endl;
		}
		else
			cout << "解决失败" << endl;
	}
	return 0;
}