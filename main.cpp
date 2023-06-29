#include "sudoku.h"
#include "getdata.h"
#include "savetxt.h"
#include "do_event.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>

using namespace std;

//用于调试
int main(int argc, char** argv)
{
	if(argc == 1)
	{
		zero_event();
	}
	else if(argc == 3)
	{
		if(strcmp(argv[1], "-c") == 0) 
		{
			c_event(argv[2]);
		}
		else if(strcmp(argv[1], "-s") == 0)
		{
			s_event(argv[2]);
		}
		else if(strcmp(argv[1], "-n") == 0)
		{
			n_event(argv[2]);
		}
		else
		{
			cout<<"传入参数错误！"<<endl;
		}
	}
	else if(argc == 4)
	{
		if((strcmp(argv[1], "-n") == 0) && (strcmp(argv[3], "-u") == 0)) 
		{
			n_u_event(argv[2]);
		}
	}
	else if(argc == 5)
	{
		if((strcmp(argv[1], "-n") == 0) && (strcmp(argv[3], "-m") == 0)) 
		{
			n_m_event(argv[2], argv[4]);
		}
		if((strcmp(argv[1], "-n") == 0) && (strcmp(argv[3], "-r") == 0)) 
		{
			n_r_event(argv[2], argv[4]);
		}
	}
	else
	{
		cout<<"传入参数错误！"<<endl;
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
	return 0;
}

//用于单元测试
//int main(int argc, char* argv[]) {
//    // 结果控制，流程的主要控制者
//	CPPUNIT_NS::TestResult tr;
//	CPPUNIT_NS::TestResultCollector trc;
//	tr.addListener(&trc);
//    
//	CPPUNIT_NS::BriefTestProgressListener progress;
//	tr.addListener(&progress);
//
//    //测试运行类，添加测试包，运行
//	CPPUNIT_NS::TestRunner runner;
//	CPPUNIT_NS::TestFactoryRegistry& reg = CppUnit::TestFactoryRegistry::getRegistry("aTest");
//	runner.addTest(reg.makeTest());
//	runner.run(tr);
//
//    //输出结果
//	CPPUNIT_NS::CompilerOutputter outputter(&trc, CPPUNIT_NS::stdCOut());
//	outputter.write();
//	
//	return 0;
//}