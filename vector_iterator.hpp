#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
template <typename iterator>
class vector_iterator{
	
public:

	typedef iterator iterator_category;
	typedef typename ft::iterator_traits<iterator>::value_type value_type;
	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<iterator>::pointer pointer;
	typedef typename ft::iterator_traits<iterator>::reference reference;


	vector_iterator(void) : _ptr(NULL) {} 
	vector_iterator(iterator ptr): _ptr(ptr) {}
	vector_iterator(const vector_iterator & src): _ptr(src.base()){}
	template <class U>
	vector_iterator(const vector_iterator<U>& src): _ptr(src.base()){}

	virtual ~vector_iterator() {}

	iterator base() const{
		return this->_ptr;
	}


	template< class U >
	vector_iterator& operator=( const vector_iterator<U>& other ){
		this->_ptr = other.base();
		return *this;
	}

	reference operator*() const{ return *this->_ptr; }
    pointer operator->(){ return this->_ptr; }
		
    vector_iterator& operator++(){
		this->_ptr++;
		return *this;
	}

	vector_iterator operator++(int){
		vector_iterator tmp(*this);
		this->_ptr++;
		return tmp;
	}

	vector_iterator& operator--(){
		this->_ptr--;
		return *this;
	}

    vector_iterator operator--(int){
		vector_iterator tmp(*this);
		this->_ptr--;
		return tmp;
	}

	vector_iterator operator+(difference_type n) const{ 
        return vector_iterator(this->_ptr + n); 
    }

	vector_iterator operator-(difference_type n) const{ 
        return vector_iterator(this->_ptr - n); 
    }

	vector_iterator & operator+=(difference_type n){
		this->_ptr += n;
		return *this;
	}

	vector_iterator & operator-=(difference_type n){
		this->_ptr -= n;
		return *this;
	}

	reference operator[](int i){
        return this->_ptr[i];
	}

private:
	iterator_category _ptr;

};


	template<typename T, typename U>
	bool operator==(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() == rhs.base();
	}

	template<typename T, typename U>
	bool operator!=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() != rhs.base();
	}


	template<typename T, typename U>
	bool operator<(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() < rhs.base();
	}


	template<typename T, typename U>
	bool operator>(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() > rhs.base();
	}

	template<typename T, typename U>
	bool operator<=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() <= rhs.base();
	}


	template<typename T, typename U>
    bool operator>=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() >= rhs.base();
	}

	template<typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &it){
		return vector_iterator<T>(it.base() + n);
	}

	template<typename T, typename U>
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs){
		return lhs.base() - rhs.base();
	}

}

#endif
