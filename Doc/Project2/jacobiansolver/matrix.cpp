#include "matrix.h"
#include <string>

using namespace std;

Matrix::Matrix(){
}

void Matrix::setZeros(int row, int column) {
    rows = row;
    columns = column;
    M = new real*[column];
    for(int i = 0; i<column; i++){
        M[i] = new real[row];
        for(int j = 0; j<row ; j++){
            M[i][j] = 0;
        }
    }
}

void Matrix::setOnes(int row, int column) {
    rows = row;
    columns = column;
    M = new real*[column];
    for(int i = 0; i<column; i++){
        M[i] = new real[row];
        for(int j = 0; j<row ; j++){
            M[i][j] = 1;
        }
    }
}

void Matrix::setIdentity(int size) {
    columns = size;
    rows = size;
    M = new real*[size];
    for(int i = 0; i<size; i++) {
        M[i] = new real[size];
        for(int j = 0; j<size ; j++) {
            if(i==j){
                M[i][j] = 1;
            }else{
                M[i][j] = 0;
            }
        }
    }
}

void Matrix::setDiagonal(int size, real a, real b, real c, real d, real e) {
    columns = size;
    rows = size;
    M = new real*[size];
    for(int i = 0; i<size; i++) {
        M[i] = new real[size];
        for(int j = 0; j<size ; j++) {
            if(i==j) {
                M[i][j]=a;
            }else if(i==j-1 || i==j+1) {
                M[i][j]=b;
            }else if(i==j-2 || i==j+2) {
                M[i][j]=c;
            }else if(i==j-3 || i==j+3) {
                M[i][j]=d;
            }else if(i==j-4 || i==j+4) {
                M[i][j]=e;
            }
        }
    }
}

void Matrix::setRandom(int row, int column) {
    rows = row;
    columns = column;
    M = new real*[column];
    for(int i = 0; i<column; i++) {
        M[i] = new real[row];
        for(int j = 0; j<row ; j++) {
            M[i][j] = (real) rand()/rand();
        }
    }
}

real Matrix::operator()(int i, int j) {//Access element
    return this->M[i][j];
}

void Matrix::setElement(int i, int j, real value) {//Access element
    this->M[i][j] = value;
}

void Matrix::setColumn(int n, const Matrix &B) { //Set column
    if(B.columns==columns) {
        for(int i = 0; i<columns; i++) {
            M[i][n]=B.M[i][0];
        }
    }else{
        printf("Error in column assignment:\n Matrix dimention does not match, no changes made.\n");
    }
}

void Matrix::setRow(int n, const Matrix &B) { //Set column
    if(B.rows==rows) {
        for(int i = 0; i<rows; i++) {
            M[n][i]=B.M[0][i];
        }
    }else{
        printf("Error in row assignment:\n Matrix dimention does not match, no changes made.\n");
    }
}

Matrix Matrix::operator+(const Matrix &B) {//Matrix addition
    if(this->rows == B.rows && this->columns == B.columns) {
        Matrix C;
        int col = this->columns;
        int row = this->rows;
        C.setZeros(row,col);
        for(int i = 0; i<col; i++) {
            for(int j = 0; j<row ; j++) {
                real a = this->M[i][j];
                real b = B.M[i][j];
                C.M[i][j] = a + b;
            }
        }
        return C;
    }else{
        printf("Error: Matrix addition\n Matrix dimentions dont match.");
    }
}

Matrix Matrix::operator-(const Matrix &B) {//Matrix addition
    if(this->rows == B.rows && this->columns == B.columns) {
        Matrix C;
        int col = this->columns;
        int row = this->rows;
        C.setZeros(row,col);
        for(int i = 0; i<col; i++) {
            for(int j = 0; j<row ; j++) {
                real a = this->M[i][j];
                real b = B.M[i][j];
                C.M[i][j] = a - b;
            }
        }
        return C;
    }else{
        printf("Error: Matrix addition\n Matrix dimentions dont match.");
    }
}

Matrix Matrix::operator*(const Matrix &B) {//Matrix multiplication
    if(this->columns == B.rows) {
        Matrix C;
        rows = this->rows;
        columns = B.columns;
        C.setZeros(rows,columns);
        for(int i = 0; i<columns; i++) {
            for(int j = 0; j<rows ; j++) {
                for(int k=0; k<rows; k++) {
                    C.M[i][j] += this->M[k][j]*B.M[i][k];
                }
            }
        }
        return C;
    }else{
        printf("Error: matrix multiplication.\n Invalid matrix dimentions.\n");
    }
}

Matrix Matrix::operator*(const real &b) {
    Matrix C;
    int row = this->rows;
    int col = this->columns;
    C.setZeros(row,col);
    for(int i = 0; i<col; i++) {
        for(int j = 0; j<row ; j++) {
            C.M[i][j] = this->M[i][j]*b;
        }
    }
    return C;
}

Matrix Matrix::operator/(const real &b) {
    Matrix C;
    rows = this->rows;
    columns = this->rows;
    C.setZeros(rows,columns);
    for(int i = 0; i<columns; i++) {
        for(int j = 0; j<rows ; j++) {
            C.M[i][j] = this->M[i][j]/b;
        }
    }
    return C;
}

Matrix &Matrix::operator=(Matrix copy_from) {//Assign matrix eaqual to another
    columns=copy_from.columns;
    rows=copy_from.rows;
    M = new real*[columns];
    for(int i = 0; i<columns; i++) {
        M[i] = new real[rows];
        for(int j = 0; j<rows ; j++) {
            M[i][j] = copy_from.M[i][j];
        }
    }
}

Matrix Matrix::transpose() { //Transpose
    Matrix C;
    C.setZeros(columns,rows);
    for(int i = 0; i<C.columns; i++) {
        for(int j = 0; j<C.rows ; j++) {
            C.setElement(i,j,M[j][i]);
        }
    }
    return C;
}

Matrix Matrix::getColumn(int n) { //Get column
    Matrix C;
    int row = rows;
    C.setZeros(1,row);
    for(int i = 0; i<row; i++) {
        C.setElement(i,0,M[i][n]);
    }
    return C;
}

Matrix Matrix::getRow(int n) { //Get row
    Matrix C;
    int col = columns;
    C.setZeros(col,1);
    for(int i = 0; i<col; i++) {
        C.setElement(0,i,M[n][i]);
    }
    return C;
}

void Matrix::print(string name) {
    printf("%s = \n", name.c_str());
    for(int i = 0; i<columns; i++) {
        for(int j = 0; j<rows ; j++) {
            printf("%.4f  ",M[i][j]);
        }
        printf("\n");
    }
}

void Matrix::printToFile(string dataLabelInFile, string fileName) {
    ofstream ofile;
    ofile.open(fileName,std::ios::app);
    if(!ofile.good()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }
    ofile << dataLabelInFile << endl;
    for(int i = 0; i<columns; i++) {
        for(int j = 0; j<rows ; j++) {
            double m = M[i][j];
            ofile << m << "\t";
        }
        ofile <<"\n"<< endl;
    }
    ofile.close();
}
