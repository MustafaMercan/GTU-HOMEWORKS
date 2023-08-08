#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

int char_to_int(char x);
char int_to_char(int x);
string reverse_number(string str);//reversing the string
string fill_with_0(string num,int size);//It fills the array with 0 so that operations can be done more easily.
string sum_process(string num1,string num2);//performs the collection as desired



int main()
{
	string num1,num2,sum;//for input values
	int i;
	int choice=1;//to see if the user can continue
	do
	{
		cout<< "Enter First Number  : ";
		cin>>num1;
		cout<<"Enter Second Number : ";
		cin>>num2;
		
		int size1 = num1.length();
		int size2 = num2.length();
		int size3;
		
		
		num1 = reverse_number(num1);
		num2 = reverse_number(num2);
		
		if(size1 > size2)
		{
			num2 = fill_with_0(num2,size1-size2+1);
			num1 = num1 + '0';
		}
		else if(size2 > size1)
		{
			num1 = fill_with_0(num1,size2-size1+1);
			num2 = num2 + '0';
		}
		else
		{
			num2 = num2 + '0';
			num1 = num1 + '0';
		}
		
	
		sum = sum_process(num1,num2);
		if(sum[0] == '0')
		{
			cout <<"Result: ";
			size3 = sum.length();
			for(i=1;i<size3;i++)
				cout<<sum[i];
			cout<<endl;
		}	
		else
			cout <<"Result:"<< sum << endl;
		cout<<"For continue press 1:"<<endl<<"For Exit Press 2:";
		cin>>choice;
		
	}while(choice==1);
	
	

    
}
string sum_process(string num1,string num2)
{
	int size1 = num1.length();
	int size2 = num2.length();
	string str;
	string last_version;
	int tmp_last=0;
	int index;
	int i;

	
	
	char tmp_sum;
	char tmp_dec;
	
	int num_1,num_2,tmp=0;
	int sum=0;
	
	if(size1 > size2)
		index = size1;
	else
		index = size2;
		
	for(i=0 ; i<index ; i++)
	{

		num_1 = char_to_int(num1[i]);
		num_2 = char_to_int(num2[i]);
		sum = num_1 + num_2 + tmp_last;
		if(sum > 9)
		{
			tmp = sum % 10;
			tmp_last = sum / 10;
			tmp_dec = int_to_char(tmp);
			str[i] = tmp_dec;
			
		}
		else 
		{
			tmp_sum = int_to_char(sum);
			str[i] = tmp_sum;
			tmp_last = 0;
		}
		last_version = last_version + str[i];
		
	}
	last_version = reverse_number(last_version);
	return last_version;
	

}
int char_to_int(char x)
{
	int num;
	num = x - '0';
	return num;
}
char int_to_char(int num)
{
	char x;
	x = num + '0';
	return x;


}
string reverse_number(string str)
{
	int size = str.length()-1;
	int i=0;
	for(i = 0; i<size ; i++,size--)
	{
		swap(str[i],str[size]);
	}
	return str;
}
string fill_with_0(string num,int size)
{
	int i;
	for(i=0 ; i < size ; i++)
	{
		num = num + '0';
	}
	return num;

}











