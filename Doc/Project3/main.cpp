#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "matrix.h"
#include "vec3.h"
using namespace std;

int main(){

    int NUMBER_OF_ITERATIONS = 1000;
    double START_TIME = 0;
    double END_TIME = 100;
    int stepLength = (END_TIME - START_TIME)/NUMBER_OF_ITERATIONS;

    vec3 vector1(1,2,3);
    vector1.print();
    cout << vector1 << endl;

    return 0;
}
