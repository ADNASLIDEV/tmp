/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_swap.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:20:45 by aasli             #+#    #+#             */
/*   Updated: 2022/12/16 23:27:08 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_SWAP_HPP
#define G_SWAP_HPP

namespace ft{
	template<typename T>
	void	swap(T&a, T&b){
		T tmp;
	
		tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
