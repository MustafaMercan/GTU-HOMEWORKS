#include<iostream>
#include <fstream>
#include <vector>
#include<string>
#ifndef SparseVector_h
#define SparseVector_h
using namespace std;
class SparseVector
{
    public:
        SparseVector(string file_name);
        SparseVector();
        friend ostream& operator<<(ostream& os, const SparseVector& dt);
        SparseVector operator+(SparseVector dt); 
        SparseVector operator-(SparseVector dt); 
        SparseVector operator-();
        SparseVector operator*(SparseVector dt);
        double get_value(int loc);
        double get_index(int loc);
        int  get_size();
        void order_data(SparseVector &vec);
        
        //SparseVector operator=(SparseVector dt);
    private:
    int size;//keeps the number of elements
    vector <int> index;//keeps indexes on data
    vector <double> value;//keeps values on data
};
double dot(SparseVector v1,SparseVector v2);
#endif