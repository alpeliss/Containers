#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <typename iterator>
class	reverse_iterator
{
public:

	typedef typename iterator::value_type		value_type;
	typedef typename iterator::reference		reference;
	typedef typename iterator::const_reference	const_reference;
	typedef typename iterator::pointer			pointer;
	typedef typename iterator::const_pointer	const_pointer;
	typedef typename iterator::difference_type	difference_type;

	reverse_iterator(void) {};

	reverse_iterator(pointer ptr) { _ptr = ptr; };

//	reverse_iterator(iterator<value_type> const &src) { _ptr = src.operator->(); } ;
	
	reverse_iterator(reverse_iterator const &src) { *this = src; } ;

	virtual ~reverse_iterator() {};

	reverse_iterator &operator=(reverse_iterator const &src) { _ptr = src._ptr; return (*this); };

	// BOOLEANS
	bool operator ==(reverse_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(reverse_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(reverse_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(reverse_iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(reverse_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(reverse_iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	reverse_iterator operator +(difference_type b) { return (reverse_iterator(_ptr - b)); }; // a + b
	reverse_iterator operator -(difference_type b) { return (reverse_iterator(_ptr + b)); }; // a - b

	difference_type operator +(reverse_iterator b) { return (_ptr - b._ptr); }; // a + b
	difference_type operator -(reverse_iterator b) { return (_ptr + b._ptr); }; // a - b

	// INCREMENTERS
	reverse_iterator operator ++() { _ptr--; return (*this); };			// ++a
	reverse_iterator operator ++(int) { _ptr--; return (reverse_iterator(_ptr + 1)); };	// a++
	reverse_iterator operator --() { _ptr++; return (*this); };			// --a
	reverse_iterator operator --(int) { _ptr++; return (reverse_iterator(_ptr - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _ptr -= b; };	// a += b
	void operator -=(difference_type b) { _ptr += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	iterator operator ->() const { return (_ptr); };											// a->b


	private:
		iterator _ptr;
};

}

#endif