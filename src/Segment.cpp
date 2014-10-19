/*
 * Segment.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include "Segment.h"

Segment::Segment() {
	start = 0.0;
	end = 0.0;
	label = 1;
}

Segment::Segment(double start, double end, int label) {
	this->start = start;
	this->end = end;
	this->label = label;
}

Segment::Segment(const Segment &segment) {
	start = segment.start;
	end = segment.end;
	label = segment.label;
}
double Segment::getStart() const {
	return start;
}

double Segment::getEnd() const {
	return end;
}

int Segment::getLabel() const {
	return label;
}

double Segment::getLength() {
	return end - start;
}

void Segment::setStart(double start) {
	this->start = start;
}

void Segment::setEnd(double end) {
	this->end = end;
}

void Segment::setLabel(int label) {
	this->label = label;
}

Segment Segment::copy() {
	Segment s(start, end, label);
	return s;
}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}

