#ifndef MEMORYPOOL_H_
#define MEMORYPOOL_H_

#include <cstring>
#include <cassert>

class MemoryPool {
	 char * pool;
	 char * used;
	 int sizeElem;
	 int nbELem;
public:

	MemoryPool(int sizeElem, int nbELem) : sizeElem(sizeElem), nbELem(nbELem) {
		pool = new char[sizeElem * nbELem];
		used = new char[nbELem];
		std::memset(used, 0, nbELem);
	}

	~MemoryPool() {
		delete pool;
		delete used;
	}

	void * allocate() {
		for (int i = 0; i<nbELem; i++)
		if (!used[i]){
			used[i] = 1;
			return pool + (i * sizeElem);
		}
		return NULL;
	}
	void release(void * p) {
		char * _p = static_cast<char *>(p);
		assert(_p >= pool && p <= (pool +
			sizeElem* (nbELem - 1)));
		int index = (_p - pool) / sizeElem;
		used[index] = 0;
	}
};

#endif // MEMORYPOOL_H_

