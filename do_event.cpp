#include "sudoku.h"
#include "getdata.h"
#include "savetxt.h"
#include "do_event.h"
using namespace std;

void zero_event()
{
	//�Զ�������������
	Sudoku test(10, 20);
	cout << "���ɵ�����������ʾ��" << endl;
	test.PrintBoard(test.question);
	cout << "�����£�" << endl;
	bool flag = test.InitSolveDfs(0, test.answer);
	if (flag)
	{
		test.PrintBoard(test.answer);
	}
	else
	{
		cout << "�޽�" << endl;
	}
}

void c_event(char* x)
{
	int t_num = get_num(x, "-c");
	if(t_num == -1)
	{
		return;
	}
	if(t_num > 1000000)
	{
		cout<<"��������!"<<endl;
	}
	else
	{
		ofstream mytxt("final.txt");
		Sudoku tmp(0, 0);
		default_random_engine e;
		e.seed(time(0));
		uniform_int_distribution<int> u(10,60);
		for(int i = 0;i < t_num; i++)
		{
			int swaptemp = u(e);
			tmp.CreatBoard(tmp.answer,swaptemp,0);
			if(i == 0)
			{
				save_to_txt(mytxt, tmp.answer, false);
			}
			else
			{
				save_to_txt(mytxt, tmp.answer, true);
			}
		}
		mytxt.close();
	}
	cout<<t_num<<"�������վ��Ѿ�ȫ�����ɣ�������final.txt�У�"<<endl;
	return;
}

void s_event(char* x)
{
	string t_x = x;
	int judge_num = t_x.length();
	if((x[judge_num - 4] != '.') && (x[judge_num - 3] != 't') && (x[judge_num - 2] != 'x') && (x[judge_num - 1] != 't'))
	{
		cout<<"Ŀ���ļ�����txt�ļ���"<<endl;
		return;
	}
	ifstream gettxt(x);
	if(!gettxt.good())
	{
		cout<<"û���ҵ�Ŀ���ļ���"<<endl;
		return;
	}

	string line;
	int sudoku_count = 0;
	char** t_sudoku;
	t_sudoku = new char* [9];
	for (int i = 0; i < 9; i++)
	{
		t_sudoku[i] = new char[9];
	}
	ofstream mytxt("sudoku.txt");
	int space_flag = 0;
	int times = 1;
	Sudoku tmp;
	while(!gettxt.eof())
	{
		getline(gettxt, line);
		if(line.length() == 0)
		{
			continue;
		}
		else
		{
			int t_count = 0;
			for(int i = 0;i < line.length(); i++)
			{
				if(t_count >= 9)
				{
					break;
				}
				if(line[i] != ' ')
				{
					t_sudoku[sudoku_count][t_count++] = line[i];
				}
			}
			sudoku_count++;
		}
		if(sudoku_count == 9)
		{
			sudoku_count = 0;
			tmp.LoadBoard(t_sudoku);
			tmp.InitSolveDfs(0, tmp.answer);
			if(space_flag == 0)
			{
				save_to_txt(mytxt, tmp.answer, false);
				space_flag = 1;
			}
			else
			{
				save_to_txt(mytxt, tmp.answer, true);
			}
		}
	}
	mytxt.close();
	gettxt.close();
	cout<<"�����Ѿ�ȫ����ȡ����𱣴���sudoku.txt�У�"<<endl;
	return;
}

void n_event(char* x)
{
	int t_num = get_num(x, "-n");
	if(t_num == -1)
	{
		return;
	}
	if(t_num > 100000)
	{
		cout<<"��������!"<<endl;
	}
	else
	{
		cout<<"��������������Ϸ..."<<endl;
		ofstream mytxt("game.txt");
		Sudoku tmp(0, 0);
		default_random_engine e;
		e.seed(time(0));
		uniform_int_distribution<int> u(10,60);
		uniform_int_distribution<int> v(1,55);
		for(int i = 0;i < t_num; i++)
		{
			int swaptemp = u(e);
			int blanktemp = v(e);
			tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
			if(i == 0)
			{
				save_to_txt(mytxt, tmp.question, false);
			}
			else
			{
				save_to_txt(mytxt, tmp.question, true);
			}
			CopyBoard(tmp.question, tmp.remain);
		}
		mytxt.close();
	}
	cout<<t_num<<"��������Ϸ�Ѿ�ȫ�����ɣ�������game.txt�У�"<<endl;
	return;
}

void n_m_event(char* x, char* y)
{
	int t_num = get_num(x, "-n");
	if(t_num == -1)
	{
		return;
	}
	int t_level = get_num(y, "-m");
	if((t_level != 1) && (t_level != 2) && (t_level != 3))
	{
		cout<<"�Ѷ�ֻ��Ϊ1,2,3��"<<endl;
		return;
	}
	else
	{
		cout<<"���������Ѷ�Ϊ"<<t_level<<"��������Ϸ..."<<endl;
		int swaptemp;
		int blanktemp;
		ofstream mytxt("game.txt");
		Sudoku tmp(0, 0);
		default_random_engine e;
		e.seed(time(0));
		if(t_level == 1)
		{
			uniform_int_distribution<int> u(5,25);
			uniform_int_distribution<int> v(1,6);
			for(int i = 0;i < t_num; i++)
			{
				swaptemp = u(e);
				blanktemp = v(e);
				tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
				if(i == 0)
				{
					save_to_txt(mytxt, tmp.question, false);
				}
				else
				{
					save_to_txt(mytxt, tmp.question, true);
				}
				CopyBoard(tmp.question, tmp.remain);
			}
		}
		else if(t_level == 2)
		{
			uniform_int_distribution<int> u(10,40);
			uniform_int_distribution<int> v(6,21);
			for(int i = 0;i < t_num; i++)
			{
				swaptemp = u(e);
				blanktemp = v(e);
				tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
				if(i == 0)
				{
					save_to_txt(mytxt, tmp.question, false);
				}
				else
				{
					save_to_txt(mytxt, tmp.question, true);
				}
				CopyBoard(tmp.question, tmp.remain);
			}
		}
		else
		{
			uniform_int_distribution<int> u(15,65);
			uniform_int_distribution<int> v(21,55);
			for(int i = 0;i < t_num; i++)
			{
				swaptemp = u(e);
				blanktemp = v(e);
				tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
				if(i == 0)
				{
					save_to_txt(mytxt, tmp.question, false);
				}
				else
				{
					save_to_txt(mytxt, tmp.question, true);
				}
				CopyBoard(tmp.question, tmp.remain);
			}
		}
		mytxt.close();
	}
	cout<<t_num<<"��������Ϸ�Ѿ�ȫ�����ɣ�������game.txt�У�"<<endl;
	return;
}

void n_r_event(char* x, char* y)
{
	int t_num = get_num(x, "-n");
	if(t_num == -1)
	{
		return;
	}
	char *y1, *y2;
	y1 = strtok(y, "~");
	y2 = strtok(NULL, "~");
	int t_low = get_num(y1, "-r");
	int t_high = get_num(y2, "-r");
	if((t_low < 20) || (t_high > 55) || (t_low > t_high))
	{
		cout<<"�ڿ�����ΧӦ��20~55֮�䣡"<<endl;
		return;
	}
	else
	{
		cout<<"���������ڿ�����"<<t_low<<"~"<<t_high<<"֮���������Ϸ..."<<endl;
		ofstream mytxt("game.txt");
		Sudoku tmp(0, 0);
		default_random_engine e;
		e.seed(time(0));
		uniform_int_distribution<int> u(10,60);
		uniform_int_distribution<int> v(t_low,t_high);
		for(int i = 0;i < t_num; i++)
		{
			int swaptemp = u(e);
			int blanktemp = v(e);
			tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
			if(i == 0)
			{
				save_to_txt(mytxt, tmp.question, false);
			}
			else
			{
				save_to_txt(mytxt, tmp.question, true);
			}
			CopyBoard(tmp.question, tmp.remain);
		}
		mytxt.close();
	}
	cout<<t_num<<"��������Ϸ�Ѿ�ȫ�����ɣ�������game.txt�У�"<<endl;
	return;
}

void n_u_event(char* x)
{
	int t_num = get_num(x, "-n");
	if(t_num == -1)
	{
		return;
	}
	if(t_num > 100000)
	{
		cout<<"��������!"<<endl;
	}
	else
	{
		cout<<"�������ɽⷨΨһ��������Ϸ..."<<endl;
		ofstream mytxt("game.txt");
		Sudoku tmp(0, 0);
		default_random_engine e;
		e.seed(time(0));
		uniform_int_distribution<int> u(10,60);
		uniform_int_distribution<int> v(1,55);
		for(int i = 0;i < t_num; i++)
		{
			tmp.AnserSheet.clear();
			int swaptemp = u(e);
			int blanktemp = v(e);
			tmp.CreatBoard(tmp.question, swaptemp, blanktemp);
			CopyBoard(tmp.answer, tmp.question);
			tmp.InitNum();
			tmp.SolveDfs(0, tmp.answer);
			CopyBoard(tmp.answer, tmp.question);
			if(tmp.AnserSheet.size() == 0)
			{
				i--;
				CopyBoard(tmp.question, tmp.remain);
				continue;
			}
			if(!tmp.GetAnswerNum())
			{
				if(!tmp.SolveReat(10))
				{
					i--;
					CopyBoard(tmp.question, tmp.remain);
					continue;
				}
			}
			if(i == 0)
			{
				save_to_txt(mytxt, tmp.question, false);
			}
			else
			{
				save_to_txt(mytxt, tmp.question, true);
			}
			CopyBoard(tmp.question, tmp.remain);
		}
		mytxt.close();
	}
	cout<<t_num<<"��������Ϸ�Ѿ�ȫ�����ɣ�������game.txt�У�"<<endl;
	return;
}