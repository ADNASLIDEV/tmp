/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:14:54 by aasli             #+#    #+#             */
/*   Updated: 2023/02/12 21:14:54 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PAIR_HPP
#define	PAIR_HPP

// ISO98 20.2.2 Pairs p 358
// See https://en.cppreference.com/w/cpp/utility/pair

namespace ft{

	template <class T1, class T2>
	struct pair {

		typedef T1 first_type;
		typedef T2 second_type;

	// Member type

		first_type		first;
		second_type		second;

	// Constructors

		pair(): first(T1()), second(T2()) {} //  Default

		pair(const first_type& x, const second_type& y): first(x), second(y) {}

		template<class U, class V> 
		pair(const pair<U, V> &p): first(p.first), second(p.second) {}

//		pair( const pair& p ) = default;

		pair& operator=( const pair& other ){
			if (*this == other)
				return *this;
			first = other.first;
			second = other.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y){
		return (x.first == y.first && x.second == y.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y){
		return !(x.first == y.first && x.second == y.second);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y){
		if (x.first != y.first)
			return (x.first < y.first);
		return (x.second < y.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y){
		if (x.first != y.first)
			return (x.first <= y.first);
		return (x.second <= y.second);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y){
		if (x.first != y.first)
			return (x.first > y.first);
		return (x.second > y.second);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y){
		if (x.first != y.first)
			return (x.first >= y.first);
		return (x.second >= y.second);
	}

	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair( T1 t, T2 u ){
		return (pair<T1, T2>(t, u));
	}
}

#endif
