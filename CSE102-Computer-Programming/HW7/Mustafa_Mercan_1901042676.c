#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void read_file(FILE *dosya1 , int data[][512], int *L);
void detect_island(int i,int j,int data[][512],int L,int step,int check);
int check_cordinate(int i, int j);
//Sir, my program is working, but there may be some delay when there is too much data.
int main()
{
	
	int data[512][512];
	int i= 0,j=0;
	int L = 0;
	int flag = 1;
	int check ;
	FILE *dosya1,*dosya2;
	FILE *dosya3;
	dosya3 = fopen("tmp.txt","w+");//Opens file to hold coordinates
	dosya1 = fopen("input.txt","r");//Opens the input file
	dosya2 = fopen("output.txt","w+");//Opens the output file	
	fclose(dosya2);
	fclose(dosya3);
	read_file(dosya1,data,&L);
	fclose(dosya1);
	for(i=0;i<512;i++)
	{
		for(j=0;j<512;j++)
		{
			check = check_cordinate(i,j);
			detect_island(i,j,data,L,0,check);
		}
	}
	remove("tmp.txt");
	return 0;
}
int check_cordinate(int i, int j)//checking if the coordinate has already been evaluated
{
	FILE *dosya1;
	int x,y;
	int flag = 1;
	dosya1 =fopen("tmp.txt","r");
	while(fscanf(dosya1,"%d %d",&y,&x) != -1)
	{
		if(y == i && x == j)
		{
			flag = 0;
		}
	}
	fclose(dosya1);
	return flag;

}
void detect_island(int i,int j,int data[512][512],int L,int step,int check)
{
	int check_right,check_down,check_left,check_up;
	FILE *dosya3;
	FILE *output;
	if(check == 1 && data[i][j] > L)
	{
		dosya3 = fopen("tmp.txt","a+");
		step++;
		if(step == 1)//prints the coordinate in the output file 
		{
			output = fopen("output.txt","a+");
			fprintf(output,"%d %d \n",j,i);
			fclose(output); 
		}
		fprintf(dosya3,"%d %d\n",i,j);
		fclose(dosya3);
		if(i>0 && i<511 && j>0 && j<511)//allows you to act according to the situation
		{
		
			check_right = check_cordinate(i,j+1);
			check_down = check_cordinate(i+1,j);
			check_left = check_cordinate(i,j-1);
			check_up = check_cordinate(i-1,j);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
			if(check_left == 1 && data[i][j-1] > L)
			{	
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}
		}
		else if(i == 0 && j != 511 && j != 0)
		{
			check_right = check_cordinate(i,j+1);
			check_down = check_cordinate(i+1,j);
			check_left = check_cordinate(i,j-1);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
			if(check_left == 1 && data[i][j-1] > L)
			{
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}			
		}
		else if(j == 0 && i != 0 && i!= 511)
		{
			check_right = check_cordinate(i,j+1);
			check_down = check_cordinate(i+1,j);
			check_up = check_cordinate(i-1,j);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}
		}
		else if(i == 511 && j != 0 && j!= 511)
		{
			check_right = check_cordinate(i,j+1);
			check_left = check_cordinate(i,j-1);
			check_up = check_cordinate(i-1,j);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_left == 1 && data[i][j-1] > L)
			{
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}
		}
		else if(j == 511 && i!= 0 && i != 511)
		{
			check_down = check_cordinate(i+1,j);
			check_left = check_cordinate(i,j-1);
			check_up = check_cordinate(i-1,j);
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
			if(check_left == 1 && data[i][j-1] > L)
			{
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}
		}
		else if(i == 0 && j == 0)
		{

			check_right = check_cordinate(i,j+1);
			check_down = check_cordinate(i+1,j);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
		}
		else if(i == 0 && j == 511)
		{
			
			check_down = check_cordinate(i+1,j);
			check_left = check_cordinate(i,j-1);
			if(check_down == 1 && data[i+1][j] > L)
			{
				check = check_cordinate(i+1,j);
				detect_island(i+1,j,data,L,step,check);
			}
			if(check_left == 1 && data[i][j-1] > L)
			{
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}
		}
		else if(i == 511 && j == 0)
		{
			check_right = check_cordinate(i,j+1);
			check_up = check_cordinate(i-1,j);
			if(check_right == 1 && data[i][j+1] > L )
			{
				check = check_cordinate(i,j+1);
				detect_island(i,j+1,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}

		}
		else if(i == 511 && j == 511)
		{
			check_left = check_cordinate(i,j-1);
			check_up = check_cordinate(i-1,j);
			if(check_left == 1 && data[i][j-1] > L)
			{
				check = check_cordinate(i,j-1);
				detect_island(i,j-1,data,L,step,check);
			}
			if(check_up == 1 && data[i-1][j] > L)
			{
				check = check_cordinate(i-1,j);
				detect_island(i-1,j,data,L,step,check);
			}
		}
	}		
}
void read_file(FILE *dosya1 , int data[][512], int *L)//Reads data from input file
{
	fscanf(dosya1,"%d",L);
	int i=0,j=0;
	while(fscanf(dosya1,"%d",&data[i][j]) != -1)
	{
		j++;
		if(j == 512)
		{
			i++;
			j = 0;
		}

	}

}
