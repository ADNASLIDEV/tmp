/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:11:57 by aasli             #+#    #+#             */
/*   Updated: 2022/12/20 20:11:59 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		VECTOR_ITERATOR_HPP
#define		VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

	template <typename Iterator>
	class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, Iterator>{

		protected:
			Iterator _current;

		public:
			typedef 			Iterator											iterator_type;
			typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename	ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename 	ft::iterator_traits<Iterator>::reference			reference;
			typedef typename 	ft::iterator_traits<Iterator>::pointer				pointer;


			/* CONSTRUCTORS */

			vector_iterator(): _current() {}

			explicit vector_iterator(const iterator_type it): _current(it) {}

			template <typename Iter>
			vector_iterator(const vector_iterator<Iter>& it): _current(it.base())  {}

			vector_iterator &operator=(vector_iterator const &src){
				if (*this != src)
					_current = src._current;
				return (*this);
			}

			~vector_iterator(){}

			/* MEMBERS FUNCTIONS */

			iterator_type base() const {
				return _current;
			}

			reference operator*() const{
				return *_current;
			}

			pointer operator->() const{
				return &(operator*());
			}

			vector_iterator& operator++(){
				++_current;
				return (*this);
			}

			vector_iterator operator++(int){
				vector_iterator tmp = *this;
				_current++;
				return tmp;
			}

			vector_iterator& operator--(){
				--_current;
				return (*this);
			}

			vector_iterator operator--(int){
				vector_iterator tmp = *this;
				_current--;
				return tmp;
			}

			vector_iterator operator+ (difference_type n) const{
				return (vector_iterator(_current + n));
			}

			vector_iterator& operator+=(difference_type n){
				_current += n;
				return (*this);
			}

			vector_iterator operator- (difference_type n) const{
				return (vector_iterator(_current - n));
			}

			vector_iterator& operator-=(difference_type n){
				_current -= n;
				return (*this);
			}

			reference operator[](difference_type n) const{
				return _current[n];
			}
	};

	/* RELATIONAL OPERATORS */

	template <typename Iterator, typename Iterator2>
	bool operator==(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() == y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator<(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() < y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator!=(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() != y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator>(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() > y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator>=(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() >= y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator<=(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() <= y.base());
	}

	/* OPERATORS + and - */

	template <typename Iterator, typename Iterator2>
	typename vector_iterator<Iterator>::difference_type operator-(const vector_iterator<Iterator>& x, const vector_iterator<Iterator2>& y){
		return (x.base() - y.base());
	}

	template <typename Iterator>
	vector_iterator<Iterator> operator+(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator>& x){
		return (vector_iterator<Iterator> (x.base() + n));
	}
}

#endif
