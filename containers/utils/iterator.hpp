/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:06:27 by adesgran          #+#    #+#             */
/*   Updated: 2023/02/03 13:45:42 by adesgran         ###   ########.fr       */
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
		class iterator <std::input_iterator_tag, T, _Distance, _Pointer, _Reference>
		{
			public :
				typedef	T						value_type;
				typedef	ptrdiff_t				difference_type;
				typedef	T*						pointer;
				typedef	T&						reference;
				typedef	std::input_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<std::forward_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<std::input_iterator_tag, T>
		{
			public :
				typedef	T							value_type;
				typedef	ptrdiff_t					difference_type;
				typedef	T*							pointer;
				typedef	T&							reference;
				typedef	std::forward_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<std::bidirectional_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<std::forward_iterator_tag, T>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	std::bidirectional_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator
		<std::random_access_iterator_tag, T, _Distance, _Pointer, _Reference> : public iterator<std::bidirectional_iterator_tag, T>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	std::random_access_iterator_tag	iterator_category;
		};

};

#endif
