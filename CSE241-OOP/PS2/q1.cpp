#include <iostream>
#include <cstdlib> 
#include <ctime> 
#define DUALS 10000

using namespace std;

int random_number();
bool chance_of_aaron();
bool chance_of_bob();


// Aaron -> 1/3
// Bob -> 1/2
// Charlie -> 1

int main()
{
	
	int i;
	float win_aaron = 0 , win_bob = 0 , win_charlie = 0;
	
	//keeps track of whether players are alive or not
	bool aaron = true;
	bool bob = true;
	bool charlie = true;
	
	//determines whether the player will hit or miss on the next shot
	bool aaron_shout;
	bool bob_shout ;
	bool charlie_shout;
	
	srand((int)time(0)); 
	
	for(i=0;i<DUALS;i++)
	{
		aaron = true;
		bob = true;
		charlie = true;
		
		while((aaron == true && bob == true) || (aaron == true && charlie == true) || (bob == true && charlie == true))
		{
			aaron_shout = chance_of_aaron();
			bob_shout = chance_of_bob();
			charlie_shout = true;
			
			if(aaron == true && aaron_shout == true)
			{
				if(charlie == true)
					charlie = false;
				else if(bob == true)
					bob = false;
			}
			if(bob == true && bob_shout == true)
			{
				if(charlie == true)
					charlie = false;
				else if(aaron == true)
					aaron = false;
			}
			if(charlie == true && charlie_shout == true)
			{
				if(bob == true)
					bob = false;
				else if(aaron == true)
					aaron = false;
			}
		}
		//win_aaron = 0 , win_bob = 0 , win_charlie = 0;
		if(aaron)
			win_aaron++;
		else if(bob)
			win_bob++;
		else if(charlie)
			win_charlie++;
	}
	cout <<"Aaron won %"<<win_aaron / 100 <<endl;
	cout << "Bob won %"<<win_bob / 100 <<endl;
	cout << "Charlie won % "<<win_charlie / 100 <<endl;
	
	
		
		
	

    return 0;
}
int random_number()
{
	int num;
	num = rand(); 
	return num;

}
bool chance_of_aaron()
{
	int num;
	num = random_number();
	//cout << num % 3 <<endl;
	if(num % 3 == 0)
		return true;
	else
		return false;
}
bool chance_of_bob()
{
	int num;
	num = random_number();
	//cout << num % 3 <<endl;
	if(num % 2 == 0)
		return true;
	else
		return false;
}














