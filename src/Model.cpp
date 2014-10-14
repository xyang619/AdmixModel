/*
 * Model.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: young
 */

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
	int nhaps1 = (int) 2 * ne * prop;
	int nhaps2 = 2 * ne - nhaps1;
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

}

void Model::CGFMod(double len) {

}
Model::~Model() {
	// TODO Auto-generated destructor stub
}

