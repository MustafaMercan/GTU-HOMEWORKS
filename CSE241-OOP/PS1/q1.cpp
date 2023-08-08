#include <iostream>

using namespace std;

int main()
{
	int num = 2;
	int flag = 1;
	int i,j;
	for(i=2;i<100;i++)
	{
		for(j=2;j<i;j++)
		{
			if(i % j == 0)
			{
				flag = 0;
			}
		}
		if(flag == 1)
		{
			cout<<"Prime Numbers: " <<  i <<" "<<endl;
			
			
		}
		flag = 1;
	}	




    return 0;
}
