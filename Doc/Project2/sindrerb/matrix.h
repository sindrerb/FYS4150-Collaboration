#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
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
    matrix assign(int i, int j, T value){//Access element
        this->M[i][j] =  value;
    }
    matrix operator+(const matrix &B){//Matrix addition
        matrix C;
        C.zeros(this->rows,this->columns);
        for(int i = 0; i<columns; i++){
            for(int j = 0; j<rows ; j++){
                C.M[i][j] = this->M[i][j]+B.M[i][j];
            }
        }
        return C;
    }
    matrix operator*(const matrix &B){//Matrix multiplication
        matrix C;
        C.zeros(this->rows,this->columns);
        for(int i = 0; i<columns; i++){
            for(int j = 0; j<rows ; j++){

                for(int k=0;k<rows;k++){
                    C.M[i][j] += this->M[k][j]*B.M[i][k];

                }
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

};

#endif // MATRIX_H
