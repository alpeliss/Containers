#ifndef CONST_ITERATOR_HPP
# define CONST_ITERATOR_HPP

#include "iterator.hpp"
namespace ft
{

template <typename T>
class	ConstIterator : public base_it<T>
{
public:

	typedef const T					value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef typename std::ptrdiff_t difference_type;

	ConstIterator(void) {};
	ConstIterator(pointer ptr) { _ptr = ptr; };
	ConstIterator(Iterator<T> const &src) { _ptr = src.operator->(); } ;
	ConstIterator(ConstIterator const &src) { *this = src; } ;

	virtual ~ConstIterator() {};

	ConstIterator &operator=(ConstIterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	/*
	bool operator ==(ConstIterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(ConstIterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(ConstIterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(ConstIterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(ConstIterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(ConstIterator const& b) const { return (_ptr <= b._ptr); };*/

	// ARITHMETICS
	ConstIterator operator +(difference_type b) const { return (ConstIterator(_ptr + b)); }; 
	ConstIterator operator -(difference_type  b) const { return (ConstIterator(_ptr - b)); }; 

	difference_type operator +(ConstIterator const b) const { return (_ptr + b._ptr); };
	difference_type operator -(ConstIterator const b) const { return (_ptr - b._ptr); }; 

	// INCREMENTERS
	ConstIterator operator ++() { 
		this->_ptr++; 
		return (*this); 
	};
	
	ConstIterator operator ++(int) { 
		ConstIterator tmp(*this);
		this->_ptr++; 
		return (tmp); 
	};	
	
	ConstIterator operator --() { 
		this->_ptr--; 
		return (*this); 
	};
	
	ConstIterator operator --(int) { 
		ConstIterator tmp(*this);
		this->_ptr--; 
		return (tmp); 
	}
	//COMPOUND ASSIGNMENTS
	ConstIterator operator +=(difference_type b) { 
		this->_ptr += b; 
		return (*this);
	};

	ConstIterator operator -=(difference_type b) {
		this->_ptr -= b; 
		return (*this);
	};
	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_ptr); };								// *a
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b


	private:
		pointer _ptr;

};

}

#endif