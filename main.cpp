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

//���ڵ���
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
			cout<<"�����������"<<endl;
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
		cout<<"�����������"<<endl;
	}

	//�ֶ��������
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
	cout << "����������ʾ��" << endl;
	newtest.PrintBoard(newtest.question);
	newtest.SolveDfs(0, newtest.answer);
	cout << "�����£�" << endl;
	newtest.PrintBoard(newtest.question);*/
	return 0;
}

//���ڵ�Ԫ����
//int main(int argc, char* argv[]) {
//    // ������ƣ����̵���Ҫ������
//	CPPUNIT_NS::TestResult tr;
//	CPPUNIT_NS::TestResultCollector trc;
//	tr.addListener(&trc);
//    
//	CPPUNIT_NS::BriefTestProgressListener progress;
//	tr.addListener(&progress);
//
//    //���������࣬��Ӳ��԰�������
//	CPPUNIT_NS::TestRunner runner;
//	CPPUNIT_NS::TestFactoryRegistry& reg = CppUnit::TestFactoryRegistry::getRegistry("aTest");
//	runner.addTest(reg.makeTest());
//	runner.run(tr);
//
//    //������
//	CPPUNIT_NS::CompilerOutputter outputter(&trc, CPPUNIT_NS::stdCOut());
//	outputter.write();
//	
//	return 0;
//}