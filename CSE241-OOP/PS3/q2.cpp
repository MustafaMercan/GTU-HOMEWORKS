#include <iostream>
#include <vector>

using namespace std ;

vector <int> full_vector(vector <int>suitors_list ,int num_of_suitors);
void defination_winner(vector <int> suitors_list);


int main()
{	
	int i = 0;
	int num_of_suitors;
	
	
	cout << "Enter a number for suitor : "<<endl;
	cin>>num_of_suitors;
	vector <int> suitors_list(num_of_suitors);
	suitors_list = full_vector(suitors_list,num_of_suitors);
	defination_winner(suitors_list);
	return 0;
}
void defination_winner(vector <int> suitors_list)
{
	int loc = 0;
	int i;
	while(suitors_list.size() > 1 )
	{
		for(i=0;i<2;i++)
		{
			loc = loc + 1;
			if(loc == suitors_list.size())
			{
				loc = 0;
			}
		}
		
		suitors_list.erase(suitors_list.begin()+loc);
		if(loc == suitors_list.size())
		{
			loc = 0;
		}
		
	}
	cout<<suitors_list[0]<<" is the lucky winner."<<endl;
	exit(1);
	
}
vector <int> full_vector(vector <int>suitors_list ,int num_of_suitors)
{

	int i ;
	for(i=0;i<num_of_suitors;i++)
	{
		suitors_list[i] = i+1;
	}

	return suitors_list;
}
