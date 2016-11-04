#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 3;

    // Initialize lattice with values
    double **lattice = new double*[n];
    for(int i = 0; i<n;i++) {
        lattice[i] = new double[n];
        for(int j = 0; j<n;j++) {
            lattice[i][j] = 1;
        }
    }
    //Pseudo lattice containting pointers to the original lattice
    double corner = 0;
    //Initialize pseudo lattice with empty pointers
    double ***pseudoLattice = new double**[n+2];
    for(int i = 0; i<n+2;i++) {
        pseudoLattice[i] = new double*[n+2];
        for(int j = 0; j<n+2;j++) {
            pseudoLattice[i][j] = NULL;
        }
    }
    //Set pointers to lattice
    for(int i = 1; i<n+1;i++) {
        for(int j = 1; j<n+1;j++) {
            pseudoLattice[i][j] = &lattice[i-1][j-1];
        }
    }
    for(int i = 1; i<n+1;i++) {
        pseudoLattice[0][i] = &lattice[n-1][i-1];
        pseudoLattice[n+1][i] = &lattice[0][i-1];
        pseudoLattice[i][0] = &lattice[i-1][n-1];
        pseudoLattice[i][n+1] = &lattice[i-1][0];
    }
    pseudoLattice[0][0] = &corner;
    pseudoLattice[0][n+1] = &corner;
    pseudoLattice[n+1][0] = &corner;
    pseudoLattice[n+1][n+1] = &corner;
}
