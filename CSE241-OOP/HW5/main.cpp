#include <iostream>
#include "Gate.h"
#include <vector>
#include <fstream>
#include <typeinfo>
using namespace std;
//===================================================//
//for reads input and circuit files
int read_input(vector <vector<int>> &data_variables);
int read_circuit(vector <vector<string>> &gates_names_and_datas);
//===================================================//
//function created to perform necessary operations
void update_data_2(Gate **data,int size,int check_flip_flop);
//===================================================//
//prints outputs
void print_output(Gate **data,int size);
//===================================================//
//it detects the former out value
void detect_former_out(Gate **data,int total_count);
int main()
{
    int circuit_number = 0;
    int gate_number = 0;


    vector <vector<int>> data_variables;    
    vector <vector<string>> gates_names_and_datas;//Holds the data inside the input and circuit file

    circuit_number = read_input(data_variables);
    gate_number = read_circuit(gates_names_and_datas);



//===============================================================//
 //vector <vector<string>> gates_names_and_datas; -> ınput a1 a2 a3 a4
 //                                               -> output b1 b2 b3 b4
 //vector <vector<int>> data_variables; -> 1 0 1 0
 //                                     -> 1 1 1 1
    Gate *check[circuit_number][1000];// Created Gate array
    int i;
    int loc = 0;//holds number of lines in input txt
    int total_count;//holds number of element in circuit txt 
    for(auto x :data_variables)
    {
       i=0;
       total_count = 0;
       //The necessary assignments from the vector file are made into the gates array.
        for(auto y: gates_names_and_datas)
        {
            if(y[0]=="INPUT")
            {
                for(auto z : y)
                {
                    if(z!= "INPUT")
                    {
                        check[loc][total_count] = new Input(z,x[i]);
                        total_count++;
                        i++;
                    }
                }
            }
            else if(y[0] == "OUTPUT")
            {
                for(auto z : y)
                {
                    if(z!="OUTPUT")
                    {
                        check[loc][total_count] = new Output(z);
                        total_count++;
                    }
                }
            }
            else if(y[0] == "AND")
            {
                check[loc][total_count] = new And(y[3],y[2],y[1]);
                total_count++;
            }
            else if(y[0] == "OR")
            {
                check[loc][total_count] = new Or(y[3],y[2],y[1]);
                total_count++;
            }
            else if(y[0] =="NOT")
            {
                check[loc][total_count] = new Not(y[2],y[1]);
                total_count++;
            }
            else if(y[0]=="DECODER")
            {
                check[loc][total_count] = new Decoder(y[1],y[2],y[3],y[4],y[5],y[6]);
                total_count++;
            }
            else if(y[0]== "FLIPFLOP")
            {
                
                
                    check[loc][total_count] = new Flipflop(y[2],y[1]);
                    total_count ++;
                
            }
        }
        loc++;
    }
    int total_size = total_count;

    for(int x = 0 ; x<loc ; x++)//The number of lines in the input txt is processed as much as the number of lines.
    {   
        if(x!= 0)
        {
            for(int y = 0 ; y < total_size; y++)
            {

                if(check[x][y]->get_type()=="Flipflop")
                {
                    check[x][y]->set_former_out(check[x-1][y]->get_output_value());//finds former out
                }
            }
        }
        update_data_2(check[x],total_size,x);//necessary actions are taken
        print_output(check[x],total_size);//prints the outputs
    }
    return 0;
}
/*
    00->INPUT
    01->a
    02->b
*/
void update_data_2(Gate **data,int size,int check_flip_flop)
{

    for(int i = 0 ;i<size ; i++)
    {

        if(data[i]->get_type() != "Input")
        {
            if(data[i]->get_type() =="Not")
            {
                for(int j = 0 ; j<size ; j++)
                {
                    if(data[j]->get_type() == "Input")
                    {
                        if(data[i]->get_name_1() == data[j]->get_name_1())
                        {
                            data[i]->set_value_1(data[j]->get_value_1());
                            data[size] = new Input(data[i]->get_output_name(),data[i]->evaluation());
                            size++;
                            break;
                        }
                    }
                }
            }
            else if(data[i]->get_type() == "Flipflop")
            {
                for(int j = 0 ; j< size ;j++)
                {
                    if(data[j]->get_type() == "Input")
                    {
                        if(data[i]->get_name_1() == data[j]->get_name_1())
                        {
                            data[i]->set_value_1(data[j]->get_value_1());
                            data[size] = new Input(data[i]->get_output_name(),data[i]->evaluation());
                            size++;
                            break; 
                        }
                    }
                }
            }
            else if(data[i]->get_type() == "Decoder")
            {
                for(int j = 0 ;j<size ;j++)
                {
                    if(data[j]->get_type() == "Input")
                    {
                        if(data[i]->get_name_1() == data[j]->get_name_1())
                        {
                            data[i]->set_value_1(data[j]->get_value_1());
                        }
                        if(data[i]->get_name_2() == data[j]->get_name_1())
                        {
                            data[i]->set_value_2(data[j]->get_value_1());
                        }
                    }  
                }
                if(data[i]->get_value_1() != -1)
                {
                    if(data[i]->get_value_2() != -1)
                    {
                        data[i]->evaluation();

                        data[size] = new Input(data[i]->get_output_name(),data[i]->get_output_value());
                        size++;

                        data[size] = new Input(data[i]->get_output_name_2(),data[i]->get_output_value_2());
                        size++;

                        data[size] = new Input(data[i]->get_output_name_3(),data[i]->get_output_value_3());
                        size++;

                        data[size] = new Input(data[i]->get_output_name_4(),data[i]->get_output_value_4());
                        size++;
                        
                    }
                }
            }
            else if(data[i]->get_type() == "Output")
            {
                for(int j = 0 ; j<size ;j++)
                {
                    if(data[j]->get_type() == "Input")
                    { 
                        if(data[i]->get_name_1() == data[j]->get_name_1())
                        {
                            data[i]->set_value_1(data[j]->get_value_1());
                        }
                    }
                }
            }
            else if(data[i]->get_type()!= "Output")//and or 
            {
                for(int j = 0 ; j<size ; j++)
                {
                    if(data[j]->get_type() == "Input")
                    {
                        if(data[i]->get_name_1() == data[j]->get_name_1())
                        {
                            data[i]->set_value_1(data[j]->get_value_1());
                        }
                        if(data[i]->get_name_2() == data[j]->get_name_1())
                        {
                            data[i]->set_value_2(data[j]->get_value_1());
                        }
                    }
                }
                if(data[i]->get_value_1() != -1 )
                {
                    if(data[i]->get_value_2() != -1)
                    {
                        data[i]->evaluation();
                        data[size] = new Input(data[i]->get_output_name(),data[i]->get_output_value());
                        size++;  
                    }
                }
            }
        }
    }
    for(int i = 0 ; i<size ;i++)
    {
        if(data[i]->get_type() == "Output")
        {
            for(int j = 0 ; j < size ; j++)
            {
                if(data[i]->get_name_1() == data[j]->get_name_1())
                {
                    data[i]->set_value_1(data[j]->get_value_1());
                }
            } 
        }
    }
}
int read_input(vector <vector<int>> &data_variables)
{
    
    ifstream FILE("input.txt"); // tmp -> 0 1 1 1
    string tmp;
    int x;
    int count = 0;
    vector <int> vector_1d;
    while(getline(FILE,tmp))
    {
        for(int i = 0 ; i<tmp.length();i++)
        {
            if(tmp[i] != ' ')
            {
                x = tmp[i] - '0';
                vector_1d.push_back(x);
            }
        }
        data_variables.push_back(vector_1d);
        vector_1d.clear();
        count++;
    }
    return count;
}
int read_circuit(vector <vector<string>> &gates_names_and_datas)
{
    vector <string> vec_1d;
    string tmp_1;
    string tmp = "";
    ifstream FILE("circuit.txt");
    int count = 0;
    while(getline(FILE,tmp_1))
    {
        for(auto x : tmp_1) // -> INPUT a b c d
        {
            if(x != ' ')
            {
                tmp+= x;
            }
            else
            {
                vec_1d.push_back(tmp);
                tmp ="";
            }
        }
        vec_1d.push_back(tmp);
        gates_names_and_datas.push_back(vec_1d);
        vec_1d.clear();
        tmp ="";
        count++;
        
    }

    return count;
}
void print_output(Gate **data,int size)
{
    for(int i = 0 ; i<size ;i++)
    {
        if(data[i]->get_type() == "Output")
        {
            cout<<data[i]->get_value_1()<<" ";
        }
    }
    cout<<"\n";
}