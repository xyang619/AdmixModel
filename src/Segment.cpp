/*
 * Segment.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include "Segment.h"

Segment::Segment() {
	start = 0;
	end = 0;
	label = 1;
}

Segment::Segment(float start, float end, int label) {
	this->start = start;
	this->end = end;
	this->label = label;
}

Segment::Segment(const Segment &segment) {
	start = segment.start;
	end = segment.end;
	label = segment.label;
}
float Segment::getStart() const {
	return start;
}

float Segment::getEnd() const {
	return end;
}

int Segment::getLabel() const {
	return label;
}

float Segment::getLength() {
	return end - start;
}

void Segment::setStart(float start) {
	this->start = start;
}

void Segment::setEnd(float end) {
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

