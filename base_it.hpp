#ifndef BASE_IT_CLASS_HPP
# define BASE_IT_CLASS_HPP



# include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef> // ptrdiff_t
# include <sstream> // ostring

namespace ft {

	template <typename T>
	class base_it {
		protected:
		T									*_ptr;

		public:
		typedef T						value_type;
		typedef ptrdiff_t				difference_type;

		base_it(void) : _ptr(NULL) {} ;
		base_it(T *src) : _ptr(src){};
		base_it(const base_it &src){
            *this = src;
        };

		virtual ~base_it(void){};

		base_it	&operator=(base_it const &b){
            if (this == &b)
                return (*this);
            this->_ptr = b._ptr;
            return (*this);
        };

		virtual bool	operator==(const base_it &b) const{ 
			return (this->_ptr == b._ptr); 
		};
		virtual bool	operator!=(const base_it &b) const{ 
			std::cout << "la\n" << b._ptr << "\n";
			std::cout << this->_ptr << "\n";
			return (this->_ptr != b._ptr); 
		};

		bool	operator<(const base_it &b) const{ return (this->_ptr < b._ptr); };
		bool	operator<=(const base_it &b) const{ return (this->_ptr <= b._ptr); };
		bool	operator>(const base_it &b) const{ return (this->_ptr > b._ptr); };
		bool	operator>=(const base_it &b) const{ return (this->_ptr >= b._ptr); };

		base_it<T>	&operator++(void) { 
	    	this->_ptr++; 
		    return (*this); 
	    };

		base_it<T>	operator++(int){ 
		    base_it tmp(*this);

		    this->_ptr++; 
		    return (tmp); 
	    };	

		base_it<T>	&operator--(void){ 
		    this->_ptr--; 
		    return (*this); 
	    };

		base_it<T>	operator--(int) { 
		    base_it tmp(*this);

		    this->_ptr--; 
		    return (tmp); 
	    }

		difference_type				operator-(const base_it &b) const{
	        return (this->_value - b._value);
        }

		base_it<T>			operator+(difference_type n) const{
	        return (base_it(this->_value + n));
        }
		
        base_it<T>			operator-(difference_type n) const{
	        return (base_it(this->_value - n));
        }

		friend base_it<T>	operator+(difference_type n, const base_it &b)
			{ return b.operator+(n); };
    };
}
#endif