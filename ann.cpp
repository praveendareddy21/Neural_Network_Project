/*
 * ann.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Praveen
 */
#include"ann.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<time.h>
using namespace std;



long double Ann::getEuclideanDistance(vector<long double> X, vector<long double> Y)
{
	long double X_test, Y_test;
	long double squareddist = 0.0;
	long double result=0.0;
	for(unsigned i=0; i<X.size();i++){
		X_test = X[i];
		Y_test = Y[i];
		squareddist += pow(X[i] - Y[i], 2);
	}
	result = sqrt(squareddist);
	return result;
}

int Ann::findDigit(){
	long double minDistance = -1;
	int minDigit = -1;
	long double tempDistance = 0.0;
	std::vector<long double> X;
	std::vector<long double> Y;


	for(int i=0; i < structure[structure.size() -1]; i++){
		X.push_back(output[structure.size() -1][i]);
	}
	for(int i=0; i < structure[structure.size() -1]; i++){
		Y.clear();
		for(int j=0; j < structure[structure.size() -1]; j++){
			Y.push_back(digit_encoding[i][j]);
		}
		tempDistance = getEuclideanDistance(X, Y);
		//cout<<"X size : "<<X.size()<<" Y size : "<<Y.size()<<endl;
		if(minDistance == -1){
			minDistance = tempDistance;
			minDigit = i;
		}
		else if(tempDistance < minDistance){
			minDistance = tempDistance;
			minDigit = i;
		}
	}

	return minDigit;
}

long double Ann::getSigmoid(long double in){
	long double exp_value;
	long double return_value;
	exp_value = exp(-in);
	return_value = ((long double)1) / (1 + exp_value);
	 return return_value;
}

long double Ann::getFSigmoid(long double in){
	long double exp_value;
	long double return_value;
	exp_value = abs(in);
	return_value = ((long double)in) / (1 + exp_value);
	 return return_value;
}

long double Ann::getSigmoidError(long double out, long double error){
	return out * (1-out) * error;

}

long double Ann::getRectifier(long double in){
	return in==0 ? (0.01 * in ): in;
}
long double Ann::getRectifierError(long double in){
		return in==0 ? 0.01: 1;
	}


void Ann::initStructure(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}
	while(true){
		inFile>>z;
		if(inFile.eof())
			break;
		//cout<<" :"<<z<<endl;
		structure.push_back(z);
		}


	std::cout<<"structure matrix"<<std::endl;
	for(unsigned i=0;i<structure.size();i++){
			std::cout<<structure[i]<<" "<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}


void Ann::initTrainInput(char * filename){

	vector<long double> temp;
	fstream inFile;   // input file
	long double z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		if(inFile.peek() == EOF){
			break;
		}
	    //while (inFile.peek() != '\n')
	    for(int k=0; k<structure[0]; k++)
		{
			inFile>>z;
			temp.push_back(z);
	    }
		if(inFile.peek() == EOF){
			break;
		}
	    train_inputTable.push_back(temp);
	    temp.clear();

		}
	std::cout<<"Train input matrix"<<std::endl;
	for(unsigned i=0;i<train_inputTable.size();i++){
		for(unsigned j=0;j<train_inputTable[i].size();j++){
			std::cout<<train_inputTable[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;


}

void Ann::initTrainOutput(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(!inFile.eof()){
		inFile>>z;
		train_output.push_back(z);
		}

	std::cout<<"train_output matrix"<<std::endl;
	for(unsigned i=0;i<train_output.size();i++){
			std::cout<<train_output[i]<<" "<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;

}

void Ann::initTestInput(char * filename){
	vector<long double> temp;
	fstream inFile;   // input file
	long double z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		if(inFile.peek() == EOF){
			break;
		}
	    for(int k=0; k<structure[0]; k++)
		{
			inFile>>z;
			temp.push_back(z);
	    }
		if(inFile.peek() == EOF){
			break;
		}
	    test_inputTable.push_back(temp);
	    temp.clear();


		}
	std::cout<<"test_inputTable matrix"<<std::endl;
	for(unsigned i=0;i<test_inputTable.size();i++){
		for(unsigned j=0;j<test_inputTable[i].size();j++){
			std::cout<<test_inputTable[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;


}

void Ann::initTestOutput(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(!inFile.eof()){
		inFile>>z;
		test_output.push_back(z);
		}

	std::cout<<"test_output matrix"<<std::endl;
	for(unsigned i=0;i<test_output.size();i++){
			std::cout<<test_output[i]<<" "<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;

}

void Ann::initweightTable(char * filename){

	int nodes = 1;
	fstream inFile;   // input file
	long double z;
	for(unsigned i=0;i<structure.size();i++){
		nodes += structure[i];
	}
	weightTable = vector<vector<long double> > (nodes, vector<long double>(nodes, 0) );

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	int irand;
	long double wt;

	srand(time(NULL));

	irand = (rand() % 20) -10 ;

	wt = (long double) irand / 1.0;
	cout<<"rand wt : "<<wt;


	for(int j=0; j<structure.size()-1;j++){
		for(int i=0;i<structure[j];i++){
			for(int k=0; k< structure[j+1]; k++){
				irand = (rand() % 20) -10 ;

				wt = (long double) irand / 100.0;
				//cout<<"rand wt : "<<wt;
				//inFile>>z;
				weightTable[node[j][i]][node[j+1][k]] = ( (long double) irand / 100.0 );// z;
				//cout<<"setting weightTable ["<<node[j][i]<<"]["<<node[j+1][k]<<"] as : "<< weightTable[node[j][i]][node[j+1][k]] <<endl;//weightTable[node[j][i]][node[j+1][k]]<<endl;
			}
		}
	}

	for(int j=1; j<structure.size();j++){
		for(int i=0;i<structure[j];i++){
			//cout<<"initializing weightTable ["<<0<<"]["<<node[j][i]<<"] as : "<<0.01<<endl;
			weightTable[0][node[j][i]] = 0.01;  // weights from dummy to all nodes is 0.01
		}
	}
}

void Ann::initOutput(){
	std::vector<std::vector<long double> > out;
	std::vector <int > :: iterator struct_iter;

	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		out.push_back(vector<long double>(*(struct_iter), 0));
	}
	output = out;
}

void Ann::initDigitEncoding(){

	std::vector<std::vector<long double> > out(10, std::vector<long double>(10, 0.9));
	std::vector <int > :: iterator struct_iter;

	for(int i=0;i<10;i++){
		out[i][i] = 0.1;
	}
	digit_encoding = out;

	std::cout<<"digit_encoding matrix"<<std::endl;
	for(unsigned i=0;i<digit_encoding.size();i++){
		for(unsigned j=0;j<digit_encoding[i].size();j++){
			std::cout<<digit_encoding[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}

void Ann::initError(){

	std::vector<std::vector<long double> > out;
	std::vector <int > :: iterator struct_iter;

	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		out.push_back(vector<long double>(*(struct_iter), 0));
	}
	error = out;
}

void Ann::initNode(){

	std::vector<std::vector< int> > out;
	std::vector <int > :: iterator struct_iter;
	int nodenum=1;
	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		vector<int> temp;
		for(int i=0;i<*(struct_iter);i++){
			temp.push_back(nodenum);
			nodenum++;
		}
		out.push_back(temp);
	}
	node = out;
}

void Ann::calculateValueAt(int layer, int nodeNum){

	long double value = weightTable[0][node[layer][nodeNum]];
	int input_node = 0;

	for(int i=0;i < output[layer-1].size();i++ ){
		input_node = node[layer-1][i];
		value += output[layer-1][i]* weightTable[input_node][node[layer][nodeNum]];
	}


	output[layer][nodeNum] = getSigmoid(value);
	//output[layer][nodeNum] = getFSigmoid(value);

	//output[layer][nodeNum] = getRectifier(value);
}

void Ann::calculateErrorAt(int layer, int nodeNum){

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

void Ann::calculateErrorAtOutputLayer(int layer, int nodeNum, long double outputLayerValue){

	long double calculatedValue = output[layer][nodeNum];
	error[layer][nodeNum] =  getSigmoidError(calculatedValue, outputLayerValue - calculatedValue );
}

void Ann::updateErrorsInBackwardPass(){

	for(int j=structure.size()-2; j>=0;j--){
		for(int i=0;i<structure[j];i++){
			//cout<<"invoking updateError for "<<node[j][i]<<endl;
			calculateErrorAt(j,i);
		}
	}
}

void Ann::updateValuesInForwardPass(){

	for(int j=1; j<structure.size();j++){
		for(int i=0;i<structure[j];i++){
			//cout<<"invoking updateValue for "<<node[j][i]<<endl;
			calculateValueAt(j,i);
		}
	}
}

void Ann::updateWeights(){

	for(int j=1; j<structure.size();j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){

			//cout<<"current node : "<<node[j][i]<<endl;
			weightTable[0][node[j][i]] =  weightTable[0][node[j][i]] + alpha * 1 * error[j][i] ;
			//cout<<"setting  ["<<0<<"]["<<node[j][i]<<"] as : "<<weightTable[0][node[j][i]]<<endl;
		}
	}

	for(int j=0; j<structure.size()-1;j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){

			for(int k=0; k< structure[j+1]; k++){

				weightTable[node[j][i]][node[j+1][k]] =  weightTable[node[j][i]][node[j+1][k]] + alpha * output[j][i] * error[j+1][k] ;

				//cout<<"setting  ["<<node[j][i]<<"]["<<node[j+1][k]<<"] as : "<<weightTable[node[j][i]][node[j+1][k]]<<endl;
			}
		}
	}

}

void Ann::doForwardPassIteration(std::vector< std::vector<long double> > inputlayer, int number){

	for(int j=0; j<structure[0];j++){
		output[0][j] = inputlayer[number][j];
	}
	updateValuesInForwardPass();

}

void Ann::doBackwardPassIteration(std::vector< int> outputlayer,int number){
	int digit = outputlayer[number];

	for(int j=0; j<structure[structure.size()-1];j++){
		calculateErrorAtOutputLayer(structure.size()-1, j, digit_encoding[digit][j]);
	}
	updateErrorsInBackwardPass();

}

void Ann::validateTestInput(){
	int total_tests = test_inputTable.size(), digit = -1;
	int correctly_validated = 0;
	long double accuracy = 0.0;
	for(int i=0;i<total_tests;i++){
		doForwardPassIteration(test_inputTable,i);
		digit = findDigit();
		cout<<"digit : "<<digit<<endl;

		if(digit == test_output[i]){
			correctly_validated++;
		}
	}
	accuracy = ((long double) correctly_validated  )/ total_tests;

	cout<<"total : "<<total_tests<<" validated : "<<correctly_validated<<endl;
	cout<<"accuracy : ";
	cout << showpoint << fixed << setprecision(12) << accuracy << endl;

}

void Ann::trainWeightsModel(int iteration_count){

	for(int j=0;j<iteration_count;j++){

		for(int i=0;i<train_inputTable.size();i++){
			doForwardPassIteration(train_inputTable,i);
			//showOutput();
			doBackwardPassIteration(train_output,i);
			//showError();
			updateWeights();
			//showWeight();
		}
	}

}

Ann::Ann(){

	alpha= 0.01;
	initStructure("structure.txt");
	initDigitEncoding();
	initNode();
	initOutput();
	initError();

	//showNode();

	initTrainInput("train_input.txt");
	initTrainOutput("train_output.txt");
	initTestInput("test_input.txt");
	initTestOutput("test_output.txt");
	initweightTable("weights.txt");


	cout<<"Sizes : "<<train_inputTable.size()<<" : "<<train_output.size() <<" : "<< test_inputTable.size() <<" : "<<test_output.size()<<endl;






	trainWeightsModel(500);
	validateTestInput();



	/*

	updateValuesInForwardPass();


	cout<<"#######################################"<<endl;


	updateErrorsInBackwardPass();

	showError();


	cout << showpoint << fixed << setprecision(12) << error[0][0] << endl;
	cout << showpoint << fixed << setprecision(12) << error[0][1] << endl;

	updateWeights();
	*/

}































Ann::Ann(  char * train_input_file, char *train_output_file, char * test_input_file, char *test_output_file,
		char * structure_file, char * weight_file){

	alpha= 0.01;
	initStructure("structure.txt");
	initDigitEncoding();
	initNode();
	initOutput();
	initError();


	initTrainInput("train-input.txt");
	initTrainOutput("train-output.txt");
	initTestInput("test-input.txt");
	initTestOutput("test-output.txt");
	initweightTable("weights.txt");

}




void Ann::showOutput(){
	std::cout<<"output matrix"<<std::endl;
	for(unsigned i=0;i<output.size();i++){
		for(unsigned j=0;j<output[i].size();j++){
			std::cout<<output[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}

void Ann::showError(){
	std::cout<<"Error matrix"<<std::endl;
	for(unsigned i=0;i<error.size();i++){
		for(unsigned j=0;j<error[i].size();j++){
			std::cout<<error[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;

}

void Ann::showNode(){
	std::cout<<"Node matrix"<<std::endl;
	for(unsigned i=0;i<node.size();i++){
		for(unsigned j=0;j<node[i].size();j++){
			std::cout<<node[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}

void Ann::showWeight(){
	std::cout<<"Weight matrix"<<std::endl;
	for(unsigned i=0;i<weightTable.size();i++){
		for(unsigned j=0;j<weightTable[i].size();j++){
			std::cout<<weightTable[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}



