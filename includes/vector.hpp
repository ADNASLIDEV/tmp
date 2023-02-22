/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:11:38 by aasli             #+#    #+#             */
/*   Updated: 2023/02/18 16:55:12 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include "vector_iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "g_swap.hpp"

namespace ft
{

	/* See 			https://cplusplus.com/reference/vector/vector/ */
	/* Allocator:	https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/	*/

	template < class T, class Allocator = std::allocator<T> >// generic template
	class vector{
		public:

			/* MEMBER TYPES */

			/* Why typedef typename following ?*/
			/* https://stackoverflow.com/questions/18385418/c-meaning-of-a-statement-combining-typedef-and-typename */

			/* Typedef tells to the compiler that there is a new type */
			/* Typname tells to the compiler that there is no new type but an alias to an actual type*/

			typedef				T 										value_type;
			typedef 			Allocator								allocator_type;
			typedef 			size_t									size_type;
			typedef 			ptrdiff_t								difference_type;
			typedef typename	Allocator::pointer						pointer;
			typedef typename	Allocator::const_pointer				const_pointer;
			typedef typename	Allocator::reference					reference;
			typedef typename	Allocator::const_reference				const_reference;
			typedef 			ft::vector_iterator<pointer> 			iterator;
			typedef 			ft::vector_iterator<const_pointer>		const_iterator;
			typedef 			ft::reverse_iterator<iterator>			reverse_iterator;
			typedef 			ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:

	// How I found the possible private members to use
	// Source: https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/

			value_type		*_v;
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;

			size_type	growThisBig(size_type n){
				if (n > _capacity * 2)
					return (n);
				else
					return (_capacity * 2);
			}

		public:
			/* MEMBER FUNCTIONS */

			/* CONSTRUCTORS */
			/* https://cplusplus.com/reference/vector/vector/vector/ */

			/* Why using explicit syntax */
			/* https://www.tutorialspoint.com/What-does-the-explicit-keyword-mean-in-Cplusplus */

			explicit vector (const allocator_type& alloc = allocator_type()){
				_v = _alloc.allocate(0);
				_alloc = alloc;
				_size = 0;
				_capacity = 0;
			} // Default constructor

			explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type()){
				_v = _alloc.allocate(n);
				_alloc = alloc;
				_size = n;
				_capacity = n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_v + i, val);
			} // Fill constructor

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				_v = _alloc.allocate(0);
				assign(first, last);

			} // Range constructor

			vector (const vector& x){
				_size = x._size;
				_capacity = x._capacity;
				_v = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_v + i, x._v[i]);
			} // Copy constructor

			/* DESTRUCTOR */
			/* https://cplusplus.com/reference/vector/vector/~vector/ */
			~vector(){
				clear();
				_alloc.deallocate(_v, _capacity);
			}

			vector& operator= (const vector& x){
				if (*this == x)
					return (*this);
				// Delete everything in the container
				clear();
				_alloc.deallocate(_v, _capacity);
				// Make a copy
				_size = x._size;
				_capacity = x._capacity;
				_v = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_v + i, x._v[i]);
				return (*this);
			}

			/* ITERATORS */

			iterator begin(){
				return iterator(_v);
			}

			const_iterator begin() const{
				return const_iterator(_v);
			}

      		iterator end(){
				return iterator(_v + _size);
			}

			const_iterator end() const{
				return const_iterator(_v + _size);
			}

      		reverse_iterator rbegin(){
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend(){
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const{
				return const_reverse_iterator(begin());
			}

			/* CAPACITY */

			size_type size() const{
				return (_size);
			}

			size_type max_size() const{
				return (_alloc.max_size());
			}

			size_type capacity() const{
				return (_capacity);
			}

			bool empty() const{
				if (_size == 0)
					return (true);
				return (false);
			}

			void reserve (size_type n){

				if (n > max_size())
					throw (std::length_error("vector::reserve"));
				if (n > _capacity)
				{
					value_type *new_v = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(new_v + i, *(_v + i));
						_alloc.destroy(_v + i);
					}
					_alloc.deallocate(_v, _capacity);
					_capacity = n;
					_v = new_v;
				}
			}

			/* ELEMENT ACCESS */

      		reference operator[] (size_type n){
				return (*(_v + n));
			}

			const_reference operator[] (size_type n) const{
				return (*(_v + n));
			}

      		reference at (size_type n){
				if (n >= size())
					throw (std::out_of_range("vector::at -> out of bounds"));
				return (*(_v + n));
			} // with bounds checking

			const_reference at (size_type n) const{
				if (n >= size())
					throw (std::out_of_range("vector::at const -> out of bounds"));
				return (*(_v + n));
			} // with bounds checking

			reference front(){
				return (*_v);
			}

			const_reference front() const{
				return (*_v);
			}

			reference back(){
				size_type i = size() - 1;
				return (*(_v + i));
			}

			const_reference back() const{
				size_type i = size() - 1;
				return (*(_v + i));
			}

			/* MODIFIERS */

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
				clear();
				for (; first != last; first++)
					push_back(*first);
			}

			void assign (size_type n, const value_type& val){
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back (const value_type& val){
				if (_capacity == 0)
					reserve(1);
				if (_size + 1 > _capacity){
					reserve(_size * 2);
					_alloc.construct(_v + _size, val);
				}
				else{
					_alloc.construct(_v + _size, val);
				}
				_size++;
			}

			void pop_back(){
				if (_size > 0){
					_alloc.destroy(_v + _size - 1);
					_size--;
				}
			}

			iterator insert (iterator position, const value_type& val){
				size_type pos = position - begin();
				size_type size = _size;

				if (size + 1 > _capacity)
					reserve (growThisBig(size + 1));
				if (_size > 0){
					_alloc.construct(&_v[size], _v[size - 1]);
					for (size = _size - 1; size > pos; size--){
						_v[size] = _v[size - 1];
					}
					_v[pos] = val;
				}else
					_alloc.construct(_v, val);

				_size++;
				iterator n_pos = begin() + pos;
				return (n_pos);
			}

			void insert (iterator position, size_type n, const value_type& val){
				size_type pos = position - begin();
				size_type new_size = _size + n;
				if ( n != 0)
				{
					if (new_size > _capacity)
						reserve (growThisBig(new_size));
					if (_size > 0){
						for (size_type i = _size; i > pos; i--){
							_alloc.construct(_v + i + n - 1, *(_v + i - 1));
							_alloc.destroy(_v + i - 1);
						}
						for (size_type i = 0; i <  n; i++){
							_alloc.construct(_v + pos + i, val);
						}
					}else{
						for (size_type i = 0; i < n; i++)
							_alloc.construct(_v + pos + i, val);
					}
					_size += n;
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){

				size_type	pos		= position - begin();
				size_type	range	= 0;

				for (InputIterator tmp = first; tmp != last; tmp++)
					range++;
				size_type new_size = _size + range;
				if (new_size > _capacity)
					reserve(growThisBig(new_size));
				if (_size > 0){
					for (size_type i = _size; i > pos; i--){
						_alloc.construct(_v + i + range - 1, *(_v + i - 1));
						_alloc.destroy(_v + i - 1);
					}
					for (size_type i = 0; i < range; i++)
						_alloc.construct(_v + pos + i, *first++);
				}else{
					for (size_type i = 0; i < range; i++)
						_alloc.construct(_v + pos + i, *first++);
				}
				_size += range;
			}

			iterator erase (iterator position){
				size_type pos = position - begin();

				size_type i = 0;
				for (i = pos; i < _size-1; i++)
					_v[i] = _v[i + 1];
				_alloc.destroy(_v + i);
				_size--;
				return (position);
			}

			iterator erase (iterator first, iterator last){
				while (last != first)
					erase(--last);
				return last;
			}

			void swap (vector& x){
				if (*this == x)
					return ;
				ft::swap(_size, x._size);
				ft::swap(_capacity, x._capacity);
				ft::swap(_v, x._v);
				ft::swap(_alloc, x._alloc);
			}

			void resize (size_type n, value_type val = value_type()){
				if (n > max_size())
					throw (std::length_error("vector::resize -> bad_alloc"));
				if (n < _size){
					for (size_type i = n; i < _size; i++){
						_alloc.destroy(_v + i);
					}
				}
				else if (n > _size){
					// Complexity :Linear in the difference between the current size and n. Additional complexity possible due to reallocation if capacity is less than n
					// Additional complexity not implemented
					if (_size * 2 > n)
						reserve(_size * 2);
					else
						reserve(n);
					for (size_type i = _size; i < n; i++){
						_alloc.construct(_v + i, val);
					}
				}
				_size = n;
			}

			void clear(){
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_v + i);
				_size = 0;
			}

			/* ALLOCATOR */

			allocator_type get_allocator() const{
				return (_alloc);
			}
	};

			/* NON MEMBER FUNCTIONS */

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		size_t i = 0;
		if (lhs.size() != rhs.size())
			return (false);
		for (; i < lhs.size(); i++){
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (!(lhs == rhs));
	}

	// https://en.cppreference.com/w/cpp/container/vector/operator_cmp
	// Compares the contents of lhs and rhs lexicographically.
	// The comparison is performed by a function equivalent to std::lexicographical_compare.

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (!(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
		x.swap(y);
	}
}

#endif
