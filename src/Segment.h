/*
 * Segment.h
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

class Segment {
private:
	float start;
	float end;
	int label;
public:
	Segment(float, float, int);
	Segment(const Segment &);
	float getStart() const;
	float getEnd() const;
	int getLabel() const;
	float getLength();
	void setStart(float);
	void setEnd(float);
	void setLabel(int);
	Segment copy();
	virtual ~Segment();
};

#endif /* SEGMENT_H_ */
