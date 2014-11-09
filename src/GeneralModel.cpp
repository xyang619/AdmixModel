/*
 * GeneralModel.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: young
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "GeneralModel.h"

GeneralModel::GeneralModel(int nes[], double prop[][]) {
	this->nes = nes;
	this->prop = prop;
}
GeneralModel::GeneralModel(int nes[], double prop[][], Population pop) {
	this->nes = nes;
	this->prop = prop;
	this->pop = pop;
}
GeneralModel::GeneralModel(string file, int gen, int nanc) {
	readParam(file, gen, nanc);
}
bool GeneralModel::isValidNe(int gen) {
	for (int i = 0; i < gen; ++i) {
		if (nes[i] <= 0) {
			cout << "Effective population size must be positive" << endl;
			return 0;
		}
	}
	return 1;
}
bool GeneralModel::isValidProp(int gen, int nanc) {
	for (int i = 0; i < gen; ++i) {
		double tsum = 0;
		for (int j = 0; j < nanc; ++j) {
			if (prop[i][j] < 0 || prop[i][j] > 1) {
				cout << "Admixture proportion must be between 0 and 1" << endl;
				return 0;
			}
			tsum += prop[i][j];
		}
		if (i == 0 && tsum != 1.0) {
			cout
					<< "Then admixture proportion of initial generation must sum to 1"
					<< endl;
			return 0;
		}
		if (tsum > 1) {
			cout << "The sum of admixture proportion in generation " << i
					<< " larger than 1" << endl;
			return 0;
		}
	}
	return 1;
}
void GeneralModel::readParam(string file, int gen, int nanc) {
	ifstream fin(file);
	if (!fin.is_open()) {
		cout << "Can't open file" << endl;
		exit(1);
	}
	int tNes[gen];
	double tProp[gen][nanc];
	for (int i = 0; i < gen; ++i) {
		fin >> tNes[i];
		for (int j = 0; j < nanc; ++j) {
			fin >> tProp[i][j];
		}
	}
	fin.close();
	this->nes = tNes;
	this->prop = tProp;
}
void GeneralModel::evolve(int gen, int nanc, double len) {

}
Population GeneralModel::getPop() {
	return pop;
}

GeneralModel::~GeneralModel() {
	// TODO Auto-generated destructor stub
}

