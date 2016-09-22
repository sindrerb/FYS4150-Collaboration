#include <iostream>
#include <armadillo>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include "time.h"

using namespace std;
using namespace arma;



void findLargestNonDiagonalElement(mat A, int n, int *k, int *l){
    // FIND THE LARGEST NON-DIAGONAL ELEMENT
    double a_max = 0;
    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n; j++){
            if(i!=j){
                if(fabs(A(i,j))>a_max){
                    *k = i;
                    *l = j;
                    a_max = A(i,j);
                }
            }
        }
    }

}

mat JacobiRotation(mat A, int n, int k, int l){
    double a_kl = A(k,l);
    double a_kk = A(k,k);
    double a_ll = A(l,l);
    //SOLVE T^2+2*tau*T-1=0
    double c,s,t;
    if(a_kl!=0.0){
        double tau = (a_ll-a_kk)/(2*a_kl);
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
    A(k,k)=a_kk*cc-cross+a_ll*ss;
    A(l,l)=a_ll*cc+cross+a_kk*ss;
    A(k,l)=0.0;
    A(l,k)=0.0;
    for(int i=0;i<n;i++){
        if(i!=k && i!=l){
            a_ik=A(i,k);
            a_il=A(i,l);
            A(i,k)=a_ik*c-a_il*s;
            A(k,i)=A(i,k);
            A(i,l)=a_il*c+a_ik*s;
            A(l,i)=A(i,l);
        }

    }
    return A;
}

int main(int argc, char *argv[])
{
    int n;
    int *k = new int;
    int *l = new int;
    n = 4;
    double amax,tolerance;
    tolerance = 1E-4;

    mat A = randu<mat>(n,n);
    A.print("A=");
    findLargestNonDiagonalElement(A,n,k,l);
    amax = A(*k,*l);
    int i = 0;
    int maxit = 10;
    while(fabs(amax)>=tolerance && i<maxit){
        A = JacobiRotation(A,n,*k,*l);
        printf("max[%i]=%f \n",i,amax);
        findLargestNonDiagonalElement(A,n,k,l);
        amax = A(*k,*l);
        i++;
    }
    A.print("A=");
}

