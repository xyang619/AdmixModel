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

GeneralModel::GeneralModel(char * file, int gen, int nanc) {
	readParam(file, gen, nanc);
	if (isValidNe(gen) && isValidProp(gen, nanc))
		pop = Population();
	else
		exit(1);
}

bool GeneralModel::isValidNe(int gen) const {
	for (int i = 0; i < gen; ++i) {
		if (nes.at(i) <= 0) {
			cout << "Effective population size must be positive" << endl;
			return 0;
		}
	}
	return 1;
}

bool GeneralModel::isValidProp(int gen, int nanc) const {
	for (int i = 0; i < gen; ++i) {
		double tsum = 0;
		for (int j = 0; j < nanc; ++j) {
			if (prop.at(i).at(j) < 0 || prop.at(i).at(j) > 1) {
				cout << "Admixture proportion must be between 0 and 1" << endl;
				return 0;
			}
			tsum += prop.at(i).at(j);
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

void GeneralModel::readParam(char * file, int gen, int nanc) {
	ifstream fin(file);
	if (!fin.is_open()) {
		cout << "Can't open model file " << file << endl;
		exit(1);
	}
	vector<int> tnes;
	vector<vector<double> > tprop;
	for (int i = 0; i < gen; ++i) {
		int ne;
		fin >> ne;
		tnes.push_back(ne);
		vector<double> pp1g;
		for (int j = 0; j < nanc; ++j) {
			double pp;
			fin >> pp;
			pp1g.push_back(pp);
		}
		tprop.push_back(pp1g);
	}
	fin.close();
	nes = tnes;
	prop = tprop;
}

void GeneralModel::evolve(int gen, int nanc, double len) {
	for (int i = 0; i < gen; ++i) {
		int numbIndsPrev = 0;
		int curNe = nes.at(i);
		int numbInds[nanc];
		int sumNumbInds = 0;
		for (int j = 0; j < nanc; ++j) {
			numbInds[j] = (int) (curNe * prop.at(i).at(j));
			sumNumbInds += numbInds[j];
		}
		// prepare individuals in current generation
		numbIndsPrev = curNe - sumNumbInds;
		vector<ChromPair> indsCur;
		if (numbIndsPrev > 0) {
			indsCur = pop.sample(numbIndsPrev);
		}
		for (int j = 0; j < nanc; j++) {
			if (numbInds[j] > 0) {
				for (int k = 0; k < numbInds[j]; k++) {
					vector<Segment> segs;
					segs.push_back(Segment(0, len, j+1));
					Chrom chr(segs);
					indsCur.push_back(ChromPair(chr, chr));
				}
			}
		}
		Population tmpPop(0, curNe, indsCur);
		pop = tmpPop.evolve(tmpPop.getNe());
	}

}

Population GeneralModel::getPop() const {
	return pop;
}

GeneralModel::~GeneralModel() {
}

