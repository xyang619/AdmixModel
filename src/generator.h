/*
 * generator.h
 *
 *  Created on: Sep 25, 2014
 *      Author: xiong_yang
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>
using namespace std;

void setSeed(long);
char *genSeq(long, char*, int);
vector<float> genPos(long, float);
char random(char[]);

#endif /* GENERATOR_H_ */
