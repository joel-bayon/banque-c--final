#ifndef COMPTEEPARGNE_H_
#define COMPTEEPARGNE_H_

#include <string>
#include <memory>
#include "Compte.h"

class CompteEpargne : public Compte {
protected :
	float taux;
	float cumulDesBeneficesFinanciers;
public:
	~CompteEpargne() override ;
	CompteEpargne(float depotInitial, float taux, std::shared_ptr<titulaire::Titulaire> titulaire);
	void produireInterets();
	std::string toString() const override;

};

#endif /* COMPTEEPARGNE_H_ */
