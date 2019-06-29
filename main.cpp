#include <iostream>
#include <vector>
#include <thread>
#include "Matrix.h"
#include "Utilities.h"



using namespace std;

int main() {

    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix <double> M( 5000, 400 );
    M.fillArchive("Xdata.txt");
    sigmoidFunction( M );
    
    Matrix <double> initTheta1; 
    Matrix <double> initTheta2;
    initTheta1 = randInitializeWeights( inputLayer, hiddenLayer );
    initTheta2 = randInitializeWeights( hiddenLayer, outputLayer );

    cout << initTheta1 << endl;
    cout << initTheta2 << endl;

    return 0;
}
