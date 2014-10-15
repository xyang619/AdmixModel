/*
 * Chrom.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include <iostream>
#include "Chrom.h"

Chrom::Chrom() {
	vector<Segment> segments;
	this->segments = segments;
	vector<double> breaks;
	this->breaks = breaks;
}

Chrom::Chrom(const vector<Segment> & segments) {
	this->segments = segments;
	vector<double> breaks;
	for (size_t i = 0; i < segments.size(); ++i) {
		breaks.push_back(segments[i].getEnd());
	}
	if (breaks.size() > 0) {
		breaks.pop_back();
	}
	this->breaks = breaks;
}

Chrom::Chrom(const Chrom & chrom) {
	segments = chrom.segments;
	breaks = chrom.breaks;
}

double Chrom::getLength() const {
	return segments.back().getEnd();
}

int Chrom::getNumSegments() const {
	return segments.size();
}

int Chrom::indexOf(double pos) {
	//if(breaks.size)
	return 0;
}

void Chrom::addSegment(Segment & segment) {
	if (segments.size() > 0) {
		if (segment.getStart() != segments.back().getEnd()) {
			cout
					<< "There is a gap between newly added segment and the last segment already in, segment shifted"
					<< endl;
			//shift the segment
			double prevEnd = segments.back().getEnd();
			segment.setEnd(prevEnd + segment.getLength());
			segment.setStart(prevEnd);
		}
		//cout << segment.getEnd() << endl;
		breaks.push_back(segment.getEnd());
	}
	segments.push_back(segment);
}

void Chrom::smooth() {
	size_t i;
	vector<Segment> tmpSegments;
	Segment seg1 = segments[0];
	for (i = 1; i < segments.size(); ++i) {
		Segment seg2 = segments[i];
		//if adjacent segments have the same label, merge it
		if (seg1.getLabel() == seg2.getLabel()) {
			seg1.setEnd(seg2.getEnd());
		} else {
			//different label, then add segment to segments
			//and assign segment 2 to segment 1
			tmpSegments.push_back(seg1);
			seg1 = seg2;
		}
	}
	tmpSegments.push_back(seg1);
	segments = tmpSegments;
}

Segment Chrom::getSegment(int index) {
	return segments[index];
}

vector<Segment> Chrom::extSegment(double start, double end) {
	vector<Segment> segs;
	return segs;
}

Chrom Chrom::duplicate() {
	return Chrom(segments);
}

void Chrom::print() {
	int i;
	int nseg = getNumSegments();
	for (i = 0; i < nseg; ++i) {
		Segment seg = getSegment(i);
		cout << "(" << seg.getStart() << "," << seg.getEnd() << ":"
				<< seg.getLabel() << ")-";
	}
	cout << endl;
}

Chrom::~Chrom() {
// TODO Auto-generated destructor stub
}

//test case
int main() {
	vector<Segment> segs;
	segs.push_back(Segment(0.0, 0.2, 1));
	segs.push_back(Segment(0.2, 0.8, 1));
	segs.push_back(Segment(0.8, 1.0, 2));
	segs.push_back(Segment(1.0, 1.25, 2));
	segs.push_back(Segment(1.25, 1.5, 1));
	Chrom chr(segs);
	Segment ss(1.6, 1.8, 1);
	chr.addSegment(ss);
	size_t i;
	cout << "before smooth, the num is: " << chr.getNumSegments() << endl;
	for (i = 0; i < chr.getNumSegments(); ++i) {
		Segment s = chr.getSegment(i);
		cout << "Seg " << i << ":" << s.getStart() << "-" << s.getEnd()
				<< "; pop " << s.getLabel() << endl;
	}
	chr.smooth();
	cout << "after smooth, the num is: " << chr.getNumSegments() << endl;
	for (i = 0; i < chr.getNumSegments(); ++i) {
		Segment s = chr.getSegment(i);
		cout << "Seg " << i << ":" << s.getStart() << "-" << s.getEnd()
				<< "; pop " << s.getLabel() << endl;
	}
}

