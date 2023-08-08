#include <stdio.h>
/*Mustafa Mercan 1901042676*/


int find_digit(int num);/*function created to find the number of digits of a number*/

int main()
{
	FILE *dosya1;
	dosya1 = fopen("file.txt","r+");
	int num;
	int tmp;
	int count ;
	int digit;
	int i ;
	int flag = 0;

	if(dosya1 == NULL)
		printf("Error!\n");

	while(fscanf(dosya1,"%d",&num)!= -1)
	{
		count = ftell(dosya1);
		fseek(dosya1,0,SEEK_SET);/*for the program to return to the beginning when the process starts again.*/
		while(fscanf(dosya1,"%d",&tmp)!= -1)
		{
			if(num == tmp)
			{
				flag++;
				if(flag >= 2)/*It was created so that there is no error when checking the same number at first*/
				{
					fseek(dosya1, -find_digit(num) , SEEK_CUR);
					for(i=0;i<find_digit(num);i++)/*to put as many spaces as the number of digits*/
					{
						fputs(" ",dosya1);
					}			
				}
	
			}
				
		}
		flag = 0;
		fseek(dosya1,count,SEEK_SET);
	}
}

int find_digit(int num)
{
	int count = 0;
	if(num < 0)/*if the number is negative it adds one to the number of digits*/
		count++;
	
	while(num != 0 )
	{
		num /= 10;
		count++;
	}
	return count;
}




























