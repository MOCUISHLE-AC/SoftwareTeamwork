#include "sudoku.h"
#include "getdata.h"
#include "savetxt.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc == 1)
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
	}
	else if(argc == 3)
	{
		if(strcmp(argv[1], "-c") == 0) 
		{
			int t_num = get_num(argv[2], argv[1]);
			if(t_num == -1)
			{
				return 0;
			}
			else
			{
				ofstream mytxt("final.txt");
				Sudoku tmp(0, 0);
				for(int i = 0;i < t_num; i++)
				{
					tmp.CreatBoard(tmp.answer,2 * t_num + 1,0);
					/*if(i != 0)
					{
						mytxt<<endl;
					}
					for(int i = 0;i < 9; i++)
					{
						for(int j = 0;j < 9; j++)
						{
							mytxt<<tmp.answer[i][j];
						}
						mytxt<<endl;
					}*/
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
		}
	}

	//手动输入测试
	/*char** test2;
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
	newtest.PrintBoard(newtest.question);*/
	system("pause");
	return 0;
}
