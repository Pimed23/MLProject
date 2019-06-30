#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Utilities.h"
#include "Layer.h"
#include "NeuralNetwork.h"

using namespace std;

int main() {

    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix <double> X( 5000, 400 );
    X.fillArchive("Xdata.txt");
    
    Matrix <double> y(5000,1);
    y.fillArchive("ydata.txt");
    
    vector<int> n;
    n.push_back(400);
    n.push_back(25);
    n.push_back(10);
    
	
    NeuralNetwork a(3,n,X,y);
    return 0;
}
