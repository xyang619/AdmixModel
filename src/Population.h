/*
 * Population.h
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include "ChromPair.h"
using namespace std;

class Population {
private:
	int label;
	int ne;
	vector<ChromPair> indivs;
public:
	Population();
	Population(int, int, const vector<ChromPair> &);
	int getLabel() const;
	int getNe();
	vector<ChromPair> getIndivs() const;
	void setLabel(int);
	void updateNe();
	void addIndiv(ChromPair &);
	Population evolve(int);
	vector<ChromPair> sample(int) const;
	vector<Population> split(float);
	virtual ~Population();
};

#endif /* POPULATION_H_ */
