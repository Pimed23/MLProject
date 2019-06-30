#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Utilities.h"

using namespace std;

int main() {

    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix <double> M( 5000, 400 );
    M.fillArchive("Xdata.txt");
    
    Matrix <double> initTheta1; 
    Matrix <double> initTheta2;
    initTheta1 = randInitializeWeights( inputLayer, hiddenLayer );
    initTheta2 = randInitializeWeights( hiddenLayer, outputLayer );


    return 0;
}
