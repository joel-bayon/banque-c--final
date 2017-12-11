/*
 * Societe.h
 *
 *  Created on: 17 janv. 2017
 *      Author: joel
 */

#ifndef SOCIETE_H_
#define SOCIETE_H_

#include "Titulaire.h"

namespace titulaire {
	namespace impl {

		class Societe : public Titulaire {
			std::string raisonSociale;
			std::string siret;
			std::string siege;

		public:
			Societe(const std::string& raisonSociale, const std::string& siret, const std::string& siege)
			: raisonSociale(raisonSociale), siret(siret), siege(siege) {std::cout << "Instanciation de Societe" << std::endl;}

			~Societe(){std::cout << "******* Destruction de Societe *******" << std::endl;}

			std::string getIdentite() const override {
					return raisonSociale + " " + siret;
				}
			std::string getAdressePostale() const override {
				return siege;
			}

		};
	}
}


#endif /* SOCIETE_H_ */
