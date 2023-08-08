#include<iostream>
#include <fstream>
#include <vector>
#include<string>
#ifndef SparseMatrix_h
#define SparseMatrix_h
using namespace std;
tuple <double,vector<double>,vector<double>> separate_string(string data);//Stores and returns data read from file
void last_hit_function(double row_tmp,vector <double> index_tmp,vector <double> value_tmp,vector<vector<vector<double>>> &data,int loc);//puts values ​​read from file into class

class SparseMatrix{
    public:
        SparseMatrix(string file_name);
        SparseMatrix();
        SparseMatrix operator+(SparseMatrix matrix);
        friend ostream& operator<<(ostream& os, const SparseMatrix& matrix);
        SparseMatrix operator-(SparseMatrix matrix);
        SparseMatrix operator*(SparseMatrix matrix);
        SparseMatrix operator-();
        vector <vector<vector<double>>> data;//holds all necessary information
        SparseMatrix transpose();

    private:

};
void order_function(SparseMatrix &matrix);//sorts data by row and index from smallest to largest
void order_index(SparseMatrix &matrix);//only sorts by index from smallest to largest
int check_row_func(int loc,double row,SparseMatrix matrix);//checks if both matrices have the same row
void fill_with_data_according_row(SparseMatrix &tmp,vector <vector<vector<double>>>data,SparseMatrix matrix);//Compares 2 matrices and places rows and indexes that one does not have, with values ​​0
void fill_with_zero(SparseMatrix &tmp,vector <vector<vector<double>>>data,SparseMatrix matrix);//It makes the values ​​0 if the indices of the 2 matrices are different.
void found_same_row_index(int &loc,double row,SparseMatrix matrix);//Determines the location where the rows of 2 matrices are the same
int check_index_2(double index,SparseMatrix matrix,int &loc,int &loc2);//checks indexes
void found_same_line_index(int &loc_index,int loc_row,int i,SparseMatrix tmp,SparseMatrix tmp2);//finds the desired index in the specified matrix
void operator_function(int process_num,SparseMatrix tmp2,SparseMatrix tmp,SparseMatrix &result);//function to perform the function of some operators so as not to repeat the same operations

#endif

