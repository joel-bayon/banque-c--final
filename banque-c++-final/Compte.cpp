#include <iostream>
#include "Compte.h"

using namespace std;
using namespace titulaire;

static int cptNumero = 10000;

Compte::Compte(float depotInitial, shared_ptr<Titulaire> titulaire)
: numero(cptNumero++), solde(0), titulaire(titulaire) {
	cout << "Construction d'un Compte" << endl;
	crediter(depotInitial);
}

Compte::~Compte() {
	cout << "Destruction d'un Compte" << endl;
//	for(auto o  : operations)
//		delete o;
}

void Compte::crediter(float montant) {
	solde+=montant;
	operations.push_back(unique_ptr<Operation>(new Operation(montant, Operation::typeOperation::credit)));

}

void Compte::debiter(float montant) {
		solde-=montant;
		operations.push_back(unique_ptr<Operation>(new Operation(montant, Operation::typeOperation::debit)));
}

void Compte::editerReleve() const {

	cout << "**** releve de compte ****" << endl;
	cout << "Titulaire=" + titulaire->getIdentite() << " adresse postale=" << titulaire->getAdressePostale() << endl;
	cout << toString() << endl;
	for( auto& op : operations)
		cout << op->toString() << endl;
}

std::string Compte::toString() const {
	return "numero=" + to_string(numero) + " solde=" + to_string(solde);
}

void Compte::traiterDebitNonAutorise(float montant) {
	std::cout << "débit max autorisé = " << debitMaxAutorise() << " entrez un nouveau montant :" ;
	thread_local float nouveauMontant;
	cin >> nouveauMontant;
	try {
		debiter(nouveauMontant);
	}
	catch (DebiterException& e) {
		cerr << e.what() << endl;
		traiterDebitNonAutorise(e.montant);
	}
}

