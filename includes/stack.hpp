/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:45:51 by aasli             #+#    #+#             */
/*   Updated: 2023/02/19 13:58:54 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STACK_HPP
#define	STACK_HPP

#include "vector.hpp"

// See ISO98 23.2.3.3 Template class stack
// See https://en.cppreference.com/w/cpp/container/stack

namespace ft {
	
	template <class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef typename 	Container::value_type 	value_type;
			typedef typename 	Container::size_type 	size_type;
			typedef 			Container 				container_type;

		protected:
			Container c;

		public:
			explicit stack(const Container &container = Container()): c(container) {}
		
//			stack( const stack& other ): c(other.c) {}	//cppreference.com

			~stack() {}

			stack& operator=( const stack& other ){
				if (*this == other)
					return (*this);
				c = other.c;
				return (*this);
			}

			bool				empty() const { return c.empty(); }

			size_type			size() const { return c.size(); }

			value_type& 		top() { return c.back(); }

			const value_type& 	top() const { return c.back(); }

			void 				push(const value_type& x) { c.push_back(x); }

			void 				pop() { c.pop_back(); }

// Why define friend function within the class body ?
// Another approach is to define the friend function within the class body at the same moment you declare it to be a friend.
// See https://isocpp.org/wiki/faq/templates#template-friends
	
		friend bool operator==(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c == y.c);
		}

		friend bool operator< (const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c < y.c);
		}

		friend bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c != y.c);
		}

		friend bool operator> (const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c > y.c);
		}

		friend bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c >= y.c);
		}

		friend bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c <= y.c);
		}

	};

// We can use the friend declaration because the operators of stack are in the underlying container wich is protected.
// See https://en.cppreference.com/w/cpp/language/friend
// How to implement it: https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/

		template <class T, class Container>
		bool operator==(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c == y.c);
		}

		template <class T, class Container>
		bool operator< (const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c < y.c);
		}

		template <class T, class Container>
		bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c != y.c);
		}

		template <class T, class Container>
		bool operator> (const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c > y.c);
		}

		template <class T, class Container>
		bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c >= y.c);
		}

		template <class T, class Container>
		bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y){
			return (x.c <= y.c);
		}
}

#endif
