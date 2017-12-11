#ifndef GENERIC_MEMORYPOOL_H_
#define GENERIC_MEMORYPOOL_H_

#include <iostream>
#include <cassert>

using namespace std;

template<typename T = int, int nbElem=100>
class GenericMemoryPool {
	 char pool[nbElem * sizeof(T) ];
	 char used[nbElem];
public :
	 GenericMemoryPool() {
	  cout << "construction d'un pool de mémoire via un template" << endl;
  }

 ~GenericMemoryPool() {
	 cout << "destruction d'un pool de mémoire via un template" << endl;
 }

  void * allocate() {
	  for(int i=0; i<nbElem; i++)
		  if(!used[i]){
			  used[i]=1;
			  return pool + (i * sizeof(T));
		  }
	  return NULL;
  }

  void release(void * p) {
	 char* _p = static_cast<char *>(p);
	 	assert(_p >= pool && p <= (pool +
	 			sizeof(T) * (nbElem-1)));
 	 int index = (_p-pool) / sizeof(T);
 	 used[index]=0; }
};


#endif /* GENERIC_MEMORYPOOL_H_ */
