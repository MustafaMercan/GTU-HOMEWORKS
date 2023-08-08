#include <stdio.h>
#include <string.h>
#define max 250
void read_file(char *str , char *file_name);
void recursive_function(char *str , int loc , int count , FILE *dosya2);
void counter_function(char tmp, int *count);
void print_element(char tmp, int count, int step,FILE *dosya2);

int main()
{
	FILE *dosya2;
	char file_name[50] = "input.txt";
	char str[max];
	int loc = 0;
	int count = 0;
	dosya2= fopen("output.txt","w+");
	read_file(str,file_name);
	recursive_function(str,loc,count,dosya2);
	fclose(dosya2);
	return 0;

}
void recursive_function(char *str , int loc, int count, FILE *dosya2)/*function to perform operations*/
{
	if(loc != strlen(str))
	{
		counter_function(str[loc],&count);
		if(str[loc] != '(' && str[loc] != ')' && str[loc] != ',')
		{
			print_element(str[loc],count,0,dosya2);
			loc++;
			recursive_function(str,loc,count,dosya2);
		}
		else
		{
			loc++;
			recursive_function(str,loc,count,dosya2);
		}
	}
	
}
void print_element(char tmp, int count, int step,FILE *dosya2)/*function created to print*/
{
	if(count != step)
	{
		fprintf(dosya2,"-");
		print_element(tmp,count,step+1,dosya2);
	}
	else if(count == step)
	{
		fprintf(dosya2,"%c\n",tmp);
	}
}
void counter_function(char tmp, int *count)/*function that determines sets*/
{
	if(tmp == '(')
		*count = *count + 1;
	else if(tmp == ')')
		*count = *count - 1 ;

}
void read_file(char *str, char *file_name)/*file reading function*/
{
	FILE *dosya1;
	dosya1 = fopen(file_name,"r");
	fscanf(dosya1,"%s",str);
	fclose(dosya1);
}
