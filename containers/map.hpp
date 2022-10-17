/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:32 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/17 14:56:00 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utils/pair.hpp"
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/utils.hpp"

namespace ft
{
	template <class Arg1, class Arg2, class Result>
		struct binary_function {
			typedef Arg1 first_argument_type;
			typedef Arg2 second_argument_type;
			typedef Result result_type;
		};
	template <class T> struct less : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map
		{

			public :
				template <bool Const = false>
					class mapIterator
					{

						public:
							typedef	ft::bidirectional_iterator_tag				iterator_category;
							typedef	typename Ternary<Const, const T, T>::type	value_type;
							typedef	ptrdiff_t									difference_type;
							typedef	value_type*									pointer;
							typedef	value_type&									reference;
							typedef	mapIterator									iterator;

							mapIterator() : _ptr(NULL) {};
							mapIterator(pointer const ptr) : _ptr(ptr) {};
							//mapIterator(const mapIterator<Const> &it) : _ptr(it._ptr) {};
							~mapIterator() {};

							pointer	getPtr(void) const {return (_ptr);};

							iterator	operator= (iterator const & it) {_ptr = it._ptr;return (*this);};
							bool		operator== (iterator const & it) const {return (_ptr == it._ptr);};
							bool		operator!= (iterator const & it) const {return (_ptr != it._ptr);};

							reference	operator* (void) const {return (*_ptr);};
							pointer		operator-> (void) const {return (_ptr);};

							iterator	&operator++ (void) {_ptr++; return (*this);};
							iterator	operator++ (int) {iterator res = *this; _ptr++; return (res);};
							iterator	&operator-- (void) {_ptr--; return (*this);};
							iterator	operator-- (int) {iterator res = *this; _ptr--; return (res);};

						private:
							pointer	_ptr;
					};

				typedef	Key											key_type;
				typedef	T											mapped_type;
				typedef	ft::pair<const key_type, mapped_type>		value_type;
				typedef	Compare										key_compare;

				class value_compare
				{
					friend class map;
					protected :
					Compare comp;
					value_compare (Compare c) : comp(c) {}
					public :
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					};
				};

				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference			reference;
				typedef	typename allocator_type::const_reference	const_reference;
				typedef	typename allocator_type::pointer			pointer;
				typedef	typename allocator_type::const_pointer		const_pointer;
				typedef	mapIterator<>								iterator;
				typedef	mapIterator<true>							const_iterator;
				typedef	ft::reverse_iterator<mapIterator<> >		reverse_iterator;
				typedef	ft::reverse_iterator<mapIterator<true> >	const_reverse_iterator;
				typedef typename iterator::difference_type			difference_type;
				typedef	size_t										size_type;

				map() {};
				~map() {};
		};
};

#endif
