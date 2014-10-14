//============================================================================
// Name        : AdmixModel.cpp
// Author      : Young
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : An Admixture Model Simulator
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Model.h"

using namespace std;

void help();
void HIModel(int, double, double, int, int);

int main(int argc, char **argv) {
	//cout<<argc<<endl;

	if ((argc < 2) || (argc < 12 && string(argv[1]) != "-h")) {
		cout << "Need more arguments than provided, please check help again"
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
		} else if (string(argv[i]) == "-n") {
			ne = atoi(argv[++i]);
		} else if (string(argv[i]) == "-s") {
			nsample = atoi(argv[++i]);
		}
	}
	cout << "Model description:" << endl;
	cout << "generation: " << gen << endl;
	cout << "proportion: " << prop << endl;
	cout << "model: " << mod << endl;
	cout << "length: " << len << endl;
	cout << "Ne: " << ne << endl;
	cout << "nsample: " << nsample << endl;

	if (mod != 1 && mod != 2 && mod != 3) {
		cout << "Error, model must be HI(1), GA(2) or CGF(3)\n";
		help();
		exit(1);
	}
	Model model(mod, gen, ne, prop);
	model.evolve(len);
	vector<Chrom> sample = model.getPop().sample(nsample);
	for (i = 0; i < nsample; ++i) {
		Chrom chr = sample[i];
		chr.smooth();
		int nseg = sample[i].getNumSegments();
		cout << "chrom-" << i << ": ";
		for (int j = 0; j < nseg; ++j) {
			Segment seg = chr.getSegment(j);
			cout << "(" << seg.getStart() << "," << seg.getEnd() << ":"
					<< seg.getLabel() << ")-";
		}
		cout << endl;
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
	cout << "	-n 	effective population size for admixed population" << endl;
	cout << "	-s	number of haplotypes to be sampled" << endl;
}

void HIModel(int gen, double prop, double len, int ne, int nsamp) {
	int nhap1 = ne * 2 * prop;
	int nhap2 = ne * 2 - nhap1;
	vector<Chrom> mixhaplos;
	int i;
	for (i = 0; i < nhap1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		mixhaplos.push_back(Chrom(segs));
	}
	for (i = 0; i < nhap2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		mixhaplos.push_back(Chrom(segs));
	}
	Population admp;
	admp = Population(3, ne, mixhaplos);
	for (i = 0; i < gen; ++i) {
		admp = admp.evolve(ne);
	}
	vector<Chrom> shaplos = admp.sample(nsamp);
	for (size_t i = 0; i < shaplos.size(); i++) {
		int j;
		int nseg = shaplos[i].getNumSegments();
		cout << "hap" << (i + 1) << ":";
		for (j = 0; j < nseg; ++j) {
			cout << "-(" << shaplos[i].getSegment(j).getStart();
			cout << "," << shaplos[i].getSegment(j).getEnd();
			cout << "," << shaplos[i].getSegment(j).getLabel() << ")";
		}
		cout << endl;
	}
}

