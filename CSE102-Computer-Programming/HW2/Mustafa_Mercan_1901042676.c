#include <stdio.h>
#define SIZE 100
int check_number(FILE *input,int count,int num);
void order_array(int numbers[],int counters[],int size);


int main()
{
	FILE *dosya1,*dosya2;
	dosya1 = fopen("input.txt","r+");
	dosya2 = fopen("output.txt","w+");
	int numbers[SIZE],counters[SIZE];
	int num = 0;
	int x = 1;
	int i = 0;
	int loc = 0;
	int tmp = 0;
	int size;
	int flag;
	if(dosya1 == NULL)
		printf("The file named input.txt could not be found.\n");
	while(fscanf(dosya1,"%d",&num) != -1)
	{
		loc = ftell(dosya1);/*to hold the location inside the txt document*/
		while(fscanf(dosya1,"%d",&tmp)  != -1 )/*to keep numbers inside txt document*/
		{
			if(num == tmp)/*finds the number of repetitions*/
			{
				x++;	
			}
		}
		flag = check_number(dosya1,loc,num);/*adds the number to the array if the required conditions are met*/
		if(flag)
		{
			numbers[i] = num;
			counters[i]=x;
			i++;
		}

		x = 1;/*counter reset*/
		fseek(dosya1,loc,SEEK_SET);

	}
	size = i ;
	order_array(numbers,counters,size); /*sorts the array*/
	for(i=0;i<size;i++)
	{
		fprintf(dosya2,"%d : %d\n",numbers[i],counters[i]);
	}
	fclose(dosya1);
	fclose(dosya2);
	return 0;

}
int check_number(FILE *input,int count,int num)
{
	int x;
	int flag = 1;
	input = fopen("input.txt","r+");
	
	while(fscanf(input,"%d",&x) != -1)
	{
		if(ftell(input) != count && ftell(input) < count)
		{
			if(num == x)
			{
				flag = 0;
			}
		}
	}
	fclose(input);

	return flag;
}
void order_array(int numbers[],int counters[],int size)
{
	int tmp;
	int i;
	int j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(counters[i] < counters[j])
			{
				tmp = counters[i];
				counters[i] = counters[j];
				counters[j] = tmp;
				/*=======================*/
				tmp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = tmp;
			}
			else if(counters[i] == counters[j])
			{
				if(numbers[i] < numbers[j])
				{
					tmp = counters[i];
					counters[i] = counters[j];
					counters[j] = tmp;
					/*=======================*/
					tmp = numbers[i];
					numbers[i] = numbers[j];
					numbers[j] = tmp;
				}
			}
			
		}
	}
}









































