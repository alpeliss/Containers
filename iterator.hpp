#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "base_it.hpp"

namespace ft
{

template <typename T>
class	Iterator : public base_it<T>
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	Iterator(void) {};
	Iterator(pointer ptr) { this->_ptr = ptr; };
	Iterator(Iterator const &src) { *this = src; } ;

	virtual ~Iterator() {};

	Iterator &operator=(Iterator const &src) { this->_ptr = src.operator->(); return (*this); };

	// ARITHMETICS
	Iterator operator +(difference_type b) const { return (Iterator(this->_ptr + b)); }; // a + n
	Iterator operator -(difference_type b) const { return (Iterator(this->_ptr - b)); }; // a - n

	difference_type operator +(Iterator b) const { return (this->_ptr + b._ptr); }; // a + b
	difference_type operator -(Iterator b) const { return (this->_ptr - b._ptr); }; // a - b


	friend Iterator	operator+(difference_type n, const Iterator &rhs)
			{ return rhs.operator+(n); };




	/*
		bool	operator==(const Iterator &b) const{ return (this->_ptr == b._ptr); };
		bool	operator!=(const Iterator &b) const{ return (this->_ptr != b._ptr); };
		bool	operator<(const Iterator &b) const{ return (this->_ptr < b._ptr); };
		bool	operator<=(const Iterator &b) const{ return (this->_ptr <= b._ptr); };
		bool	operator>(const Iterator &b) const{ return (this->_ptr > b._ptr); };
		bool	operator>=(const Iterator &b) const{ return (this->_ptr >= b._ptr); };*/
	// INCREMENTERS
	

		Iterator	&operator++(void) { 
	    	this->_ptr++; 
		    return (*this); 
	    };

		Iterator	operator++(int){ 
		    Iterator tmp(*this);

		    this->_ptr++; 
		    return (tmp); 
	    };	

		Iterator	&operator--(void){ 
		    this->_ptr--; 
		    return (*this); 
	    };

		Iterator	operator--(int) { 
		    Iterator tmp(*this);

		    this->_ptr--; 
		    return (tmp); 
	    }

	//COMPOUND ASSIGNMENTS
	Iterator &operator +=(difference_type b) { 
		this->_ptr += b; 
		return (*this);
	};
	Iterator &operator -=(difference_type b) { 
		this->_ptr -= b; 
		return (*this);
	};
	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*this->_ptr); };											// *a
	const_reference operator *() const { return (*this->_ptr); };								// *a
	reference operator [](difference_type b) { return (*(this->_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(this->_ptr + b)); };		// a[]
	pointer operator ->() { return (this->_ptr); };											// a->b
	pointer operator ->() const { return (this->_ptr); };											// a->b


};
}

#endif