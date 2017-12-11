#ifndef SPECIFIC_ALLOCATOR
#define SPECIFIC_ALLOCATOR

#include <memory>
#include "GenericMemoryPool.h"
#include <iostream>

namespace util {

	template <typename T> class my_allocator : public std::allocator<T> {

		typedef GenericMemoryPool<T,10000> poolType;
		static poolType& getPool() {
			static poolType pool;
			return pool;
		}
	public :

		template<typename _T>
		struct rebind
		{ typedef my_allocator<_T> other; };

		   typedef size_t            size_type;
			typedef ptrdiff_t         difference_type;
			typedef T*              pointer;
			typedef const T*        const_pointer;
			typedef T&              reference;
			typedef const T&        const_reference;
			typedef T               value_type;

			typedef true_type propagate_on_container_move_assignment;
			typedef true_type is_always_equal;

		pointer allocate(size_type n, const void *hint=0)
		{
			std::cout << "MyAllocator::allocate" << std::endl;
			if (n > this->max_size())
				std::__throw_bad_alloc();
			return static_cast<T*>(getPool().allocate());
		}

		void deallocate(pointer p, size_type n)
		{
			std::cout << "MyAllocator::deallocate" << std::endl;
			 getPool().release(p);
		}

	};
}

#endif // SPECIFIC_ALLOCATOR
