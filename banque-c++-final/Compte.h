/*
 * Compte.h
 *
 *  Created on: 16 janv. 2017
 *      Author: joel
 */

#ifndef COMPTE_H_
#define COMPTE_H_

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Operation.h"
#include "Titulaire.h"
#include "DebiterException.h"

class Compte {

protected:
	const int numero;
	float solde;
	std::shared_ptr<titulaire::Titulaire> titulaire;
	std::vector<std::unique_ptr<Operation>> operations;

public:
	Compte(float depotInitial, std::shared_ptr<titulaire::Titulaire> titulaire);
	virtual ~Compte();

	void crediter(float montant);
	void editerReleve() const ;
	virtual void  debiter(float montant);
	virtual std::string toString() const;
	virtual float debitMaxAutorise() { return solde; }
	void traiterDebitNonAutorise(float montant);

	Compte(const Compte &) = delete;
	Compte & operator = (const Compte &) = delete;

	int getNumero() const {
		return numero;
	}

	float getSolde() const {
		return solde;
	}

	const std::shared_ptr<titulaire::Titulaire>& getTitulaire() const {
		return titulaire;
	}

	const std::vector<std::unique_ptr<Operation>>& getOperations() const {
		return operations;
	}
};

class CompteCourant : public Compte {
protected :
	float decouvertAutorise;

public :
	CompteCourant(float depotInitial, std::shared_ptr<titulaire::Titulaire> titulaire) : Compte(depotInitial, titulaire), decouvertAutorise(depotInitial) {
		std::cout << "Construction d'un CompteCourant" << std::endl;
	}

	void  debiter(float montant) override {
		if(solde+decouvertAutorise > montant)
			Compte::debiter(montant);
		else throw DebiterException(this,montant);
	}

	std::string toString() const override {
		return "CompteCourant[" + Compte::toString() + " decouvertAutorise=" + std::to_string(decouvertAutorise) + "]";
	}

	float debitMaxAutorise() override { return solde+decouvertAutorise; }
};



#endif /* COMPTE_H_ */
