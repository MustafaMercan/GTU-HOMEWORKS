#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
double read_polynom(double num,char *str);
int main()
{

	FILE *dosya1,*dosya2,*dosya3;	
	char polynom[SIZE];
	double num;
	dosya1 = fopen("values.txt","r");
	dosya2 = fopen("polynomial.txt","r");
	dosya3 = fopen("evaluations.txt","w+");
	if(dosya1 == NULL || dosya2 == NULL || dosya3 == NULL)
	{
		printf("Error!\n");
		exit(1);
	}
	fscanf(dosya2,"%s",polynom);/* reading polynomial */
	while(fscanf(dosya1,"%lf",&num) != -1 )
	{
		fprintf(dosya3,"%lf\n",read_polynom(num,polynom));/* printing to file after operation */
	}

	




	return 0;
}
double read_polynom(double num,char *str)/*reads the polynomial and splits it into parts*/
{
	int i;
	int j=0,l=0,n=0,m=0,x=0;
	double sum = 0;
	double tmp1;
	double tmp2;
	double tmp3=0;
	char efficent[SIZE][10];
	char pow_str[SIZE][10];
	char sign[SIZE];
	int flag = 0;
	for(i=0;i<SIZE;i++)
	{
		strcpy(efficent[i],"0");
		strcpy(pow_str[i],"0");
	}
	for(i=0;i<strlen(str) + 1 ;i++)
	{
		if(((str[i] <= '9' && str[i] >= '0') || str[i] == '.') && str[i] != '^' && flag == 0 )
		{
			efficent[l][j] = str[i];
			j++; 
		}
		else if(str[i] == 'x')
		{
			l++;
			j=0;
		}
		else if(str[i] == '^')
		{
			flag = 1;
		}	
		else if(flag)
		{
			if(str[i] == '+' || str[i] == '-' || str[i] == '\0')
			{
				flag = 0;
				n++;
				sign[x] = str[i];
				x++;
				m=0;
			}
				
			if(flag)
			{
				pow_str[n][m] = str[i];
				m++;
			}
		}
		else if(str[i] == '+' || str[i] == '-')
		{
			n++;
			sign[x] = str[i];
			x++;
			
		}	
			
	}
	for(i=0;i<l;i++)/*Transactions are made after the separation process is completed*/
	{
		tmp3 = 0;
		sscanf(efficent[i],"%lf",&tmp1);
		sscanf(pow_str[i],"%lf",&tmp2);
		if(tmp2 == 0 && tmp1 == 0)
		{
			tmp3 += num;
		}
		else if(tmp2 == 0 && tmp1 != 0)
		{
			tmp3+=tmp1*num;
		}
		else if(tmp2 != 0 && tmp1 == 0)
		{
			tmp3+=pow(num,tmp2);
		}
		else
		{
			tmp3+= pow(num,tmp2);
			tmp3*=tmp1;
		}
		
		if(sign[i-1] == '-')
			tmp3 = tmp3  * -1;

		sum+=tmp3;
		

	}

	return sum;
	
	
	






}

















