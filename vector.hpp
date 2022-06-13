#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>
#include <new>
#include <stdexcept>

namespace ft
{
template<class T,class Allocator = std::allocator<T> >
class vector
{
public:
	typedef T value_type;
    typedef Allocator allocator_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

protected:
	allocator_type		_alloc;
	size_type			_size;
	size_type			_capacity;
	pointer		        _p;
    


public:
    virtual ~vector() {}
    //empty container constructor
	explicit vector(const allocator_type& alloc = allocator_type()) {
	    this->_alloc = alloc;
	    this->_p = _alloc.allocate(0);
        this->_size = 0;
	    this->_capacity = 0;
    }

    //fill constructor
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
        this->_alloc = alloc;
		this->_p = _alloc.allocate(n);
		this->_size = n;
		this->_capacity = n;

		size_type i = 0;
        while (i < n){
            this->_p[i] = val;
            i++;
        }
        return ;
    }

    //range constructor	
    /*template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
            _alloc = alloc;

        }*/

    //copy constructor
    vector (const vector& x){
        this->_alloc = x._alloc;
        this->_size = x._size;
        this->_capacity = x._capacity;
        this->_p =_alloc.allocate(this->_capacity);

        size_type i = 0;
        while (i < this->_size){
            this->_p[i] = x._p[i];
            i++;
        }
        return;
    }

    size_type size() const{
        return this->_size;
    }

    size_type max_size() const{
        return this->_alloc.max_size(); 
    }

    size_type capacity() const{
        return this->_capacity;
    }

    bool empty() const{
        return this->_size == 0;
    }

    void resize (size_type n, value_type val = value_type()){
        pointer tmp;


        if (n > this->max_size())
            throw std::length_error("Can't resize this big.");
        tmp = NULL;
        tmp = this->_alloc.allocate(n);
        size_type i = 0;
        while (i < this->_size && i < n){
            tmp[i] = this->_p[i];
            i++;
        }
        while (i < n){
            tmp[i] = val;
            i++;
        }
        this->_alloc.deallocate(this->_p, this->_capacity);
        this->_p = tmp;
        this->_size = n;
        this->_capacity = n;
    }

    void reserve (size_type n){
        if (n > this->max_size())
            throw std::length_error("Can't reserve this much.");
    }

};
}

#endif
