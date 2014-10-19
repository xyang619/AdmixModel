/*
 * Model.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: young
 */
#include <cmath>
#include "Model.h"

Model::Model() {
	mod = 1;
	gen = 1;
	ne = 1000;
	prop = 0.5;
	Population p;
	pop = p;
}

Model::Model(int mod, int gen, double prop) {
	this->mod = mod;
	this->gen = gen;
	this->ne = 1000;
	this->prop = prop;
	Population p;
	pop = p;
}

Model::Model(int mod, int gen, int ne, double prop) {
	this->mod = mod;
	this->gen = gen;
	this->ne = ne;
	this->prop = prop;
	Population p;
	pop = p;
}

Model::Model(const Model & model) {
	mod = model.mod;
	gen = model.gen;
	ne = model.ne;
	prop = model.prop;
	pop = model.pop;
}

int Model::getMod() const {
	return mod;
}

int Model::getNe() const {
	return ne;
}

int Model::getGen() const {
	return gen;
}

double Model::getProp() const {
	return prop;
}

void Model::setMod(int mod) {
	this->mod = mod;
}

void Model::setNe(int ne) {
	this->ne = ne;
}

void Model::setGen(int gen) {
	this->gen = gen;
}

void Model::setProp(double prop) {
	this->prop = prop;
}

Population Model::getPop() {
	return pop;
}

void Model::evolve(double len) {
	switch (mod) {
	case 1:
		HIMod(len);
		break;
	case 2:
		GAMod(len);
		break;
	case 3:
		CGFMod(len);
		break;
	}
}

void Model::HIMod(double len) {
	//generate 2*Ne*Prop chromosomes from population 1 and rest of from population 2
	//combine the mixed chromosomes to one population and let evolve g generations
	int nhaps1 = (int) 2 * ne * prop;
	int nhaps = 2 * ne;
	int nhaps2 = nhaps - nhaps1;
	vector<Chrom> mixhaplos;
	int i;
	for (i = 0; i < nhaps1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		mixhaplos.push_back(Chrom(segs));
	}
	for (i = 0; i < nhaps2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		mixhaplos.push_back(Chrom(segs));
	}
	Population admp;
	admp = Population(3, ne, mixhaplos);
	for (i = 0; i < gen; ++i) {
		admp = admp.evolve(ne);
	}
	pop = admp;
}

void Model::GAMod(double len) {
	//admixture for first generation as HI Model
	//from the second to current generation,
	//nhaps1/gen chromosome from population 1, nhaps2/gen chromosomes from population 2,
	//the rest of are randomly drop from previous generation
	int nhaps1 = (int) 2 * ne * prop;
	int nhaps = 2 * ne;
	int nhaps2 = nhaps - nhaps1;
	vector<Chrom> mixhaplos;
	int i;
	for (i = 0; i < nhaps1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		mixhaplos.push_back(Chrom(segs));
	}
	for (i = 0; i < nhaps2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		mixhaplos.push_back(Chrom(segs));
	}
	Population admp = Population(3, ne, mixhaplos);
	admp.evolve(ne);
	nhaps1 = nhaps1 / gen;
	nhaps2 = nhaps2 / gen;
	int nprev = nhaps - nhaps1 - nhaps2;
	for (int g = 1; g < gen; ++g) {
		vector<Chrom> tmpHaplos = admp.sample(nprev);
		for (i = 0; i < nhaps1; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 1));
			tmpHaplos.push_back(Chrom(segs));
		}
		for (i = 0; i < nhaps2; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 2));
			tmpHaplos.push_back(Chrom(segs));
		}
		Population tmp = Population(3, ne, tmpHaplos);
		admp = tmp.evolve(ne);
	}
	pop = admp;
}

void Model::CGFMod(double len) {
	//admixture for first generation as HI Model
	//from second generation, nhaps1 from previous generation and nhaps2 from population 2
	int nhaps2 = (int) 2 * ne * (1 - pow(prop, 1.0 / gen));
	int nhaps = 2 * ne;
	int nhaps1 = nhaps - nhaps2;
	vector<Chrom> mixhaplos;
	int i;
	for (i = 0; i < nhaps1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		mixhaplos.push_back(Chrom(segs));
	}
	for (i = 0; i < nhaps2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		mixhaplos.push_back(Chrom(segs));
	}
	Population admp = Population(3, ne, mixhaplos);
	admp.evolve(ne);
	for (int g = 1; g < gen; ++g) {
		vector<Chrom> tmpHaplos = admp.sample(nhaps1);
		for (i = 0; i < nhaps2; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 2));
			tmpHaplos.push_back(Chrom(segs));
		}
		Population tmp = Population(3, ne, tmpHaplos);
		admp = tmp.evolve(ne);
	}
	pop = admp;

}
Model::~Model() {
// TODO Auto-generated destructor stub
}

