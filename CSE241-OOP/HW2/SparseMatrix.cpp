#include<iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include<string>
#include<tuple>
#include "SparseMatrix.h"
using namespace std;

SparseMatrix :: SparseMatrix()
{

}
SparseMatrix :: SparseMatrix(string file_name)
{
    int loc = 0;
    string mystr;
    ifstream FILE;
    double row_tmp;
    FILE.open(file_name);
    vector <double> index_tmp;
    vector <double> value_tmp;
    vector<vector<vector<double>>> tmp_data;
    while(FILE)//reads the file
    {
        getline(FILE,mystr);
        if(mystr[0] != '\0')
        {
            auto [row_tmp,index_tmp,value_tmp] = separate_string(mystr);//splits the line read from the file into parts
            last_hit_function(row_tmp,index_tmp,value_tmp,data,loc);//adds the split parts to the data inside the class
            loc++;
            mystr.clear();
        }
    }
    
}
SparseMatrix SparseMatrix :: transpose()
{
    SparseMatrix tmp;
    vector<double> row;
    vector<double> v1d;
    vector<vector<double>> v2d;
    int size = data.size();
    int i,j,l;
    int x = 0;
    int y = 1;

    for(i=0;i<size;i++)
    {
        row.push_back(data[i][0][0]);
        v2d.push_back(row);
        row.clear();
        for(j=1;j<data[i].size();j++)
        {
            v1d.push_back(data[i][j][0]);
            v1d.push_back(data[x][y][1]);
            v2d.push_back(v1d);
            v1d.clear();
            x++;
        }
        tmp.data.push_back(v2d);
        v2d.clear();
        y++;
        x=0;
    }
    return tmp;
}
ostream &operator<<(ostream& out, const SparseMatrix& matrix)
{
    int i,j,l;
    for(i=0;i<matrix.data.size();i++)
    {
        for(j=0;j<matrix.data[i].size();j++)
        {
            for(l=0;l<matrix.data[i][j].size();l++)
            {
                if(j==0 && l==0)
                    out<<matrix.data[i][j][l]<<" ";
                else if(l==0)
                    out<<matrix.data[i][j][l]<<":";
                else   
                    out<<matrix.data[i][j][l]<<" ";
            }
        }
        out<<"\n";
    }
    return out;
}
void found_same_row_index(int &loc,double row,SparseMatrix matrix)//finds the position of the sent row in the other matrix
{
    int i;
    for(i=0;i<matrix.data.size();i++)
    {
        if(matrix.data[i][0][0] == row)
        {
            loc = i;
            break;
        }
    }

}
void operator_function(int process_num,SparseMatrix tmp2,SparseMatrix tmp,SparseMatrix matrix,SparseMatrix &result)//performs the necessary action according to the values ​​assigned to the operators
{
    int i;
    int x,y;
    int check;
    int loc_row;
    int flag;
    int location;
    SparseMatrix for_data;
    for_data.data = tmp2.data;

    vector <double> v1d;
    vector <vector<double>> v2d;
    vector <double> row;

    fill_with_zero(tmp2,matrix.data,tmp2);
    fill_with_zero(tmp,for_data.data,matrix);
    for(i=0;i<tmp.data.size();i++)
    {
       check =  check_row_func(i,tmp.data[i][0][0],tmp2);
       if(check == 1)
       {
            row.push_back(tmp.data[i][0][0]);
            v2d.push_back(row);
            row.clear();
            found_same_row_index(loc_row,tmp.data[i][0][0],tmp2);
            for(x=1;x<tmp2.data[loc_row].size();x++)
            {
                for(y=1;y<tmp.data[i].size();y++)
                {
                    if(tmp2.data[loc_row][x][0]== tmp.data[i][y][0] )
                    {
                        flag = 1;
                        location = y;
                        break;
                    }
                }
                if(flag == 1 && process_num == 1)
                {
                    v1d.push_back(tmp2.data[loc_row][x][0]);
                    v1d.push_back(tmp2.data[loc_row][x][1] + tmp.data[i][location][1]);
                    v2d.push_back(v1d);
                    v1d.clear();
                    flag = 0;
                }
                else if(flag==1 && process_num == 2)
                {
                    v1d.push_back(tmp2.data[loc_row][x][0]);
                    v1d.push_back(tmp2.data[loc_row][x][1] - tmp.data[i][location][1]);
                    v2d.push_back(v1d);
                    v1d.clear();
                    flag = 0;                    
                }
                else if(flag==1 && process_num == 3)
                {
                    v1d.push_back(tmp2.data[loc_row][x][0]);
                    v1d.push_back(tmp2.data[loc_row][x][1] * tmp.data[i][location][1]);
                    v2d.push_back(v1d);
                    v1d.clear();
                    flag = 0;     
                }
                
            }
            result.data.push_back(v2d);
            v2d.clear();
       }
    }
    order_function(result);    
}
SparseMatrix SparseMatrix :: operator+(SparseMatrix matrix)
{
    int process_decide = 1;
    SparseMatrix result;
    SparseMatrix tmp = matrix;
    SparseMatrix tmp2;
    tmp2.data = data;
    operator_function(process_decide,tmp2,tmp,matrix,result);
    return result;
}
SparseMatrix SparseMatrix :: operator-(SparseMatrix matrix)
{
    int process_decide = 2;
    SparseMatrix result;
    SparseMatrix tmp = matrix;
    SparseMatrix tmp2;
    tmp2.data = data;
    operator_function(process_decide,tmp2,tmp,matrix,result);
    return result;
}
SparseMatrix SparseMatrix :: operator*(SparseMatrix matrix)
{
    int process_decide = 3;
    SparseMatrix result;
    SparseMatrix tmp = matrix;
    SparseMatrix tmp2;
    tmp2.data = data;
    operator_function(process_decide,tmp2,tmp,matrix,result);
    return result;
}
SparseMatrix SparseMatrix :: operator-()
{
    SparseMatrix tmp;
    vector <double> v1d;
    vector <vector <double>> v2d;
    vector <double> row;
    int i,j,l;
    for(i=0;i<data.size();i++)
    {
        row.push_back(data[i][0][0]);
        v2d.push_back(row);
        row.clear();
        for(j=1;j<data[i].size();j++)
        {
            v1d.push_back(data[i][j][0]);
            v1d.push_back(data[i][j][1] * -1);
            v2d.push_back(v1d);
            v1d.clear();
        }
        tmp.data.push_back(v2d);
        v2d.clear();
    }
    return tmp;
    
}
void order_function(SparseMatrix &matrix)//sorts data
{

    int i,j,l;
    for(i=0;i<matrix.data.size();i++)
    {
        for(j=i+1;j<matrix.data.size();j++)
        {
            if(matrix.data[i][0][0] > matrix.data[j][0][0])
            {
                swap(matrix.data[i],matrix.data[j]);
            }
        }
    }
    order_index(matrix);
}
void order_index(SparseMatrix &matrix)//sorts indexes
{
    int i,j,l;
    for(i=0;i<matrix.data.size();i++)
    {
        for(j=1;j<matrix.data[i].size();j++)
        {
            for(l=j+1;l<matrix.data[i].size();l++)
            {
                if(matrix.data[i][j][0]  > matrix.data[i][l][0])
                {
                    swap(matrix.data[i][j],matrix.data[i][l]);
                }
            }
        }
    }
}

int check_row_func(int loc,double row,SparseMatrix matrix)//detects if the same row exists in two different matrices and returns a value accordingly
{
    int i;
    for(i=0;i<matrix.data.size();i++)
    {
        if(row == matrix.data[i][0][0])
            return 1;
    }

    return 0;
}

int check_index_2(double index,SparseMatrix matrix,int &loc,int &loc2)//detects if the same index is in the same row of two different matrices and returns a value accordingly
{
    int i ;
    int check = 0;
    double tmp;
    for(i=0;i<matrix.data[loc].size();i++)
    {
 
        if(matrix.data[loc][i][0] == index)
        {
            loc2 = i;
            check = 1;
            return 1;   
        }
    }
    return 0;
}
void fill_with_zero(SparseMatrix &tmp,vector <vector<vector<double>>>data,SparseMatrix matrix)//compares two matrices and populates missing indexes and sets values ​​to 0 to perform operations properly
{
    vector <vector<double>> v2d;
    vector <double> v1d;

    int check1;
    int check2 = 0;
    int i,j,l;
    int     x,y,z;
    int loc;
    int loc2;
    for(i=0;i<data.size();i++)
    {
        check1 = check_row_func(i,data[i][0][0],matrix);
        
        if(check1 == 1)
        {
            found_same_row_index(loc,data[i][0][0],matrix);
            for(j=1;j<data[i].size();j++)
            {
                check2 = check_index_2(data[i][j][0],matrix,loc,loc2);
                if(check2 == 0)
                {
                    v1d.push_back(data[i][j][0]);
                    v1d.push_back(0);
                    tmp.data[loc].push_back(v1d);
                    v1d.clear();
                }
            }
        }

    }
    fill_with_data_according_row(tmp,data,matrix);
}

void fill_with_data_according_row(SparseMatrix &tmp,vector <vector<vector<double>>>data,SparseMatrix matrix)//Compares two matrices and adds missing rows to perform operations properly
{
    int i,j,l;
    int check_row;
    vector <double>row;
    vector <double> v1d;
    vector <vector <double>> v2d;
    double row_tmp;

    for(i=0;i<data.size();i++)
    {
        check_row = check_row_func(i,data[i][0][0],matrix);
        if(check_row == 0)
        {
            row_tmp = data[i][0][0];
            row.push_back(row_tmp);
            v2d.push_back(row);
            for(j=1;j<data[i].size();j++)
            {
                v1d.push_back(data[i][j][0]);
                v1d.push_back(0);
                v2d.push_back(v1d);
                v1d.clear();
            }
            tmp.data.push_back(v2d);
            v2d.clear();
            v1d.clear();
            row.clear();
        }
    }
    
}
void last_hit_function(double row_tmp,vector <double> index_tmp,vector <double> value_tmp,vector<vector<vector<double>>> &data,int loc)//puts data into data inside the class
{
    vector <double> row_1;
    vector<double>tmp_index_value;
    vector<vector<double>> v2d;
    int i,j=0,l=0;
    int x,y,z;
    row_1.push_back(row_tmp); //1-> row_1
    v2d.push_back(row_1);
    for(i=0;i<index_tmp.size();i++)
    {
        tmp_index_value.push_back(index_tmp[i]);
        tmp_index_value.push_back(value_tmp[i]);

        v2d.push_back(tmp_index_value);
        tmp_index_value.clear();
    }
    data.push_back(v2d);

}

tuple <double,vector<double>,vector<double>> separate_string(string data)//parses the string and returns the required values
{
    double index1;
    vector <double> index2;
    vector <double> value;
    int size = data.length();
    int i = 0;
    char tmp;
    string index1_string;
    string index2_string;
    string value_string;

    int j = 0;
    int flag_1 = 1;
    int flag_2 = 1;
    int flag_3 = 1;
    int check = 1;
    while(i<size)
    {
        tmp = data[i];
        if(flag_1 == 1)
        {
            while(tmp != ' ')
            {
                index1_string = index1_string + tmp;
                i++;
                tmp = data[i];
            }
            flag_1 = 0;
        }
        else if(flag_2 == 1)
        {
            while(tmp != ':')
            {
                index2_string = index2_string+tmp;
                i++;
                tmp = data[i];
            }
            flag_2 = 0;
        }
        else if(flag_3 == 1)
        {
            while(tmp != ' ' & tmp != '\0')
            {
                value_string = value_string + tmp;
                i++;
                tmp = data[i];
            }
            flag_3 = 0;
        }
        i++;
        if(flag_1== 0 && check== 1)
        {
            index1= stod(index1_string);
            check = 0;
        }
        if(flag_2 == 0 && flag_3 == 0)
        {
            index2.push_back(stod(index2_string));
            value.push_back(stod(value_string));
            index2_string.clear();
            value_string.clear();
            flag_2 = 1;
            flag_3 = 1;
        }
    }
    return {index1,index2,value};
}
