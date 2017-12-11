
#include <sstream>
#include <iostream>
#include <string>
#include "Operation.h"
#include "GenericMemoryPool.h"
#include <boost/pool/object_pool.hpp>



using namespace std;

	static const char * stringType[2] = { "credit", "debit" };
	static GenericMemoryPool<Operation, 10000> pool;
	//static boost::object_pool<Operation> pool(10000);

	Operation::Operation(float montant,  typeOperation type) : type(type), montant(montant)
	{
		cout << "instanciation d'une operation" << endl;
	}


	Operation::~Operation()
	{
		cout << "destruction d'une operation" << endl;
	}

	string Operation::toString() const  {
		return "type=" + string(stringType[static_cast<int>(type)]) + " montant=" +  to_string(montant) + " date=" + date.toString();
	}

	/*void * Operation::operator new (size_t taille){
		cout << "Operation::operator new" << endl;
		return pool.malloc();

	}

	void Operation::operator delete (void * p) {
		cout << "Operation::operator delete" << endl;
		 pool.destroy(static_cast<Operation *>(p));
	}*/

	void * Operation::operator new (size_t taille){
		cout << "Operation::operator new" << endl;
		return pool.allocate();

	}
	void Operation::operator delete (void * p) {
		cout << "Operation::operator delete" << endl;
		return pool.release(p);
	}


