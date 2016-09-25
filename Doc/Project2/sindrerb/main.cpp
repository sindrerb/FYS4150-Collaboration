#include <matrix.h> //Private
#include <iostream>
#include <armadillo>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h>
#include "time.h"

using namespace std;
using namespace arma;

void findLargestNonDiagonalElement(matrix<double>A, int n, int *k, int *l){
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
    int n;
    int *k = new int;
    int *l = new int;
    n = 20;
    double amax,tolerance;
    tolerance = 1E-4;

    matrix<double> A,R;
    A.random(n,n);
    R.identity(n);


    findLargestNonDiagonalElement(A,n,k,l);
    amax = A(*k,*l);
    int i = 0;
    int maxit = 1000;
    while(fabs(amax)>=tolerance && i<maxit){
        JacobiRotation(A,R,n,*k,*l);
        findLargestNonDiagonalElement(A,n,k,l);
        amax = A(*k,*l);
        i++;
    }
}

