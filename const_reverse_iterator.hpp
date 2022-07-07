
#ifndef CONST_REVERSE_ITERATOR_HPP
# define CONST_REVERSE_ITERATOR_HPP

namespace ft
{

template <typename iterator>
class	ConstReverseIterator
{
public:

	typedef typename iterator::value_type		value_type;
	typedef typename iterator::reference		reference;
	typedef typename iterator::const_reference	const_reference;
	typedef typename iterator::pointer			pointer;
	typedef typename iterator::const_pointer	const_pointer;
	typedef typename iterator::difference_type	difference_type;

	ConstReverseIterator(void) {};
	//ConstReverseIterator(ConstIterator<value_type> const &src) { _ptr = src.operator->(); } ;
	ConstReverseIterator(ReverseIterator<iterator> const &src) { _ptr = src.operator->(); } ;
	ConstReverseIterator(ConstReverseIterator const &src) { *this = src; } ;

	virtual ~ConstReverseIterator() {};

	ConstReverseIterator &operator=(ConstReverseIterator const &src) { _ptr = src._ptr; return (*this); };

	// BOOLEANS
	bool operator ==(ConstReverseIterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(ConstReverseIterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(ConstReverseIterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(ConstReverseIterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(ConstReverseIterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(ConstReverseIterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	ConstReverseIterator operator +(difference_type b) { return (ConstReverseIterator(_ptr - b)); }; // a + b
	ConstReverseIterator operator -(difference_type b) { return (ConstReverseIterator(_ptr + b)); }; // a - b

	difference_type operator +(ConstReverseIterator b) { return (_ptr - b._ptr); }; // a + b
	difference_type operator -(ConstReverseIterator b) { return (_ptr + b._ptr); }; // a - b

	// INCREMENTERS
	ConstReverseIterator operator ++() { _ptr--; return (*this); };			// ++a
	ConstReverseIterator operator ++(int) { _ptr--; return (ConstReverseIterator(_ptr + 1)); };	// a++
	ConstReverseIterator operator --() { _ptr++; return (*this); };			// --a
	ConstReverseIterator operator --(int) { _ptr++; return (ConstReverseIterator(_ptr - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _ptr -= b; };	// a += b
	void operator -=(difference_type b) { _ptr += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b


	private:

		ConstReverseIterator(pointer ptr) { _ptr = ptr; };
		pointer _ptr;
};

}

#endif