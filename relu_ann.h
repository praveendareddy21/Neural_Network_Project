
#ifndef _REL_ANN_H_
#define _REL_ANN_H_

#include"ann.h"

class Relu_Ann : public Ann{

	virtual void calculateValueAt(int layer, int nodeNum);
	virtual void calculateErrorAt(int layer, int nodeNum);
	virtual void calculateErrorAtOutputLayer(int layer, int nodeNum, long double output);


};






#endif

