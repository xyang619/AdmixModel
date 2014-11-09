/*
 * GeneralModel.h
 *
 *  Created on: Nov 9, 2014
 *      Author: young
 */

#ifndef GENERALMODEL_H_
#define GENERALMODEL_H_

#include <string>
#include "Population.h"
using namespace std;

class GeneralModel {
private:
	int nes[];
	double prop[][];
	Population pop;
public:
	//GeneralModel();
	GeneralModel(int[], double[][]);
	GeneralModel(int[], double[][], Population);
	GeneralModel(string, int, int);
	bool isValidNe(int);
	bool isValidProp(int, int);
	void readParam(string, int, int);
	void evolve(int, int, double);
	Population getPop();
	virtual ~GeneralModel();
};

#endif /* GENERALMODEL_H_ */
