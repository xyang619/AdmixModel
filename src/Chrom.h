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
	vector<double> breaks;
	vector<Segment> segments;

public:
//	Chrom();
	Chrom(const vector<Segment> &);
	double getLength() const;
	int getNumSegments() const;
	int indexOf(double) const;
	void addSegment(Segment &);
	vector<Segment> extSegment(double, double) const;
	void smooth();
	void updateBreaks();
	Segment getSegment(int) const;
	void print() const;
	virtual ~Chrom();
};

#endif /* CHROM_H_ */
