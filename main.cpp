#include <iostream>
#include <vector>
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

  std::cout << "The elements of myvector add up to " << sum << '\n';

}

template<class vect>
void    test_assign(vect test){
  vect first;
  vect second;
  vect third;

  test.capacity();
  first.assign (7, 'c');             // 7 ints with a value of 100

  typename vect::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
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

int main ()
{

  ft::vector<int> vide;         // vector int empty
  ft::vector<int> v_int(1,100);    // vector int                
  ft::vector<char> v_char (4,'c'); // vector char  
  ft::vector<double> v_double (4,42.42);// vector double  
  ft::vector<double> copy (v_double);// copy vector double     

/*
  test_capacity(v_int, "v_int");
  test_front_back(v_int);
  test_other(v_int);
  test_reverse(v_int);
  test_assign(v_char);
  test_push_back(v_int);
  test_pop_back(v_int);*/
  //test_insert(v_int);
  print_vect(v_int);
  v_int.insert(v_int.begin() + 4, 4,12);
  v_int.insert(v_int.end() + 12, 120);
  print_vect(v_int);
  

  return 0;
}