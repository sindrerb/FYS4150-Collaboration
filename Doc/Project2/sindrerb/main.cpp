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

matrix<double> Hamiltonian(int n,double h){
    matrix<double> H;
    double v,rho,rho0,alpha;
    alpha = 1.0;
    rho0 = 1.0/alpha;
    matrix<double> I,V;
    H.diagonal(n,2,-1);
    V.identity(n);
    for(int i = 0; i<n;i++){
        rho = rho0 + ((double)i+1.0)*h;
        v = rho*rho;
        V.assign(i,i,v);
    }
    H = H/(h*h);
    H = H+V;
    return H;
}

void findLargestNonDiagonalElement(matrix<double> A, int n, int *k, int *l){
    // FIND THE LARGEST NON-DIAGONAL ELEMENT
    double a_max,a_temp,a;
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

int main()//int argc, char *argv[])
{
    string eigenvals = "eigenvals";
    string eigenvecs = "eigenvecs";
    int N;
    double h,amax,tolerance;
    N = 3;
    h = 1;
    tolerance = 1E-4;

    //INITSIALIZE
    int *k = new int;
    int *l = new int;
    matrix<double> H,R,E,L;
    R.identity(N);
    H = Hamiltonian(N,h);
    L.ones(N,1);
    H.print('H');
    findLargestNonDiagonalElement(H,N,k,l);
    amax = H(*k,*l);

    int i = 0;
    int unittest = 1;
    int maxit = 1000;
    while(fabs(amax)>=tolerance && i<maxit){
        JacobiRotation(H,R,N,*k,*l);
        findLargestNonDiagonalElement(H,N,k,l);
        amax = H(*k,*l);
        i++;
        if(unittest == 50){
            OrthogonalTest(R,i,"ortoTest");
            unittest = 0;
        }
        unittest++;

    }

    /* COMPARE TO ARMADILLO, EAQUAL RESULTS
    double hh = 1/(h*h);
    double V;
    mat G(N,N);
    for(int i = 0; i<N;i++){
        for(int j= 0;j<N;j++){
            if(i==j){
                V = 1+(i+1)*h;
                G(i,j)= 2*hh+V*V;
            }else if(i+1==j || i-1==j){
                G(i,j)= -hh;
            }else{
                G(i,j)=0.0;
            }
        }
    }
    G.print("G");
    mat F = eig_sym(G);
    F.print("F");
    */


    printf("i=%i \n",i);
    E = H*L;
    E.print('E');

    ofile.open(eigenvals);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Number of iterations: " << i << "     "<< endl;
    E.fprint('E');
    ofile.close();

    ofile.open(eigenvecs);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    R.fprint('R');
    ofile.close();


}

