#include <iostream>
#include "CompteEpargne.h"

using namespace std;
using namespace titulaire;

CompteEpargne::~CompteEpargne() {
	cout << "Destruction d'un CompteEpargne" << endl;
}

CompteEpargne::CompteEpargne(float depotInitial, float taux,  shared_ptr<Titulaire> titulaire)
: Compte(depotInitial, titulaire) , taux(taux), cumulDesBeneficesFinanciers(0) {
	cout << "Construction d'un CompteEpargne" << endl;
}

void CompteEpargne::produireInterets()  {
	float benefices = taux * solde;
	crediter(benefices);
	cumulDesBeneficesFinanciers+=benefices;
}

std::string CompteEpargne::toString() const  {
	return "CompteEpargne[" + Compte::toString()
			+ " taux=" + to_string(taux)
			+ " cumulDesInterets="
			+ to_string(cumulDesBeneficesFinanciers)
			+ "]";
}

