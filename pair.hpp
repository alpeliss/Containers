#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

#include <utility>

namespace ft
{
	template <class T1, class T2>
	class pair
	{
        public:

		typedef T1 first_type;
		typedef T2 second_type;


		first_type first;
		second_type second;


		pair() : first(), second(){}

		template <class U, class V>
		pair(const pair<U, V> &src) : first(src.first), second(src.second){}
		pair(const first_type &a, const second_type &b): first(a), second(b){}


		pair& operator=(const pair& other)
		{
			if (this != &other)
			{
				this->first = other.first;
				this->second = other.second;
			}
			return *this;
		}

	};

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u )
	{
		return ft::pair<T1, T2>(t, u);
	}

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

}

#endif
