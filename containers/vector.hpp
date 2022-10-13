/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/13 12:09:36 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEBUG 1

# include <iostream>
# include <string>
# include <iterator>
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"

namespace ft
{
	template <bool Cond, class Res1, class Res2> class Ternary;
	template <class Res1, class Res2> class Ternary <0, Res1, Res2 >
	{ typedef Res2 type; };
	template <class Res1, class Res2> class Ternary <1, Res1, Res2 >
	{ typedef Res1 type; };

	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				template <bool Const = false>
					class vecIterator
				{
					typedef	ft::random_access_iterator_tag	iterator_category;
					typedef	Ternary<Const, const T, T>		value_type;
					typedef	ptrdiff_t						difference_type;
					typedef	value_type*						pointer;
					typedef	value_type&						reference;
					typedef	vecIterator						iterator;

					public:
						vecIterator() : _ptr(NULL) {};
						vecIterator(pointer ptr) : _ptr(ptr) {};
						vecIterator(const vecIterator<Const> &it) : _ptr(it._ptr) {};
						~vecIterator() {};

						pointer	getPtr(void) const {return (_ptr);};

						iterator	operator= (iterator const & it) {_ptr = it._ptr;return (*this);};
						bool		operator== (iterator const & it) const {return (_ptr == it._ptr);};
						bool		operator!= (iterator const & it) const {return (_ptr != it._ptr);};
						bool		operator> (iterator const & it) const {return (_ptr > it._ptr);};
						bool		operator>= (iterator const & it) const {return (_ptr >= it._ptr);};
						bool		operator< (iterator const & it) const {return (_ptr < it._ptr);};
						bool		operator<= (iterator const & it) const {return (_ptr <= it._ptr);};

						pointer		operator+ (int i) const {return (_ptr + i);};
						pointer		operator- (int i) const {return (_ptr - i);};
						difference_type	operator- (const vector::vecIterator<true>& it) const {return (_ptr - it.getPtr());};
						difference_type	operator- (const vector::vecIterator<false>& it) const {return (_ptr - it.getPtr());};
						iterator	&operator+= (int i) {_ptr += i; return (*this);};
						iterator	&operator-= (int i) {_ptr -= i; return (*this);};

						reference	operator[] (size_t n) const {return (_ptr + n);};
						reference	operator* (void) const {return (*_ptr);};
						pointer		operator-> (void) const {return (_ptr);};
						
						iterator	&operator++ (void) {_ptr++; return (*this);};
						iterator	operator++ (int) {iterator res = *this; _ptr++; return (res);};
						iterator	&operator-- (void) {_ptr--; return (*this);};
						iterator	operator-- (int) {iterator res = *this; _ptr--; return (res);};

					private:
						pointer	_ptr;
				};
				typedef	T											value_type;
				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef	typename allocator_type::const_reference				const_reference;
				typedef	typename allocator_type::pointer						pointer;
				typedef	typename allocator_type::const_pointer				const_pointer;
				typedef	vecIterator<>									iterator;


				vector( void )
				{
					this->content = value_type();
					constit = vecIterator<true>();
					it = vecIterator<>();
					*it++;
					std::cout << constit- it << std::endl;
				}
				vector( T t )
				{
					this->content = t;	
				};

				vector( const vector &vector )
				{
					this->content = vector.content;
				};

				~vector( void )
				{

				};

				vector &operator=( const vector &vector )
				{
					this->content = vector.content;
					return (*this);
				};

				T	&getContent( void )
				{
					return (this->content);
				}

			private:
				T	content;
				iterator	it;
				vecIterator<true>	constit;

		};
}

#endif
