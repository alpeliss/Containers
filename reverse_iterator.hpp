#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{

template <class iterator>
class	reverse  
	
{
public:


	typedef iterator iterator_category;
	typedef typename ft::iterator_traits<iterator>::value_type value_type;
	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<iterator>::pointer pointer;
	typedef typename ft::iterator_traits<iterator>::reference reference;


	reverse(void) : _ptr(NULL)  {}
	reverse(iterator ptr) : _ptr(ptr) {}
	reverse(const reverse  &src) : _ptr(src.base()) {} 
	template <class U>
	reverse(const reverse<U>  &src) : _ptr(src.base()) {}

	virtual ~reverse() {};

    iterator base() const{
        return this->_ptr;
    };	


	reverse operator +(difference_type b) const {   
        return reverse(this->_ptr - b); 
    };

	reverse operator -(difference_type b) const {    
        return reverse(this->_ptr + b); 
    };

	reverse operator ++() { 
		this->_ptr--; 
		return (*this); 
	};	

	reverse operator ++(int) { 
		reverse tmp(*this);
		this->_ptr--; 
		return (tmp); 
	};

	reverse operator --() { 
		this->_ptr++; 
		return (*this); 
	};		
	reverse operator --(int) { 
		reverse tmp(*this);
		this->_ptr++; 
		return (tmp); 
	};	

	reverse &operator +=(difference_type b) { 
        this->_ptr = this->_ptr - b; 
        return (*this); 
    };

	reverse &operator -=(difference_type b) { 
        this->_ptr = this->_ptr + b; ; 
        return (*this);
    };	

	reference operator *() const {
			iterator tmp = this->_ptr;
			return *(--tmp);
	}						
	reference operator [](difference_type b) { return *(*this + b); };			
	pointer operator ->() const { return &this->operator*(); };	
    								


	private:
		iterator_category _ptr;
};

	template <class T, class U>
	bool operator==(const reverse<T> & lhs, const reverse<U> & rhs){
		return lhs.base() == rhs.base();
	}


	template <class T, class U>
	bool operator!=(const reverse<T> & lhs, const reverse<U> & rhs){
		return lhs.base() != rhs.base();
	}


	template <class T, class U>
	bool operator<(const reverse<T> & lhs, const reverse<U> & rhs){
		return lhs.base() > rhs.base();
	}


	template <class T, class U>
	bool operator<=(const reverse<T> & lhs, const reverse<U> & rhs)	{
		return lhs.base() >= rhs.base();
	}


	template <class T, class U>
	bool operator>(const reverse<T> & lhs, const reverse<U> & rhs){
		return lhs.base() < rhs.base();
	}

	template <class T, class U>
	bool operator>=(const reverse<T> & lhs, const reverse<U> & rhs){
		return lhs.base() <= rhs.base();
	}

	template<class iterator>
	reverse<iterator> operator+(typename reverse<iterator>::difference_type n, const reverse<iterator> &rev){
		return (reverse<iterator>(rev.base() - n));
	}

	template<class T, class U>
	typename reverse<T>::difference_type operator-(const reverse<T> &lhs, const reverse<U> &rhs){
		return (rhs.base() - lhs.base());
	}
}

#endif