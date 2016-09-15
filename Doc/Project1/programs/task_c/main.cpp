#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include "time.h"

using namespace std;
ofstream ofile;

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

    //Set steplenght
    double h = 1.0/(N+1.0);
    double hh = h*h;

    //declare vectors
    double* x = new double[N+2];
    double* vec_f_approx = new double[N+2];
    double* vec_f_solution = new double[N+2];
    double* vec_u = new double[N+2];
    double* diagonal = new double[N];

    for(int i = 0; i<N;i++){
        diagonal[i] = (i+1.0)/i;
    }

    //Set initial values to vectors
    x[0] = 0;
    for(int i=0;i<N+2;i++){
        x[i] = i*h;
        vec_f_approx[i] = hh*f(x[i]);
        vec_f_solution[i] = f_solution(x[i]);
    }

    //initialize clock
    clock_t start,finish;

    //start clock
    start = clock();

    //Special algoritme for unique matix
    //Forward substitution
    for(int i = 1; i<N+1;i++){
        vec_f_approx[i+1] = vec_f_approx[i+1] + vec_f_approx[i]/diagonal[i];
    }

    //Backwards substitution
    vec_u[N] = (vec_f_approx[N]*N)/(N+1);
    vec_u[0] = 0;
    for(int i = N-1;i>=1;i--){
        vec_u[i] = (vec_f_approx[i]+vec_u[i+1])/diagonal[i];
    }

    //clock stops here
    finish = clock();
    double time = (double) (finish - start)/CLOCKS_PER_SEC;
    cout << "Time in sec:" << time << endl;
/*
    //Prints out final values
    for(int i =0;i<N+1;i++){
        cout<<"approx = "<<vec_u[i]<<" exact = "<<vec_f_solution[i]<<endl;
    }
*/

    //Open file and write results to file
    if(N<1E5){
    ofile.open(filename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile <<"Time to run matrix of size "<<N<<" was:"<< time << endl;
    ofile << "      x:      approx:     exact:  " << endl;
    for(int i=0;i<N+2;i++){
        ofile << setw(15) << setprecision(8) << x[i];
        ofile << setw(15) << setprecision(8) << vec_u[i];
        ofile << setw(15) << setprecision(8) << vec_f_solution[i] << endl;
    }
    ofile.close();
    }

    delete [] x;
    delete [] vec_f_approx;
    delete [] vec_f_solution;

    //the end
    cout<<"task_c DONE"<<endl;
    return 0;
}
