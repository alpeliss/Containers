#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
public:

	typedef Container container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;


	explicit stack(const Container& cont = Container()): _c(cont) {}
	stack(const stack& other) : _c(other._c){}


	~stack(){}


	stack& operator=(const stack& other){
		if (this == &other)
			return *this;
		this->_c = other._c;
		return *this;
	}


	bool empty() const{
		return this->_c.empty();
	}

	size_type size() const{
		return this->_c.size();
	}

	value_type& top(){
		return this->_c.back();
	}

	const value_type& top() const{
		return this->_c.back();
	}

	void push(const value_type& val){
		this->_c.push_back(val);
	}

	void pop(){
		this->_c.pop_back();
	}
	template<typename _T, typename C>
	friend bool operator==(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c == rhs._c);
	}

	template<typename _T, typename C>
	friend bool operator!=(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c != rhs._c);
	}

	template<typename _T, typename C>
	friend bool operator>(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c > rhs._c);
	}

	template<typename _T, typename C>
	friend bool operator>=(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c >= rhs._c);
	}

	template<typename _T, typename C>
	friend bool operator<(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c < rhs._c);
	}

	template<typename _T, typename C>
	friend bool operator<=(const stack<_T, C>& lhs, const stack<_T, C>& rhs){
		return (lhs._c <= rhs._c);
	}
	
protected:

	container_type _c;


};

}

#endif
