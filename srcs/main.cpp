/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:36:53 by aasli             #+#    #+#             */
/*   Updated: 2023/02/20 10:29:34 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <deque>
#include <list>
#include <exception>

#include <map>
#include <stack>
#include <vector>

#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

#include "colors.hpp"

# define NS ft
# define VECTOR
# define STACK
# define MAP

# define T1 int
# define T2 std::string

void	vector_test();
void	printVec(NS::vector<T1> &vec, bool displayContainer);
void	printVec(NS::vector<T2> &vec, bool displayContainer);
void	stack_test();
void	map_test();
void	printMap(NS::map<T1, T1> &map, bool displayContainer);
void	printMap(NS::map<T1, T2> &map, bool displayContainer);

int main(){
#ifdef VECTOR
	vector_test();
#endif
#ifdef STACK 
	stack_test();
#endif
#ifdef MAP 
	map_test();
#endif
	return (0);
}

#ifdef VECTOR

void	vector_test(){
	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==             VECTOR TESTS             ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "---------- CONSTRUCTORS TESTS ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	std::cout << BOLD << ORANGE << "--> default:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec;
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> fill constructor - size:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(3);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> fill constructor - size + value:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(3, 42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> range constructor:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> creating a list of 5 and filling it with multiples of 2." << std::endl;
			std::list<T1> lst;

			for (int i = 0; i < 5; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\t   -> vector<T1> vec1(list.begin(), list.end());" << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> copy constructor:" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;

			for (int i = 0; i < 5; i++)
				lst.insert(lst.end(), i * 2);
			NS::vector<T1> vec1(lst.begin(), lst.end());
			std::cout << "\n\t-> copying the previous vector." << std::endl;
			NS::vector<T1> vec = vec1;
			printVec(vec, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------  OPERATOR = TEST   ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	std::cout << BOLD << ORANGE << "--> assigning one vector to another:" << RESET << std::endl;
	{
			std::cout << "\n\t-> Create a first vector." << std::endl;
			NS::vector<T1> vec1(5, 42);
			printVec(vec1, 1);
			std::cout << "\t-> Create a second vector." << std::endl;
			NS::vector<T1> vec2(13, 24);
			printVec(vec2, 1);
			std::cout << "\t-> Assign the first one to the second." << std::endl;
			vec2 = vec1;
			printVec(vec2, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------ASSIGN FUNCTION TEST------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	std::cout << BOLD << ORANGE << "--> assigning x times the value:" << RESET << std::endl;
	{
			std::cout << "\n\t-> Create a vector of 10 times 42." << std::endl;
			NS::vector<T1> vec1(10, 42);
			printVec(vec1, 1);
			std::cout << "\t-> Assign 3 times 24 to it." << std::endl;
			vec1.assign(3, 24);
			printVec(vec1, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------GET  ALLOCATOR  TEST------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	std::cout << BOLD << ORANGE << "--> Getting the allocator and allocate 4 * size of int:" << RESET << std::endl;
	{
			NS::vector<T1> vec1;
			void *alloc = (vec1.get_allocator()).allocate(4);
			std::cout << "\n\t-> the allocator just allowed " << sizeof(alloc) << " bytes." << std::endl;
			vec1.get_allocator().deallocate((int *)alloc, sizeof(alloc));
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------      ITERATORS     ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> iterator begin:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec[0] = 42;
			printVec(vec, 1);
			NS::vector<T1>::iterator it = vec.begin();
			std::cout << "Iterator begin gives " << *it << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> const iterator begin:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec[0] = 42;
			printVec(vec, 1);
			NS::vector<T1>::const_iterator it = vec.begin();
			std::cout << "Iterator begin gives " << *it << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> iterator end:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec.push_back(42);
			printVec(vec, 1);
			NS::vector<T1>::iterator ite = vec.end();
			std::cout << "Iterator end gives " << *ite << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> const iterator end:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec.push_back(42);
			printVec(vec, 1);
			NS::vector<T1>::const_iterator ite = vec.end();
			std::cout << "Iterator end gives " << *ite << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> reverse_iterator rbegin:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec.push_back(42);
			printVec(vec, 1);
			NS::vector<T1>::reverse_iterator it = vec.rbegin();
			std::cout << "Iterator rbegin gives " << *it << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> const reverse_iterator rbegin:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec.push_back(42);
			printVec(vec, 1);
			NS::vector<T1>::const_reverse_iterator it = vec.rbegin();
			std::cout << "Iterator rbegin gives " << *it << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> reverse_iterator rend:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec[0] = 42;
			printVec(vec, 1);
			NS::vector<T1>::reverse_iterator it = vec.rend();
			std::cout << "Reverse_iterator rend gives " << *it << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> const reverse_iterator rend:"<< RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec[0] = 42;
			printVec(vec, 1);
			NS::vector<T1>::const_reverse_iterator it = vec.rend();
			std::cout << "Const reverse_terator rend gives " << *it << "." << "\n\n";
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------      CAPACITY      ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> size, empty, capacity already tested:" << RESET << " vector();" << std::endl;
	std::cout << BOLD << ORANGE << "--> max_size():" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(1);
			printVec(vec, 1);
			std::cout << "Max size of vector: " << vec.max_size() << "." << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> resize():" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a first vector of 5." << std::endl;
			NS::vector<T1> vec(5);
			printVec(vec, 1);
			std::cout << "\t-> Resize at 2." << std::endl;
			vec.resize(2);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> resize() + value:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a first vector of 5." << std::endl;
			NS::vector<T1> vec(5);
			printVec(vec, 1);
			std::cout << "\t-> Resize at 7 with 35 as value." << std::endl;
			vec.resize(7, 35);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> reserve < size()" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a first vector of 5." << std::endl;
			NS::vector<T1> vec(5);
			printVec(vec, 1);
			std::cout << "\t-> Reserve 3. <-- not working" << std::endl;
			vec.reserve(3);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> reserve" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a first vector of 5." << std::endl;
			NS::vector<T1> vec(5);
			printVec(vec, 1);
			std::cout << "\t-> Reserve 10" << "\n";
			vec.reserve(10);
			printVec(vec, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------   ELEMENT ACCESS   ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> operator[]:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(5);
			vec[1] = 42;
			printVec(vec, 1);
			std::cout << "Element at vec[1]: " << vec[1] << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> at()" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vector of 3." << std::endl;
			NS::vector<T1> vec(3);
			vec[1] = 42;
			printVec(vec, 1);
			std::cout << "Element at vec.(1): " << vec.at(1) << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> front()" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vector of 3." << std::endl;
			NS::vector<T1> vec(3);
			vec[0] = 42;
			printVec(vec, 1);
			std::cout << "Element at vec.front(): " << vec.front() << "\n\n";
	}
	std::cout << BOLD << ORANGE << "--> back()" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vector of 3." << std::endl;
			NS::vector<T1> vec(3);
			vec[2] = 42;
			printVec(vec, 1);
			std::cout << "Element at vec.back(): " << vec.back() << "\n\n";
	}

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------      MODIFIERS     ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> push_back on empty vec:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec;
			std::cout << "\n\t-> Create an empty vec and push_back 42 to it." << std::endl;
			vec.push_back(42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> push_back on non empty vec:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(3);
			std::cout << "\n\t-> Create a vector of size 3 and push_back 42 to it." << std::endl;
			vec.push_back(42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> pop_back:" << RESET << " vector();" << std::endl;
	{
			NS::vector<T1> vec(3);
			std::cout << "\n\t-> Create a vec of size 3 and pop_back to it <-- not working" << std::endl;
			vec.pop_back();
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, value) on empty vec:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create an empty vec." << std::endl;
			NS::vector<T1> vec;
			printVec(vec, 1);
			std::cout << "\n\t-> Insert 42 at vec.begin()." << std::endl;
			vec.insert(vec.begin(), 42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, value) on vec:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(3);
			printVec(vec, 1);
			std::cout << "\n\t-> Insert 42 at vec.begin() + 1." << std::endl;
			vec.insert(vec.begin() + 1, 42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, n, value) on empty vec:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create an empty vec." << std::endl;
			NS::vector<T1> vec;
			printVec(vec, 1);
			std::cout << "\n\t-> Insert 42 3 times at vec.begin()." << std::endl;
			vec.insert(vec.begin(), 3, 42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, n, value) on vec:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(3);
			printVec(vec, 1);
			std::cout << "\n\t-> Insert 42 3 times at vec.begin() + 1." << std::endl;
			vec.insert(vec.begin() + 1, 3, 42);
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, iterator, iterator) on empty vec:" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			NS::vector<T1> vec;

			for (int i = 0; i < 5; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\n\t-> Insert a list of multiple of 2." << std::endl;
			vec.insert(vec.begin(), lst.begin(), lst.end());
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> insert (iterator, iterator, iterator) on empty vec:" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec (3);
			printVec(vec, 1);
			for (int i = 0; i < 5; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\n\t-> Insert a list of multiple of 2 at position 4." << std::endl;
			vec.insert(vec.begin() + 3, lst.begin(), lst.end());
			printVec(vec, 1);
	}
	std::cout << BOLD << ORANGE << "--> erase(position):" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			for (int i = 0; i < 3; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
			std::cout << "\t-> erase first position." << std::endl;
			vec.erase(vec.begin());
			printVec(vec, 1);

	}
	std::cout << BOLD << ORANGE << "--> erase(first, last):" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			for (int i = 0; i < 3; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
			std::cout << "\t-> erase the last two positions." << std::endl;
			vec.erase(vec.begin() + 1, vec.end());
			printVec(vec, 1);

	}
	std::cout << BOLD << ORANGE << "--> swap(vec, vec):" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			for (int i = 0; i < 3; i++)
				lst.insert(lst.end(), i * 2);
			std::list<T1> lst2;
			for (int i = 0; i < 3; i++)
				lst2.insert(lst2.end(), i * 3);
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
			std::cout << "\t-> Create an other vec of size 3." << std::endl;
			NS::vector<T1> vec2(lst2.begin(), lst2.end());
			printVec(vec2, 1);
			std::cout << "\t-> Swap the two vectors." << std::endl;
			vec.swap(vec2);
			printVec(vec, 1);
			printVec(vec2, 1);
	}
	std::cout << BOLD << ORANGE << "--> clear():" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			for (int i = 0; i < 3; i++)
				lst.insert(lst.end(), i * 2);
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
			std::cout << "\t-> Clearing the vec." << std::endl;
			vec.clear();
			printVec(vec, 1);
			std::cout << "\t-> Clearing on the empty vec." << std::endl;
			vec.clear();
			printVec(vec, 1);
	}

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------RELATIONAL OPERATORS------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> all relational operators:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vector of size 4." << std::endl;
			NS::vector<T1>vec(4, 42);
			printVec(vec, 1);
			std::cout << "\n\t-> Create a vector of size 3." << std::endl;
			NS::vector<T1>vec2(3, 42);
			printVec(vec2, 1);
			bool b = (vec == vec2);
			std::cout << "\t-> Are vec and vec2 equals ? : " << b << std::endl;
			b = (vec != vec2);
			std::cout << "\t-> Are vec and vec2 equals ? : " << b << std::endl;
			b = (vec < vec2);
			std::cout << "\t-> Are vec < vec2 ? : " << b << std::endl;
			b = (vec > vec2);
			std::cout << "\t-> Are vec > vec2 ? : " << b << std::endl;
			b = (vec >= vec2);
			std::cout << "\t-> Are vec >= vec2 ? : " << b << std::endl;
			b = (vec <= vec2);
			std::cout << "\t-> Are vec <= vec2 ? : " << b << std::endl;
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------SPECIALIZE ALGORITHMS-----------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> no member swap:" << RESET << " vector();" << std::endl;
	{
			std::list<T1> lst;
			for (int i = 0; i < 3; i++)
				lst.insert(lst.end(), i * 2);
			std::list<T1> lst2;
			for (int i = 0; i < 3; i++)
				lst2.insert(lst2.end(), i * 3);
			std::cout << "\n\t-> Create a vec of size 3." << std::endl;
			NS::vector<T1> vec(lst.begin(), lst.end());
			printVec(vec, 1);
			std::cout << "\t-> Create an other vec of size 3." << std::endl;
			NS::vector<T1> vec2(lst2.begin(), lst2.end());
			printVec(vec2, 1);
			std::cout << "\t-> Swap the two vectors." << std::endl;
			swap(vec, vec2);
			printVec(vec, 1);
			printVec(vec2, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------     OTHER TYPES    ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> vector of strings:" << RESET << " vector();" << std::endl;
	{
			std::cout << "\n\t-> Create a vector of size 4." << std::endl;
			NS::vector<T2>vec(4, "Hello world");
			printVec(vec, 1);
	}

	std::cout << BOLD << RED << "------------------------------------------" << std::endl;
	std::cout << "--------------- BIG VECTOR ---------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << "-> push_back 1000000 times;" << std::endl << std::endl;
	NS::vector<T1> vec;
	for (int i = 0; i < 1000000; i++)
		vec.push_back(i);
	

	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==            END OF VECTOR             ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;
}
#endif
#ifdef STACK

void	stack_test(){
	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==              STACK TESTS             ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "---------- CONSTRUCTORS TESTS ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	{
			std::cout << BOLD << ORANGE << "--> default container:" << RESET << " stack();" << std::endl;
			std::cout << "\n\t   -> stack()" << std::endl;
			NS::stack<T1, NS::vector<T1> > s;
			std::cout << "\t   -> size of stack: " << s.size()  << std::endl;
			std::cout << "\t   -> adding 5 multiple of 5" << std::endl;
			for (int i = 0; i < 5; i++)
				s.push(i * 2);
			std::cout << "\t   -> size of stack: " << s.size()  << std::endl;
			std::cout << "\n\t   -> stack(NS::vector<T1> vec(3, 42))" << std::endl;
			NS::stack<T1, NS::vector<T1> > s2(NS::vector<T1>(3, 42));
			std::cout << "\t   -> size of stack: " << s2.size()  << std::endl;
			std::cout << "\n\t   -> stack(NS::list<T1> lst(2, 24))" << std::endl;
			NS::stack<T1, std::list<T1> > s3(std::list<T1>(2, 24));
			std::cout << "\t   -> size of stack: " << s3.size()  << std::endl;
			std::cout << "\n\t   -> stack(const &stack)) of the first stack" << std::endl;
			NS::stack<T1, NS::vector<T1> > s4(s);
			std::cout << "\t   -> size of stack: " << s4.size()  << std::endl;
			std::cout << "\n\t   -> operator = use with the second stack" << std::endl;
			NS::stack<T1, NS::vector<T1> > s5 = s2;
			std::cout << "\t   -> size of stack: " << s5.size()  << std::endl;
	
			std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
			std::cout << "----------  MOFIFIERS TESTS   ------------" << std::endl;
			std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
			
			std::cout << BOLD << ORANGE << "--> top() returns the last element added to the stack:" << RESET << " stack();" << std::endl;
			s.pop();
			std::cout << "\n\t   -> top element of the stack: " << s.top()  << "\n\n";
			std::cout << BOLD << ORANGE << "--> pop() delete the last element added to the stack:" << RESET << " stack();" << std::endl;
			std::cout << "\n\t   -> top element of the stack after top: " << s.top()  << "\n\n";
			std::cout << BOLD << ORANGE << "--> push(8) 8 to the top of the stack:" << RESET << " stack();" << std::endl;
			s.push(8);  
			std::cout << "\n\t   -> top element of the stack: " << s.top()  << std::endl;
	
			std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
			std::cout << "----------RELATIONAL OPERATORS------------" << std::endl;
			std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
			std::cout << BOLD << ORANGE << "--> all relational operators:" << RESET << " stack();" << std::endl;
			bool b = (s == s2);
			std::cout << "\t-> Are  stack and stack2 equals ? : " << b << std::endl;
			b = (s != s2);
			std::cout << "\t-> Are stack and stack2 equals ? : " << b << std::endl;
			b = (s < s2);
			std::cout << "\t-> Are stack < stack2 ? : " << b << std::endl;
			b = (s > s2);
			std::cout << "\t-> Are stack > stack2 ? : " << b << std::endl;
			b = (s >= s2);
			std::cout << "\t-> Are stack >= stack2 ? : " << b << std::endl;
			b = (s <= s2);
			std::cout << "\t-> Are stack <= stack2 ? : " << b << std::endl;
	}
	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==            END OF STACK              ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;
}
#endif
#ifdef MAP

void	map_test(){
	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==              MAP TESTS               ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "---------- CONSTRUCTORS TESTS ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
 
	std::cout << BOLD << ORANGE << "--> default:" << RESET << " map();" << std::endl;
	NS::map<T1, T1> map;
	printMap(map, 1);		
	std::cout << BOLD << ORANGE << "--> fill constructor - first, last:" << RESET << " map();" << std::endl;
	std::cout << "\n\t-> creating a list of 10 and filling it with multiples of 5." << std::endl;
	std::list<NS::pair<T1, T1> > lst;
	for (int i = 0; i < 10; i++)
		lst.insert(lst.end(), NS::make_pair(i, i * 5));
	std::cout << "\t   -> map<T1, T1> map(list.begin(), list.end());" << std::endl;
	NS::map<T1, T1> map1(lst.begin(), lst.end());
	printMap(map1, 1);
	std::cout << BOLD << ORANGE << "--> copy constructor:" << RESET << " map();" << std::endl;
	std::cout << "\n\t   -> map<T1, T1> map2(const reference &map1);" << std::endl;
	NS::map<T1, T1> map2(map1);
	printMap(map2, 1);

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------      ITERATORS     ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> iterator begin:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::iterator it = map.begin();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> const iterator begin:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::const_iterator it = map.begin();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> iterator end:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::iterator it = map.end();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> const iterator end:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::const_iterator it = map.end();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> reverse_iterator rbegin:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::reverse_iterator it = map.rbegin();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> const reverse_iterator rbegin:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::const_reverse_iterator it = map.rbegin();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> reverse_iterator rend:" << RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::reverse_iterator it = map.rend();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << BOLD << ORANGE << "--> const reverse_iterator rend:"<< RESET << " map();" << std::endl;
	{
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			NS::map<T1, T1>::const_reverse_iterator it = map.rend();
			std::cout << "Iterator returns : " << it->second << std::endl << std::endl;
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------      CAPACITY      ------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << BOLD << ORANGE << "--> empty:" << RESET << " map();" << std::endl;
	{
			std::cout << "\n\t-> Create a map of 10 with multipleof 5." << std::endl;
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			if (map.size())
				std::cout << "The map is not empty" << "\n";
			else
				std::cout << "The map is empty" << "\n";
			std::cout << "\n\t-> Create an empty map." << std::endl;
			NS::map<T1, T1> map2;
			printMap(map2, 1);
			if (map2.size())
				std::cout << "The map is not empty" << "\n";
			else
				std::cout << "The map is empty" << "\n";
	}
	std::cout << BOLD << ORANGE << "--> max_size:" << RESET << " map();" << std::endl;
	{
			std::cout << "\n\t-> Create a map of 10 with multipleof 5." << std::endl;
			std::list<NS::pair<T1, T1> > lst;
				for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 5));
			NS::map<T1, T1> map(lst.begin(), lst.end());
			printMap(map, 1);
			std::cout << "max_size of the map : " << map.max_size()  << "\n";
			std::cout << "\n\t-> Create an empty map." << std::endl;
			NS::map<T1, T1> map2;
			printMap(map2, 1);
			std::cout << "max_size of the map : " << map2.max_size()  << "\n";
	}

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "----------- OPERATOR[] TESTS -------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	{
		std::cout << ORANGE "--> operator[]():" << RESET << " map[?];" << std::endl << std::endl;
		std::list<NS::pair<T1, T1> > lst;

		for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 10));
		NS::map<T1, T1> map(lst.begin(), lst.end());
		std::cout << "-> creating a map with 10 mutliples of 10" << std::endl;
		printMap(map, 1);
		std::cout << "map[1]" << ORANGE << " = " << RESET << map[1] << std::endl;
		std::cout << "map[0]" << ORANGE << " = " << RESET << map[0] << std::endl;
		std::cout << "map[4]" << ORANGE << " = " << RESET << map[4] << std::endl;
		std::cout << "map[7]" << ORANGE << " = " << RESET << map[7] << std::endl;
		std::cout << "map[9]" << ORANGE << " = " << RESET << map[9] << std::endl << std::endl ;
		std::cout << "-> creates a new element if out of range." << std::endl;
		std::cout << "-> map[231]" << ORANGE << " = " << RESET << map[231] << std::endl;
		std::cout << "-> map[42] = 666"  << std::endl;
		map[42] = 666;
		std::cout << "-> map[-21] = 42"  << std::endl;
		map[-21] = 42;
		std::cout << "-> map[999] = 238"  << std::endl;
		map[999] = 238;
		printMap(map, 1);
	}

	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "-----------     MODIFIERS    -------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	{
		std::cout << ORANGE "--> insert():" << RESET << std::endl << std::endl;
		std::list<NS::pair<T1, T1> > lst;

		for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 10));
		std::cout << "-> creating an empty map" << std::endl;
		NS::map<T1, T1> map;
		printMap(map, 1);
		std::cout << "-> insert(value)" << std::endl;
		map.insert(NS::pair<T1, T1>(1, 1));
		printMap(map, 1);
		std::cout << "-> insert(pos, value)" << std::endl;
		NS::map<T1, T1>::iterator it = map.begin();
		map.insert(it, NS::pair<T1, T1>(2, 2));
		printMap(map, 1);
		std::cout << "-> insert(first, last)" << std::endl;
		NS::map<T1, T1> map2(lst.begin(), lst.end());
		printMap(map2, 1);
		std::cout << "-> erase(value) : value = 2" << std::endl;
		map2.erase(2);
		printMap(map2, 1);
		std::cout << "-> erase(pos) : pos = begin" << std::endl;
		it = map2.begin();
		map2.erase(it);
		printMap(map2, 1);
		std::cout << "-> erase(first, last)" << std::endl;
		it = map2.begin();
		NS::map<T1, T1>::iterator ite = map2.end();
		map2.erase(it, ite);
		printMap(map2, 1);
		std::cout << "-> using swap" << std::endl;
		printMap(map, 1);
		printMap(map2, 1);
		std::cout << "-> map.swap(map2)" << std::endl;
		map.swap(map2);
		printMap(map, 1);
		printMap(map2, 1);
		std::cout << "-> clear() on map2" << std::endl;
		printMap(map2, 1);
		map2.clear();
		printMap(map2, 1);
	}
	std::cout << std::endl << BOLD << GREEN << "------------------------------------------" << std::endl;
	std::cout << "-----------      LOOK UP     -------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	{
		std::cout << ORANGE "--> count(key):" << RESET << std::endl << std::endl;
		std::list<NS::pair<T1, T1> > lst;

		for (int i = 0; i < 10; i++)
			lst.insert(lst.end(), NS::make_pair(i, i * 10));
		std::cout << "-> insert(first, last)" << std::endl;
		NS::map<T1, T1> map(lst.begin(), lst.end());
		printMap(map, 1);
		std::cout << "Is count(2) is true : " << map.count(2) << "\n\n";
		std::cout << ORANGE "--> find(key):" << RESET << std::endl << std::endl;
		std::cout << "find(2) give us : " << (map.find(2))->second << std::endl << std::endl;
		
		std::cout << ORANGE "--> lower_bound(key):" << RESET << std::endl << std::endl;
		NS::map<T1, T1>::iterator it = map.lower_bound(3);
		std::cout << "lower_bound(3) give us " << it->first << " : " << it->second << RESET << std::endl << std::endl;
		
		std::cout << ORANGE "--> upper_bound(key):" << RESET << std::endl << std::endl;
		it = map.upper_bound(5);
		std::cout << "upper_bound(5) give us " << it->first << " : " << it->second << RESET << std::endl << std::endl;
	}

	NS::map<T1, T2> type2;
	type2.insert(NS::pair<T1, T2>(1, "Yoooooooooo"));
	printMap(type2, 1);
	

	std::cout << BOLD << RED << "------------------------------------------" << std::endl;
	std::cout << "---------------- BIG MAP -----------------" << std::endl;
	std::cout << "------------------------------------------" << RESET << std::endl << std::endl;
	std::cout << "-> insert 1000000 times;" << std::endl << std::endl;
	NS::map<T1, T1> big;
	for (int i = 0; i < 10000; i++)
		big[i] = i;
	std::cout << BOLD << PINK << "==========================================" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==              END OF MAP              ==" << std::endl;
	std::cout << "==                                      ==" << std::endl;
	std::cout << "==========================================" << RESET << std::endl;
}
#endif

void printMap(NS::map<T1, T1> &m, bool displayContainer) {
	std::cout << std::endl;
	std::cout << BOLD << BLUE << "====== PRINT MAP ======" << RESET << std::endl;
	std::cout << "size()" << ORANGE << " = " << RESET << m.size() << std::endl;
	std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	if (displayContainer) {
		if (m.empty())
			std::cout << "        Map's empty !" << std::endl;
		else {
			NS::map<T1, T1>::iterator it = m.begin();
			NS::map<T1, T1>::iterator ite = m.end();
			for (int i = 0; it != ite; it++) {
				std::cout << "map[" << i << "]" << ORANGE << " = " << RESET << it->first << " : " << it->second << std::endl;
				i++;
			}
		}
		std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	}
	std::cout << std::endl;
}

void printMap(NS::map<T1, T2> &m, bool displayContainer) {
	std::cout << std::endl;
	std::cout << BOLD << BLUE << "====== PRINT MAP ======" << RESET << std::endl;
	std::cout << "size()" << ORANGE << " = " << RESET << m.size() << std::endl;
	std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	if (displayContainer) {
		if (m.empty())
			std::cout << "        Map's empty !" << std::endl;
		else {
			NS::map<T1, T2>::iterator it = m.begin();
			NS::map<T1, T2>::iterator ite = m.end();
			for (int i = 0; it != ite; it++) {
				std::cout << "map[" << i << "]" << ORANGE << " = " << RESET << it->first << " : " << it->second << std::endl;
				i++;
			}
		}
		std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	}
	std::cout << std::endl;
}

void printVec(NS::vector<T1> &vec, bool displayContainer) {
	std::cout << std::endl;
	std::cout << BOLD << BLUE << "====== PRINT VECTOR ======" << RESET << std::endl;
	std::cout << "size()" << ORANGE << " = " << RESET << vec.size() << std::endl;
	std::cout << "capacity()" << ORANGE << " = " << RESET << vec.capacity() << std::endl;
	std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	if (displayContainer) {
		if (vec.empty())
			std::cout << "        Vec's empty !" << std::endl;
		else {
			NS::vector<T1>::iterator it = vec.begin();
			NS::vector<T1>::iterator ite = vec.end();
			for (int i = 0; it != ite; it++) {
				std::cout << "vector[" << i << "]" << ORANGE << " = " << RESET << *it << std::endl;
				i++;
			}
		}
		std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	}
	std::cout << std::endl;
}

void printVec(NS::vector<T2> &vec, bool displayContainer) {
	std::cout << std::endl;
	std::cout << BOLD << BLUE << "====== PRINT VECTOR ======" << RESET << std::endl;
	std::cout << "size()" << ORANGE << " = " << RESET << vec.size() << std::endl;
	std::cout << "capacity()" << ORANGE << " = " << RESET << vec.capacity() << std::endl;
	std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	if (displayContainer) {
		if (vec.empty())
			std::cout << "        Vec's empty !" << std::endl;
		else {
			NS::vector<T2>::iterator it = vec.begin();
			NS::vector<T2>::iterator ite = vec.end();
			for (int i = 0; it != ite; it++) {
				std::cout << "vector[" << i << "]" << ORANGE << " = " << RESET << *it << std::endl;
				i++;
			}
		}
		std::cout << BOLD << BLUE  << "==========================" << RESET << std::endl;
	}
	std::cout << std::endl;
}
