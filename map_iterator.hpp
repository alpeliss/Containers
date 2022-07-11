#ifndef MAP_ITE_CLASS_HPP
# define MAP_ITE_CLASS_HPP


namespace ft {

template <typename T, typename node_type>
class map_iterator {
	public:
		node_type						*_node;
		typedef T						iterator_category;
		typedef T						value_type;
		typedef ptrdiff_t				difference_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;

		map_iterator(void): _node(NULL) {} 
		map_iterator(const map_iterator &src){
			*this = src;
		}
		map_iterator(node_type *node) : _node(node) {}
		virtual ~map_iterator() {}
		
		map_iterator	&operator=(map_iterator const &rhs){
			if (this == &rhs)
				return (*this);
			this->_node = rhs._node;
			return (*this);
		}


		template <class U> 
		bool	operator==(const map_iterator<U, node_type> &rhs) const{
			return (this->_node == rhs._node);
		}

		template <class U> 
		bool	operator!=(const map_iterator<U, node_type> &rhs) const{
			return (this->_node != rhs._node);
		}

		map_iterator		&operator++(void){
			if (this->_node->right != NULL)
				this->_node = farLeft(this->_node->right);
			else{
				node_type	*child = this->_node;

				this->_node = this->_node->parent;
				while (this->_node && child == this->_node->right){
					child = this->_node;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}

		map_iterator		operator++(int){
			map_iterator	tmp(*this);
			++(*this);
			return (tmp);
		}

		map_iterator		&operator--(void){
			if (this->_node->left != NULL)
				this->_node = farRight(this->_node->left);
			else{
				node_type	*tmp = this->_node;

				this->_node = this->_node->parent;
				while (this->_node && tmp == this->_node->left){
					tmp = this->_node;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}

		map_iterator		operator--(int){
			map_iterator	tmp(*this);
			--(*this);
			return (tmp);
		}

		reference	operator*(void) const{
			return (this->_node->data);
		}

		pointer		operator->(void) const{
			return &this->operator*();
		}

		operator map_iterator<const T, node_type>(void) const {
			return map_iterator<const T, node_type>(this->_node);
		}

}; 

} 

#endif 