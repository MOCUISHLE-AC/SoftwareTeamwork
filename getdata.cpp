#include "getdata.h"
using namespace std;

int get_num(char* target, char* location)
{
	string t_target = target;
	int t_count = t_target.length();
	int t_num = 0;
	if(t_count >= 11)
	{
		cout<<"参数过大！"<<endl;
	}
	for(int i = 0;i < t_count; i++)
	{
		if((t_target[i] < '0') || (t_target[i] > '9'))
		{
			cout<<"invalid parameters after '"<<location<<"' !"<<endl;
			return -1;
		}
		else
		{
			t_num = t_num * 10 + (t_target[i] - '0');
		}
	}
	
	return t_num;
}
