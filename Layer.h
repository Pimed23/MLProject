#ifndef LAYER_H
#define LAYER_H

#include "Matrix.h"
#include "Utilities.h"
#include <vector>


using namespace std;

class Layer{
	private:
		int noUnits;
		Matrix<double> unitsZ;
		Matrix<double> weights;
	public:
		Layer();
		Layer(const Matrix<double>& unitsZ,int unitsLayerIn,int unitsLayerOout);
		Layer(const Layer& copy);
		~Layer();
		int getNoUnits ();
		Matrix<double>& getUnitsZ();
		Matrix<double>& getWeights();
		void setNoUnits(int noUnits);
		void setUnitsZ(const Matrix<double>& unitsZ);
		void setWeights(const Matrix<double>& weights);
		Matrix<double> getSigmoidZ();
		
};

Layer::Layer(){
	this->noUnits = 0;
}

Layer::Layer(const Matrix<double>& unitsZ,int unitsLayerIn,int unitsLayerOut){
	this->weights=randInitializeWeights(unitsLayerIn,unitsLayerOut);
	this->noUnits=unitsLayerIn;
	this->unitsZ=unitsZ;
}

Layer::Layer(const Layer& copy){
	this->noUnits = copy.noUnits;
	this->unitsZ  = copy.unitsZ;
	this->weights = copy.weights;
}

Layer::~Layer(){
	
}

int Layer::getNoUnits (){
	return this->noUnits;
}

Matrix<double>& Layer::getUnitsZ(){
	return this->unitsZ;
}

Matrix<double>& Layer::getWeights(){
	return this->weights;
}

void Layer::setNoUnits(int noUnits){
	this->noUnits = noUnits;
}

void Layer::setUnitsZ(const Matrix<double>& unitsZ){
	this->unitsZ = unitsZ;
}

void Layer::setWeights(const Matrix<double>& weights){
	this->weights = weights;
}

Matrix<double> Layer::getSigmoidZ(){
	Matrix<double> aux=this->unitsZ;
	sigmoidFunction(aux);
	return aux;
}

#endif
