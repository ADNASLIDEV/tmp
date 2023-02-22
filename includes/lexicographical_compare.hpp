/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:44:41 by aasli             #+#    #+#             */
/*   Updated: 2022/12/19 20:44:44 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LEXICOGRAPHICAL_COMPARE_HPP
#define		LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

	// Source: https://www.geeksforgeeks.org/lexicographical_compare-in-cpp-stl/
	// Source: https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare 

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1,
		InputIt1 last1, InputIt2 first2, InputIt2 last2){
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
    		++first1;
			++first2;
  		}
  		return (first2 != last2);
	}

}

#endif
