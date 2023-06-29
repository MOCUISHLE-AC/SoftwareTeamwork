#include  <cppunit/extensions/HelperMacros.h>

class testSudoku:public CppUnit::TestFixture {//继承TestFixture
	CPPUNIT_TEST_SUITE(testSudoku); //把testSudoku类添加到测试包
	CPPUNIT_TEST(testSudoku1);//添加要测试的函数
	CPPUNIT_TEST(testSudoku2);
	CPPUNIT_TEST(testSudoku3);
	CPPUNIT_TEST(testSudoku4);
	CPPUNIT_TEST(testSudoku5);
	CPPUNIT_TEST(testSudoku6);
	CPPUNIT_TEST(testSudoku7);
	CPPUNIT_TEST(testSudoku8);
	CPPUNIT_TEST(testSudoku9);
	CPPUNIT_TEST(testSudoku10);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	testSudoku();
	~testSudoku();
	void testSudoku1();
	void testSudoku2();
	void testSudoku3();
	void testSudoku4();
	void testSudoku5();
	void testSudoku6();
	void testSudoku7();
	void testSudoku8();
	void testSudoku9();
	void testSudoku10();
};