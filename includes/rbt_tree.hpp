/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:09:37 by aasli             #+#    #+#             */
/*   Updated: 2023/02/19 22:02:48 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RBT_TREE_HPP
#define	RBT_TREE_HPP

#include "rbt_iterator.hpp"
#include "g_swap.hpp"
#include "pair.hpp"

enum	rbt_color{
	BLACK	= true,
	RED		= false
};

namespace ft{

	template<typename T, typename K, class Compare = std::less<K>, class Alloc = std::allocator<T> >
	class	rbt{
		public:
			typedef	T						value_type;
		private:
			struct Node{
				T			data;
				rbt_color	color;
				Node		*parent;
				Node		*left;
				Node		*right;

				// Constructor to initialize everithing but the value type to NULL
				Node(const value_type& v = value_type()):
					data(v), color(BLACK), parent(NULL), left(NULL), right(NULL) {}

			};

		public:

			typedef	const T					const_value_type;
			typedef	K						key_type;
			typedef	Alloc					allocator_type;
			typedef	size_t					size_type;
			typedef	value_type*				pointer;
			typedef	const value_type*		const_pointer;
			typedef	value_type&				reference;
			typedef	const value_type&		const_reference;
			typedef	Node*					node_pointer;
			typedef	const Node*				const_node_pointer;
			typedef Compare					compare_type;
			typedef typename allocator_type::template rebind<Node>::other	node_allocator;
			typedef typename ft::rbt_iterator<value_type, Node>				iterator;
			typedef typename ft::rbt_iterator<const_value_type, Node>		const_iterator;

		private:


			node_pointer					_root;
			node_pointer					_end;
			node_allocator					_alloc;
			size_type						_size;
			compare_type					_compare;
	
	// Begin with a BST

	// Function to create a new node

			node_pointer _new_node(const value_type& v = value_type()){
				node_pointer tmp = _alloc.allocate(1);
				_alloc.construct(tmp, Node(v));
				return tmp;
			}
	
	// Function to delete a node

			void	_delete_node(node_pointer node){
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

	// Find the node with the maximum key

			node_pointer	_maximum() const{
				node_pointer	tmp = _root;
				while (tmp && tmp->right != NULL && tmp->right != _end) {
					tmp = tmp->right;
				}
				return (tmp);
			}

	// Find the node with the minimum key

			node_pointer	_minimum() const{
				node_pointer	tmp = _root;
				while (tmp && tmp->left != NULL) {
					tmp = tmp->left;
				}
				return (tmp);
			}

	// Search a node by key

			node_pointer	_search_tree(const value_type & v) const {
				node_pointer	tmp = _root;

				if (tmp == NULL){
					return (NULL);
				}
				while(tmp != NULL && tmp != _end){
					if (_compare(tmp->data.first, v.first))
						tmp = tmp->right;
					else if (_compare(v.first, tmp->data.first))
						tmp = tmp->left;
					else
						return (tmp);
				}
				return (NULL);
			}

	// Assign to root if the tree is empty on insert
	
			ft::pair<iterator, bool>	_assignToRoot(node_pointer node){
				_root 			=	node;
				_root->color 	=	BLACK;
				_root->parent 	=	NULL;
				_root->right 	=	_end;
				_root->left		=	NULL;
				_size++;
				_update_end();
				return (ft::make_pair(iterator(node), true));
			}

	// Update the _end node wich is at the far most right of the tree

			void	_update_end(){
				node_pointer max = _maximum();

				max->right = _end;
				_end->parent = max;
				_end->right = NULL;
				_end->left = NULL;
			}

	// recursive function to delete every node except _end

			void	_clear(node_pointer toDelete){
				if (toDelete == NULL || toDelete == _end)
					return ;
				_clear(toDelete->left);
				_clear(toDelete->right);
				_delete_node(toDelete);
			}

	// Source: https://www.softwaretestinghelp.com/binary-search-tree-in-cpp/#1_Insert

			node_pointer	_erase_tree_node(node_pointer node){
				node_pointer	parent		= node->parent;
				node_pointer	child		= _get_one_child(node);
				node_pointer	successor	= _get_successor(node);

				//	There is 3 cases: 
				//		1) has no child
				//		2) has one child
				//		3) has two children
			
				if (node->left == NULL && node->right == NULL){ //	case 1:
					if (node == _root){
						_root = NULL;
					}else {
						if (_is_right_child(node))
							parent->right = NULL;
						else
							parent->left = NULL;
					}
					_size--;
					_delete_node(node);
					_update_end();	
					return (successor);
				}
				else if (node->left == NULL || node->right == NULL || node->right == _end) { //	case 2:
					if (node == _root){
						_root = child;
						child->parent = NULL;
						_delete_node(node);
						_size--;
						_update_end();
					}else {
						if (_is_right_child(node))
							parent->right	=	child;
						else
							parent->left	=	child;
						_delete_node(node);
						child->parent = parent;
						_size--;
						_update_end();
					}
					return (successor);
				}
				//	case 3
				_swap_values(node, successor);
				_erase_tree_node(successor);
				return (node); // wich is not the node anymore
			}

			node_pointer	_get_one_child(node_pointer node){
				if (node->right)
					return (node->right);
				return (node->left);
			}

			node_pointer	_get_successor(node_pointer node){
				node_pointer	successor = node;

				if (node->right && node->right != _end){
					successor = successor->right;
					while (successor->left != NULL)
						successor = successor->left;
					return (successor);
				}
				while (successor->parent && successor == successor->parent->right)
					successor = successor->parent;
				return (successor->parent);
			}
			
			void	_give_values(node_pointer n1, node_pointer n2){
				key_type	*k1;
				key_type	*k2;

				k1 = const_cast<key_type *>(&n1->data.first);
				k2 = const_cast<key_type *>(&n2->data.first);

				*k1		=	*k2;

				n1->data.second	=	n2->data.second;
			}

			void	_swap_values(node_pointer n1, node_pointer n2){
				key_type	k_tmp;
				key_type	*k1;
				key_type	*k2;
				value_type	tmp;

				k1 = const_cast<key_type *>(&n1->data.first);
				k2 = const_cast<key_type *>(&n2->data.first);

				k_tmp	=	*k1;
				*k1		=	*k2;
				*k2		=	k_tmp;

				tmp.second		=	n1->data.second;
				n1->data.second	=	n2->data.second;
				n2->data.second	=	tmp.second;
			}

			bool	_is_right_child(node_pointer node){
				return (node == node->parent->right);
			}

			bool	_is_left_child(node_pointer node){
				return (node == node->parent->left);
			}

		public:
		
	// construct/destroy

			rbt(const compare_type &comp = compare_type(), const allocator_type &alloc = allocator_type()){
				_alloc		=		alloc;
				_compare	=		comp;
				_end 		=		_new_node();
				_root 		=		_end;
				_size 		=		0;
			}

			~rbt(){
				if (_size)
					clear();
				_delete_node(_root);
			}

			node_allocator	get_allocator() const{
				return (_alloc);
			}
			
	// capacity;

			bool	empty() const{
				return (_size == 0);
			}

			size_type	size() const{
				return (_size);
			}

			size_type	max_size() const{
				return (_alloc.max_size());
			}

	// iterators:
			iterator begin(){
				return (iterator(_minimum()));
			}

			const_iterator begin() const{
				return (const_iterator(_minimum()));
			}

			iterator end(){
				return (iterator(_end));
			}

			const_iterator end() const{
				return (const_iterator(_end));
			}

	// From map operations:

		ft::pair<iterator, bool> insert(const value_type &v){
			node_pointer	node	= 	_new_node(v);
			node_pointer	current = 	_root;
			node_pointer	parent	= 	NULL;

			// Case: empty tree
			if (empty())
				return (_assignToRoot(node));

			// Go through the tree until we find the end or the key exists already
			while (current != _end && current != NULL){
				parent = current;
				//	_compare uses std:less by default so current < node returns false, go to right
				if (_compare(current->data.first, node->data.first))
					current = current->right;
				//	_compare uses std:less by default so node > current returns false, go to left
				else if (_compare(node->data.first, current->data.first))
					current = current->left;
				//	_compares failed to returns true before so current = node
				//  So we do nothing except to return the already existing node
				else{
					_delete_node(node);
					return (ft::make_pair(iterator(current), false));
				}
				// At the end, the current is at _end or at NULL, so we can insert now
			}
			
			// The key doesn't exist so we insert it at the right place
			node->parent = parent;

			if (_compare(parent->data.first, node->data.first))
				parent->right = node;
			else if (_compare(node->data.first, parent->data.first))
				parent->left = node;
			// Need to balance the tree
			_size++;
			_update_end();
			return (ft::make_pair(iterator(node), true));	
		}

		size_type	erase(const value_type& v){
			node_pointer node;
//	std::cout << "erase function called\n";

			node = _search_tree(v);
			if (!node)
//				std::cout << "Node set as NULL\n";
			if (_size == 0 || node == NULL)
				return (0);
//	std::cout << "Node to erase found\n";
			if (_size == 1){
				clear();	
				return (1);
			}
			_erase_tree_node(node);
			return (1);
		}

		void	multi_erase(iterator it, iterator ite){
//	std::cout << "multi erase function called\n";
			size_type		n = 0;
			node_pointer	node = it.base();

			for (; it != ite; it++)
				n++;
			while (n > 0){
				node = _erase_tree_node(node);
				n--;	
			}
		}

		void	swap(rbt & rhs){
			ft::swap(_root, rhs._root);
			ft::swap(_end, rhs._end);
			ft::swap(_alloc, rhs._alloc);
			ft::swap(_size, rhs._size);
			ft::swap(_compare, rhs._compare);
		}		

		void	clear(){
			_clear(_root);
			_root = _end;
			_size= 0;
		}

	// lookup:

		iterator find(const value_type& v){
			node_pointer	find	=	_search_tree(v);

			if (find == NULL)
				return (iterator(_end));
			else
				return (iterator(find));
		}

		const_iterator find(const value_type& v) const{
			node_pointer	find	=	_search_tree(v);

			if (find == NULL)
				return (const_iterator(_end));
			else
				return (const_iterator(find));
		}

		size_type count(const value_type& v) const{
			node_pointer	find	=	_search_tree(v);

			if (find == NULL)
				return (0);
			return (1);
		}

		iterator lower_bound(const value_type& x){
			iterator	it	=	begin();
			iterator	ite	=	end();

			for (; it != ite; it++){
				if (!_compare(it->first, x.first))
					return (it);
			}
			return (ite);
		}

		const_iterator lower_bound(const value_type& x) const{
			const_iterator	it	=	begin();
			const_iterator	ite	=	end();

			for (; it != ite; it++){
				if (!_compare(it->first, x.first))
					return (it);
			}
			return (ite);
		}

		iterator upper_bound(const value_type& x){
			iterator	it	=	begin();
			iterator	ite	=	end();

			for (; it != ite; it++){
				if (_compare(x.first, it->first))
					return (it);
			}
			return (ite);
		}

		const_iterator upper_bound(const value_type& x) const{
			const_iterator	it	=	begin();
			const_iterator	ite	=	end();

			for (; it != ite; it++){
				if (_compare(x.first, it->first))
					return (it);
			}
			return (ite);
		}

	// observers:

		compare_type	compare() const{
			return (_compare);
		}

		void	printHelper(node_pointer root, std::string indent, bool last)
		{
			 if (root != NULL)
			 {
		 		std::cout << indent;
			 	if (last)
			 	{
			 		std::cout << "R---- ";
			 		indent += "   ";
			 	}else{
			 		std::cout << "L---- ";
			 		indent += "|  ";
			 	}
			 	std::string sColor = "BLACK";
			 	if (root->color == RED)
			 		sColor = "RED";
			 	std::cout << root->data.first << " : " << root->data.second << " (" << sColor << ")" << std::endl;
			 	printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}

		void	print_rbt()
		{
			if (_root)
			 	printHelper(_root, "", true);
		}
	};

}

#endif
