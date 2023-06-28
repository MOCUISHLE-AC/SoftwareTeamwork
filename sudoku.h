#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iterator>
#include <random>
using namespace std;

bool CompareBetween(char** a, char** b);

class Sudoku {
private:
	int AnswerNum;
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
	//保存初版
	char** remain;
	//是否合法
	bool isLegal;
	//初始化
	Sudoku(int t_time = 10, int t_blank = 20);
	Sudoku(char** board);
	//解数独
	bool SolveDfs(int layer,char** board);
	bool InitSolveDfs(int layer, char** board);
	//打印
	void PrintBoard(char** board);
	//检验函数
	bool validate(char** board, int row, int col, char num);
	//创建数独（通过交换）
	void CreatBoard(char** board,int SwapTimes=10, int BlankNUM = 20);
	//载入状态
	void LoadBoard(char** board);
	//获取解的个数
	bool GetAnswerNum();
	//解决多个解的问题
	bool SolveReat(int Trytimes=10);
	void InitNum();
};

void CopyBoard(char** board1, char** board2);
