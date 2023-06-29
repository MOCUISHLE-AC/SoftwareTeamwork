#include "test_sudoku.h"
#include "sudoku.h"
#include "getdata.h"
#include "savetxt.h"
#include "do_event.h"
// °Ñ²âÊÔ°ü×¢²áÎª aTest
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(testSudoku, "aTest");

testSudoku::testSudoku() {};

testSudoku::~testSudoku() {};

void testSudoku::setUp() {
	std::cout << "test begin" << std::endl;
}

void testSudoku::tearDown() {
	std::cout << "test end" << std::endl;
}

void testSudoku::testSudoku1() {
	CPPUNIT_ASSERT(c_event("20") == true);
	CPPUNIT_ASSERT(s_event("./testdata/test0.txt") == true);
	CPPUNIT_ASSERT(n_event("1000") == true);
	CPPUNIT_ASSERT(n_m_event("1000", "1") == true);
	CPPUNIT_ASSERT(n_r_event("10", "20~55") == true);
	CPPUNIT_ASSERT(n_u_event("20") == true);
}

void testSudoku::testSudoku2() {
	CPPUNIT_ASSERT(c_event("100000000") == false);
	CPPUNIT_ASSERT(n_event("100000") == false);
	CPPUNIT_ASSERT(n_m_event("1000", "5") == false);
	CPPUNIT_ASSERT(n_r_event("10", "15~55") == false);
}

void testSudoku::testSudoku3() {
	CPPUNIT_ASSERT(c_event("ss") == false);
	CPPUNIT_ASSERT(s_event("./testdata/null.txt") == false);
	CPPUNIT_ASSERT(s_event("./testdata/test0.csv") == false);
	CPPUNIT_ASSERT(n_event("10a") == false);
	CPPUNIT_ASSERT(n_m_event("10b0", "2") == false);
	CPPUNIT_ASSERT(n_m_event("10", "x") == false);
	CPPUNIT_ASSERT(n_r_event("10", "2w~55") == false);
	CPPUNIT_ASSERT(n_r_event("-10", "20~55") == false);
}

void testSudoku::testSudoku4() {
	CPPUNIT_ASSERT(s_event("./testdata/test_null.txt") == true);
}

void testSudoku::testSudoku5() {
	CPPUNIT_ASSERT(s_event("./testdata/test_max.txt") == true);
}

void testSudoku::testSudoku6() {
	CPPUNIT_ASSERT(s_event("./testdata/test_easy.txt") == true);
	CPPUNIT_ASSERT(s_event("./testdata/test_medium.txt") == true);
	CPPUNIT_ASSERT(s_event("./testdata/test_hard.txt") == true);
}

void testSudoku::testSudoku7() {
	CPPUNIT_ASSERT(s_event("./testdata/test_mess.txt") == true);
}

void testSudoku::testSudoku8() {
	CPPUNIT_ASSERT(s_event("./testdata/test_limit.txt") == false);
}

void testSudoku::testSudoku9() {
	CPPUNIT_ASSERT(s_event("./testdata/test_u.txt") == true);
}

void testSudoku::testSudoku10() {
	CPPUNIT_ASSERT(s_event("./testdata/test_empty.txt") == false);
}
