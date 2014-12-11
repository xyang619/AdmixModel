/*
 * Population.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#include <cstdlib>
//#include <ctime>
#include "Population.h"

Population::Population() :
		label(1), ne(100) {
	vector<ChromPair> indivs;
	this->indivs = indivs;
}

Population::Population(int label, int ne, const vector<ChromPair> &indivs) :
		label(label), ne(ne), indivs(indivs) {
}

int Population::getLabel() const {
	return label;
}

int Population::getNe() {
	updateNe();
	return ne;
}

vector<ChromPair> Population::getIndivs() const {
	return indivs;
}

void Population::setLabel(int label) {
	this->label = label;
}

void Population::updateNe() {
	ne = indivs.size();
}

void Population::addIndiv(ChromPair & cp) {
	indivs.push_back(cp);
}

Population Population::evolve(int ne) {
	vector<ChromPair> indivs_next;
	int size = indivs.size();
	//srand(time(NULL));
	for (int i = 0; i < ne; ++i) {
		int ind1, ind2;
		ind1 = rand() % size;
		ind2 = rand() % size;
		while (ind1 == ind2) {
			ind2 = rand() % size;
		}
		int chr_index = rand() % 2;
		Chrom chr1 = indivs.at(ind1).getChrom(chr_index);
		chr_index = rand() % 2;
		Chrom chr2 = indivs.at(ind2).getChrom(chr_index);
		ChromPair cp(chr1, chr2);
		indivs_next.push_back(cp.recombine());
	}
	return Population(label, ne, indivs_next);
}

vector<ChromPair> Population::sample(int nsamp) const {
	int size = indivs.size();
	vector<ChromPair> samp;
	//srand(time(NULL));
	for (int i = 0; i < nsamp; ++i) {
		samp.push_back(indivs.at(rand() % size));
	}
	return samp;
}

vector<Population> Population::split(float prop) {
	vector<ChromPair> indivs1;
	vector<ChromPair> indivs2;
	//srand(time(NULL));
	int size = indivs.size();
	int size1 = (int) size * prop;
	vector<int> index, index1;
	int i;
	for (i = 0; i < size; ++i) {
		index.push_back(i);
	}
	for (i = 0; i < size1; ++i) {
		int tmp = rand() % index.size();
		index1.push_back(index.at(tmp));
		index.erase(index.begin() + tmp);
	}
	for (i = 0; i < size1; ++i) {
		indivs1.push_back(indivs.at(index1.at(i)));
	}
	int ilen = index.size();
	for (i = 0; i < ilen; ++i) {
		indivs2.push_back(indivs.at(index.at(i)));
	}
	vector<Population> pops;
	Population pop1(getLabel(), size1, indivs1);
	Population pop2(getLabel() + 1, ne - size1, indivs2);
	pops.push_back(pop1);
	pops.push_back(pop2);
	return pops;
}
Population::~Population() {
	// TODO Auto-generated destructor stub
}

//int main(){
//	srand(time(NULL));
//	vector<Chrom> haplos;
//	vector<Segment> segs;
//	segs.push_back(Segment(0,2,1));
//	vector<Segment> segs2;
//	segs2.push_back(Segment(0,2,2));
//	haplos.push_back(Chrom(segs));
//	haplos.push_back(Chrom(segs2));
//	Population p(1,1,haplos);
//	p=p.evolve(10);
//	p.split(0.2);
//
//	vector<Chrom> haps = p.sample(5);
//	for(size_t i=0;i<haps.size();++i){
//		haps.at(i).print();
//	}
//}
