//============================================================================
// Name        : AdmixModel.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Population.h"

using namespace std;

void help();
void HIModel(int, double, double, int, int);
void GAModel(int, double, double, int[], int[]);
void CGFModel(int, double, double, int[], int[]);

int main(int argc, char **argv) {
	//cout<<argc<<endl;
	if (argc < 17) {
		cout << "Need more arguments than provided, please check help again"
				<< endl;
		help();
		exit(0);
	}
	int i;
	int gen = 0;
	int mod = 1;
	double prop = 0;
	double len = 0;
	int nes[3];
	int nsample[3];

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
			for (int j = 0; j < 3; ++j) {
				nes[j] = atoi(argv[++i]);
			}
		} else if (string(argv[i]) == "-s") {
			for (int j = 0; j < 3; ++j) {
				nsample[j] = atoi(argv[++i]);
			}
		}
	}
	cout << "Model description:" << endl;
	cout << "generation: " << gen << endl;
	cout << "proportion: " << prop << endl;
	cout << "model: " << mod << endl;
	cout << "length: " << len << endl;
	cout << "Nes: " << nes[0] << " " << nes[1] << " " << nes[2] << endl;
	cout << "nsamples: " << nsample[0] << " " << nsample[1] << " " << nsample[2]
			<< endl;
	int ne = nes[2];
	int nsamp = nsample[2];
	switch (mod) {
	case 1:
		HIModel(gen, prop, len, ne, nsamp);
		break;
	case 2:
		GAModel(gen, prop, len, nes, nsample);
		break;
	case 3:
		CGFModel(gen, prop, len, nes, nsample);
		break;
	default:
		cout
				<< "The model you entered has an error, model must be HI, GA or CGF"
				<< endl;
		help();
		exit(1);
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
	cout
			<< "	-n 	effective population size for ancestral and admixed populations"
			<< endl;
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
	for (i = 0; i < shaplos.size(); i++) {
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
void GAModel(int g, double p, double l, int ns[], int ss[]) {

}

void CGFModel(int g, double p, double l, int ns[], int ss[]) {

}
