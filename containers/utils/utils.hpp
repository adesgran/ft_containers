/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:24:41 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/16 00:31:05 by adesgran         ###   ########.fr       */
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
	}
};


#endif
