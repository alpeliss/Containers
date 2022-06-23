#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>
#include <new>
#include <unistd.h>

namespace ft
{
template<class T,class Allocator = std::allocator<T> >
class vector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
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
    template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
            unsigned int i = 0;
            InputIterator   tmp;

            tmp = first;
            while (tmp != last){
                tmp++;
                i++;
            }
            this->_alloc = alloc;
		    this->_size = i;
		    this->_capacity = i;    
            this->_p = this->_alloc.allocate(i);
            i = 0;
            while (first != last){
                this->_p[i] = *first;
                first++;
                i++;
            }

        }

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
        pointer tmp;

        if (n > this->max_size())
            throw std::length_error("Can't reserve this much.");
        if (n > this->_capacity)
        tmp = NULL;
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
        return this->_p;
    }

    const_iterator begin() const{
        return this->_p;
    }

    iterator end(){
        return this->_p + this->_size;
    }

    const_iterator end() const{
        return this->_p + this->_size;
    }

    reverse_iterator rbegin(){
        return reverse_iterator(this->end());
    }
    reverse_iterator rend(){
        return reverse_iterator(this->begin());
    }


    void assign (size_type n, const value_type& val) {
        this->_alloc.deallocate(this->_p, this->_capacity);
        vector tmp(n, val);
        this->_p = tmp._p;
        this->_size = tmp._size;
        this->_capacity = tmp._capacity;
    }

   /* void assign (int n, T val) {
        this->_alloc.deallocate(this->_p, this->_capacity);
        vector tmp(n, val);
        this->_p = tmp._p;
        this->_size = tmp._size;
        this->_capacity = tmp._capacity;
    }*/

   template <class InputIterator>
    void assign (InputIterator first, InputIterator last){
        this->_alloc.deallocate(this->_p, this->_capacity);
        InputIterator tmp = first;
        unsigned int i = 0;
        while (tmp != last){
            tmp++;
            i++;
        }
	    this->_p = _alloc.allocate(i);
        this->_size = i;
	    this->_capacity = i;

        unsigned int j = 0;
        while (j < i){
            this->_p[j] = *first;
            first++;
            j++;
        }
    }

    void push_back (const value_type& val){
        if (this->_capacity <= this->_size)
            this->reserve(2 * this->_size + 1);
        this->_p[this->_size] = val;
        this->_size++;
    }

	void pop_back(void) {
        if (this->empty() == true)
            throw std::out_of_range("No pop_back in an empty vector.");
		this->_p[this->_size - 1].value_type::~value_type();
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
	difference_type const	idx = position - this->begin();
	difference_type const	old_end_idx = this->end() - this->begin();
	iterator				old_end, end;

	this->resize(this->_size + n);

	end = this->end();
	position = this->begin() + idx;
	old_end = this->begin() + old_end_idx;
	while (old_end != position)
		*--end = *--old_end;
	while (n-- > 0)
		*position++ = val;
}

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last){

	difference_type const	idx = position - this->begin();
	difference_type const	old_end_idx = this->end() - this->begin();
	iterator				old_end, end;
    unsigned int i = 0;
    InputIterator tmp;

    tmp = first;
    while (tmp != last){
        tmp++;
        i++;
    }
	this->resize(this->_size + i);

	end = this->end();
	position = this->begin() + idx;
	old_end = this->begin() + old_end_idx;
	while (old_end != position)
		*--end = *--old_end;
	while (first != last)
		*position++ = *first++;
    }

};
}

#endif
