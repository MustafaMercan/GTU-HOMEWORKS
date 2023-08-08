#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;

int humanTurn(int humanScore);
int computerTurn(int computerScore);
int random_number();

int main()
{
	srand((int)time(0)); 
	int humanscore = 0;//to keep the player's score
	int computerscore = 0;//to keep the computer's score
	int human_or_computer = 1;//variable defined to determine whose turn it is
	
	while(computerscore < 100 && humanscore < 100)
	{
		if(human_or_computer == 1)
		{
			humanscore = humanTurn(humanscore);
			human_or_computer = 0;
		}
		else if(human_or_computer == 0)
		{
			computerscore = computerTurn(computerscore);
			human_or_computer = 1;
		}
	}
	if(humanscore > 100)
	{
		cout<<"Human won!!!!"<<endl;
	}
	else if(computerscore> 100)
	{
		cout<<"Computer Won!!"<<endl;
	}

    return 0;
}







int random_number()
{
	int num;
	num = (rand()%6)+1; 
	return num;

}
int humanTurn(int humanScore)
{
	cout << "IT'S HUMAN'S TURN!!"<<endl<<"=========================="<<endl;
	
	char choice = 'r' ;
	int num = 0;
	while(choice == 'r' && num != 1 && humanScore < 100)
	{
		num = random_number();
		cout << "Player Score is : "<< num << endl;
		if(num == 1)
		{
			cout<<"Player's Score Reset and Now Human's Turn."<<endl;
			return 0;		
		}
		humanScore += num;
		cout << "Player's Total Score is "<< humanScore<<endl;
		if(humanScore > 100)
		{
			return humanScore;
		}
		cout << "For Roll Again Press: r"<<endl<<"For Hold The Score Press : h"<<endl<<"Your Choice : ";
		cin >> choice;
		
		
	
	}
	
	
	return humanScore;

}
int computerTurn(int computerScore)
{

	cout << "IT'S COMPUTER'S TURN!!"<<endl<<"=========================="<<endl;
	int num = 0;//it hold the random number.
	int tmp = 0;//To check if it is greater than 20
	
	while(tmp < 20 && num != 1 && computerScore < 100)
	{
		num = random_number();
		cout<<"Computer Score is : "<<num<<endl;
		tmp += num;
		if(num == 1)
		{
			cout<<"Computer's Score Reset and Now Human's Turn."<<endl;
			return 0;
		}
		else if(num != 1)
		{
			computerScore += num;
			cout<<"Computer's Total Score is : "<< computerScore<<endl;
		
		}
	}
	return computerScore;
	
}




















