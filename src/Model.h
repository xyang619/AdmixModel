/*
 * Model.h
 *
 *  Created on: Oct 14, 2014
 *      Author: young
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Population.h"

class Model {
private:
	int mod;
	int gen;
	int ne;
	double prop;
	Population pop;
public:
	Model();
	Model(int, int, double);
	Model(int, int, int, double);
	Model(const Model &);
	int getMod() const;
	int getNe() const;
	int getGen() const;
	double getProp() const;
	void setMod(int);
	void setNe(int);
	void setGen(int);
	void setProp(double);
	void evolve(double);
	void HIMod(double);
	void GAMod(double);
	void CGFMod(double);
	Population getPop();
	virtual ~Model();
};

#endif /* MODEL_H_ */
