#include "getdata.h"
using namespace std;

int get_num(char* target, char* location)
{
	int t_count = strlen(target);
	for(int i = 0;i < t_count; i++)
	{
		if((target[i] < '0') || (target[i] > '9'))
		{
			cout<<"invalid parameters after '"<<location<<"' !"<<endl;
			return -1;
		}
	}
	int t_num = atoi(target);
	return t_num;
}