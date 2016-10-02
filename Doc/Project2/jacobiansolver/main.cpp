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
    //Write the temporary eigenbasis to a file to check orthogonality and normality
    ofile.open(filename + to_string(i));
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Printout for unit tests: "<<endl;
    ofile << "Iteration "<<i<<endl;
    ofile.close();
    M.printToFile("Matrix:",filename + to_string(i));
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
Matrix  TwoParticlePotential(int n, Matrix  X, double frequency, bool useColumbInteraction){
    double v,x;
    Matrix  V;  
    V.setIdentity(n);
    for(int i = 0; i<n;i++){
        x = X(0,i);
        v = x*x*frequency*frequency;
        if(useColumbInteraction){
            v += 1.0/x;
        }
        V.setElement(i,i,v);
    }
    return V;
}

Matrix  Hamiltonian(int n,Matrix  X,double frequency,bool useColumbInteraction){
    Matrix  H,V;
    double h;
    h = (X(0,1)-X(0,0));
    H.setDiagonal(n,2,-1);
    H = H/(h*h);
    if(frequency != 0){
        V = TwoParticlePotential(n,X,frequency,useColumbInteraction);
    }else{
        V = OneParticlePotential(n,X);
    }
    H = H+V;
    return H;
}

void findLargestNonDiagonalElement(Matrix  A, int n, int *k, int *l){
    double largestElement,temporaryElement;
    largestElement = 0;
    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n; j++){
            if(i!=j){
                temporaryElement = fabs(A(i,j));
                if(temporaryElement>largestElement){
                    *k = i;
                    *l = j;
                    largestElement = temporaryElement;
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
    //REASSIGN ELEMENTS
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
    //REASSIGN EIGENVECTOR BASIS
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
    double maximumRho,minimumRho,frequency,largestElement,accuaracyTolerance, unitTestIterationPoint;
    bool useColumbInteraction, useUnitTesting;
    if(argc<6){
        printf("Please write arguments:\n Iterations:100-300\n Frequency:0-10 (leave 0 for single particle)\n Maximal rho: 5-50\n Columb interactions (1=true/0=false)\n Unit test at iteration i: 100-10 000 (leave 0 for no test)\n");
        return 0;
    }else{
        N = atoi(argv[1]);
        frequency = atof(argv[2]);
        maximumRho = atof(argv[3]);
        if(atoi(argv[4])==1){
            useColumbInteraction = true;
        }else{
            useColumbInteraction=false;
        }
        unitTestIterationPoint = atoi(argv[5]);

    }
    if(unitTestIterationPoint>0){
        useUnitTesting = true;
    }else{
        useUnitTesting = false;
    }
    if(useColumbInteraction){
            printf("Running calculations using N=%i, Freq.=%.4f and maximal rho %.4f with columb interactions.\n",N,frequency,maximumRho);
    }else{
            printf("Running calculations using N=%i, Freq.=%.4f and maximal rho %.4f without columb interactions.\n",N,frequency,maximumRho);
    }
    accuaracyTolerance = 1E-5;
    minimumRho = 0.0;
    //INITZIALISE
    int *k = new int;
    int *l = new int;

    Matrix  HamiltonianMatrix,EigenvectorBasis,EigenvalueVector,onesVector,RhoVector;

    RhoVector = rho(minimumRho,maximumRho,N);
    EigenvectorBasis.setIdentity(N);
    HamiltonianMatrix = Hamiltonian(N,RhoVector,frequency,useColumbInteraction);
    onesVector.setOnes(N,1);
    findLargestNonDiagonalElement(HamiltonianMatrix,N,k,l);
    largestElement = HamiltonianMatrix(*k,*l);
    int i = 0;
    int unitTestCounter = 1;
    int maximumIterations = 500000;
    while(fabs(largestElement)>=accuaracyTolerance && i<maximumIterations){
        JacobiRotation(HamiltonianMatrix,EigenvectorBasis,N,*k,*l);
        findLargestNonDiagonalElement(HamiltonianMatrix,N,k,l);
        largestElement = HamiltonianMatrix(*k,*l);
        i++;

        if(unitTestCounter == unitTestIterationPoint && useUnitTesting){
            UnitTest(EigenvectorBasis,i,N,"UnitTest");
            unitTestCounter = 0;
        }
        unitTestCounter++;
    }
    printf("Ended successfully with i=%i iterations.\n",i);
    EigenvalueVector = HamiltonianMatrix*onesVector;

    //SORTING EIGENVALUES AND VECTORS IN INCREASING ORDER
    double eigenvalueElement,minimumEigenvalue;
    int j_minimumEigenvalue;
    Matrix  Eigenvector;
    for(int i=0;i<N;i++){
        j_minimumEigenvalue = i;
        minimumEigenvalue = EigenvalueVector(0,i);
        for(int j=i+1;j<N;j++){
            if(minimumEigenvalue>EigenvalueVector(0,j)){
                minimumEigenvalue = EigenvalueVector(0,j);
                j_minimumEigenvalue = j;
            }
        }
        if(j_minimumEigenvalue != i){
            //RESASSIGN EIGENVALUES
            eigenvalueElement = EigenvalueVector(0,i);
            EigenvalueVector.setElement(0,i,EigenvalueVector(0,j_minimumEigenvalue));
            EigenvalueVector.setElement(0,j_minimumEigenvalue,eigenvalueElement);
            //REASSIGN EIGENVECTOR BASIS
            Eigenvector = EigenvectorBasis.getColumn(i);
            EigenvectorBasis.setColumn(i,EigenvectorBasis.getColumn(j_minimumEigenvalue));
            EigenvectorBasis.setColumn(j_minimumEigenvalue,Eigenvector);
        }
    }

    //WRITE RESULTS TO FILES
    string addon;
    if(frequency > 0){
        addon = 'F' + to_string(frequency);
        addon.erase(addon.end()-4,addon.end());
        if(useColumbInteraction){
            addon = addon+"Columb";
        }


    }else{
        addon = 'N' + to_string(N);
    }
    ofile.open(eigenvals + addon);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    if(i==maximumIterations){
        printf("WARNING! Maximal number of iterations reached. Increase 'maxiteration' \n");
        ofile << "WARNING! Maximal number of iterations reached. Increase 'maxiteration' " << endl;
    }
    ofile << "Number of iterations: " << i << "     Freq: " << frequency << endl;
    ofile.close();
    EigenvalueVector.printToFile("E",eigenvals + addon);

    ofile.open(eigenvecs + addon);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "X-coordinates at first line, Eigenvectors below:" << endl;
    ofile.close();
    RhoVector.printToFile(" ",eigenvecs + addon);
    EigenvectorBasis.printToFile(" ",eigenvecs + addon);
}

