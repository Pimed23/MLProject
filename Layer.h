#ifndef LAYER_H
#define LAYER_H

#include "Matrix.h"
#include "Utilities.h"
#include <vector>


using namespace std;

//Incluye BIAS en unitsZ y noUnits, menos la última capa
class Layer{
	private:
		int noUnits;
		Matrix<double> units_a;
		Matrix<double> weights;
	public:
		Layer();
		Layer(const Matrix<double>& units_a,int unitsLayerIn,int unitsLayerOut);
		Layer(const Layer& copy);
		~Layer();
		int getNoUnits ();
		Matrix<double>& getUnits_a();
		Matrix<double>& getWeights();
		void setNoUnits(int noUnits);
		void setUnits_a(const Matrix<double>& units_a);
		void setWeights(const Matrix<double>& weights);
		
};

Layer::Layer(){
	this->noUnits = 0;
}

//El unitsZ que recibe debe incluir BIAS
Layer::Layer(const Matrix<double>& units_a,int unitsLayerIn,int unitsLayerOut){
	this->weights = randInitializeWeights(unitsLayerIn,unitsLayerOut);
	this->noUnits = unitsLayerIn + 1;
	this->units_a = units_a;
}

Layer::Layer(const Layer& copy){
	this->noUnits = copy.noUnits;
	this->units_a  = copy.units_a;
	this->weights = copy.weights;
}

Layer::~Layer(){
	
}

int Layer::getNoUnits (){
	return this->noUnits;
}

Matrix<double>& Layer::getUnits_a(){
	return this->units_a;
}

Matrix<double>& Layer::getWeights(){
	return this->weights;
}

void Layer::setNoUnits(int noUnits){
	this->noUnits = noUnits;
}

void Layer::setUnits_a(const Matrix<double>& units_a){
	this->units_a = units_a;
}

void Layer::setWeights(const Matrix<double>& weights){
	this->weights = weights;
}

#endif
