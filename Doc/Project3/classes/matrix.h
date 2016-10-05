#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef double real;

class Matrix {
    int rows, columns;
    real **M;
public:
    //Constructor
    Matrix ();

    //Defining array type
    void setZeros(int row, int column);
    void setOnes(int row, int column);
    void setIdentity(int size);
    void setDiagonal(int size, real a = 0,real b = 0,real c = 0,real d = 0, real e = 0);
    void setRandom(int row, int column);
    void setElement(int i, int j, real value);
    void setColumn(int n, const Matrix &B);
    void setRow(int n, const Matrix &B);

    //Operators
    real operator()(int i, int j);
    Matrix getColumn(int n);
    Matrix getRow(int n);
    Matrix operator+(const Matrix &B);
    Matrix operator-(const Matrix &B);
    Matrix operator*(const Matrix &B);
    Matrix operator*(const real &b);
    Matrix operator/(const real &b);
    Matrix& operator= (const Matrix copy_from);
    Matrix transpose();


//    //Get info
    void print(string name);

    void printToFile(string dataLabelInFile, string fileName);
};

#endif // MATRIX_H
