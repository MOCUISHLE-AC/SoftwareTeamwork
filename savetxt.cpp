#include "savetxt.h"
using namespace std;

void save_to_txt(ofstream &file, char** x, bool space)
{
	if(space)
	{
		file<<endl;
	}
	for(int i = 0;i < 9; i++)
	{
		for(int j = 0;j < 9; j++)
		{
			file<<x[i][j];
			if(j != 8)
			{
				file<<" ";
			}
		}
		file<<endl;
	}
}
