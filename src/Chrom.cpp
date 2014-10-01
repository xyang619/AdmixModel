/*
 * Chrom.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include "Chrom.h"
#include <iostream>

Chrom::Chrom() {
	vector<Segment> segments;
	this->segments = segments;
}

Chrom::Chrom(const vector<Segment> & segments) :
		segments(segments) {
}

Chrom::Chrom(const Chrom & chrom) {
	segments = chrom.segments;
}

float Chrom::getLength() {
	return segments.back().getEnd();
}

int Chrom::getNumSegments() const{
	return segments.size();
}

void Chrom::addSegment(Segment & segment) {
	segments.push_back(segment);
}

Segment Chrom::getSegment(int index) {
	return segments[index];
}

Chrom Chrom::duplicate() {
	return Chrom(segments);
}

Chrom::~Chrom() {
	// TODO Auto-generated destructor stub
}

//int main() {
//	vector<Segment> segs;
//	segs.push_back(Segment(0.0, 0.2, 1));
//	segs.push_back(Segment(0.2, 0.8, 1));
//	Chrom chr(segs);
//	size_t i;
//	for (i = 0; i < segs.size(); i++) {
//		Segment s = chr.getSegment(i);
//		cout << "Seg " << i << ":" << s.getStart() << "-" << s.getEnd() << endl;
//	}
//}

