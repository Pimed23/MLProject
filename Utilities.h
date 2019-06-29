#ifndef UTILITIES_H
#define UTILITIES_H

#include "Matrix.h"
#include <math.h>
#include <cstdlib>

void sigmoidFunction( Matrix<double> &M ) {
    for( int i = 0; i < M.getRow(); ++i )
        for( int j = 0; j < M.getCol(); ++j )
            M[ i ][ j ] = 1.0 / ( 1.0 + exp( M[ i ][ j ]));
}

Matrix<double> randInitializeWeights( int L_in, int L_out) {
    Matrix<double> M( L_out, L_in + 1 );
    double epsInit = 0.12;
    for( int i = 0; i < M.getRow(); ++i )
        for( int j = 0; j < M.getCol(); ++j ) {
            double nRand = ( rand() % 1001 ) / 1000.0f;
            M[ i ][ j ] = nRand * 2 * epsInit - epsInit;
        }
    return M;
}





#endif


