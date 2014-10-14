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

void Model::evolve() {

}
Population Model::getPop() {
	return pop;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

