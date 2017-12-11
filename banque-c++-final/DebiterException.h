
#ifndef DEBITER_EXCEPTION_H_
#define DEBITER_EXCEPTION_H_

#include <stdexcept>
#include <sstream>
#include <cstring>

class Compte;

struct DebiterException: public std::logic_error {
	Compte * compte;
	float montant;
	DebiterException(Compte * compte, float montant) : logic_error("débit non autorisé exception"), compte(compte), montant(montant){}
};

#endif /* DEBITER_EXCEPTION_H_ */
