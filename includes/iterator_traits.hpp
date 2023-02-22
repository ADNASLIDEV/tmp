/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:07:43 by aasli             #+#    #+#             */
/*   Updated: 2022/12/20 14:14:51 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

#include <cstddef>
/* This header provides uniform interface to the properties of an iterator */

namespace ft {

// empty class types used to indicate iterator categories
// See https://www.fluentcpp.com/2018/04/27/tag-dispatching/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// Create a basic iterator struct
// See https://cplusplus.com/reference/iterator/iterator/
	template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  		struct iterator {
    		typedef 			T							value_type;
    		typedef 			Distance					difference_type;
    		typedef 			Pointer						pointer;
    		typedef 			Reference					reference;
    		typedef 			Category					iterator_category;
  		};

// Implement the iterator_traits structs
// See https://cplusplus.com/reference/iterator/iterator_traits/ for member types
	template <class Iterator>
		struct iterator_traits {
			typedef typename	Iterator::difference_type	difference_type;
			typedef typename	Iterator::value_type		value_type;
			typedef typename	Iterator::pointer			pointer;
			typedef typename	Iterator::reference			reference;
			typedef typename	Iterator::iterator_category	iterator_category;
		};

	template <class T>
		struct iterator_traits<T*>{
			typedef 	std::ptrdiff_t				difference_type;
			typedef 	T							value_type;
			typedef 	T*							pointer;
			typedef 	T&							reference;
			typedef 	random_access_iterator_tag	iterator_category;
		};

	template <class T>
		struct iterator_traits<const T*>{
			typedef 	ptrdiff_t					difference_type;
			typedef 	T							value_type;
			typedef		const	T*					pointer;
			typedef 	const	T&					reference;
			typedef 	random_access_iterator_tag	iterator_category;
		};
}

#endif
