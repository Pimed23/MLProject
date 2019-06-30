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

Matrix<double> sigmoidGradient( Matrix<double> &M ) {
    Matrix<double> N( M.getRow(), M.getCol());
    N = M % oneMinus( M );
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

    Matrix<double> z3( a2.getRow(), Theta2.getRow());
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

void backPropagation( Matrix<double> X, Matrix<double> y, Matrix<double> Theta1, Matrix<double> Theta2, double lambda ) {
    
    int m = X.getRow();
    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix<double> yVec( m, outputLayer );
    for( int i = 0; i < m; ++i ) {
        int j = y[ i ][ 0 ];
        if( j != 10 )
            yVec[ i ][ j - 1 ] = 1;
        else
            yVec[ i ][ 9 ] = 1;
    }
    
    Matrix<double> XPrep;
    XPrep = X.addOnes().transpose();

    Matrix<double> Theta1Grad( Theta1.getRow(), Theta1.getCol());
    Matrix<double> Theta2Grad( Theta2.getRow(), Theta2.getCol());
       
    for( int i = 0; i < m; ++i ) {
        Matrix<double> a1( inputLayer + 1, 1 );
        a1 = XPrep.columna( i );
        
        Matrix<double> z2( hiddenLayer, inputLayer + 1 );
        z2 = Theta1 * a1;

        Matrix<double> a2( hiddenLayer + 1, z2.getCol());
        sigmoidFunction( z2 );
        a2 = z2.addOnesCol();

        Matrix<double> z3( outputLayer, 1 );
        z3 = Theta2 * a2;

        Matrix<double> a3( z3.getCol(), z3.getRow());
        sigmoidFunction( z3 );
        a3 = z3;

        Matrix<double> yy;
        yy = yVec.transpose().columna( i );

        Matrix<double> delta3;
        delta3 = a3 - yy;

        Matrix<double> z2SigGrad;
        z2SigGrad = sigmoidGradient( z2 );

        Matrix<double> delta2;
        delta2 = ( Theta2.transpose() * delta3 ) % z2SigGrad.addOnesCol();
        delta2 = delta2.cutOnesCol();
            
        Theta1Grad = Theta1Grad + ( delta2 * a1.transpose());
        Theta2Grad = Theta2Grad + ( delta3 * a2.transpose()); 
    }

    Theta1Grad = Theta1Grad.multScalar( 1.0 / m ) + Theta1.cutOnes().addZeros().multScalar( lambda / m );
    Theta2Grad = Theta2Grad.multScalar( 1.0 / m ) + Theta2.cutOnes().addZeros().multScalar( lambda / m );

}

#endif


