#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ofstream ofile;

template < typename T > class matrix {
    int rows, columns;
    T **M;
public:
    //Constructor
    matrix (){
    };

    //Defining array type
    void zeros(int row, int column){
        rows = row;
        columns = column;
        M = new T*[column];
        for(int i = 0; i<column; i++){
            M[i] = new T[row];
            for(int j = 0; j<row ; j++){
                M[i][j] = 0;
            }
        }
    }
    void ones(int row, int column){
        rows = row;
        columns = column;
        M = new T*[column];
        for(int i = 0; i<column; i++){
            M[i] = new T[row];
            for(int j = 0; j<row ; j++){
                M[i][j] = 1;
            }
        }
    }
    void identity(int size){
        columns = size;
        rows = size;
        M = new T*[size];
        for(int i = 0; i<size; i++){
            M[i] = new T[size];
            for(int j = 0; j<size ; j++){
                if(i==j){
                    M[i][j] = 1;
                }else{
                    M[i][j] = 0;
                }
            }
        }
    }
    void diagonal(int size, T a = 0,T b = 0,T c = 0,T d = 0, T e = 0){
        columns = size;
        rows = size;
        M = new T*[size];
        for(int i = 0; i<size; i++){
            M[i] = new T[size];
            for(int j = 0; j<size ; j++){
                if(i==j){
                    M[i][j]=a;
                }else if(i==j-1 || i==j+1){
                    M[i][j]=b;
                }else if(i==j-2 || i==j+2){
                    M[i][j]=c;
                }else if(i==j-3 || i==j+3){
                    M[i][j]=d;
                }else if(i==j-4 || i==j+4){
                    M[i][j]=e;
                }

            }
        }
    }
    void random(int row, int column){
        rows = row;
        columns = column;
        M = new T*[column];
        for(int i = 0; i<column; i++){
            M[i] = new T[row];
            for(int j = 0; j<row ; j++){
                M[i][j] = (T) rand()/rand();
            }
        }
    }

    //Operators
    T operator()(int i, int j){//Access element
        return this->M[i][j];

    }
    void assign(int i, int j, T value){//Access element
        this->M[i][j] = value;
    }

    void setcol(int n, const matrix &B){ //Set column
        if(B.columns==columns){
            for(int i = 0; i<columns; i++){
                    M[i][n]=B.M[i][0];
            }
        }else{
            printf("Error in column assignment:\n Matrix dimention does not match, no changes made.\n");
        }
    }
    void setrow(int n, const matrix &B){ //Set column
        if(B.rows==rows){
            for(int i = 0; i<rows; i++){
                    M[n][i]=B.M[0][i];
            }
        }else{
            printf("Error in row assignment:\n Matrix dimention does not match, no changes made.\n");
        }
    }

    matrix operator+(const matrix &B){//Matrix addition
        if(this->rows == B.rows && this->columns == B.columns){
            matrix C;
            int col = this->columns;
            int row = this->rows;
            C.zeros(row,col);
            for(int i = 0; i<col; i++){
                for(int j = 0; j<row ; j++){
                    T a = this->M[i][j];
                    T b = B.M[i][j];
                    C.M[i][j] = a + b;
                }
            }
            return C;
        }else{
            printf("Error: Matrix addition\n Matrix dimentions dont match.");
        }
    }
    matrix operator-(const matrix &B){//Matrix addition
        if(this->rows == B.rows && this->columns == B.columns){
            matrix C;
            int col = this->columns;
            int row = this->rows;
            C.zeros(row,col);
            for(int i = 0; i<col; i++){
                for(int j = 0; j<row ; j++){
                    T a = this->M[i][j];
                    T b = B.M[i][j];
                    C.M[i][j] = a - b;
                }
            }
            return C;
        }else{
            printf("Error: Matrix addition\n Matrix dimentions dont match.");
        }
    }
    matrix operator*(const matrix &B){//Matrix multiplication
        if(this->columns == B.rows){
            matrix C;
            rows = this->rows;
            columns = B.columns;
            C.zeros(rows,columns);
            for(int i = 0; i<columns; i++){
                for(int j = 0; j<rows ; j++){

                    for(int k=0;k<rows;k++){
                        C.M[i][j] += this->M[k][j]*B.M[i][k];

                    }
                }
            }
            return C;
        }else{
            printf("Error: matrix multiplication.\n Invalid matrix dimentions.\n");
        }
    }
    matrix operator*(const T &b){
        matrix C;
        int row = this->rows;
        int col = this->columns;
        C.zeros(row,col);
        for(int i = 0; i<col; i++){
            for(int j = 0; j<row ; j++){
                C.M[i][j] = this->M[i][j]*b;
            }
        }
        return C;
    }
    matrix operator/(const T &b){
        matrix C;
        rows = this->rows;
        columns = this->rows;
        C.zeros(rows,columns);
        for(int i = 0; i<columns; i++){
            for(int j = 0; j<rows ; j++){
                    C.M[i][j] = this->M[i][j]/b;
            }
        }
        return C;
    }
    matrix& operator= (matrix copy_from){//Assign matrix eaqual to another
        columns=copy_from.columns;
        rows=copy_from.rows;
        M = new T*[columns];
        for(int i = 0; i<columns; i++){
            M[i] = new T[rows];
            for(int j = 0; j<rows ; j++){
                M[i][j] = copy_from.M[i][j];
            }
        }
    }
    matrix transpose(){ //Transpose
        matrix C;
        C.zeros(columns,rows);
        for(int i = 0; i<C.columns; i++){
            for(int j = 0; j<C.rows ; j++){
                C.assign(i,j,M[j][i]);
            }
        }
        return C;
    }
    matrix col(int n){ //Get column
        matrix C;
        int row = rows;
        C.zeros(1,row);
        for(int i = 0; i<row; i++){
                C.assign(i,0,M[i][n]);
        }
        return C;
    }
    matrix row(int n){ //Get row
        matrix C;
        int col = columns;
        C.zeros(col,1);
        for(int i = 0; i<col; i++){
                C.assign(0,i,M[n][i]);
        }
        return C;
    }

    //Get info
    void print(char name){
        printf("%c = \n",name);
        for(int i = 0; i<columns; i++){
            for(int j = 0; j<rows ; j++){
                printf("%.4f  ",M[i][j]);
            }
            printf("\n");
        }
    }

    void fprint(char name){
        double m;
        ofile << name <<endl;
        for(int i = 0; i<columns; i++){
            for(int j = 0; j<rows ; j++){
                m = M[i][j];
                ofile << m << "    ";
            }
            ofile << endl;
        }
    }




};

#endif // MATRIX_H
