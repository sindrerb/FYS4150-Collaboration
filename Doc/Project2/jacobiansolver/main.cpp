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
ofstream ofile;

//using namespace arma;

void UnitTest(Matrix M, int i, int N, string filename){
    ofile.open(filename + to_string(i));
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Printout for unit tests: "<<endl;
    ofile << "Matrix M at iteration "<<i<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            ofile << M(i,j) << "    ";
        }
        ofile << endl;
    }
    ofile.close();
}

Matrix rho(double xmin, double xmax,int N){
    double h,x;
    Matrix  X;
    X.setZeros(N,1);
    h = (xmax-xmin)/(N);
    for(int i =0;i<N;i++){
        x = ((double)(i+1))*h;
        X.setElement(0,i,x);
    }
    return X;
}

Matrix  OneParticlePotential(int n, Matrix  X){
    double v,x;
    Matrix  V;
    V.setIdentity(n);
    for(int i = 0; i<n;i++){
        x = X(0,i);
        v = x*x;
        V.setElement(i,i,v);
    }
    return V;
}
Matrix  TwoParticlePotential(int n, Matrix  X, double freq, bool columb){
    double v,x;
    Matrix  V;
    V.setIdentity(n);
    for(int i = 0; i<n;i++){
        x = X(0,i);
        v = x*x*freq*freq;
        if(columb){
            v += 1.0/x;
        }
        V.setElement(i,i,v);
    }
    return V;
}

Matrix  Hamiltonian(int n,Matrix  X,double freq,bool columb){
    Matrix  H,V;
    double h;
    h = (X(0,1)-X(0,0));
    H.setDiagonal(n,2,-1);
    H = H/(h*h);
    if(freq != 0){
        V = TwoParticlePotential(n,X,freq,columb);
    }else{
        V = OneParticlePotential(n,X);
    }
    H = H+V;
    return H;
}

void findLargestNonsetDiagonalElement(Matrix  A, int n, int *k, int *l){
    // FIND THE LARGEST NON-setDiagonal ELEMENT
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

void JacobiRotation(Matrix A,Matrix R, int n, int k, int l){
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
    //REsetElement ELEMENTS
    double a_ik,a_il,r_ik,r_il;
    double cc = c*c;
    double ss = s*s;
    double cross = 2*a_kl*c*s;
    A.setElement(k,k,(a_kk*cc-cross+a_ll*ss));
    A.setElement(l,l,(a_ll*cc+cross+a_kk*ss));
    A.setElement(k,l,0.0);
    A.setElement(l,k,0.0);
    for(int i=0;i<n;i++){
        if(i!=k && i!=l){
            a_ik=A(i,k);
            a_il=A(i,l);
            A.setElement(i,k,(a_ik*c-a_il*s));
            A.setElement(k,i,A(i,k));
            A.setElement(i,l,(a_il*c+a_ik*s));
            A.setElement(l,i,A(i,l));
        }
    //REsetElement EIGENVECTORS
    r_ik = R(i,k);
    r_il = R(i,l);

    R.setElement(i,k,(c*r_ik-s*r_il));
    R.setElement(i,l,(c*r_il+s*r_ik));
    }

}

int main(int argc, char *argv[])
{
    string eigenvals = "eigenvals";
    string eigenvecs = "eigenvecs";
    string marker;

    int N;
    double maxRho,minRho,frequency,amax,tolerance, unitIteration;
    bool columbInteraction, unitTesting;
    if(argc<6){
        printf("Please write arguments:\n Iterations:100-300\n Frequency:0-10 (leave 0 for single particle)\n Maximal rho: 5-50\n Columb interactions (1=true/0=false)\n Unit test at iteration i: 100-10 000 (leave 0 for no test)\n");
        return 0;
    }else{
        N = atoi(argv[1]);
        frequency = atof(argv[2]);
        maxRho = atof(argv[3]);
        if(atoi(argv[4])==1){
            columbInteraction = true;
        }else{
            columbInteraction=false;
        }
        unitIteration = atoi(argv[5]);

    }
    if(unitIteration>0){
        unitTesting = true;
    }else{
        unitTesting = false;
    }
    if(columbInteraction){
            printf("Running calculations using N=%i, Freq.=%.4f and maximal rho %.4f with columb interactions.\n",N,frequency,maxRho);
    }else{
            printf("Running calculations using N=%i, Freq.=%.4f and maximal rho %.4f without columb interactions.\n",N,frequency,maxRho);
    }
    tolerance = 1E-5;
    minRho = 0.0;
    //INITZIALISE
    int *k = new int;
    int *l = new int;

    Matrix  H,R,E,L,X,P;

    X.setZeros(N,1);
    X = rho(minRho,maxRho,N);
    R.setIdentity(N);
    H = Hamiltonian(N,X,frequency,columbInteraction);
    L.setOnes(N,1);
    findLargestNonsetDiagonalElement(H,N,k,l);
    amax = H(*k,*l);
    int i = 0;
    int unittest = 1;
    int maxIterations = 500000;
    while(fabs(amax)>=tolerance && i<maxIterations){
        JacobiRotation(H,R,N,*k,*l);
        findLargestNonsetDiagonalElement(H,N,k,l);
        amax = H(*k,*l);
        i++;

        if(unittest == unitIteration && unitTesting){
            UnitTest(R,i,N,"UnitTest");
            unittest = 0;
        }
        unittest++;
    }
    printf("Ended successfully with i=%i iterations.\n",i);
    E = H*L;

    //SORTING EIGENVALUES AND VECTORS IN INCREASING ORDER
    double e,emin;
    int jmin;
    Matrix  r;
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
            E.setElement(0,i,E(0,jmin));
            E.setElement(0,jmin,e);
            r = R.getColumn(i);
            R.setColumn(i,R.getColumn(jmin));
            R.setColumn(jmin,r);
        }
    }

    //WRITE RESULTS TO FILES
    string addon;
    if(frequency > 0){
        addon = 'F' + to_string(frequency);
        addon.erase(addon.end()-4,addon.end());
        if(columbInteraction){
            addon = addon+"Columb";
        }


    }else{
        addon = 'N' + to_string(N);
    }
    ofile.open(eigenvals + addon);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    if(i==maxIterations){
        printf("WARNING! Maximal number of iterations reached. Increase 'maxiteration' \n");
        ofile << "WARNING! Maximal number of iterations reached. Increase 'maxiteration' " << endl;
    }
    ofile << "Number of iterations: " << i << "     Freq: " << frequency << endl;
    ofile << "Eigenvalues:" << endl;
    for(int i = 0;i<N;i++){
        ofile << E(0,i) << "    ";
    }
    ofile.close();

    ofile.open(eigenvecs + addon);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "X-coordinates at first line, Eigenvectors below:" << endl;
    for(int i = 0;i<N;i++){
        ofile << X(0,i) << "    ";
    }
    ofile << endl;
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            ofile << R(i,j) << "    ";
        }
        ofile << endl;
    }
    ofile.close();
}

