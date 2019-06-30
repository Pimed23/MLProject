#ifndef UTILITIES_H
#define UTILITIES_H

#include "Matrix.h"
#include <math.h>
#include <tgmath.h> 
#include <cstdlib>

void sigmoidFunction( Matrix<double> &M ) {
    for( int i = 0; i < M.getRow(); ++i )
        for( int j = 0; j < M.getCol(); ++j )
            M[ i ][ j ] = 1.0 / ( 1.0 + exp( -1 * M[ i ][ j ]));
}

Matrix<double> logaritmo( Matrix<double> M ) {
    Matrix<double> N( M.getRow(), M.getCol());
    for( int i = 0; i < M.getRow(); ++i )
        for( int j = 0; j < M.getCol(); ++j )
            N[ i ][ j ] = log( M[ i ][ j ]);
    return N;
}

Matrix<double> oneMinus( Matrix<double> M ) {
    Matrix<double> N( M.getRow(), M.getCol());
    for( int i = 0; i < M.getRow(); i++ ) 
        for( int j = 0; j < M.getCol(); j++ )
            N[ i ][ j ] = 1 - M[ i ][ j ];
    return N;
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

Matrix<double> feedForward( Matrix<double> X, Matrix<double> Theta1, Matrix<double> Theta2 ) {
    Matrix<double> a1( X.getRow(), X.getCol() + 1 );
    a1 = X.addOnes();

    Matrix<double> z2( a1.getRow(), Theta1.getRow());
    z2 = a1 * Theta1.transpose();

    Matrix<double> a2( z2.getRow(), z2.getCol() + 1 );
    sigmoidFunction( z2 );
    a2 = z2.addOnes();

    Matrix<double> z3( a2.getRow(), Theta2.getCol());
    z3 = a2 * Theta2.transpose();

    Matrix<double> hyp( z3.getRow(), z3.getCol());
    sigmoidFunction( z3 );
    hyp = z3;

    return hyp;    
}

double costFunction( Matrix<double> hyp, Matrix<double> y, Matrix<double> Theta1, Matrix<double> Theta2, int outputLayer, double lambda ) {
    int m = y.getRow();
    Matrix<double> yVec( m, outputLayer );
    for( int i = 0; i < m; ++i ) {
        int j = y[ i ][ 0 ];
        if( j != 10 )
            yVec[ i ][ j - 1 ] = 1;
        else
            yVec[ i ][ 9 ] = 1;
    }

    Matrix<double> cost;
    Matrix<double> oneMHyp;
    oneMHyp = oneMinus( hyp );
    cost =  yVec.multScalar( -1 ) % logaritmo( hyp ) - oneMinus( yVec ) % logaritmo( oneMHyp );
    double J = cost.addAll() / 5000;

    Matrix<double> t1;
    t1 = Theta1.cutOnes().powTwice();

    Matrix<double> t2;
    t2 = Theta2.cutOnes().powTwice();

    
    double reg = ( t1.addAll() + t2.addAll()) * ( lambda /( 2 * m ));
    
    J = J + reg;
    return J; 
}


#endif


