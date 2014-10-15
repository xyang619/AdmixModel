/*
 * Chrom.h
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef CHROM_H_
#define CHROM_H_

#include <vector>
#include "Segment.h"

using namespace std;

class Chrom {
private:
	vector<Segment> segments;
	vector<double> breaks;
public:
	Chrom();
	Chrom(const vector<Segment> &);
	Chrom(const Chrom &);
	double getLength() const;
	int getNumSegments() const;
	int indexOf(double);
	void addSegment(Segment &);
	vector<Segment> extSegment(double, double);
	void smooth();
	Segment getSegment(int);
	Chrom duplicate();
	void print();
	virtual ~Chrom();
};

#endif /* CHROM_H_ */
