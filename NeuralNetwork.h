#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Matrix.h"
#include "Layer.h"
#include "Utilities.h"
#include <vector>
using namespace std;

class NeuralNetwork{
	private:
		Matrix<double> trainingSet;//X
		Matrix<double> trainingLabels;//Y
		int noLayers;
		double lambda; //Regularize constant
		Layer* layer;
	public:
		NeuralNetwork();
		NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, const Matrix<double>& trainingLabels, 						 double lamda);
		~NeuralNetwork();
		double getLambda();
		void setLambda(double lambda);
		void setWeightsByLayer(int index,Matrix<double>& aux);
		Matrix<double>& feedForwardPropagation();
		double costFunction();
		void backPropagation();
		void gradientDescent(double alpha);
};

NeuralNetwork::NeuralNetwork(){
	this->noLayers=0;
	layer = new Layer[0];
}

NeuralNetwork::NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, 
                             const Matrix<double>& trainingLabels, double lambda){
	this->noLayers = noLayers;
	this->lambda = lambda;
	this->trainingSet = trainingSet;
	this->trainingLabels = trainingLabels;
	layer = new Layer [noLayers];
	int i=0;
	for(;i<noLayers-1;i++){
		layer[i].setNoUnits(unitsPerLayer[i]);
		Matrix<double> aux1;
		aux1 = randInitializeWeights(unitsPerLayer[i],unitsPerLayer[i+1]);
		layer[i].setWeights(aux1);
	}
	layer[i].setNoUnits(unitsPerLayer[i]);
}

NeuralNetwork::~NeuralNetwork(){
	delete [] layer;
}

double NeuralNetwork::getLambda(){
	return this->lambda;
}

void NeuralNetwork::setLambda(double lambda){
	this->lambda = lambda;
}

void NeuralNetwork::setWeightsByLayer(int index,Matrix<double>& aux){
	this->layer[index].setWeights(aux);
}

Matrix<double>& NeuralNetwork::feedForwardPropagation(){
	(this->layer)[0].setUnits_a(this->trainingSet);
	Matrix<double> X=(this->trainingSet);
	Matrix<double> a1;
    a1 = X.addOnes();

    Matrix<double> z2;
    z2 = a1 * (this->layer)[0].getWeights().transpose();
	sigmoidFunction( z2 );
	
    (this->layer)[1].setUnits_a(z2);
	Matrix<double> a2;
    a2 = z2.addOnes();

    Matrix<double> z3;
    z3 = a2 * (this->layer)[1].getWeights().transpose();
    sigmoidFunction( z3 );
    
    (this->layer)[2].setUnits_a(z3);
    return (this->layer)[2].getUnits_a();
}

double NeuralNetwork::costFunction(){
	int m = (this->trainingLabels).getRow();
    Matrix<double> yVec( m, 10 );
    for( int i = 0; i < m; ++i ) {
        int j = (this->trainingLabels)[ i ][ 0 ];
        if( j != 10 )
            yVec[ i ][ j - 1 ] = 1;
        else
            yVec[ i ][ 9 ] = 1;
    }

    Matrix<double> cost;
    Matrix<double> oneMHyp;
    oneMHyp = oneMinus( layer[2].getUnits_a() );
    cost =  yVec.multScalar( -1 ) % logaritmo( layer[2].getUnits_a() ) - oneMinus( yVec ) % logaritmo( oneMHyp );
    double J = cost.addAll() / 5000;

    Matrix<double> t1;
    t1 = layer[0].getWeights().cutOnes().powTwice();

    Matrix<double> t2;
    t2 = layer[1].getWeights().cutOnes().powTwice();

    
    double reg = ( t1.addAll() + t2.addAll()) * ( lambda /( 2 * m ));
    
    J = J + reg;
    return J; 
}

void NeuralNetwork::backPropagation(){
	int m = (this->trainingLabels).getRow();
    int inputLayer = 400;
    int hiddenLayer = 25;
    int outputLayer = 10;

    Matrix<double> yVec( m, outputLayer );
    for( int i = 0; i < m; ++i ) {
        int j = (this->trainingLabels)[ i ][ 0 ];
        if( j != 10 )
            yVec[ i ][ j - 1 ] = 1;
        else
            yVec[ i ][ 9 ] = 1;
    }
    
    Matrix<double> XPrep;
    XPrep = (this->trainingSet).addOnes().transpose();

    Matrix<double> Theta1Grad( (layer[0].getWeights()).getRow(), (layer[0].getWeights()).getCol());
    Matrix<double> Theta2Grad( (layer[1].getWeights()).getRow(), (layer[1].getWeights()).getCol());
       
    for( int i = 0; i < m; ++i ) {
        Matrix<double> a1( inputLayer + 1, 1 );
        a1 = XPrep.columna( i );
        
        Matrix<double> z2( hiddenLayer, inputLayer + 1 );
        z2 = (layer[0].getWeights()) * a1;

        Matrix<double> a2( hiddenLayer + 1, z2.getCol());
        sigmoidFunction( z2 );
        a2 = z2.addOnesCol();

        Matrix<double> z3( outputLayer, 1 );
        z3 = (layer[1].getWeights()) * a2;

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
        delta2 = ( (layer[1].getWeights()).transpose() * delta3 ) % z2SigGrad.addOnesCol();
        delta2 = delta2.cutOnesCol();
            
        Theta1Grad = Theta1Grad + ( delta2 * a1.transpose());
        Theta2Grad = Theta2Grad + ( delta3 * a2.transpose()); 
    }

    Theta1Grad = Theta1Grad.multScalar( 1.0 / m ) + (layer[0].getWeights()).cutOnes().addZeros().multScalar( lambda / m );
    Theta2Grad = Theta2Grad.multScalar( 1.0 / m ) + (layer[1].getWeights()).cutOnes().addZeros().multScalar( lambda / m );

	layer[0].setPartialDerivatives(Theta1Grad);
	layer[1].setPartialDerivatives(Theta2Grad);

}

void NeuralNetwork::gradientDescent(double alpha){
	for(int i=0;i < 500; i++){
		backPropagation();
		layer[0].setUnits_a(layer[0].getUnits_a() - (layer[0].getPartialDerivatives()).multDouble(alpha));
		layer[1].setUnits_a(layer[1].getUnits_a() - (layer[1].getPartialDerivatives()).multDouble(alpha));
		cout<<"Iteracion "<<i<<endl;
	}
}












#endif
