#include <iostream>
#include <new>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "time.h"
extern "C" {
#include "lib.h"
}
using namespace std;
ofstream ofile;

void inverse(double**, int);

//Function
double f(double x){
    return 100*exp(-10*x);
}

//Function for exact solution
double f_solution(double x){
    return 1-x*(1-exp(-10))-exp(-10*x);
}


//Main program reads filename and N form command line
int main() {

    /*
     Declaration of initial variables
     by user input.
    */
    string filename;
    int N;
    cout << "Number of iterations:" << endl;
    cin >> N;
    cout << "Filename and format:" << endl;
    cin >> filename;

    /*
    //Set steplenght
    double h = 1.0/(N+1.0);
    double hh = h*h;

    //declare vectors
    double* x = new double[N+2];
    double* vec_f_approx = new double[N+2];
    double* vec_u_exact = new double[N+2];
    double* vec_u_nummerical = new double[N+2];
    */
    //Initialize matrix
    double **Matrix = new double*[N];
    for(int i = 0; i<N; i++){
        Matrix[i] = new double[N];
        for(int j = 0; j<N; j++){
            Matrix[i][j] = 0;
        }
        Matrix[i][i]=2; //Center diagonal
    }
    for(int i = 0; i<N-1; i++){
        Matrix[i][i+1]=-1;//Top diagonal
        Matrix[i+1][i]=-1;//Bottom diagonal
    }
    /* Writing the matrix to terminal
    for(int i = 0; i<N; i++){
        for(int j=0;j<N;j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    */

    inverse(Matrix, N);

    // Writing the matrix to terminal
    for(int i = 0; i<N; i++){
        for(int j=0;j<N;j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }

    //the end
    cout<<"task_e DONE"<<endl;
    return 0;
}

void inverse(double**a, int n){
    int i,j, *indx;
    double d, *col;
    //allocate space
    indx = new int[n];
    col = new double[n];
    double **y = new double*[n];
    for(i = 0; i<n; i++){
        y[i] = new double[n];
    }

    ludcmp(a,n,indx,&d); //LU-decomposition of a[][]

    /*
    //find inverse of a[][]
    for(j=0;j<n;j++){
        for(i=0;i<n;i++){
            col[i] = 0.0;
            col[j] = 1.0;
            lubksb(a,n,indx,col);
        }
        //Save result to y[][]
        for(i = 0; i<n;i++){
            y[i][j]=col[i];
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
        a[i][j]=y[i][j];
    }}
    free_matrix((void **)y);
    */
    delete [] col;
    delete [] indx;
}
