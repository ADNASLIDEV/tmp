/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:05:40 by aasli             #+#    #+#             */
/*   Updated: 2023/02/16 21:57:57 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR
# define RBT_ITERATOR

#include "iterator_traits.hpp"

namespace ft {
	
	template<typename T, typename N>
	class	rbt_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>  {
		
		public:
			typedef	N*		node_pointer;
			typedef	T&		reference;
			typedef	T*		pointer;

		protected:
			node_pointer	_current;

		public:
			rbt_iterator(): _current() {}

			rbt_iterator(node_pointer np): _current(np) {}

			rbt_iterator(const rbt_iterator &x): _current(x._current)  {}

			~rbt_iterator() {}

			rbt_iterator &operator=(rbt_iterator const &src){
				if (*this != src)
					_current = src._current;
				return (*this);
			}
			
			operator	rbt_iterator<const T, N>() const {
				return (rbt_iterator<const T, N>(_current));
			}

			/* MEMBERS FUNCTIONS */

			node_pointer base() const {
				return (_current);
			}

			reference operator*() const{
				return (_current->data);
			}

			pointer operator->() const{
				return (&(_current->data));
			}

// Second implementation

			rbt_iterator& operator++(){
				node_pointer current = _current;
				node_pointer tmp = _current->parent;

				if (_current && _current->right){
					_current = _current->right;
					while (_current && _current->left){
						_current = _current->left;
					}
				} else if (_current && _current->parent){
					current = _current;
					tmp		= _current->parent;
					while (tmp && _current == tmp->right){
						if (tmp->parent == NULL){
							_current = current->parent;
							return (*this);
						}
						_current = tmp;
						tmp = tmp->parent;
					}
					_current = tmp;
				}
				return (*this);
			}

			rbt_iterator operator++(int){
				rbt_iterator tmp = *this;
				operator++();
				return (tmp);
			}

// Second implementation

			rbt_iterator& operator--(){
				node_pointer current = _current;
				node_pointer tmp = _current->parent;

			// If you got a left child, go down and move right until you can to get it
				if (_current && _current->left){
					_current = _current->left;
					while (_current && _current->right){
						_current = _current->right;
					}
			// You have to go up till the current is the right child or the parent is NULL so you are root
				} else if (_current && _current->parent){
					current = _current;
					tmp		= _current->parent;
					while (tmp && _current == tmp->left){
						if (tmp->parent == NULL){
							_current = current;
							return (*this);
						}
						_current = tmp;
						tmp = tmp->parent;
					}
					_current = tmp;
				}
				return (*this);
			}

			rbt_iterator operator--(int){
				rbt_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			friend bool operator== (const rbt_iterator& a, const rbt_iterator& b){
				return (a.base() == b.base());
			};

    		friend bool operator!= (const rbt_iterator& a, const rbt_iterator& b){
				return (a.base() != b.base());
			};     
	};
}

#endif
