#include <iostream>
#include <vector>
#include "vector.hpp"

template<class vect>
void    print_vect(vect test){
   std::cout << "myvector contains:";
  unsigned int i = 0;
  for (ft::vector<int>::iterator it = test.begin() ; it != test.end(); ++it)
  {
    std::cout <<  "[" << test[i] << "." << test.at(i) << "." << *it << "]";
    i++;
    }
  std::cout << std::endl;
}


template<class vect>
void    capacity_test(vect test, std::string name){
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
  // constructors used in the same order as described above:
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<char> third (4,'c');
  ft::vector<double> fourth (4,42.42);
  ft::vector<double> copy (fourth);
 /* ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);                    // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';*/
/*
  capacity_test(first, "First");
  capacity_test(second, "Second");
  capacity_test(third, "Third");
  capacity_test(fourth, "fourth");
  capacity_test(copy, "copy");*/

  std::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) 
    myvector.push_back(i);
  capacity_test(first, "1");
  first.resize(5);
  capacity_test(first, "2");
  first.resize(8,100);
  capacity_test(first, "3");
  first.resize(12);
  capacity_test(first, "4");

  return 0;
}