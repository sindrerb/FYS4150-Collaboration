#include <matrix.h> //Private
#include <iostream>
#include <iomanip>
//#include <armadillo>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h>
#include "time.h"

using namespace std;
//using namespace arma;

void OrthogonalTest(matrix<double> M, int i,string filename){
    ofile.open(filename + to_string(i));
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Printout for orthogonal test: "<<endl;
    ofile << "Matrix M at iteration "<<i<<endl;
    M.fprint('M');
    ofile.close();
}

matrix<double> rho(double xmin, double xmax,int N){
    double h,x;
    matrix<double> X;
    X.zeros(N,1);
    h = (xmax-xmin)/(N);
    for(int i =0;i<N;i++){
        x = ((double)(i+1))*h;
        X.assign(0,i,x);
    }
    return X;
}

matrix<double> OneParticlePotential(int n, matrix<double> X){
    double v,x;
    matrix<double> V;
    V.identity(n);
    for(int i = 0; i<n;i++){
        x = X(0,i);
        v = x*x;
        V.assign(i,i,v);
    }
    return V;
}
matrix<double> TwoParticlePotential(int n, matrix<double> X, double freq){
    double v,x;
    matrix<double> V;
    V.identity(n);
    for(int i = 0; i<n;i++){
        x = X(0,i);
        v = x*x*freq*freq+1.0/x;
        V.assign(i,i,v);
    }
    return V;
}

matrix<double> Hamiltonian(int n,matrix<double> X,double freq){
    matrix<double> H,V;
    double h;
    h = (X(0,1)-X(0,0));
    H.diagonal(n,2,-1);
    H = H/(h*h);
    if(freq != 0){
        V = TwoParticlePotential(n,X,freq);
    }else{
        V = OneParticlePotential(n,X);
    }
    H = H+V;
    return H;
}

void findLargestNonDiagonalElement(matrix<double> A, int n, int *k, int *l){
    // FIND THE LARGEST NON-DIAGONAL ELEMENT
    double a_max,a_temp;
    a_max = 0;
    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n; j++){
            if(i!=j){
                a_temp = fabs(A(i,j));
                if(a_temp>a_max){
                    *k = i;
                    *l = j;
                    a_max = a_temp;
                }
            }
        }
    }

}

void JacobiRotation(matrix<double>A,matrix<double>R, int n, int k, int l){
    double a_kl = A(k,l);
    double a_kk = A(k,k);
    double a_ll = A(l,l);
    //SOLVE T^2+2*tau*T-1=0
    double c,s,t;
    if(a_kl!=0.0){
        //printf("a_kl=%f \t",a_kl);
        double tau = (a_ll-a_kk)/(2.0*a_kl);
        if(tau>=0.0){
            t = 1.0/(tau+sqrt(1.0+tau*tau));
        } else {
            t = -1.0/(-tau+sqrt(1.0+tau*tau));
        }

        c = 1.0/sqrt(1.0+t*t);
        s = c*t;
    }else{
        c = 1.0;
        s = 0.0;
    }
    //printf("c=%f\ts=%f\n");
    //REASSIGN ELEMENTS
    double a_ik,a_il,r_ik,r_il;
    double cc = c*c;
    double ss = s*s;
    double cross = 2*a_kl*c*s;
    A.assign(k,k,(a_kk*cc-cross+a_ll*ss));
    A.assign(l,l,(a_ll*cc+cross+a_kk*ss));
    A.assign(k,l,0.0);
    A.assign(l,k,0.0);
    for(int i=0;i<n;i++){
        if(i!=k && i!=l){
            a_ik=A(i,k);
            a_il=A(i,l);
            A.assign(i,k,(a_ik*c-a_il*s));
            A.assign(k,i,A(i,k));
            A.assign(i,l,(a_il*c+a_ik*s));
            A.assign(l,i,A(i,l));
        }
    //REASSIGN EIGENVECTORS
    r_ik = R(i,k);
    r_il = R(i,l);

    R.assign(i,k,(c*r_ik-s*r_il));
    R.assign(i,l,(c*r_il+s*r_ik));
    }

}

int main(int argc, char *argv[])
{
    string eigenvals = "eigenvals";
    string eigenvecs = "eigenvecs";
    string marker;

    int N;
    double maxRho,minRho,frequency,amax,tolerance;
    if(argc<2){
        printf("Please write arguments:\n N:100-300 Frequency:0-10 (leave 0 for single particle) Maximal rho: 5-50\n");
        return 0;
    }else if(argc=3){
        N = atoi(argv[1]);
        frequency = atof(argv[2]);
        maxRho = atof(argv[3]);
    }else{
        frequency = atof(argv[2]);
        maxRho = 0.5/frequency;
    }
    if(argc=4){
        marker = argv[4];
    }else{
        marker = ' ';
    }
    printf("Running calculations using N=%i, Freq.=%.4f and maximal rho %.4f \n",N,frequency,maxRho);
    tolerance = 1E-5;
    minRho = 0.0;
    //INITZIALISE
    int *k = new int;
    int *l = new int;
    matrix<double> H,R,E,L,X,P;
    X.zeros(N,1);
    X = rho(minRho,maxRho,N);
    R.identity(N);
    H = Hamiltonian(N,X,frequency);

    L.ones(N,1);
    findLargestNonDiagonalElement(H,N,k,l);
    amax = H(*k,*l);

    int i = 0;
    int unittest = 1;
    int maxIterations = 500000;
    while(fabs(amax)>=tolerance && i<maxIterations){
        JacobiRotation(H,R,N,*k,*l);
        findLargestNonDiagonalElement(H,N,k,l);
        amax = H(*k,*l);
        i++;
        /*
        if(unittest == 5000){
            OrthogonalTest(R,i,"ortoTest");
            unittest = 0;
        }
        unittest++;
        */
    }

    printf("i=%i \n",i);
    E = H*L;
    //E.print('E');
    //R.print('R');
    //SORTING EIGENVALUES AND VECTORS IN INCREASING ORDER
    double e,emin;
    int jmin;
    matrix<double> r;
    for(int i=0;i<N;i++){
        jmin = i;
        emin = E(0,i);
        for(int j=i+1;j<N;j++){
            if(emin>E(0,j)){
                emin = E(0,j);
                jmin = j;
            }
        }
        if(jmin != i){
            e = E(0,i);
            E.assign(0,i,E(0,jmin));
            E.assign(0,jmin,e);
            r = R.col(i);
            R.setcol(i,R.col(jmin));
            R.setcol(jmin,r);
        }
    }
    //*/
    //E.print('E');
    //R.print('R');

    //WRITE RESULTS TO FILES

    ofile.open(eigenvals + marker + to_string(frequency));
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    if(i==maxIterations){
        printf("WARNING! Maximal number of iterations reached. Increase 'maxiteration' \n");
        ofile << "WARNING! Maximal number of iterations reached. Increase 'maxiteration' " << endl;
    }
    ofile << "Number of iterations: " << i << "     Freq: " << frequency << endl;
    E.fprint('E');
    X.fprint(' ');
    ofile.close();

    ofile.open(eigenvecs + marker + to_string(frequency));
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    R.fprint('R');
    ofile.close();


}

