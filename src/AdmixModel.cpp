//============================================================================
// Name        : AdmixModel.cpp
// Author      : Young
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : An Admixture Model Simulator
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Model.h"

using namespace std;

void help();
void HIModel(int, double, double, int, int);

int main(int argc, char **argv) {
	//cout<<argc<<endl;

	if ((argc < 2) || (argc < 12 && string(argv[1]) != "-h")) {
		cerr << "Need more arguments than provided, please check help again"
				<< endl;
		help();
		exit(0);
	}
	int i;
	int mod = 1;
	int gen = 1;
	int ne = 1000;
	double prop = 0.5;
	double len = 0;
	int nsample = 10;
	long seed = 0;
	bool givenSeed = 0;

	for (i = 0; i < argc; ++i) {
		if (string(argv[i]) == "-h") {
			help();
			exit(0);
		} else if (string(argv[i]) == "-g") {
			gen = atoi(argv[++i]);
		} else if (string(argv[i]) == "-p") {
			prop = atof(argv[++i]);
		} else if (string(argv[i]) == "-m") {
			mod = atoi(argv[++i]);
		} else if (string(argv[i]) == "-l") {
			len = atof(argv[++i]);
		} else if (string(argv[i]) == "-e") {
			ne = atoi(argv[++i]);
		} else if (string(argv[i]) == "-n") {
			nsample = atoi(argv[++i]);
		} else if (string(argv[i]) == "-s") {
			seed = atol(argv[++i]);
			givenSeed = 1;
		}
	}
	cerr << "Model description:" << endl;
	cerr << "generation: " << gen << endl;
	cerr << "proportion: " << prop << endl;
	cerr << "model: " << mod << endl;
	cerr << "length: " << len << endl;
	cerr << "Ne: " << ne << endl;
	cerr << "nsample: " << nsample << endl;
	cerr << "seed: " << seed << endl;

	if (mod != 1 && mod != 2 && mod != 3) {
		cerr << "Error, model must be HI(1), GA(2) or CGF(3)\n";
		help();
		exit(1);
	}
	if (!givenSeed) {
		srand (time(NULL));} else {
			srand(seed);
		}
	Model model(mod, gen, ne, prop);
	model.evolve(len);
	vector<Chrom> sample = model.getPop().sample(nsample);
	for (i = 0; i < nsample; ++i) {
		Chrom chr = sample.at(i);
		chr.smooth();
		int nseg = chr.getNumSegments();
		//cout << "chrom-" << i << ": ";
		for (int j = 0; j < nseg; ++j) {
			Segment seg = chr.getSegment(j);
			cout <<seg.getStart() << "\t" << seg.getEnd() << "\t" << seg.getLabel() << endl;
		}
	}
	return 0;
}

void help() {
	cout << "Admixture Model Simulator" << endl;
	cout << "Arguments:" << endl;
	cout << "	-h	print help message" << endl;
	cout << "	-g	generation since admixture" << endl;
	cout << "	-p	ancestry proportion of admixed population" << endl;
	cout << "	-m	admixture model, 1 for HI, 2 for GA and 3 for CGF" << endl;
	cout << "	-l	length of chromsome to simulate, unit in Morgan" << endl;
	cout << "	-e 	effective population size for admixed population" << endl;
	cout << "	-n	number of haplotypes to be sampled" << endl;
	cout << "	-s	seed of random number generator" << endl;
}

