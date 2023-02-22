/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:56:43 by aasli             #+#    #+#             */
/*   Updated: 2022/12/13 17:56:54 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		ENABLE_IF_HPP
# define	ENABLE_IF_HPP

// https://en.cppreference.com/w/cpp/types/enable_if
// https://eli.thegreenplace.net/2014/sfinae-and-enable_if/

namespace	ft
{
	template<bool B, class T = void>
	struct enable_if {};
 
	template<class T>
	struct enable_if<true, T> {
		typedef T type; 
	};
}

#endif
