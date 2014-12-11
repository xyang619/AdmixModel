/*
 * AdmSimulator.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: young
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include "GeneralModel.h"
#include "generator.h"

using namespace std;

void help();
int findPos(vector<double>, double);
char * copySeq(vector<double>, char *, double, double);

int main(int argc, char **argv) {
	//cout<<argc<<endl;

	if (argc > 1 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
		help();
		exit(0);
	}

	if (argc < 10) {
		cerr
				<< "Need more arguments than provided, use -h/--help to get more help"
				<< endl;
		exit(1);
	}

	int i;
	int gen = 1;
	int nanc = 2;
	double len = 1;
	int nsample = 10;
	long seed = 0;
	bool givenSeed = 0;
	char * file;
	char * output;

	for (i = 0; i < argc; ++i) {
		if (string(argv[i]) == "-h" || string(argv[i]) == "--help") {
			help();
			exit(0);
		} else if (string(argv[i]) == "-g" || string(argv[i]) == "--gen") {
			gen = atoi(argv[++i]);
		} else if (string(argv[i]) == "-k" || string(argv[i]) == "--nanc") {
			nanc = atoi(argv[++i]);
		} else if (string(argv[i]) == "-l" || string(argv[i]) == "--len") {
			len = atof(argv[++i]);
		} else if (string(argv[i]) == "-f" || string(argv[i]) == "--file") {
			file = argv[++i];
		} else if (string(argv[i]) == "-n" || string(argv[i]) == "--samp") {
			nsample = atoi(argv[++i]);
		} else if (string(argv[i]) == "-o" || string(argv[i]) == "--output") {
			output = argv[++i];
		} else if (string(argv[i]) == "-s" || string(argv[i]) == "--seed") {
			seed = atol(argv[++i]);
			givenSeed = 1;
		}
	}
	if (!givenSeed) {
		seed = time(NULL);
	}
	srand(seed);
	//output the model description
	cerr << "========================================================" << endl;
	cerr << "Arguments summary:" << endl;
	cerr << "generation: " << gen << endl;
	cerr << "number of ancestral populations: " << nanc << endl;
	cerr << "chromosome length: " << len << endl;
	cerr << "number of samples: " << nsample << endl;
	cerr << "model file: " << file << endl;
	cerr << "output prefix: " << output << endl;
	cerr << "random seed: " << seed << endl;
	cerr << "========================================================" << endl;

	GeneralModel gm(file, gen, nanc);
	gm.evolve(gen, nanc, len);
	vector<ChromPair> sample = gm.getPop().sample(nsample);
	//SNP number between 1~10 x 10k;
	long numbSnp = 1 + rand() % 10;
	numbSnp *= 100;
	vector<double> poss = genPos(numbSnp, len);
	//prepare output, same as MS output
	string segfile = string(output) + ".seg";
	string hapfile = string(output) + ".hap";
	ofstream segout(segfile.c_str());
	ofstream hapout(hapfile.c_str());
	if (!segout.is_open() || !hapout.is_open()) {
		cerr << "Can't open file " << segfile << " or " << hapfile << endl;
		abort();
	}
	for (i = 0; i < argc; ++i) {
		hapout << argv[i] << " ";
	}
	hapout << endl;
	hapout << seed << endl << endl << "//" << endl;
	hapout << "segsites: " << numbSnp << endl;
	hapout << "positions: ";
	for (i = 0; i < numbSnp; ++i) {
		hapout << setprecision(8) << poss.at(i) << " ";
	}
	hapout << endl;
	char bases[] = { 'A', 'C', 'G', 'T' };
	//seq1 and seq2 are population 1 and 2 ancestral haplotypes
	char * seq1 = genSeq(numbSnp, bases, 4);
	char * seq2 = genSeq(numbSnp, bases, 4);
	//cout << "//ancestral haplotypes" << endl;
	hapout << seq1 << endl;
	hapout << seq1 << endl;
	hapout << seq2 << endl;
	hapout << seq2 << endl;
	//cout << "//admixed haplotypes" << endl;
	for (i = 0; i < nsample; ++i) {
		ChromPair cp = sample.at(i);
		for (int j = 1; j < 3; ++j) {
			Chrom chr = cp.getChrom(i);
			chr.smooth();
			int nseg = chr.getNumSegments();
			//cout << "chrom-" << i << ": ";
			for (int j = 0; j < nseg; ++j) {
				Segment seg = chr.getSegment(j);
				double start, end;
				int label;
				start = seg.getStart();
				end = seg.getEnd();
				label = seg.getLabel();
				segout << setprecision(8) << setw(16) << start << setw(16)
						<< end << setw(4) << label << endl;
				if (seg.getLabel() == 1) {
					hapout << copySeq(poss, seq1, start, end);
				} else {
					hapout << copySeq(poss, seq2, start, end);
				}
			}
			hapout << endl;
		}
	}
	segout.close();
	hapout.close();
	return 0;
}

void help() {
	cout << "Description: General Admixture Model Simulator" << endl;
	cout << "Arguments:" << endl;
	cout << "	-h/--help	print help message" << endl;
	cout << "	-g/--gen	generation since admixture" << endl;
	cout << "	-k/--nanc	number of ancestral populations" << endl;
	cout << "	-l/--len	length of chromosome to be simulated" << endl;
	cout << "	-f/--file	model parameter description file" << endl;
	//cout << "	-p/--prefix	prefix of input file" << endl;
	cout << "	-o/--output	prefix of output file" << endl;
	cout << "	-s/--seed	seed of random generator" << endl;
}

int findPos(vector<double> poss, double pos) {
	int left = 0;
	int right = poss.size();
	if (pos <= poss.front())
		return left;
	if (pos > poss.back())
		return right;
	int mid = (left + right + 1) / 2;
	while (left < right) {
		if (pos > poss.at(mid))
			left = mid;
		else
			right = mid - 1;
		mid = (left + right + 1) / 2;
	}
	return left;
}

char * copySeq(vector<double> poss, char * seq, double start, double end) {
	char * ret;
	int left, right;
	left = findPos(poss, start);
	right = findPos(poss, end);
	//cout << left << "-" << right << endl;
	ret = new char[right + 1 - left];
	ret = strncpy(ret, seq + left, right - left);
	ret[right - left] = '\0';
	//cout << ret << endl;
	return ret;
}

