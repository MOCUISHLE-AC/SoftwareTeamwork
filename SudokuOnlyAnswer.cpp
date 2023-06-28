#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include<iterator>
using namespace std;


//�����ж� char** �е������Ƿ���ͬ
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
	//blank ����
	int blank;
	//��������
	int swaptimes;
	//��
	char** answer;
	//��ѡ�𰸣�����ܲ�Ψһ��
	vector<char**> AnserSheet;
	//��Ŀ
	char** question;
	//�Ƿ�Ϸ�
	bool isLegal = false;
	//��ʼ��
	Sudoku(int SwapTimes = 10, int BlankNUM = 20);
	Sudoku(char** board,int BlankNum);
	//������
	bool SolveDfs(int layer, char** board);
	bool InitSolveDfs(int layer, char** board);
	//��ӡ
	void PrintBoard(char** board);
	//���麯��
	bool validate(char** board, int row, int col, char num);
	//����������ͨ��������
	void CreatBoard(char** board, int SwapTimes = 10, int BlankNUM = 20);
	//��ȡ��ĸ���
	bool GetAnswerNum();
	//�������������
	bool SolveReat(int Trytimes=10);
};

Sudoku::Sudoku(int SwapTimes, int BlankNUM)
{
	//balnk �� swaptimes �ȸ�ֵ
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
	//��ʼ��һ���н������
	InitSolveDfs(0, question);
	//������н������ڿ�
	CreatBoard(question, swaptimes, blank);
	//��answer���г�ʼ��
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
	//��answer���г�ʼ��
	memcpy(answer, question, 81);
	//blank
	this->blank = BlankNum;
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
	//�Ѿ�����
	if (layer == 81)
	{
		AnswerNum++;
		//�洢�𰸺�ѡ����
		char** temp;
		temp =new char* [9];
		for (int i = 0; i < 9; i++)
		{
			temp[i] = new char[9];
		}
		//memcpy(temp, board, 81);�����ʺţ���������
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				temp[i][j] = board[i][j];
		AnserSheet.push_back(temp);
		//PrintBoard(AnserSheet.back());
		return true;
	}
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
					bool flag1 = SolveDfs(layer + 1, board);
					//����
					board[x][y] = '$';
					if (flag1)
						flag = true;
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

bool Sudoku::InitSolveDfs(int layer, char** board)
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
					flag = InitSolveDfs(layer + 1, board);
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
void Sudoku::CreatBoard(char** board, int SwapTimes, int BlankNUM)
{
	this->blank = BlankNUM;
	//С�Ź����е��к��н����������£��ֽ�����ʽ
	int choices[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
	srand(clock());//���ö�̬����
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
		/*cout << "�������У��У��±�:" << row1 << " " << row2 << endl;
		PrintBoard(board);*/
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

bool Sudoku::GetAnswerNum()
{
	if (AnswerNum == 1)
		return true;
	return false;
}

bool Sudoku::SolveReat(int Trytimes)
{
	/*
		�ҵĵ�һ����𰸲�ͬ��λ�ã�����̶�������ѡ��'$'�������ʱ��return false��
	*/
	for (int times = 0; times < Trytimes; times++)
	{
		if (!GetAnswerNum())
		{
			int state = 0;//��¼�ڼ�������һ��
			for (int i = 0; i < 9; i++)
			{
				bool flag = false;
				for (int j = 0; j < 9; j++)
				{
					//ֻ�Ƚ� answer[0] answer[1]
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
			//����
			int row = state / 9;
			int col = state % 9;
			//Ĭ��ʹ�� AnserSheet[0]�Ĵ�
			answer[row][col] = AnserSheet[0][row][col];
			//blank��������
			this->blank--;
			//���ô𰸸���
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
	//����1000��
	while (SudokuList.size()<1000)
	{
		srand(clock());//���ö�̬����
		int swaptemp = rand() % 10 + 10;
		int blanktemp = rand() % 35 + 20;

		Sudoku test(swaptemp,blanktemp);
		cout << "���ɵ�����������ʾ��" << endl;
		test.PrintBoard(test.question);
		//�н�
		if (test.SolveDfs(0, test.answer))
		{
			cout << "��ĸ�����" << test.AnserSheet.size() << endl;
		}
		else
			continue;
		//�𰸲�Ψһ
		if (!test.GetAnswerNum())
		{
			cout << "�𰸲�Ψһ" << endl;
			if (test.SolveReat())
			{
				test.PrintBoard(test.question);
				test.PrintBoard(test.answer);
				cout << "����ɹ�" << endl;
				SudokuList.push_back(test);
			}
			else
				cout << "���ʧ��" << endl;
		}
		else
		{
			SudokuList.push_back(test);
		}
	}

	//�ֶ��������
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
	cout << "����������ʾ��" << endl;
	newtest.PrintBoard(newtest.question);
	//�н�
	if (newtest.SolveDfs(0, newtest.answer))
	{
		cout << "�����£�" << endl;
		for (int i = 0; i < newtest.AnserSheet.size(); i++)
		{
			newtest.PrintBoard(newtest.AnserSheet[i]);
		}
	}
	//�𰸲�Ψһ
	if (!newtest.GetAnswerNum())
	{
		cout << "�𰸲�Ψһ" << endl;
		if (newtest.SolveReat())
		{
			newtest.PrintBoard(newtest.question);
			newtest.PrintBoard(newtest.answer);
			cout << "����ɹ�" << endl;
		}
		else
			cout << "���ʧ��" << endl;
	}
	return 0;
}