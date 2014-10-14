/*
 * generator.cpp
 *
 *  Created on: Sep 25, 2014
 *  Author: xiong_yang
 *  generate a series of position between 0 and length, and generate a sequence of given character sets
 */
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "generator.h"

char random(char Set[], int len) {
	srand(time(NULL));
	return Set[rand() % len];
}

vector<float> genPos(long size, float length) {
	vector<float> pos;
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		pos.push_back(length * (((float) rand()) / (RAND_MAX)));
	}
	sort(pos.begin(), pos.end());
	return pos;
}

char *genSeq(long size, char Set[], int len) {
	char *seq;
	seq = new char[size + 1];
	for (int i = 0; i < size; i++) {
		seq[i] = random(Set, len);
	}
	seq[size] = '\0';
	return seq;
}
//int main() {
//	long size = 100;
//	char set[] = { 'A', 'C', 'G', 'T' };
//	vector<float> p = genPos(size, 1.0);
//	char *s = genSeq(size, set, 4);
//	for (int i = 0; i < size; i++)
//		cout << p[i] << " ";
//	cout << endl;
//	cout << s << endl;
//}
