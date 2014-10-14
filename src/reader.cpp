/*
 * reader.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: xiong_yang
 */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "reader.h"

using namespace std;

//split string, directly copy from
//http://programmingknowledgeblog.blogspot.de/2013/04/the-most-elegant-way-to-split-string-in.html
vector<string> split(const string& s, const string& delim,
		const bool keep_empty = true) {
	vector<string> result;
	if (delim.empty()) {
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty()) {
			result.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

vector<string> readHaplo(char *filename) {
	ifstream in;
	vector<string> haplo;
	in.open(filename);
	if (in.is_open()) {
		string line;
		//skip first 6 lines
		for (unsigned int i = 0; i < 6; i++) {
			getline(in, line);
		}
		while (getline(in, line))
			haplo.push_back(line);
	} else {
		cout << "Error in reading " << filename << endl;
	}
	in.close();
	return haplo;
}

vector<float> readPos(char *filename) {
	ifstream in;
	vector<float> pos;
	in.open(filename);
	if (in.is_open()) {
		string line;
		//skip first 5 lines
		for (unsigned int i = 0; i < 5; i++) {
			getline(in, line);
		}
		getline(in, line);
		vector<string> tokens = split(line, " ");
		for (unsigned int i = 1; i < tokens.size() - 1; i++) {
			pos.push_back((float) atof(tokens[i].c_str()));
		}
	} else {
		cout << "Error in reading " << filename << endl;
	}
	in.close();
	return pos;
}

//int main() {
//	vector<string> haps = readHaplo("test");
//	vector<float> pos = readPos("test");
//	cout << "pos size " << pos.size() << endl;
//	for (unsigned int i = 0; i < pos.size(); i++) {
//		cout << pos[i] << " ";
//	}
//	cout << endl;
//	for (unsigned int i = 0; i < haps.size(); i++) {
//		cout << haps[i] << endl;
//	}
//}

