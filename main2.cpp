#include <iostream>
#include <vector>
#include <list>
#include "vector.hpp"

template<class vect>
void    print_vect(vect test){
   std::cout << "myvector contains:";
  unsigned int i = 0;
  typename vect::iterator it;
  for ( it = test.begin(); it != test.end(); ++it)
  {
    std::cout <<  "[" << test[i] << "." << test.at(i) << "." << *it << "]";
    i++;
    }
  std::cout << std::endl;
}

template<class vect>
void    test_push_back(vect test){
  vect myvector;
  int myint;

  test.capacity();
  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myvector.push_back (myint);
  } while (myint);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
}


template<class vect>
void    test_pop_back(vect test){
  vect myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  test.capacity();
  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }
  print_vect(myvector);
  std::cout << "The elements of myvector add up to " << sum << '\n';

}

template<class vect>
void    test_assign(vect test){
  vect first;
  vect second;
  vect third;


  test.capacity();
  first.assign (7, 100);             // 7 ints with a value of 100


  typename vect::iterator it;
  it=first.begin()+1;
  

  second.assign (it,first.end()-1); // the 5 central values of first


  int myints[] = {1776,7,4};
  third.assign (myints,myints + 3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout <<  "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  return ;
}

template<class vect>
void    test_reverse(vect test){


  int i=0;

  typename vect::reverse_iterator rit = test.rbegin();
  for (; rit!= test.rend(); ++rit)
    *rit = ++i;
  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

template<class vect>
void    test_capacity(vect test, std::string name){
    std::cout << "size  of " << name << ": " << test.size() << std::endl;
    std::cout << "max_size  of " << name << ": " << test.max_size() << std::endl;
    std::cout << "capacity  of " << name << ": " << test.capacity() << std::endl;
    std::cout << "empty " <<  std::boolalpha << name << ": " << test.empty() << std::endl;
    try {
    test.reserve(test.max_size()+1);
    }
  catch (const std::length_error& le) {
	  std::cerr << "Length error: " << le.what() << '\n';
  }
   print_vect(test);
    try {
    std::cout << test.at(test.size());
    }
  catch (const std::out_of_range& le) {
	  std::cerr << "Out of range: " << le.what() << '\n';
  }
 
    std::cout << std::endl << "             ------------------------               " << std::endl;
}


template<class vect>
void  test_other(vect test){
    try {
    test.reserve(test.max_size()+1);
    }
  catch (const std::length_error& le) {
	  std::cerr << "Length error: " << le.what() << '\n';
  }
   print_vect(test);
    try {
    std::cout << test.at(test.size());
    }
  catch (const std::out_of_range& le) {
	  std::cerr << "Out of range: " << le.what() << '\n';
  }
 
    std::cout << std::endl << "             ------------------------               " << std::endl;
}

template<class vect>
void  test_insert(vect test){
  vect myvector (3,100);
  typename vect::iterator it;

  test.empty();
  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  vect anothervector (2,400);
 // myvector.insert (it+2,anothervector.begin(),anothervector.end());

  //int myarray [] = { 501,502,503 };
  //myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

}

template<class vect>
void  test_front_back(vect test){
  try {
  test.front() += 2;
    }
  catch (const std::out_of_range& le) {
	  std::cerr << "Out of range: " << le.what() << '\n';
  }
    try {
  test.back() += 2;
    }
  catch (const std::out_of_range& le) {
	  std::cerr << "Out of range: " << le.what() << '\n';
  }
   print_vect(test);
    std::cout << std::endl << "             ------------------------               " << std::endl;

}

template<class vect>
void  test_clear(vect test){
  vect myvector;
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  test.empty();
  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

int main ()
{

  ft::vector<int> vide;         // vector int empty
  ft::vector<int> v_int(1,100);    // vector int                
  ft::vector<char> v_char (4,'c'); // vector char  
  ft::vector<double> v_double (4,42.42);// vector double  
  ft::vector<double> copy (v_double);// copy vector double     


  test_capacity(v_int, "v_int");
  test_front_back(v_int);
  test_other(v_int);
  test_reverse(v_int);
  test_assign(v_int);
  test_push_back(v_int);
  test_pop_back(v_int);
  //test_insert(v_int);
  //print_vect(v_int);
 // v_int.insert(v_int.begin() + 4, 4,12);
  //v_int.insert(v_int.end() + 12, 120);
 // print_vect(v_int);
  test_clear(v_int);

  return 0;
}

#define TESTED_TYPE int
#define T_SIZE_TYPE typename ft::vector<T>::size_type

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


void	checkErase(ft::vector<TESTED_TYPE> const &vct,
					ft::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
  i = 1;
  (void)it;
	//std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}
/*
int		main(void)
{
	ft::vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}*/

/*
int		main(void)
{
	ft::vector<TESTED_TYPE> vct(5);
	ft::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	ft::vector<TESTED_TYPE> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	ft::vector<TESTED_TYPE> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);
	return (0);
}*/