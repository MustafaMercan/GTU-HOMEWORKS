#include <stdio.h>
#include <string.h>

double price_of_the_object(char* object_main);
int buffer_number_or_not(char *str);
double string_to_double(char *str);
void divide_string(char *str,int *number,char name_object[][15],int *number_of_parts);
int string_to_int(char *str);
void empty_array(char str[]);
void divide_two_part(char tmp_str[],int *number,char name_object[][15],int loc);

int main()
{
	char object[100];
	printf("Define the object?: ");scanf("%[^\n]%*c", object);
	printf("Total cost of %s is %lf",object,price_of_the_object(object));
	return 0;
}
double price_of_the_object(char* object_main)
{
	char str[100];
	int i;
	int number[25];
	char name_object[25][15];
	int number_of_parts;
	double total = 0.0;
	double price;
	printf("What's the %s?: \n",object_main);
	scanf("%[^\n]%*c", str);
	
	if(buffer_number_or_not(str) == 1)
	{
		divide_string(str,number,name_object,&number_of_parts);
		for(i=0;i<number_of_parts;i++)
		{
			price = price_of_the_object(name_object[i]);
			total = total + number[i]*price;
		}
		return total;
	}
	else if(buffer_number_or_not(str) == 0)
	{
		return string_to_double(str);
	}
	

}
void divide_string(char *str,int *number,char name_object[][15],int *number_of_parts)/*Built-in function to separate input from + signs */
{
	int i =0;
	char tmp;
	char tmp_str[100];
	int l=0;
	int loc = 0;
	int count = 0;
	tmp = str[i];
	while(tmp!='\0')
	{
		if(tmp == '*')
		{
			count++;
		}
			
		if(tmp == '+')
		{
			l=0;
			divide_two_part(tmp_str,number,name_object,loc);/*Built-in function to split input into two parts*/
			loc++;
			empty_array(tmp_str);

		}
		else if(tmp != ' ')
		{
			tmp_str[l] = tmp;
			l++;

		}		
		i++;
		tmp = str[i];
	}
	l++;
	divide_two_part(tmp_str,number,name_object,loc);
	*number_of_parts = count;
}

void divide_two_part(char tmp_str[],int *number,char name_object[][15],int loc)
{
	char *symbol;
	symbol = strtok(tmp_str,"*");
	number[loc] = string_to_int(symbol);
	symbol = strtok(NULL,"*");
	strcpy(name_object[loc],symbol);
}

void empty_array(char str[])/*built function to empty string array*/
{
	int i =0;	
	char tmp = '\0';
	for(i=0;i<20;i++)
		str[i] = tmp;

}

int buffer_number_or_not(char *str)/*Checks if input is a number*/
{
	int count = 0;
	int i = 0;
	char tmp;
	for(i=0;i<strlen(str);i++)
	{
		tmp = str[i];
		if(tmp == '*')
			count ++;
	}
	if(count != 0)
		return 1;
	else
		return 0;

}
double string_to_double(char *str)/*Built-in function to convert string to double*/
{
	double num;
	sscanf(str,"%lf",&num);
	return num;
}
int string_to_int(char *str)/*Built-in function to convert string to integer*/
{
	int num;
	sscanf(str,"%d",&num);
	return num;
}













