#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Sudoku {	
public:
	//��
	char** answer;
	//��Ŀ
	char** question;
	//�Ƿ�Ϸ�
	bool isLegal;
	//��ʼ��
	Sudoku();
	Sudoku(int time, int blank);
	Sudoku(char** board);
	//������
	bool SolveDfs(int layer,char** temp);
	//��ӡ
	void PrintBoard(char** board);
	//���麯��
	bool validate(char** board, int row, int col, char num);
	//����������ͨ��������
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
	//��ʼ��һ���н������
	SolveDfs(0, question);
	PrintBoard(question);
	//������н������ڿ�
	CreatBoard(question,10,20);
	//��answer���г�ʼ��
	memcpy(answer, question, 81);
}

Sudoku::Sudoku(int time, int blank)
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
	//��ʼ��һ���н������
	SolveDfs(0, question);
	PrintBoard(question);
	//������н������ڿ�
	CreatBoard(question,time,blank);
	//��answer���г�ʼ��
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
	//��answer���г�ʼ��
	memcpy(answer, question, 81);
}

bool Sudoku::validate(char** board, int row, int col, char num)
{
	//������Ƿ��ظ�
	for (int i = 0; i < 9; i++)
	{
		if (board[row][i] == num)
			return false;
	}
	//������Ƿ��ظ�
	for (int j = 0; j < 9; j++)
	{
		if (board[j][col] == num)
			return false;
	}
	//��鹬���Ƿ��ظ�
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
	//�Ѿ�����
	if (layer == 81)
		return true;
	else 
	{
		//��ǰλ��
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
					//����
					if (!flag)
					{
						board[x][y] = '$';
					}
				}
			}
		}
		//��ǰλ���Ѿ�����
		else
		{
			flag = SolveDfs(layer + 1, board);
		}
		return flag;
	}
}

/*
	�������������ԣ���ͬһ��С�Ź����е��к���֮�佻��λ�ã�������֮�佻��λ�ã�������Ȼ����
*/
void Sudoku::CreatBoard(char** board, int SwapTimes,int BlankNUM)
{
	//С�Ź����е��к��н����������£��ֽ�����ʽ
	int choices[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
	srand(time(NULL));//���ö�̬����
	for (int time = 0; time < SwapTimes; time++)
	{
		//ѡȡ������ʽ
		int choice = rand() % 9;
		//�н���
		int row1 = choices[choice][0];
		int row2 = choices[choice][1];
		for (int i = 0; i < 9; i++)
		{
			char temp = board[row1][i];
			board[row1][i] = board[row2][i];
			board[row2][i] = temp;
		}
		//�н���
		int col1 = choices[choice][0];
		int col2 = choices[choice][1];
		for (int i = 0; i < 9; i++)
		{
			char temp = board[i][col1];
			board[i][col1] = board[i][col2];
			board[i][col2] = temp;
		}
		//cout << "�������У��У��±�:" << row1 << " " << row2 << endl;
		//PrintBoard(board);
	}
	//����ڿ�
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
			//�����ڿ�
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