/*
 * ann.h
 *
 *  Created on: Oct 19, 2016
 *      Author: Praveen
 */

#ifndef ANN_H_
#define ANN_H_

#include<vector>
#include"matrix.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<time.h>
using namespace std;

class Ann{
public:
	std::vector<int> structure;
	std::vector< std::vector<long double> > weightTable;
	std::vector<std::vector<long double> > output;
	std::vector<std::vector<long double> >error;
	std::vector<std::vector< int> > node;

	std::vector< std::vector<long double> > train_inputTable;
	std::vector< std::vector<long double> > test_inputTable;

	std::vector< int> train_output;
	std::vector< int> test_output;

	long double alpha;
	std::vector<std::vector<long double> > digit_encoding;

	long double getEuclideanDistance(long double x1, long double y1, long double x2, long double y2);
	long double getEuclideanDistance(std::vector<long double> X, std::vector<long double> Y);

	long double getFSigmoid(long double in);

	long double getSigmoid(long double in);
	long double getSigmoidError(long double out, long double error);

	long double getRectifier(long double in);
	long double getRectifierError(long double out);


	void initStructure(char *);
	void initweightTable(char *);
	void initOutput();
	void initError();
	void initNode();
	void initDigitEncoding();
	void initTrainInput(char *);
	void initTrainOutput(char *);
	void initTestInput(char *);
	void initTestOutput(char *);


	virtual void calculateValueAt(int layer, int nodeNum);
	virtual void calculateErrorAt(int layer, int nodeNum);
	virtual void calculateErrorAtOutputLayer(int layer, int nodeNum, long double output);
	void updateValuesInForwardPass();
	void updateErrorsInBackwardPass();
	void doForwardPassIteration(std::vector< std::vector<long double> > ,int);
	void doBackwardPassIteration(std::vector< int> , int);
	virtual void updateWeights();
	int findDigit();



	Ann();
	Ann( char *, char *, char *, char *, char *, char *);

	void trainWeightsModel(int);
	void validateTestInput();

	void showOutput();
	void showError();
	void showNode();
	void showWeight();

};




#endif /* ANN_H_ */
