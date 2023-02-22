/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:07:13 by aasli             #+#    #+#             */
/*   Updated: 2022/12/14 17:03:14 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		IS_INTEGRAL_HPP
#define		IS_INTEGRAL_HPP

namespace ft {

	template<class T, T v>
	struct integral_constant {
    	static const T 					value = v;
    	typedef T 						value_type;
    	typedef integral_constant<T,v>	type;
		operator value_type() { return v; }
	};

	// The type used as a compile-time boolean with true or false value.
	typedef	integral_constant<bool, true>	true_type;
	typedef	integral_constant<bool, false>	false_type;

	// the compilo will try every template function with integral types and set to true and if it does not find an integral type then use the template<typename T> and set at false by default
	template <typename T>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};

	template <>
	struct is_integral<char> : public true_type {};

	template <>
	struct is_integral<wchar_t> : public true_type {};

	template <>
	struct is_integral<signed char> : public true_type {};

	template <>
	struct is_integral<short int> : public true_type {};

	template <>
	struct is_integral<int> : public true_type {};

	template <>
	struct is_integral<long int> : public true_type {};

	template <>
	struct is_integral<unsigned char> : public true_type {};

	template <>
	struct is_integral<unsigned short int> : public true_type {};

	template <>
	struct is_integral<unsigned int> : public true_type {};

	template <>
	struct is_integral<unsigned long int> : public true_type {};

	// template <>
	// struct is_integral<long long int> : public true_type {}; C++98 doesnt support long long with -pedantic

	// template <>
	// struct is_integral<unsigned long long int> : public true_type {}; C++98 doesnt support long long with -pedantic

}

#endif
