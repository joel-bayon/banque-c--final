#ifndef TITULAIRE_H_
#define TITULAIRE_H_

#include <string>

namespace titulaire {
	struct Titulaire {
		virtual ~Titulaire(){}
		virtual std::string getIdentite() const = 0;
		virtual std::string getAdressePostale() const = 0;
	};
}

#endif /* TITULAIRE_H_ */
