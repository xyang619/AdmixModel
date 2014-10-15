/*
 * reader.h
 *
 *  Created on: Sep 25, 2014
 *      Author: xiong_yang
 */

#ifndef READER_H_
#define READER_H_

#include <string>
#include <vector>

using namespace std;

vector<string> split(const string&, const string&, const bool);
vector<string> readHaplo(char *filename);
vector<double> readPos(char *filename);

#endif /* READER_H_ */
