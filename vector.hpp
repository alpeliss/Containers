#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>
#include <iostream>
#include <new>
#include <unistd.h>
#include "enable_if.hpp"
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<class T,class Allocator = std::allocator<T> >
class vector
{
public:
	typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer; 
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

    typedef ft::vector_iterator<pointer>  iterator;
	typedef ft::vector_iterator<const_pointer> const_iterator;
	typedef ft::reverse<iterator>		reverse_iterator;
    typedef ft::reverse<const_iterator>	  const_reverse_iterator;


protected:
	allocator_type		_alloc;
	size_type			_size;
	size_type			_capacity;
	pointer		        _p;
    


public:
    virtual ~vector() {
        this->clear();
	    if (this->_capacity > 0){
		    this->_alloc.deallocate(this->_p, this->_capacity);
		        this->_capacity = 0;
	    }
        this->_size = 0;
    }

	explicit vector(const allocator_type& alloc = allocator_type())
            :_alloc(alloc), _size(0), _capacity(0), _p(0) {
        this->_p = this->_alloc.allocate(this->_capacity);
    }

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
        this->_alloc = alloc;
		this->_p = _alloc.allocate(n);
		this->_size = n;
		this->_capacity = n;

		size_type i = 0;
        while (i < n){
            this->_alloc.construct(&(this->_p[i]), val);
            i++;
        }
        return ;
    }

    template <class InputIterator>
        vector (InputIterator first,  InputIterator last, const allocator_type& alloc = allocator_type()
            , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
        :_alloc(alloc), _size(0), _capacity(0), _p(0){
			unsigned int i = 0;
            InputIterator tmp = first;

            while (tmp != last){
                tmp++;
                i++;
            }
            this->_size = i;
            this->_capacity = i;
            this->_p = this->_alloc.allocate(i);
            i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				this->_alloc.construct(&(this->_p[i]), (*it));
				i++;
			}
        }


    vector(vector const &x) : _alloc(allocator_type()), _size(0), _capacity(0){ 
		this->_capacity = x.capacity();
		this->_size = x.size();
		this->_p = this->_alloc.allocate(x.capacity());
        unsigned int i = 0;
        while (i < this->size()){
			this->_alloc.construct(&(this->_p[i]), x[i]);
            i++;
        }
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
        pointer tmp;

        if (n > this->max_size())
            throw std::length_error("Can't reserve this much.");
        if (n < this->_capacity)
            return ;
        tmp = this->_alloc.allocate(n);
        size_type i = 0;
        while (i < this->_size && i < n){
            tmp[i] = this->_p[i];
            i++;
        }
        this->_alloc.deallocate(this->_p, this->_capacity);
        this->_p = tmp;
        this->_capacity = n;
    }

    reference operator[] (size_type n){
        return this->_p[n];
    }

    const_reference operator[] (size_type n) const{
        return this->_p[n];
    }

    reference at (size_type n){
        if (n >= this->_size)
            throw std::out_of_range("Index not in the vector.");
        return this->_p[n];
    }

    const_reference at (size_type n) const{
        if (n >= this->_size)
            throw std::out_of_range("Index not in the vector.");
        return this->_p[n];
    }

    reference front(){
        if (this->empty() == true)
            throw std::out_of_range("No front in an empty vector.");
        return this->_p[0];
    }

    const_reference front() const{
        if (this->empty() == true)
            throw std::out_of_range("No front in an empty vector.");
        return this->_p[0];
    }

    reference back(){
        if (this->empty() == true)
            throw std::out_of_range("No back in an empty vector.");
        return this->_p[this->_size - 1];
    }

    const_reference back() const{
        if (this->empty() == true)
            throw std::out_of_range("No back in an empty vector.");
        return this->_p[this->_size - 1];
    }

    iterator begin(){
        return (iterator(this->_p));
    }

    const_iterator begin() const{
        return (const_iterator(this->_p));
    }

    iterator end(){
        return   iterator(this->_p + this->_size);
    }

    const_iterator end() const{
        return const_iterator(this->_p + this->_size);
    }

    reverse_iterator rbegin(){
        return reverse_iterator(this->end());
    }

    const_reverse_iterator	rbegin() const{
        return const_reverse_iterator(this->end());
    }

    reverse_iterator rend(){
        return reverse_iterator(this->begin());
    }

    const_reverse_iterator rend() const{ 
        return const_reverse_iterator(this->begin());
    }

    allocator_type get_allocator(){
        allocator_type tmp;

        return tmp;
    }

   template <class InputIterator>
    void assign (InputIterator first, InputIterator last
                , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0){
       InputIterator tmp;

        this->clear();
        tmp = first;
        while (tmp != last){
            this->push_back(*tmp);
            tmp++;
            }
    }


    void assign (size_type n, const value_type& val) {
        size_type i = 0;

		this->clear();
		while (i < n){
			this->push_back(val);
            i++;
        }
    }

    void push_back (const value_type& val){
        pointer         tmp;
        unsigned int    i = 0;
        
        if (this->_capacity == 0){
			this->_p = _alloc.allocate(1);
		    this->_capacity = 1;
            }
        if (this->_size == this->_capacity) {
            tmp = _alloc.allocate(this->_capacity * 2);
            while (i < this->_size){
				this->_alloc.construct(tmp + i, *(this->_p + i));
				this->_alloc.destroy(this->_p + i);
                i++;
                }
            this->_alloc.deallocate(this->_p, this->_capacity);
            this->_p = tmp;
            this->_capacity *= 2;
            }
		this->_alloc.construct(this->_p + this->_size, val);
        this->_size++;
    }

	void pop_back(void) {
        if (this->empty() == true)
            throw std::out_of_range("No pop_back in an empty vector.");
		this->_alloc.destroy(this->_p + this->_size - 1);
        this->_size--;
	}

    
	void clear (void)
	{
        unsigned int i = 0;
		while (i < this->_size){
			this->_alloc.destroy(this->_p + i);
            i++;
        }
        this->_size = 0;
	}

    iterator	insert(iterator position, const value_type &val) {
	    difference_type idx = position - this->begin();

	    this->insert(position, 1, val);
	    return (iterator(this->begin() + idx));
    }

    void	insert(iterator position, size_type n, const value_type &val) {
        difference_type pos = position - this->begin();
        unsigned int    i;
        pointer tmp1;


        while (this->_capacity - this->_size < n) {
            if (this->_capacity == 0){
			    this->_p = _alloc.allocate(1);
		        this->_capacity = 1;
            }
            else{
                tmp1 = _alloc.allocate(this->_capacity * 2);
                i = 0;
                while (i < this->_size){
				    this->_alloc.construct(tmp1 + i, *(this->_p + i));
				    this->_alloc.destroy(this->_p + i);
                    i++;        
                }
                this->_alloc.deallocate(this->_p, this->_capacity);
                this->_p = tmp1;
                this->_capacity *= 2;
            }
        }

		vector		tmp2(this->begin() + pos, this->end());

        i = 0;
		while( i < tmp2.size()){
			this->pop_back();
            i++;
        }
		while (n > 0)
		{
			this->push_back(val);
			n--;
		} 
        iterator    it = tmp2.begin();
		while (it != tmp2.end()){
			this->push_back(*it);
            it++;
        }
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last
                , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
        difference_type pos = position - this->begin();
        difference_type n = 0;
        pointer big;
        InputIterator iit;
        unsigned int i;

        iit = first;
        while (iit != last)
        {
            iit++;
            n++;
        }
        while ((difference_type)(this->_capacity - this->_size) < n) {
            if (this->_capacity == 0){
			    this->_p = _alloc.allocate(1);
		        this->_capacity = 1;
                }
            else{
                big = this->_alloc.allocate(this->_capacity * 2);
                i = 0;
                while (i < this->_size){
				    this->_alloc.construct(big + i, *(this->_p + i));
				    this->_alloc.destroy(this->_p + i);
                    i++;
                }
                this->_alloc.deallocate(this->_p, this->_capacity);
                this->_p = big;
                this->_capacity *= 2;
            }
        }

		vector		tmp(this->begin() + pos, this->end());

        i = 0;
		while( i < tmp.size()){
			this->pop_back();
            i++;
        }
		while (first != last)
		{
			this->push_back(*first);
			first++;
		} 
        iterator    it = tmp.begin();
		while (it != tmp.end()){
			this->push_back(*it);
            it++;
        }
    }

    vector &operator=(vector const  &x){
        if (this == &x)
		    return (*this);
		this->clear();
		this->_alloc.deallocate(this->_p, this->capacity());
		this->_capacity = x.capacity();
		this->_size = x.size();
		this->_p = this->_alloc.allocate(x.capacity());
        unsigned int i = 0;
        while (i < this->size()){
			this->_alloc.construct(&(this->_p[i]), x[i]);
            i++;
        }
		return (*this);
	};
    
    
    friend bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    const_iterator	it_lhs = lhs.begin();
	    const_iterator	it_rhs = rhs.begin();

	    if (lhs.size() != rhs.size())
		    return (false);
	    while (it_lhs != lhs.end() && it_rhs != rhs.end() && *it_lhs == *it_rhs){
		    it_lhs++;
		    it_rhs++;
	    }
	    return (it_lhs == lhs.end() && it_rhs == rhs.end());
    };

    friend bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    return (!(lhs == rhs));
    };
    
    friend bool operator> (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    const_iterator	it_lhs = lhs.begin();
	    const_iterator	it_rhs = rhs.begin();

	    while (it_lhs != lhs.end() && it_rhs != rhs.end() && *it_lhs == *it_rhs){
		    it_lhs++;
		    it_rhs++;
	    }
	    if (it_lhs == lhs.end())
            return false;
        if (it_rhs == rhs.end() || *it_lhs > *it_rhs)
            return true;
        return false;
    };

    friend bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    if (lhs == rhs)
            return true;
        return (lhs > rhs);
    };
    
    friend bool operator< (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    return (!(lhs >= rhs));
    };
    
    friend bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
	    return (!(lhs > rhs));
    };
    

    iterator erase (iterator position){
        unsigned int    i = 0;
        vector	        tmp(position + 1, this->end());

		while (i < tmp.size()){
			this->pop_back();
            i++;
        }
		this->pop_back();

        iterator    pos = tmp.begin();
		while (pos != tmp.end()){
			this->push_back(*pos);
            pos++;
        }
		return (position);
	};

	iterator	erase(iterator first, iterator last)
	{
		iterator tmp(first);

		while (tmp != last)
		{
			erase(first);
			tmp++;
		}
		return (first);
	};

    void swap(vector& x)
	{
		pointer tmp = x._p;
		size_type tmp_capacity = x._capacity;
		size_type tmp_size = x._size;

		x._p = this->_p;
		x._capacity = this->_capacity;
		x._size = this->_size;

		this->_p = tmp;
		this->_capacity = tmp_capacity;
		this->_size = tmp_size;
	};

};
}

#endif
