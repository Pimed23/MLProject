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
		Layer* layer;
	public:
		NeuralNetwork();
		NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, const Matrix<double>& trainingLabels);
		~NeuralNetwork();
		void feedForwardPropagation(int index);		
};

NeuralNetwork::NeuralNetwork(){
	this->noLayers=0;
	layer = new Layer[0];
}

NeuralNetwork::NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, 
                             const Matrix<double>& trainingLabels){
	this->noLayers = noLayers;
	this->trainingSet = trainingSet;
	this->trainingLabels = trainingLabels;
	layer = new Layer [noLayers];
	for(int i=0;i<noLayers-1;i++){
		layer[i].setNoUnits(unitsPerLayer[i]+1);
		Matrix<double> aux(1,unitsPerLayer[i]+1);
		layer[i].setUnits_a(aux);
		Matrix<double> aux1; 
		aux1 = randInitializeWeights(unitsPerLayer[i],unitsPerLayer[i+1]);
		layer[i].setWeights(aux1);
	}
}

NeuralNetwork::~NeuralNetwork(){
	delete [] layer;
}

void NeuralNetwork::feedForwardPropagation(int index){
	// inicializando a1 con un 1 y los valores de X en el training set index-th
	((layer[0]).getUnits_a())[0][0] = 1;
	for(int i=0;i<trainingSet.getCol();i++){
		((layer[0]).getUnits_a())[0][i+1] = trainingSet[index][i];
	}

    Matrix<double> z2(layer[0].getUnits_a().getRow(), layer[0].getWeights().getRow());
    z2 = (layer[0].getUnits_a()) * (layer[0].getWeights()).transpose();
	sigmoidFunction( z2 );
	
    // inicializando a2
    ((layer[1]).getUnits_a())[0][0] = 1;
    for(int i=0;i<z2.getCol();i++){
		((layer[1]).getUnits_a())[0][i+1] = z2[0][i];
	}

    Matrix<double> z3(layer[1].getUnits_a().getRow(), layer[1].getWeights().getRow());
    z3 = (layer[1].getUnits_a()) * (layer[1].getWeights()).transpose();

    Matrix<double> hyp( z3.getRow(), z3.getCol());
    sigmoidFunction( z3 );
    hyp = z3;
    layer[2].getUnits_a() = hyp;
    cout<<layer[2].getUnits_a()<<endl; //Hipotesis en forma de vector horizontal
}


#endif
