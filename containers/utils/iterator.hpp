/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:06:27 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/13 11:06:43 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <string>
# include "iterator_tag.hpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator;

	template <class T, class _Distance, class _Pointer, class _Reference> 
		class iterator <ft::input_iterator_tag, T, _Distance, _Pointer, _Reference>
		{
			public :
				typedef	T						value_type;
				typedef	ptrdiff_t				difference_type;
				typedef	T*						pointer;
				typedef	T&						reference;
				typedef	ft::input_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<ft::forward_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<ft::input_iterator_tag, T>
		{
			public :
				typedef	T							value_type;
				typedef	ptrdiff_t					difference_type;
				typedef	T*							pointer;
				typedef	T&							reference;
				typedef	ft::forward_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<ft::bidirectional_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<ft::forward_iterator_tag, T>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	ft::bidirectional_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator
		<ft::random_access_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<ft::bidirectional_iterator_tag, T>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	ft::random_access_iterator_tag	iterator_category;
		};

};

#endif
