
#ifndef _SIG_ANN_H_
#define _SIG_ANN_H_

#include"ann.h"

class Sig_Ann : public Ann{

	virtual void calculateValueAt(int layer, int nodeNum);
	virtual void calculateErrorAt(int layer, int nodeNum);
	virtual void calculateErrorAtOutputLayer(int layer, int nodeNum, long double output);


};






#endif

