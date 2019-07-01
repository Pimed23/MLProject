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
    
    Matrix<double> t1(25,401);
    t1.fillArchive("Theta1data.txt");
    Matrix<double> t2(10,26);
	t2.fillArchive("Theta2data.txt");
	
    NeuralNetwork a(3,n,X,y,1.0);
   //a.setWeightsByLayer(0,t1);
   //a.setWeightsByLayer(1,t2);
    
    //Matrix<double> test(1,400);
    //test.fillArchive("numx.txt");
    a.gradientDescent(0.5);
    cout<<a.feedForwardPropagation();
    //a.prediction(test);
    return 0;
}
