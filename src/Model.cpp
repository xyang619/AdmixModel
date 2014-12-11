/*
 * Model.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: young
 */
#include <cmath>
#include "Model.h"

//Model::Model() {
//	mod = 1;
//	gen = 1;
//	ne = 1000;
//	prop = 0.5;
//	Population p;
//	pop = p;
//}

Model::Model(int mod, int gen, double prop) :
		mod(mod), gen(gen), ne(100), prop(prop) {
	Population p;
	pop = p;
}

Model::Model(int mod, int gen, int ne, double prop) :
		mod(mod), gen(gen), ne(ne), prop(prop) {
	Population p;
	pop = p;
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

Population Model::getPop() const {
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
	//generate Ne*Prop chromosomes from population 1 and rest of from population 2
	//combine the mixed chromosomes to one population and let evolve g generations
	int nindivs1 = (int) ne * prop;
	int nindivs2 = ne - nindivs1;
	vector<ChromPair> mix_indivs;
	int i;
	for (i = 0; i < nindivs1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	for (i = 0; i < nindivs2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	Population admp;
	admp = Population(3, ne, mix_indivs);
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
	int nindivs1 = (int) ne * prop;
	int nindivs2 = ne - nindivs1;
	vector<ChromPair> mix_indivs;
	int i;
	for (i = 0; i < nindivs1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	for (i = 0; i < nindivs2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	Population admp = Population(3, ne, mix_indivs);
	admp.evolve(ne);
	nindivs1 = nindivs1 / gen;
	nindivs2 = nindivs2 / gen;
	int nprev = ne - nindivs1 - nindivs2;
	for (int g = 1; g < gen; ++g) {
		vector<ChromPair> tmp_indivs = admp.sample(nprev);
		for (i = 0; i < nindivs1; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 1));
			Chrom chr(segs);
			mix_indivs.push_back(ChromPair(chr, chr));
		}
		for (i = 0; i < nindivs2; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 2));
			Chrom chr(segs);
			mix_indivs.push_back(ChromPair(chr, chr));
		}
		Population tmp = Population(3, ne, tmp_indivs);
		admp = tmp.evolve(ne);
	}
	pop = admp;
}

void Model::CGFMod(double len) {
	//admixture for first generation as HI Model
	//from second generation, nhaps1 from previous generation and nhaps2 from population 2
	int nindivs2 = (int) ne * (1 - pow(prop, 1.0 / gen));
	int nindivs1 = ne - nindivs2;
	vector<ChromPair> mix_indivs;
	int i;
	for (i = 0; i < nindivs1; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 1));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	for (i = 0; i < nindivs2; ++i) {
		vector<Segment> segs;
		segs.push_back(Segment(0, len, 2));
		Chrom chr(segs);
		mix_indivs.push_back(ChromPair(chr, chr));
	}
	Population admp = Population(3, ne, mix_indivs);
	admp.evolve(ne);
	for (int g = 1; g < gen; ++g) {
		vector<ChromPair> tmp_indivs = admp.sample(nindivs1);
		for (i = 0; i < nindivs2; ++i) {
			vector<Segment> segs;
			segs.push_back(Segment(0, len, 2));
			Chrom chr(segs);
			mix_indivs.push_back(ChromPair(chr, chr));
		}
		Population tmp = Population(3, ne, tmp_indivs);
		admp = tmp.evolve(ne);
	}
	pop = admp;

}
Model::~Model() {
// TODO Auto-generated destructor stub
}

