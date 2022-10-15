/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:24:36 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/15 21:51:24 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef>
#include "iterator_tag.hpp"

namespace ft
{
	template <class Iterator> struct iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;

	};
	template <class T> class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};
	template <class T> class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef const T*							pointer;
			typedef const T&							reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};
};

#endif
