#ifndef PERSONNE_H_
#define PERSONNE_H_
#include <iostream>
#include <string>
#include  "Employe.h"
#include  "Titulaire.h"

namespace titulaire {
	namespace impl {
		class Personne :  public Titulaire {
			std::string nom;
			std::string prenom;
			std::string adresse;

		public:
			Personne(const std::string& nom, const std::string& prenom, const std::string& adresse)
			: nom(nom), prenom(prenom), adresse(adresse) { std::cout << "Instanciation de Personne" << std::endl;}
			~Personne(){std::cout << "***** Destruction de Personne ******" << std::endl;}

			std::string getIdentite() const override {
				return nom + " " + prenom;
			}
			std::string getAdressePostale() const override {
				return adresse;
			}

		};
	}

}

namespace std {

	template <>struct std::hash<titulaire::impl::Personne>
	{
		size_t operator()( const titulaire::impl::Personne& p ) const
		{
			size_t res = 17;
			res = res * 31 + hash<string>()( p.getIdentite() );
			res = res * 31 + hash<string>()( p.getAdressePostale() );
			return res;
		}
	};

	template <> struct std::equal_to<titulaire::impl::Personne>
	{
		bool operator()( const titulaire::impl::Personne& right,  const titulaire::impl::Personne& left) const
		{
			std::equal_to<string> equal_s;
			return equal_s(right.getIdentite(), left.getIdentite()) && equal_s(right.getAdressePostale(), left.getAdressePostale());

		}
	};
}

#endif /* PERSONNE_H_ */
