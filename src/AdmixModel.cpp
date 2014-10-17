//============================================================================
// Name        : AdmixModel.cpp
// Author      : Young
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : An Admixture Model Simulator
//============================================================================

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Model.h"

using namespace std;

void help();

int main(int argc, char **argv) {
	//cout<<argc<<endl;

	if ((argc < 2) || (argc < 12 && (string(argv[1]) != "-h" || string(argv[1])!="--help"))) {
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
		if (string(argv[i]) == "-h" || string(argv[i])=="--help") {
			help();
			exit(0);
		} else if (string(argv[i]) == "-g" || string(argv[i])=="--gen") {
			gen = atoi(argv[++i]);
		} else if (string(argv[i]) == "-p" || string(argv[i])=="--prop") {
			prop = atof(argv[++i]);
		} else if (string(argv[i]) == "-m" || string(argv[i])=="--model") {
			mod = atoi(argv[++i]);
		} else if (string(argv[i]) == "-l" || string(argv[i])=="--len") {
			len = atof(argv[++i]);
		} else if (string(argv[i]) == "-e" || string(argv[i])=="--ne") {
			ne = atoi(argv[++i]);
		} else if (string(argv[i]) == "-n" || string(argv[i])=="--samp") {
			nsample = atoi(argv[++i]);
		} else if (string(argv[i]) == "-s" || string(argv[i])=="--seed") {
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
			cout << setw(10) << seg.getStart() << "\t" << setw(10)
					<< seg.getEnd() << "\t" << seg.getLabel() << endl;
		}
	}
	return 0;
}

void help() {
	cout << "Description: Admixture Model Simulator" << endl;
	cout << "Arguments:" << endl;
	cout << "	-h	--help	print help message" << endl;
	cout << "	-g	--gen	generation since admixture" << endl;
	cout << "	-p	--prop	ancestry proportion of admixed population" << endl;
	cout << "	-m	--model	admixture model, 1 for HI, 2 for GA and 3 for CGF" << endl;
	cout << "	-l	--len	length of chromsome to simulate, unit in Morgan" << endl;
	cout << "	-e 	--ne	effective population size for admixed population" << endl;
	cout << "	-n	--samp	number of haplotypes to be sampled" << endl;
	cout << "	-s	--seed	seed of random number generator" << endl;
}

