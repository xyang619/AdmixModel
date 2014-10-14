/*
 * ChromPair.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ChromPair.h"

ChromPair::ChromPair() {
	Chrom chr1, chr2;
	chrom1 = chr1;
	chrom2 = chr2;
}
ChromPair::ChromPair(const Chrom & chrom1, const Chrom & chrom2) :
		chrom1(chrom1), chrom2(chrom2) {
}

ChromPair::ChromPair(const ChromPair & chromPair) {
	chrom1 = chromPair.chrom1;
	chrom2 = chromPair.chrom2;
}

Chrom ChromPair::getChrom(int index = 1) {
	if (index == 1) {
		return chrom1;
	} else {
		return chrom2;
	}
}

float ChromPair::waitTime() {
	float lambda = chrom1.getLength();
	srand(time(NULL));
	float prob = (float) (rand()) / RAND_MAX;
	float time = -log(1 - prob) / lambda;
	return time;
}

vector<float> ChromPair::breakPoints() {
	vector<float> bps;
	float length = chrom1.getLength();
	bps.push_back(0.0);
	while (bps[bps.size() - 1] < length)
		bps.push_back(bps[bps.size() - 1] + waitTime());
	bps[bps.size()] = length;
	return bps;
}

ChromPair ChromPair::recombine() {
	if (chrom1.getLength() != chrom2.getLength()) {
		cout << "Chromosome length differ, please check again" << endl;
		return ChromPair(chrom1, chrom2);
	} else {
		vector<float> bps = breakPoints();
		vector<Segment> ss1;
		vector<Segment> ss2;
		float start = bps[0];
		for (size_t i = 1; i < bps.size(); ++i) {
			float end = bps[i];
			Segment s(start, end, 1);
			if (i % 2) {
				ss1.push_back(s);
				s.setLabel(2);
				ss2.push_back(s);
			} else {
				ss2.push_back(s);
				s.setLabel(2);
				ss1.push_back(s);
			}
			start = end;
		}
		Chrom chr1(ss1);
		Chrom chr2(ss2);
		return ChromPair(ss1, ss2);
	}
}

ChromPair::~ChromPair() {
	// TODO Auto-generated destructor stub
}

int main() {
	vector<Segment> segs;
	segs.push_back(Segment(0, 2, 1));
	Chrom chr1(segs);
	vector<Segment> segs2;
	segs2.push_back(Segment(0, 2, 2));
	Chrom chr2(segs2);
	ChromPair cp = ChromPair(chr1, chr2);
	cp.getChrom(1).print();
	cp.getChrom(2).print();
	cp = cp.recombine();
	cp.getChrom(1).print();
	cp.getChrom(2).print();
	cp = cp.recombine();
	cp.getChrom(1).print();
	cp.getChrom(2).print();
	cp = cp.recombine();
	cp.getChrom(1).print();
	cp.getChrom(2).print();
}

