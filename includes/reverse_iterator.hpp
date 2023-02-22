/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:11:12 by aasli             #+#    #+#             */
/*   Updated: 2022/12/20 20:11:22 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		REVERSE_ITERATOR_HPP
#define		REVERSE_ITERATOR_HPP


/*	Sources to implement the reverse_iterator class					*/
/*	https://cplusplus.com/reference/iterator/reverse_iterator/		*/
/*	https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf	*/

#include "iterator_traits.hpp"

namespace ft {

	template <typename Iterator>
	class reverse_iterator{

		protected:
			Iterator _current;

		public:
			typedef 			Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename 	iterator_traits<Iterator>::reference			reference;
			typedef typename 	iterator_traits<Iterator>::pointer				pointer;


			/* CONSTRUCTORS */

			reverse_iterator(): _current() {}

			explicit reverse_iterator(iterator_type it): _current(it) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it): _current(rev_it.base())  {}

			reverse_iterator &operator=(reverse_iterator const &src){
				if (*this != src)
					_current = src._current;
				return (*this);
			}

			/* MEMBERS FUNCTIONS */

			iterator_type base() const {
				return _current;
			}

			reference operator*() const{
				iterator_type tmp = _current;
				return *--tmp;
			}

			pointer operator->() const{
				return &(operator*());
			}

			reverse_iterator& operator++(){
				--_current;
				return (*this);
			}

			reverse_iterator operator++(int){
				reverse_iterator tmp = *this;
				_current--;
				return tmp;
			}

			reverse_iterator& operator--(){
				++_current;
				return (*this);
			}

			reverse_iterator operator--(int){
				reverse_iterator tmp = *this;
				_current++;
				return tmp;
			}

			reverse_iterator operator+ (difference_type n) const{
				return (reverse_iterator(_current - n));
			}

			reverse_iterator& operator+=(difference_type n){
				_current -= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const{
				return (reverse_iterator(_current + n));
			}

			reverse_iterator& operator-=(difference_type n){
				_current += n;
				return (*this);
			}

			reference operator[](difference_type n) const{
				return _current[-n-1];
			}
	};

	/* RELATIONAL OPERATORS */

	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() == y.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() > y.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() != y.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() < y.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() <= y.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (x.base() >= y.base());
	}

	/* OPERATORS + and - */

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
		return (y.base() - x.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x){
		return (reverse_iterator<Iterator> (x.base() - n));
	}

}

#endif
