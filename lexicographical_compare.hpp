#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP


namespace ft {


template <class Ite1, class Ite2>
bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		++first1; ++first2;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

}

#endif