#include "Matrix.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

int main() {
    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix<double> X( 5000, 400 );
    X.fillArchive( "Xdata.txt");
    Matrix<double> y( 5000, 1 );
    y.fillArchive( "ydata.txt");
    Matrix<double> Theta1( 25, 401 );
    Theta1.fillArchive( "Theta1data.txt");
    Matrix<double> Theta2( 10, 26 );
    Theta2.fillArchive( "Theta2data.txt");
    Matrix<double> hyp;
    hyp = feedForward( X, Theta1, Theta2 );
    costFunction( hyp, y, outputLayer );


}