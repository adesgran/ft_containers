/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:06:07 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/17 02:22:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
	template <bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> 
	{
		typedef T	type;
	};
};

#endif
