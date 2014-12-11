/*
 * GeneralModel.h
 *
 *  Created on: Nov 9, 2014
 *      Author: young
 */

#ifndef GENERALMODEL_H_
#define GENERALMODEL_H_

//#include <string>
#include "Population.h"
using namespace std;

class GeneralModel {
private:
	vector<int> nes;
	vector<vector<double> > prop;
	Population pop;
public:
	GeneralModel(char *, int, int);
	bool isValidNe(int) const;
	bool isValidProp(int, int) const;
	void readParam(char *, int, int);
	void evolve(int, int, double);
	Population getPop() const;
	virtual ~GeneralModel();
};

#endif /* GENERALMODEL_H_ */
