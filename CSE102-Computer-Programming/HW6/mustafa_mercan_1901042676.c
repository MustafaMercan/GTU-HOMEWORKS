#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int former_out= 0;
struct information_data{
	
	char element_name[10][50];
	char process[50];
	int values[10];
};

int number_of_circuit(FILE *dosya1);
int number_of_element(char *circuit_data);
void read_file_input(FILE *input_txt,struct information_data *data);
void read_circuit_txt(struct information_data *data,char *input_value);
void fill_data(struct information_data *data,char *circuit_data,int count);
void decide_process(struct information_data *data,int count,char *input_value);
void str_to_int(char *input_value,int *input);
void update_new_data_except_flipflop_and_not(struct information_data *data,int count,int size);


int main()
{

	FILE *dosya1,*dosya2;
	struct information_data *data;
	int count = 0;
	dosya1 = fopen("circuit.txt","r");
	dosya2 = fopen("input.txt","r");
	count = number_of_circuit(dosya1);
	data = (struct information_data*)malloc(count * sizeof(struct information_data));
	for(int i = 0;i<count;i++)
	{	
		for(int j = 0;j<10;j++)
		{
			data[i].values[j]=-99;
		}

	}
	read_file_input(dosya2,data);
	fclose(dosya1);
	fclose(dosya2);
	free(data);
	



	return 0;



}
void read_file_input(FILE *input_txt,struct information_data *data)/*Reading data from input file*/
{
	char input_value[100];
	while(fscanf(input_txt,"%[^\n]%*c",input_value) != -1)
	{
		
		read_circuit_txt(data,input_value);
		
		
	}
}
void read_circuit_txt(struct information_data *data,char *input_value)/*Reading data from circuit file*/
{
	char circuit_data[100];
	FILE *circuit_txt;
	int count = 0;
	int size;
	circuit_txt = fopen("circuit.txt","r");
	while(fscanf(circuit_txt,"%[^\n]%*c",circuit_data) != -1)
	{
		
		size = number_of_element(circuit_data);
		fill_data(data,circuit_data,count);
		decide_process(data,count,input_value);
		count++;
	}
	count--;
	former_out = data[count].values[0];
	printf("%d\n",data[count].values[0]);

}
void decide_process(struct information_data *data,int count,char *input_value)/*determines what action to take*/
{
	int i = 0;
	int number_input;
	int *input; 
	if(strcmp(data[count].process,"INPUT") == 0)
	{
		number_input = number_of_element(input_value)+1;
		input = (int *) malloc(number_input * sizeof(int));
		str_to_int(input_value,input);
		for(i=0;i<number_input;i++)
		{
			data[count].values[i] = input[i];
			
		}
		
	}
	else if(strcmp(data[count].process,"AND") == 0)
	{
		update_new_data_except_flipflop_and_not(data,count,3);
		if(data[count].values[1] == 1 && data[count].values[2] == 1)
		{
			data[count].values[0] = 1;
		}
		else if(data[count].values[1] == 0 || data[count].values[2] == 0)
		{
			data[count].values[0] = 0;
		}

	}
	else if(strcmp(data[count].process,"OR") == 0)
	{
		update_new_data_except_flipflop_and_not(data,count,3);
		if(data[count].values[1] == 1 || data[count].values[2] == 1)
		{
			data[count].values[0] = 1;
		}
		else if(data[count].values[1] == 0 && data[count].values[2] == 0)
		{
			data[count].values[0] = 0;
		}
	}
	else if(strcmp(data[count].process,"NOT") == 0)
	{
		update_new_data_except_flipflop_and_not(data,count,2);
		if(data[count].values[1] == 1)
		{
			data[count].values[0] = 0;
		}
		else if(data[count].values[1] == 0)
		{
			data[count].values[0] = 1;
		}
	}
	else if(strcmp(data[count].process,"FLIPFLOP") == 0)
	{
		update_new_data_except_flipflop_and_not(data,count,2);
		if(data[count].values[1] == former_out)
		{
			data[count].values[0] = 0;
		}
		else if(data[count].values[1] != former_out)
		{
			data[count].values[0] = 1;
		}
	}
}
void str_to_int(char *input_value,int *input)/*converts str expression to int expression*/
{
	int i;
	int tmp;
	int size = strlen(input_value);
	int j = 0;
	for(i=0;i<size;i++)
	{
		if(input_value[i] != ' ')
		{
			input[j] = input_value[i] - '0';
			j++;
		}
	}
}
void update_new_data_except_flipflop_and_not(struct information_data *data,int count,int size)/*compares current expression with previous ones*/
{
	/*In the name of the function it says flip_flop and not included but they are also*/
	int i = 0;
	int j=0;
	int l=0;
	for(i=0;i<count;i++)
	{
		while(data[i].values[j] != -99)
		{
			for(l=1;l<size;l++)
			{
				if(strcmp(data[i].element_name[j],data[count].element_name[l]) == 0)
				{
					data[count].values[l] = data[i].values[j];
				
				}
			}
			
			j++;
		}
		j=0;
	}
}
void fill_data(struct information_data *data,char *circuit_data,int count)/*saves data to struct*/
{
	int size = strlen(circuit_data);
	int i;
	int j=0;
	int l=0;
	int flag = 1;
	int number_element = number_of_element(circuit_data);
	for(i=0;i<size;i++)
	{
		if(circuit_data[i] != ' ' && flag == 1)
		{
			data[count].process[j] = circuit_data[i];
			j++;
		}
		else if(circuit_data[i] == ' ' && flag == 1)
		{
			j=0;
			flag = 0;
		}
		else if(circuit_data[i] != ' ' && flag == 0)
		{
			data[count].element_name[l][j] = circuit_data[i];
			j++;
		}
		else if(circuit_data[i] == ' ' && flag == 0)
		{
			l++;
			j=0;
		}
	}	
}
int number_of_element(char *circuit_data)/*determines the number of elements*/
{
	int i = 0;
	int count = 0;
	int size = strlen(circuit_data);
	for(i=0;i<size;i++)
	{	
		if(circuit_data[i] == ' ')
		{
			count++;
		}

	}
	return count;
}
int number_of_circuit(FILE *dosya1)/*Determines the number of elements in the circuit file*/
{
	char *tmp;
	int count = 0;
	tmp = (char *)malloc(100*sizeof(char));
	while(fscanf(dosya1,"%[^\n]%*c",tmp) != -1)
	{
		count++;
	}
	free (tmp);
	return count;
}
