#ifndef UTILITIES_H
#define UTILITIES_H

#include "Matrix.h"
#include <math.h>

void sigmoidFunction( Matrix<double> &M ) {
    for( int i = 0; i < M.getRow(); ++i )
        for( int j = 0; j < M.getCol(); ++j )
            M[ i ][ j ] = 1.0 / ( 1.0 + exp( M[ i ][ j ]));
}





#endif


