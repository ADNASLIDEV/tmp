/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:46:39 by aasli             #+#    #+#             */
/*   Updated: 2023/02/19 08:19:20 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MAP_HPP
#define	MAP_HPP

#include <iostream>
#include <memory>
#include "rbt_tree.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "lexicographical_compare.hpp"

// ISO98 23.3.1 Template class map page 490
// See https://en.cppreference.com/w/cpp/container/map

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
		// types:
			typedef 			Key										key_type;
			typedef 			T										mapped_type;
			typedef 			ft::pair<const Key, T> 					value_type;
			typedef  			size_t									size_type; // See 23.1
			typedef  			ptrdiff_t								difference_type;// See 23.1
			typedef 			Compare 								key_compare;
			typedef 			Allocator 								allocator_type;
			typedef typename 	Allocator::reference 					reference;
			typedef typename 	Allocator::const_reference 				const_reference;
			typedef typename 	Allocator::pointer 						pointer;
			typedef typename 	Allocator::const_pointer 				const_pointer;
			typedef typename 	ft::rbt<value_type, key_type, key_compare, allocator_type>	rbt;
			typedef	typename	rbt::iterator 						iterator;
			typedef	typename	rbt::const_iterator 				const_iterator;
			typedef 			ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef 			ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			rbt		_M_tree;

		public:

			class value_compare: public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
				}
			};

		// 23.3.1.1 construct/copy/destroy:
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _M_tree(){
				static_cast<void>(comp);
				static_cast<void>(alloc);
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _M_tree(){
				static_cast<void>(comp);
				static_cast<void>(alloc);
				insert(first, last);
			}

			map(const map<Key,T,Compare,Allocator>& x){
				insert(x.begin(), x.end());
			}

			~map(){}

			map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x){
				if (*this == x)
					return (*this);
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

			allocator_type get_allocator() const{
				return (allocator_type(_M_tree.get_allocator()));
			}

		// iterators:
			iterator begin(){
				return (_M_tree.begin());
			}

			const_iterator begin() const{
				return (_M_tree.begin());
			}

			iterator end(){
				return (_M_tree.end());
			}

			const_iterator end() const{
				return (_M_tree.end());
			}

			reverse_iterator rbegin(){
				return (reverse_iterator(_M_tree.end()));
			}

			const_reverse_iterator rbegin() const{
				return (const_reverse_iterator(_M_tree.end()));
			}

			reverse_iterator rend(){
				return (reverse_iterator(_M_tree.begin()));
			}

			const_reverse_iterator rend() const{
				return (const_reverse_iterator(_M_tree.begin()));
			}

		// capacity:
			bool empty() const{
				return (_M_tree.empty());
			}

			size_type size() const{
				return (_M_tree.size());
			}

			size_type max_size() const{
				return (_M_tree.max_size());
			}

		// 23.3.1.2 element access:
			T& operator[](const key_type& x){
				return ((insert(ft::make_pair(x, mapped_type())).first)->second);
			}

//			T& at(const key_type& x); // Not in the ISO norm

		// modifiers:
			pair<iterator, bool> insert(const value_type& x){
				return (_M_tree.insert(x));
			}

			iterator insert(iterator position, const value_type& x){
				static_cast<void>(position);
				return (_M_tree.insert(x).first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last){
				for (; first != last; first++)
					_M_tree.insert(*first);
			}

			void erase(iterator position){
				erase(position->first);
			}

			size_type erase(const key_type& x){
				return (_M_tree.erase(ft::make_pair(x, mapped_type())));
			}

			void erase(iterator first, iterator last){
				_M_tree.multi_erase(first, last);
			}

			void swap(map<Key,T,Compare,Allocator>& map){
				_M_tree.swap(map._M_tree);
			}

			void clear(){
				if (!_M_tree.empty())
					_M_tree.clear();
			}

		// observers:
			key_compare key_comp() const {
				return (key_compare());
			}

			value_compare value_comp() const {
				return (value_compare(_M_tree.compare()));
			}

		// 23.3.1.3 map operations: a.k.a lookup
			iterator find(const key_type& k) {
				return (_M_tree.find(ft::make_pair(k, mapped_type())));
			}

			const_iterator find(const key_type& k) const {
				return (_M_tree.find(ft::make_pair(k, mapped_type())));
			}

			size_type count(const key_type& k) const{
				return (_M_tree.count(ft::make_pair(k, mapped_type())));
			}

			iterator lower_bound(const key_type& k){
				return (_M_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}

			const_iterator lower_bound(const key_type& k) const{
				return (_M_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}

			iterator upper_bound(const key_type& k){
				return (_M_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}

			const_iterator upper_bound(const key_type& k) const{
				return (_M_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}

			pair<iterator, iterator>	equal_range(const key_type& k){
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type& k) const{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

/*
			void printTree(){
				_M_tree.print_rbt();
			}
*/
	};

// operational refactored

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		typename map<Key,T,Compare,Allocator>::const_iterator xit = x.begin();
		typename map<Key,T,Compare,Allocator>::const_iterator xite = x.end();
		typename map<Key,T,Compare,Allocator>::const_iterator yit = y.begin();
		typename map<Key,T,Compare,Allocator>::const_iterator yite = y.end();

		if (x.size() != y.size())
			return (false);

		while (xit != xite){
			if (*xit != *yit)
				return (false);
			xit++;
			yit++;
		}

		return (true);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		typename map<Key,T,Compare,Allocator>::const_iterator xit = x.begin();
		typename map<Key,T,Compare,Allocator>::const_iterator xite = x.end();
		typename map<Key,T,Compare,Allocator>::const_iterator yit = y.begin();
		typename map<Key,T,Compare,Allocator>::const_iterator yite = y.end();
		
		return (ft::lexicographical_compare(xit, xite, yit, yite));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		return (!(x == y));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		return (!(x < y));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
		return (!(x > y));
	}

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y){
		x.swap(y);
	}
}

#endif
