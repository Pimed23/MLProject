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
		Layer* layers;
	public:
		NeuralNetwork();
		NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, const Matrix<double>& trainingLabels);
		~NeuralNetwork();
};

NeuralNetwork::NeuralNetwork(){
	this->noLayers=0;
	layers = new Layer[0];
}

NeuralNetwork::NeuralNetwork(int noLayers, vector<int>& unitsPerLayer, const Matrix<double>& trainingSet, 
                             const Matrix<double>& trainingLabels){
	this->noLayers = noLayers;
	this->trainingSet = trainingSet;
	this->trainingLabels = trainingLabels;
	layers = new Layer [noLayers];
	for(int i=0;i<noLayers-1;i++){
		layers[i].setNoUnits(unitsPerLayer[i]);
		Matrix<double> aux(unitsPerLayer[i],1);
		layers[i].setUnitsZ(aux);
		Matrix<double> aux1; 
		aux1 = randInitializeWeights(unitsPerLayer[i],unitsPerLayer[i+1]);
		layers[i].setWeights(aux1);
	}
}

NeuralNetwork::~NeuralNetwork(){
	delete [] layers;
}

#endif
