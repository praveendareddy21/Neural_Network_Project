/*
 * sigmoid_ann.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: Consumer
 */
#include"sigmoid_ann.h"

long double getSigmoid(long double in){
	long double exp_value;
	long double return_value;
	exp_value = exp(-in);
	return_value = ((long double)1) / (1 + exp_value);
	 return return_value;
}

long double getFSigmoid(long double in){

	long double return_value;
	return_value = ((long double)in) / (1 + abs(in));
	 return return_value;
}

long double getSigmoidError(long double out, long double error){
	return out * (1-out) * error;

}


void Sig_Ann::calculateValueAt(int layer, int nodeNum){

	long double value = weightTable[0][node[layer][nodeNum]];
	int input_node = 0;

	for(int i=0;i < output[layer-1].size();i++ ){
		input_node = node[layer-1][i];
		value += output[layer-1][i]* weightTable[input_node][node[layer][nodeNum]];
	}


	output[layer][nodeNum] = getFSigmoid(value);
	//output[layer][nodeNum] = getFSigmoid(value);

	//output[layer][nodeNum] = getRectifier(value);
}

void Sig_Ann::calculateErrorAt(int layer, int nodeNum){

	int input_node = 0;
	long double calculatedValue = output[layer][nodeNum];
	long double errorV = 0.0;

	for(int i=0;i < output[layer+1].size();i++ ){
		//matError.set(0,i, error[layer+1][i]);
		input_node = node[layer][nodeNum];


		errorV += error[layer+1][i] *  weightTable[input_node][node[layer+1][i]];
	}

	error[layer][nodeNum] = getSigmoidError(calculatedValue , errorV);

	//error[layer][nodeNum] = getRectifierError(errorV);
}

void Sig_Ann::calculateErrorAtOutputLayer(int layer, int nodeNum, long double outputLayerValue){

	long double calculatedValue = output[layer][nodeNum];
	error[layer][nodeNum] =  getSigmoidError(calculatedValue, outputLayerValue - calculatedValue );
}


