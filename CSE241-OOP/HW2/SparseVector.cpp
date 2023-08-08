#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include "SparseVector.h"
using namespace std;
SparseVector :: SparseVector(string file_name)
{
    ifstream FILE;
    size = 0;
    int loc;
    double num;
    char tmp;
    FILE.open(file_name);//reads the file
    while(FILE)
    {
        FILE>>loc>>tmp>>num;
        if(num == 0)
        {
            continue;
        }
        else
        {
            index.push_back(loc);
            value.push_back(num);
            size++;
        }
    }
    size--;
}
SparseVector SparseVector:: operator+(SparseVector dt)
{
    SparseVector tmp;
    int check = 1;
    int i,j ;
    tmp.size = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                tmp.index.push_back(index[i]);
                tmp.value.push_back(value[i] + dt.value[j]);
                tmp.size = tmp.size + 1;
                break;
            }
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(value[i]);
            tmp.index.push_back(index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    for(i=0;i<dt.size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(dt.index[i] == index[j])
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(dt.value[i]);
            tmp.index.push_back(dt.index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    order_data(tmp);
    return tmp;
}
void SparseVector :: order_data(SparseVector &v1)
{
    int i;
    int j;
    for(i=0;i<v1.size;i++)
    {
        for(j=i+1;j<v1.size;j++)
        {
            if(v1.index[i] > v1.index[j])
            {
                swap(v1.index[i],v1.index[j]);
                swap(v1.value[i],v1.value[j]);
            }
        }
    }
    
}
SparseVector :: SparseVector()
{

}
ostream &operator<<(ostream& out, const SparseVector& dt)
{
    int i = 0;
    for(i=0;i<dt.size;i++)
    {
        if(dt.size - 1 == i)
            out << dt.index[i]<<":"<<dt.value[i];
        else
            out << dt.index[i]<<":"<<dt.value[i]<<endl;
    }
    return out;
}
SparseVector SparseVector :: operator-(SparseVector dt)
{
    
    SparseVector tmp;
    int check = 1;
    int i,j ;
    tmp.size = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                tmp.index.push_back(index[i]);
                tmp.value.push_back(value[i] - dt.value[j]);
                tmp.size = tmp.size + 1;
                break;
            }
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(value[i]);
            tmp.index.push_back(index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    for(i=0;i<dt.size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(dt.index[i] == index[j])
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(-dt.value[i]);
            tmp.index.push_back(dt.index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    order_data(tmp);
    return tmp;
}
SparseVector SparseVector ::  operator-()
{
    SparseVector tmp;
    tmp.size = size;
    int i;
    for(i=0;i<size;i++)
    {
        tmp.index.push_back(index[i]);
        tmp.value.push_back(value[i]*(-1));
    }
    
    return tmp;
}
SparseVector SparseVector :: operator*(SparseVector dt)
{
    SparseVector tmp;
    int check = 1;
    int i,j ;
    tmp.size = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                tmp.index.push_back(index[i]);
                tmp.value.push_back(value[i] * dt.value[j]);
                tmp.size = tmp.size + 1;
                break;
            }
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<dt.size;j++)
        {
            if(index[i] == dt.index[j])
            {
                
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(0);
            tmp.index.push_back(index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    for(i=0;i<dt.size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(dt.index[i] == index[j])
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            tmp.value.push_back(0);
            tmp.index.push_back(dt.index[i]);
            tmp.size = tmp.size + 1;
        }
       check = 1;
    }
    order_data(tmp);
    return tmp;
}
double SparseVector:: get_value(int loc)//Returns the value inside the class
{
    double tmp = value[loc];
    return tmp;
}
int SparseVector :: get_size()//Returns the value inside the class
{
    return size;
}
double SparseVector :: get_index(int loc)//Returns the value inside the class
{
    double tmp = index[loc];
    return tmp;
}
double dot(SparseVector v1,SparseVector v2)
{

    int size1 = v1.get_size();
    int size2 = v2.get_size();
    int i;
    double value = 0;
    int j;
    for(i=0;i<size1;i++)
    {
        for(j=0;j<size2;j++)
        {
            if(v1.get_index(i) == v2.get_index(j))
            {
                value = value + (v1.get_value(i) * v2.get_value(j));
            }
        }
    }
    return value;
}
