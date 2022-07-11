#ifndef NODE_HPP
# define NODE_HPP


namespace ft {


template <typename T>
struct	mapNode
{
	private:
	bool _unused;

	public:
	T			data;
	mapNode		*parent;
	mapNode		*left;
	mapNode		*right;

	mapNode(const T &src = T()) : \
		data(src), parent(NULL), left(NULL), right(NULL) {};
};

template <typename T>
mapNode<T>	*farRight(mapNode<T> *node) {
	while (node->right != NULL)
		node = node->right;
	return (node);
}

template <typename T>
mapNode<T>	*farLeft(mapNode<T> *node) {
	while (node->left != NULL)
		node = node->left;
	return (node);
}
}

#endif