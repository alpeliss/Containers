#ifndef MAP_HPP
# define MAP_HPP

# include "lexicographical_compare.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "pair.hpp"
# include "node.hpp"


namespace ft {

template < class Key,                                     
		 class T,                                         
		 class Compare = std::less<Key>,                 
		 class Alloc = std::allocator<pair<const Key,T> > 
		 >
class map {
	public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef pair<const key_type, mapped_type>			value_type;
	typedef Compare										key_compare;
	class												value_compare;

	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::mapNode<value_type>						node_type;
	typedef node_type*									node_ptr;

	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

	typedef ft::map_iterator<value_type, node_type>			iterator;
	typedef ft::map_iterator<const value_type, node_type>		const_iterator;
	typedef ft::reverse<iterator>				reverse_iterator;
	typedef ft::reverse<const_iterator>		const_reverse_iterator;


	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
	this->_data = new node_type;
	return ;
    }


	template <class iter>
	map(iter first, iter last, 
            const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
	this->_data = new node_type;
	this->insert(first, last);
    }

	map(const map &src): _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0) {
	this->_data = new node_type;
	*this = src;
    }

	virtual ~map(void) {
	this->clear();
	delete this->_data;
    }


	map	&operator=(map const &rhs){
	if (this == &rhs)
		return (*this);
	this->clear();
	this->insert(rhs.begin(), rhs.end());
	return (*this);
    }

	iterator				begin(void){
	    return iterator(farLeft(this->_data));
    }

	const_iterator			begin(void) const{
	    return const_iterator(farLeft(this->_data));
    }

	iterator				end(void){
	    return iterator(farRight(this->_data));
    }

	const_iterator			end(void) const{
	    return const_iterator(farRight(this->_data));
    }

	reverse_iterator		rbegin(void){
	    return reverse_iterator(this->end());
    }

	const_reverse_iterator	rbegin(void) const{
	    return const_reverse_iterator(this->end());
    }

	reverse_iterator		rend(void){
	    return reverse_iterator(this->begin());
    }

	const_reverse_iterator	rend(void) const{
	    return const_reverse_iterator(this->begin());
    }

	size_type	size(void) const{
        return this->_size;
    }

	size_type	max_size(void) const{
        return std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1);
    }

	bool		empty(void) const{
        return this->_size == 0;
    }

	mapped_type	&operator[](const key_type &k){
	    return (this->insert(value_type(k, mapped_type()))).first->second;
    }

	ft::pair<iterator, bool>	insert(const value_type &val){
	    ft::pair<iterator, bool> res;

	    res.second = !this->count(val.first);
	    if (res.second == true)
		    this->_btree_add(new node_type(val));
	    res.first = this->find(val.first);
	    return (res);
    }

	iterator					insert(iterator position, const value_type &val){
	    static_cast<void>(position);
	    return this->insert(val).first;
    }

	template <class Ite> void	insert(Ite first, Ite last){
	    while (first != last)
		    this->insert(*first++);
    }

	void		erase(iterator position){
	    this->erase(position++, position);
    }

	size_type	erase(const key_type &k){
	    iterator element = this->find(k);

	    if (element == this->end())
		    return (0);
	    this->_btree_rm(element._node);
	    return (1);
    }


	void		erase(iterator first, iterator last){
	    while (first != last)
	    	this->_btree_rm((first++)._node);
    }

    void		swap(map &x){
	    map swp;

        node_ptr tmp = swp._data;

	    swp._data = x._data;
        swp._key_cmp = x._key_cmp;
        swp._alloc = x._alloc;
        swp._size = x._size;
        x._data = tmp;
        x._size = 0;

        tmp = x._data;
        x._data = this->_data;
        x._key_cmp = this->_key_cmp;
        x._alloc = this->_alloc;
        x._size = this->_size;
        this->_data = tmp;
        this->_size = 0;

        tmp = this->_data;
        this->_data = swp._data;
        this->_key_cmp = swp._key_cmp;
        this->_alloc = swp._alloc;
        this->_size = swp._size;
        swp._data = tmp;
        swp._size = 0;
    }

	void		clear(void){
	    node_ptr ghost = this->end()._node;

	    if (this->_size == 0)
		    return ;
	    ghost->parent->right = NULL;
	    this->_btree_clear(this->_data);
	    this->_data = ghost;
	    this->_size = 0;
    }

    allocator_type get_allocator(){
        allocator_type tmp;

        return tmp;
    }
	
	key_compare		key_comp(void) const{
	    return (key_compare());
    }

	value_compare	value_comp(void) const{
	    return (value_compare(key_compare()));
    }

	friend bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;

		const_iterator it_l = lhs.begin();	
		const_iterator it_r = rhs.begin();

		while (it_l != lhs.end()){
			if (*it_l != *it_r)
				return false;
			++it_l; 
			++it_r;
		}
		return true;
	}	

	friend bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return !(rhs == lhs);
	}	

	friend bool	operator< (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend bool	operator<= (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs == rhs)
			return true;
		return (lhs < rhs);
	}

	friend bool	operator> (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs <= rhs);
	}

	friend bool	operator>= (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs < rhs);
	}


	iterator		find(const key_type &k){
	    iterator it = this->begin(), ite = this->end();

	    while (it != ite){
		    if (!this->_key_cmp(it->first, k) && !this->_key_cmp(k, it->first))
			    break ;
		    ++it;
	    }
	    return (it);
    }

	const_iterator	find(const key_type &k) const{
	    const_iterator it = this->begin(), ite = this->end();

	    while (it != ite){
		if (!this->_key_cmp(it->first, k) && !this->_key_cmp(k, it->first))
			break ;
		++it;
	    }
	    return (it);
    }

	size_type		count(const key_type &k) const {
	    const_iterator	it = this->begin(), ite = this->end();
	    size_type		res = 0;

	    while (it != ite){
		    if (!this->_key_cmp(it->first, k) && !this->_key_cmp(k, it->first)){
                ++it;
			    ++res;
			    break ; 
		    }
            it++;
	    }
	    return (res);
    }

	iterator		lower_bound(const key_type &k){
	    iterator it = this->begin(), ite = this->end();

	    while (it != ite){
		    if (!this->_key_cmp(it->first, k))
			    break;
		    ++it;
	    }
	    return it;
    }

	const_iterator	lower_bound(const key_type &k) const{
	    const_iterator it = this->begin(), ite = this->end();

	    while (it != ite){
		    if (!this->_key_cmp(it->first, k))
			    break;
		    ++it;
	    }
	    return it;
    }

	iterator		upper_bound(const key_type &k){
	    iterator it = this->begin(), ite = this->end();

	    while (it != ite)
	    {
		    if (this->_key_cmp(k, it->first))
			    break;
		    ++it;
	    }
	    return (it);
    }

	const_iterator	upper_bound(const key_type &k) const{
	    const_iterator it = this->begin(), ite = this->end();

	    while (it != ite)
	    {
		    if (this->_key_cmp(k, it->first))
			    break;
		    ++it;
	    }
	    return (it);
    }


	pair<iterator,iterator>				equal_range(const key_type &k){
	    pair<iterator, iterator> res;

	    res.first = this->lower_bound(k);
	    res.second = this->upper_bound(k);
	    return (res);
    }

	pair<const_iterator,const_iterator>	equal_range(const key_type &k) const{
	    pair<const_iterator, const_iterator> res;

	    res.first = this->lower_bound(k);
	    res.second = this->upper_bound(k);
	    return (res);
    }


	protected:
	node_ptr				_data;
	key_compare				_key_cmp;
	allocator_type			_alloc;
	size_type				_size;

	void				_btree_clear(node_ptr node){
		if (node == NULL)
			return ;
		this->_btree_clear(node->left);
		this->_btree_clear(node->right);
		delete node;
	}
	
	void				_btree_add(node_ptr newNode){
		node_ptr	*parent = &this->_data;
		node_ptr	*node = &this->_data;
		node_ptr	ghost = farRight(this->_data);
		bool		side_left = -1;

		++this->_size;
		while (*node && *node != ghost){
			parent = node;
			side_left = this->_key_cmp(newNode->data.first, (*node)->data.first);
			node = (side_left ? &(*node)->left : &(*node)->right);
		}
		if (*node == NULL){
			newNode->parent = (*parent);
			*node = newNode;
		}
		else {
			*node = newNode;
			newNode->parent = ghost->parent;
			ghost->parent = farRight(newNode);
			farRight(newNode)->right = ghost;
		}
	}

	void				_btree_rm(node_ptr rmNode){
		node_ptr	replaceNode = NULL;
		node_ptr	*rmPlace = &this->_data;

		--this->_size;
		if (rmNode->parent)
			rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
		if (rmNode->left == NULL && rmNode->right == NULL)
			;
		else if (rmNode->left == NULL) 
			replaceNode = rmNode->right;
		else {
			replaceNode = farRight(rmNode->left);
			if (replaceNode != rmNode->left)
				if ((replaceNode->parent->right = replaceNode->left))
					replaceNode->left->parent = replaceNode->parent;
		}
		if (replaceNode){
			replaceNode->parent = rmNode->parent;
			if (rmNode->left && rmNode->left != replaceNode){
				replaceNode->left = rmNode->left;
				replaceNode->left->parent = replaceNode;
			}
			if (rmNode->right && rmNode->right != replaceNode){
				replaceNode->right = rmNode->right;
				replaceNode->right->parent = replaceNode;
			}
		}
		*rmPlace = replaceNode;
		delete rmNode;
	}

};

template <class Key, class T, class Compare, class Alloc>
class	map<Key, T, Compare, Alloc>::value_compare {
	public:
	Compare comp;
	value_compare(Compare c) : comp(c) { };

	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;
	bool	operator()(const value_type &x, const value_type &y) const {
		return comp(x.first, y.first);
	}
}; 
} 
#endif 
