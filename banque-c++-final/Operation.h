#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>

#include "Date.h"

class Operation
{

	public:
		enum class typeOperation { credit, debit };
	private:
		const typeOperation type;
		const float montant;
		const Date date;

	public:
		 explicit Operation(float montant, typeOperation type = typeOperation::credit);
		~Operation();
		std::string toString() const;

		const typeOperation getType() const { return type; }
		const float getMontant() const { return montant; }
		const Date& getDate() const { return date; }

		void * operator new (size_t taille);
		void operator delete (void *);

};



#endif /*OPERATION_H_*/
