#include <iostream>
#include <armadillo>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include "time.h"

using namespace std;
using namespace arma;
ofstream ofile;

//Function
double reference_function(double x){
    return 100*exp(-10*x);
}

//Function for exact solution
double exact_solution(double x){
    return 1.0-x*(1.0-exp(-10))-exp(-10*x);
}

int main(int argc, char *argv[])
{
    string filename;
    int n;
    cout << "Number of iterations:" << endl;
    cin >> n;
    cout << "Filename and format:" << endl;
    cin >> filename;

    clock_t start, final;

    //Initializing x
    vec x = linspace<vec>(0,1,n+2);

    double h = x(1)-x(0);
    //Initializing f and exact u
    vec f(n);
    vec u_exact(n);
    for(int i = 0; i<n; i++){
        f(i)= reference_function(x(i+1))*h*h;
        u_exact(i) = exact_solution(x(i+1));
    }

    //Initializing matrix A
    mat A(n,n);
    for(int i=1; i<n; i++){
        A(i,i-1)=-1.0;
        A(i,i)=2.0;
        A(i-1,i)=-1.0;
    }
    A(0,0)=2.0;

    vec v(n);
    vec y(n);
    mat L,U,P;

    start = clock();
    lu(L,U,P,A);

    //LUv=f
    //Ly=f ;y=Uv
    y = solve(L,f);
    v = solve(U,y);

    final = clock();
    double time = (double)(final-start)/(CLOCKS_PER_SEC);

    //Open file and write results to file
    if(n<1E5){
    ofile.open(filename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile <<"Time to run matrix of size "<<n<<" was:"<<
            time << endl;
    ofile << "      x:      approx:     exact:  " << endl;
    for(int i=0;i<n;i++){
        ofile << setw(15) << setprecision(8) << x(i+1);
        ofile << setw(15) << setprecision(8) << v(i);
        ofile << setw(15) << setprecision(8) << u_exact(i) << endl;
    }
    ofile.close();
    }



    //the end
    cout<<"task_e DONE"<<endl;

}
