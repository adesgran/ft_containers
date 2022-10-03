/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:44:55 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/03 17:47:28 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

namespace ft
{
	template <class T1, class T2>
		pair<T1, T2> make_pair (T1 x, T2 y)
		{
			return ( pair <T1, T2>(x, y) );
		};
}


#endif
