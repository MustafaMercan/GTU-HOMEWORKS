#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;
int random_number(int step);
string create_number(int size,int num[]);//to generate a random number
char int_to_char(int num);//int to convert a variable to char
bool check_size(string str);//	to check the size of the number entered by the user and the size of the secret number
bool check_digit_of_number(int number[],int size,int tmp);//to check for unique number
//============================================================//
void start_game(string number,string number_of_digit);//for -r parameter
int char_to_int(string num);//char to convert a variable to int
int count_1(string number,string input_user_number);//For C exact
int count_2(string number,string input_user_number);//For C misplaced
//============================================================//
void start_game_2(string number);//for -u parameter
bool check_u_valid_value(string number);//to check unique , first digit 0 and negative value
//===========================================================//
bool check_negative_and_zero(string number);//to check zero and negative
void check_parameter_vs(int argc , char **argv);//to check parameters
//===========================================================//
int string_to_int(string num);//to string to convert a variable int
//==========================================================//
void check_int_or_not(string num);//To check if an integer value

int main(int argc, char **argv)
{
	srand((int)time(0));


	string number_of_digit;
	string number;
	int number_digit;
	int digit_of_number[10];
	int size;
	bool valid_or_invalid;
	string parameter = argv[1];
	string parameter_1 = "-r";
	string parameter_2 = "-u";
	
	
	check_parameter_vs(argc,argv);
	if(parameter == parameter_1)
	{
		number_of_digit = argv[2];
		valid_or_invalid = check_size(number_of_digit);
		check_int_or_not(number_of_digit);
		if(!valid_or_invalid)
		{
			cout<<"E0"<<endl;
			exit(1);
		}
		else
		{
			number_digit = char_to_int(number_of_digit);
			number = create_number(number_digit,digit_of_number);//str
			start_game(number,number_of_digit);
		}
		
	}
	else if(parameter == parameter_2)
	{
		number = argv[2];
		number_of_digit;
		start_game_2(number);
	}

	return 0;
}
void check_int_or_not(string num)//To check if an integer value
{
	int i = 0;
	int size;
	size = num.length();
	for(i=0;i<size;i++)
	{
		if(num[i] < '0' || num[i] > '9' )
		{
			cout<<"E2"<<endl;
			exit(1);
		}
	}


}
void check_parameter_vs(int argc , char **argv)//to check parameters
{
	string number = argv[2];
	string parameter = argv[1];
	string parameter_1 = "-r";
	string parameter_2 = "-u";
	bool check_valid;
	check_valid = check_negative_and_zero(number);
	
	if(argc != 3)
	{
		cout<<"E0"<<endl;
		exit(1);
	}
	else if(!check_valid)
	{
		cout<<"EO"<<endl;
		exit(1);
	}
	else if(parameter != parameter_1 && parameter != parameter_2)
	{
		cout<<"E0"<<endl;
		exit(1);
	}
}
bool check_negative_and_zero(string number)//to check zero and negative
{
	if(number[0] == '0' || number[0] == '-')
	{
		return false;
	}
	return true;
}
void start_game_2(string number)//for -u parameter
{
	
	bool check_num;
	string input_user_number;
	int count_exact;
	int count_misplace;
	bool check_negative_zero;
	check_int_or_not(number);
	
	int count = 0;
	
	check_num = check_u_valid_value(number);//E0 error.
	
	if(check_num)
	{
		while(input_user_number != number)
		{
			cin>>input_user_number;
			check_int_or_not(input_user_number);
			check_num = check_u_valid_value(input_user_number);
			if(check_num != true)
			{
				cout<<"E0"<<endl;
				exit(1);
			}
			check_negative_zero = check_negative_and_zero(input_user_number);
			if(input_user_number.length() != number.length())
			{
				cout<<"E1"<<endl;
				exit(1);
			}
			if(!check_negative_zero)
			{
				cout<<"E0"<<endl;
				exit(1);
			}
			count++;
			count_exact = count_1(number,input_user_number);
			count_misplace = count_2(number,input_user_number);
			if(input_user_number == number)
			{
				cout<<"FOUND "<<count<<endl;
				exit(1);
			}
			else if(count == 100)
			{
				cout<<"Failed"<<endl;
				exit(1);
			}
			cout<<count_exact<<" "<<count_misplace<<endl;
		}
	}
	else
	{
		cout<<"E0"<<endl;
		exit(1);
	}





}
bool check_u_valid_value(string number)//to check unique , first digit 0 and negative value
{
	int i,j;
	int size = number.length();
	if(number[0] == '-' || number[0] == '0')
	{
		return false;
	}
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(number[i] == number[j])
				return false;
		}
	}
	return true;



}
void start_game(string number,string number_of_digit)//for -r parameter
{
	
	
	int size_of_digit;
	int size;
	int count = 1;
	int count_exact;
	int count_misplace;
	int check = 1;
	bool check_number;
	
	
	string input_user_number;
	
	cin>>input_user_number;
	check_number = check_u_valid_value(input_user_number);
	check_int_or_not(input_user_number);
	if(check_number != true)
	{
		cout<<"E0"<<endl;
		exit(1);
	}
	size_of_digit = char_to_int(number_of_digit);
	size = input_user_number.length();
	int invalid_or_valid;
	
	if(size != size_of_digit)
	{
		cout<<"E1"<<endl;
		exit(1);
	}
	else
	{
		while(input_user_number != number )
		{
			
			if(number.length() != input_user_number.length())
			{
				cout<<"E1"<<endl;;
				exit(1);
			}
			else if(input_user_number != number)
			{
				//count++;
				count_exact = count_1(number,input_user_number);
				count_misplace = count_2(number,input_user_number);
				cout<<count_exact<<" "<<count_misplace<<endl;
			}
			if(count == 100)
			{
				cout<<"Failed"<<endl;
				exit(1);
			}
			cin>>input_user_number;
			count++;
			check_number = check_u_valid_value(input_user_number);
			check_int_or_not(input_user_number);
			if(check_number != true)
			{		
				cout<<"E0"<<endl;
				exit(1);
			}
			
		}
		cout<<"Found "<<count<<endl;
		exit(1);

	}




}
int count_2(string number,string input_user_number)//For C misplaced
{
	int size = number.length();
	int i,j;
	int count = 0;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if((i != j) && (number[i] == input_user_number[j]))
				count++;
		}
	}
	return count;
}
int count_1(string number,string input_user_number)//For C exact
{
	int size = number.length();
	int i;
	int count = 0;
	for(i=0;i<size;i++)
	{
		if(number[i] == input_user_number[i])
		{
			count++;
		}
	}
	return count;

}
int char_to_int(string num)//char to convert a variable to int
{
	int tmp;
	int size = num.length();
	if(size == 2)
		return 10;
	else
	{
		tmp = num[0] - '0';
	}
	return tmp;
}

string create_number(int size,int num[])//to generate a random number
{
	int i;
	string number;
	int tmp;
	char digit;
	bool check;
	for(i=0;i<size;i++)
	{
		back:
		tmp = random_number(i);
		num[i]=tmp;
		check = check_digit_of_number(num,i,tmp);
		if(check)
		{
			digit = int_to_char(tmp);
			number = number+digit;		
		}
		else
		{
			goto back;
		}
	}
	return number;
	
	
}
bool check_digit_of_number(int number[],int size,int tmp)//to check for unique number
{
	int i;
	int count = 0;
	for(i=0;i<=size;i++)
	{
		if(tmp == number[i])
		{
			count++;
		}
	}
	if(count > 1)
	{
		return false;
	}
	return true;
}
char int_to_char(int num)//int to convert a variable to char
{
	char digit;
	digit = num + '0';
	return digit;
}
bool check_size(string str)//	to check the size of the number entered by the user and the size of the secret number
{
	int size = str.length();

	if(size > 1 && str[1] != '0')
		return false;

	return true;
}
int random_number(int step)
{
	int num;
	if (step==0)
	{
		num = (rand()%9) + 1; 
	}
	else
		num = (rand()%10);
	
	return num;

}
