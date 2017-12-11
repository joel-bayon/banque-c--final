#ifndef MYALLOCATOR_H_
#define MYALLOCATOR_H_

#include <iostream>
#include <memory>
#include "GenericMemoryPool.h"

namespace util {

	template <class T>
	class my_specific_allocator
	{
		typedef GenericMemoryPool<T,10000> PoolType;
		static PoolType& getPool() {
			static PoolType pool;
			return pool;
		}

	public:
	  typedef unsigned long    size_type;
	  typedef signed long      difference_type;
	  typedef  T*              pointer;
	  typedef const T*         const_pointer;
	  typedef T&               reference;
	  typedef const T&         const_reference;
	  typedef T                value_type;

	  template <class U>
	  struct rebind { typedef my_specific_allocator<U> other; };

	  pointer allocate(size_type n, const void *hint=0)
		{
			std::cout << "MyAllocator::allocate" << std::endl;
			return static_cast<T*>(getPool().allocate());
		}

		void deallocate(pointer p, size_type n)
		{
			std::cout << "MyAllocator::deallocate" << std::endl;
			 getPool().release(p);
		}
	};


}  // namespace util


#endif // SPECIFIC_ALLOCATOR

