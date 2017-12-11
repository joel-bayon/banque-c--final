#include <iostream>
#include <vector>
#include <unordered_map>
#include "Operation.h"
#include "Compte.h"
#include "CompteEpargne.h"
#include "Personne.h"
#include "Societe.h"
#include "Banque.h"
#include "MyAllocator.h"
//#include "SpecificAllocator.h"

using namespace std;
using namespace titulaire;
using namespace titulaire::impl;

struct MyClass {
	std::string firstName;
	std::string lastName;
	MyClass(const std::string& firstName, const std::string& lastName) : firstName(firstName), lastName(lastName) {}
	const std::string toString() const { return firstName + " " + lastName; }
	bool  operator == (const MyClass& o) const {
					return firstName == o.firstName && lastName == o.lastName; }
};

template <>
struct std::hash<MyClass>
    {
        size_t operator()( const MyClass& p ) const
        {
            size_t res = 17;
            res = res * 31 + hash<string>()( p.firstName );
            res = res * 31 + hash<string>()( p.lastName );
            return res;
        }
    };



int main(int argc, char **argv) {

	shared_ptr<Titulaire> p(new Personne("Long","Philip", "Bouguenais"));
	shared_ptr<Titulaire> s(new Societe("IRT Jules Verne","23123123", "Nantes"));

	Banque b("LCL", "123123");

	int nCpt1 = b.ouvrirCompte(100, p);
	b.ouvrirCompte(10, p);
	b.ouvrirCompte(50, p);
	b.ouvrirCompte(100, shared_ptr<Titulaire>(new Personne("Long","Philip", "Paris")));
	b.ouvrirCompte(200, shared_ptr<Titulaire>(new Societe("IRT Jules Verne","23123123", "Paris")));
	b.ouvrirCompte(150, p);
	b.ouvrirCompte(1500, p);
	b.ouvrirCompte(2000, p);


	int nCpt2 = b.ouvrirCompteEpargne(100,0.2f, s);
	p = s = nullptr;
	b.editerLesReleves();
	Compte * c1 = b.getCompte(nCpt1);
	Compte * c2 = b.getCompte(nCpt2);


	c1->crediter(100);
	try {
		c1->debiter(300);
	//	c1->debiter(1);	// --> débit impossible ....
	}
	catch(DebiterException& e) {
		cerr << e.what() << endl;
		e.compte->traiterDebitNonAutorise(e.montant);

	}

	c2->crediter(100);
	try {
		c2->debiter(200);
	//	c2->debiter(1);// --> débit impossible ....
	}
	catch(DebiterException& e) {
		cerr << e.what() << endl;
		e.compte->traiterDebitNonAutorise(e.montant);
	}

	b.produireBeneficesFinanciers();
	b.editerLesReleves();
	cout << "******** visualiserCompteBySolde > 1000 ********"<< endl;
	b.visualiserCompteBySolde(1000);

	cout << "******** doSomethingWithCompteByCriteria ********"<< endl;
	b.doSomethingWithCompteByCriteria(Banque::Criteria(
			[](const Compte * c) -> bool {
				return c->getTitulaire()->getAdressePostale() == "Paris";
			},
			[](const Compte * left, const Compte * right) -> bool	 {
				return left->getOperations().size() > right->getOperations().size();
			},
			[](const Compte * c) -> void {
				cout << c->toString() << endl;
			}));


	cout << "******** produireBilanFinancier ********"<< endl;
	cout << "bilan financier de la banque :" << b.produireBilanFinancier() << endl;


	cout << "******** Fin ********"<< endl;
	return 0;

}



