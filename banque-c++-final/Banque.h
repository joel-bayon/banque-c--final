#ifndef BANQUE_H_
#define BANQUE_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>
#include "Titulaire.h"
#include "Compte.h"
#include "CompteEpargne.h"
#include "CompteEpargne.h"
#include "MyAllocator.h"


class Banque {
	std::string nom;
	std::string code;
	std::unordered_map<int, std::unique_ptr<Compte>, std::hash<int>, std::equal_to<int>, util::my_specific_allocator< std::pair<const int, std::unique_ptr<Compte>>>> comptes;

	int rangerCompte(unique_ptr<Compte>& cpt) {
		int numero = cpt->getNumero();
		comptes[cpt->getNumero()] = std::move(cpt);
			return numero;
	}
public:

	typedef struct Criteria {
		bool (*predicate) (const Compte*);
		bool (*comparator)(const Compte*, const Compte*);
		void (*doSomething) (const Compte*);
		Criteria( bool (*predicate) (const Compte*),
				    bool (*comparator)(const Compte*, const Compte*),
					void (*doSomething) (const Compte*)
					) : predicate(predicate), comparator(comparator), doSomething(doSomething) {
		}
	} Criteria;


	Banque(std::string const& nom, std::string const&  code) :
		nom(nom), code(code) {
	}
	~Banque() {
		std::cout << "Destruction de Banque" << std::endl;
//		for(auto& p : comptes)
//			delete p.second;
	}

	int ouvrirCompte(float depotIntial, shared_ptr<titulaire::Titulaire> titulaire);
	int ouvrirCompteEpargne(float depotIntial, float taux, shared_ptr<titulaire::Titulaire> titulaire);
	Compte * getCompte(int numero) const;
	float fermerCompte(int numero);
	void editerLesReleves() const;
	void produireBeneficesFinanciers();
	void visualiserCompteBySolde(float soldeMin) const;
	void doSomethingWithCompteByCriteria(const Banque::Criteria& criteria) const;
	float produireBilanFinancier() const;

};

#endif /* BANQUE_H_ */
