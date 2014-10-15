/*
 * Population.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#include <cstdlib>
//#include <ctime>
#include "Population.h"

Population::Population() {
	label = 0;
	ne = 0;
	vector<Chrom> haplos;
	this->haplos = haplos;
}

Population::Population(int label, int ne, const vector<Chrom> &haplos) {
	this->label = label;
	this->ne = ne;
	this->haplos = haplos;
}

Population::Population(const Population & population) {
	label = population.label;
	ne = population.ne;
	haplos = population.haplos;
}

int Population::getLabel() const {
	return label;
}

int Population::getNe() {
	updateNe();
	return ne;
}

vector<Chrom> Population::getHaplos() {
	return haplos;
}

void Population::setLabel(int label) {
	this->label = label;
}

void Population::updateNe() {
	ne = haplos.size() / 2;
}

void Population::addHaplo(Chrom & chr) {
	haplos.push_back(chr);
}

Population Population::evolve(int ne) {
	vector<Chrom> haplo_next;
	int size = haplos.size();
	//srand(time(NULL));
	for (int i = 0; i < ne; ++i) {
		int ind1, ind2;
		ind1 = rand() % size;
		ind2 = rand() % size;
		while (ind1 == ind2) {
			ind2 = rand() % size;
		}
		ChromPair cp(haplos.at(ind1), haplos.at(ind2));
		cp = cp.recombine();
		haplo_next.push_back(cp.getChrom(1));
		haplo_next.push_back(cp.getChrom(2));
	}
	return Population(label, ne, haplo_next);
}

vector<Chrom> Population::sample(int nsamp) {
	int size = haplos.size();
	vector<Chrom> samp;
	//srand(time(NULL));
	for (int i = 0; i < nsamp; ++i) {
		samp.push_back(haplos.at(rand() % size));
	}
	return samp;
}

vector<Population> Population::split(float prop) {
	vector<Chrom> haplos1;
	vector<Chrom> haplos2;
	//srand(time(NULL));
	int size = haplos.size();
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
		haplos1.push_back(haplos.at(index1.at(i)));
	}
	int ilen = index.size();
	for (i = 0; i < ilen; ++i) {
		haplos2.push_back(haplos.at(index.at(i)));
	}
	vector<Population> pops;
	Population pop1(getLabel(), size1 / 2, haplos1);
	Population pop2(getLabel() + 1, ne - size1 / 2, haplos2);
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
