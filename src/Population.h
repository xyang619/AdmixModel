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
	vector<Chrom> haplos;
public:
	Population();
	Population(int, int, const vector<Chrom> &);
	Population(const Population &);
	int getLabel() const;
	int getNe();
	vector<Chrom> getHaplos();
	void setLabel(int);
	void updateNe();
	void addHaplo(Chrom &);
	Population evolve(int);
	vector<Chrom> sample(int);
	vector<Population> split(float);
	virtual ~Population();
};

#endif /* POPULATION_H_ */
