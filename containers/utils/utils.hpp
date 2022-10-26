/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:24:41 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/26 10:48:22 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <iostream>
#include <sstream>

namespace ft
{
	template <typename T>
		std::string	to_string(T x)
	{
		std::ostringstream ss;
		ss << x;
		return (ss.str());
	};

	template <bool Cond, class Res1, class Res2> class Ternary;
	template <class Res1, class Res2> class Ternary <false, Res1, Res2 >
	{ public : typedef Res2 type; };
	template <class Res1, class Res2> class Ternary <true, Res1, Res2 >
	{ public : typedef Res1 type; };
};


#endif
