#ifndef MYALLOCATOR_H_
#define MYALLOCATOR_H_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace MA
{

template<typename T>
inline T* _allocate(ptrdiff_t size, T*)
{
    T* tmp = static_cast<T*>(::operator new(static_cast<size_t>(size * sizeof(T))));
    if(nullptr == tmp)
    {
        std::cerr << "out of memory" << std::endl;
    }

    return tmp;
}

template<typename T>
inline void _deallocate(T* buffer)
{
    ::operator delete(buffer);
}

template<typename T1, typename T2>
inline void _constructor(T1* p, const T2& value)
{
    new(p) T1(value);
}

template<typename T>
inline void _destroy(T* p)
{
    p->~T();
}

template<typename T>
struct allocator
{
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    template<typename U>
    struct rebind
    {
        using other = allocator<U>;
    };

    pointer allocate(size_type n, const void* hint = 0)
    {
        return _allocate(static_cast<difference_type>(n), static_cast<pointer>(nullptr));
    }

    void deallocate(pointer p, size_type n)
    {
        _deallocate(p);
    }

    void construct(pointer p, const T& value)
    {
        _constructor(p, value);
    }

    void destroy(pointer p)
    {
        _destroy(p);
    }

    pointer address(reference x)
    {
        return static_cast<pointer>(&x);
    }

    const_pointer const_address(const_reference x)
    {
        return static_cast<const_pointer>(&x);
    }

    size_type max_size() const
    {
        return static_cast<size_type>(UINT_MAX / sizeof(T));
    }
};

}

#endif /* MYALLOCATOR_H_ */
