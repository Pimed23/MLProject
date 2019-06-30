#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

    Matrix<double> M( 2, 4 );
    M.fillArchive( "data.txt" );
    M.sumScalar( -1.0 );
    cout << M << endl;

    return 0;
}