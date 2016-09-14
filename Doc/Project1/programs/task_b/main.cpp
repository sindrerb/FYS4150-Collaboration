#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "time.h"

using namespace std;
ofstream ofile;

//Functon for right side of equation
double f(double x){
    return 100*exp(-10*x);
}

//Function for exact solution
double f_solution(double x){return 1.0-(1-exp(-10))*x-exp(-10*x);}

int main(){

    /*
        Declaration of initial variables
        by user input.
    */
    string filename;
    int n;
    cout << "Number of iterations:" << endl;
    cin >> n;
    cout << "Filename and format:" << endl;
    cin >> filename;

    //Steplength
    double h = 1.0/(n + 1.0);
    double hh = h*h;

    //Vectors
    double *vec_a = new double[n+1];
    double *vec_b = new double[n+1];
    double *vec_c = new double[n+1];
    double *x = new double[n+2];
    double *vec_u = new double[n+2];
    double *vec_f_approx = new double[n+2];
    double *vec_f_solution = new double[n+2];

    //Setting x values with x+1 so x_0 = 0 and x_(n+2) = 1
    for(int i=0;i<=n;i++){
      vec_a[i] = 2;
      vec_b[i] = -1;
      vec_c[i] = -1;
    }

    //Setting all vectors to zero
    for(int i=0;i<=n+1;i++){
        vec_u[i] = 0;
        x[i] = 0;
        vec_f_approx[i] = 0;
        vec_f_solution[i] = 0;
    }

    //Setting up x variable
    for(int i = 1;i<=n+1;i++){
        x[i] = h*i;
    }

    //setting solutions
    for(int i=1;i<=n+1;i++){
        vec_f_approx[i] = hh*f(x[i]);//Right side of equation
        vec_f_solution[i] = f_solution(x[i]);//Analytic
    }

    //initialize clock
    clock_t time;
    //start clock
    time = clock();

    //Gauss elemination for tridigonal matrix

    //Forward substitution
    for(int i=1;i<n;i++){
        vec_a[i+1] = vec_a[i+1] - vec_b[i]*vec_c[i]/vec_a[i];
        vec_f_approx[i+1] = vec_f_approx[i+1] - vec_f_approx[i]*vec_c[i]/vec_a[i];
    }

    //Bckwards substitution
    vec_u[n]=vec_f_approx[n]/vec_a[n];
    for(int i=n;i>=2;i--){
        vec_u[i-1] = (vec_f_approx[i-1]-vec_b[i-1]*vec_u[i])/vec_a[i-1];
    }

    //clock stops here
    time = clock() - time;
    cout << "Time in sec:" << ((float)time)/CLOCKS_PER_SEC << endl;
/*
    //Prints out final values
    for(int i =0;i<n+1;i++){
        cout<<"approx = "<<vec_u[i]<<" exact = "<<vec_f_solution[i]<<endl;
    }
*/
    //Open file and write results to file
    ofile.open(filename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile <<"Time to run matrix of size "<<n<<" was:"<<
            ((float)time)/CLOCKS_PER_SEC<< endl;
    ofile << "       x:             approx:          solution:  " << endl;
    for (int i=1;i<=n;i++) {
       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << vec_u[i];
       ofile << setw(15) << setprecision(8) << vec_f_solution[i] << endl;
    }
    ofile.close();

    //Free the memory!
    delete [] x;
    delete [] vec_a;
    delete [] vec_b;
    delete [] vec_c;
    delete [] vec_u;
    delete [] vec_f_approx;
    delete [] vec_f_solution;

    //the end
    cout<<"FYS4150_ex1_task_b_ver2 DONE"<<endl;
    return 0;
}
