#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

    Matrix<double> M( 2, 4 );
    M.fillArchive( "data.txt" );
    Matrix<double> N;
    N = M.addOnes();
    Matrix<double> S;
    S = N.cutOnes();
    cout << S << endl;
    return 0;
}