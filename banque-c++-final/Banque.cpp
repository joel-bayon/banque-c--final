#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <future>
#include <mutex>
#include "Titulaire.h"
#include "Compte.h"
#include "CompteEpargne.h"
#include "SpecificAllocator.h"
#include "Banque.h"

using namespace std;
using namespace titulaire;


int Banque::ouvrirCompte(float depotIntial, shared_ptr<Titulaire> titulaire) {
	unique_ptr<Compte> pc(new CompteCourant(depotIntial,titulaire));
	return rangerCompte(pc);
}

int Banque::ouvrirCompteEpargne(float depotIntial, float taux, shared_ptr<Titulaire> titulaire) {
	unique_ptr<Compte> pc(new CompteEpargne(depotIntial,taux, titulaire));
	return rangerCompte(pc);
}

Compte* Banque::getCompte(int numero) const {
	const auto& iter = comptes.find(numero);
	return iter != comptes.end() ? iter->second.get() : nullptr;
}

float Banque::fermerCompte(int numero) {
	Compte *cpt = getCompte(numero);
	if(cpt != nullptr && cpt->getSolde() >= 0)	 {
		float relicat = cpt->getSolde();
		comptes.erase(numero);
		return relicat;
	}
	return 0;
}

void Banque::editerLesReleves() const {
	for(auto& p : comptes)
		p.second->editerReleve();
}

void Banque::produireBeneficesFinanciers() {
	for(auto& p : comptes)  {
		CompteEpargne * ce = dynamic_cast<CompteEpargne *>(p.second.get());
		if(ce != nullptr) ce->produireInterets();
	}
}

bool comparator(const Compte * a, const Compte * b) {
	return a->getSolde() > b->getSolde();
}

void Banque::visualiserCompteBySolde(float soldeMin) const  {
	vector<const Compte*> collectionComptes;
	collectionComptes.reserve(comptes.size());

	for_each(comptes.begin(), comptes.end(),
			[soldeMin,&collectionComptes](const pair< const int, unique_ptr<Compte>>& p) {
		if(p.second->getSolde()>soldeMin) collectionComptes.push_back(p.second.get());
	}) ;

	cout << "taille de collectionComptes=" << collectionComptes.size() << endl;

	sort(collectionComptes.begin(), collectionComptes.end(), comparator );
	for_each(collectionComptes.begin(), collectionComptes.end(),[](const Compte * c) {
		c->editerReleve();

	});
}

void Banque::doSomethingWithCompteByCriteria(const Banque::Criteria& criteria) const {
	vector<const Compte*> collectionComptes;
	collectionComptes.reserve(comptes.size());

	for_each(comptes.begin(), comptes.end(),
				[&criteria, &collectionComptes](const pair< const int, unique_ptr<Compte>>& p) {
			if(criteria.predicate(p.second.get())) collectionComptes.push_back(p.second.get());
	}) ;

	sort(collectionComptes.begin(), collectionComptes.end(), criteria.comparator );
	for_each(collectionComptes.begin(), collectionComptes.end(), criteria.doSomething);

}


static float produireBilanFinancierParCompte(Compte const & cpt)  {
	float result = 0;
	for(auto & o : cpt.getOperations())
		result += o->getMontant();
	return result;
}

float Banque::produireBilanFinancier() const {
	float result = 0;
	std::vector<std::future<float>> futures;
	for(auto& cpt : comptes)
		futures.push_back(std::async(std::launch::async, produireBilanFinancierParCompte, std::ref(*cpt.second)));

	for(auto& f : futures)
		result += f.get();
	return result;
}


