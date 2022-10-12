/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:06:27 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/12 14:48:16 by adesgran         ###   ########.fr       */
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
			protected:
			public :
				typedef	T						value_type;
				typedef	ptrdiff_t				difference_type;
				typedef	T*						pointer;
				typedef	T&						reference;
				typedef	ft::input_iterator_tag	iterator_category;

				iterator(iterator const & cpy) {};
				virtual ~iterator() {};

				virtual iterator	&operator=(iterator const & cpy) = 0;

				virtual value_type	operator++(int) = 0;
				virtual reference	operator++(void) = 0;
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

				virtual bool	&operator==(iterator const & it) const = 0;
				virtual bool	&operator!=(iterator const & it) const = 0;

				virtual reference	operator*() = 0;
				virtual pointer		operator->() = 0;

				virtual value_type	operator--(int) = 0;
				virtual reference	operator--(void) = 0;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<ft::bidirectional_iterator_tag, T, _Distance, _Pointer, _Reference>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	ft::bidirectional_iterator_tag	iterator_category;
		};

	template <class T, class _Distance, class _Pointer, class _Reference> class iterator 
		<ft::random_access_iterator_tag, T, _Distance, _Pointer, _Reference>
		{
			public :
				typedef	T								value_type;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef	T&								reference;
				typedef	ft::random_access_iterator_tag	iterator_category;
		};
/*

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator : public iterator<ft::input_iterator_tag, T> {
			public :
				typedef	typename	iterator<ft::forward_iterator_tag, T>::value_type			value_type;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::difference_type	difference_type;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::pointer			pointer;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::reference			reference;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::iterator_category	iterator_category;
		};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator : public iterator<ft::forward_iterator_tag, T> {
			public :
				typedef	typename	iterator<ft::forward_iterator_tag, T>::value_type			value_type;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::difference_type	difference_type;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::pointer			pointer;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::reference			reference;
				typedef	typename	iterator<ft::forward_iterator_tag, T>::iterator_category	iterator_category;


		};
		*/

};

#endif
