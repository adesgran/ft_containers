/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/12 12:00:14 by adesgran         ###   ########.fr       */
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
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				typedef	T											value_type;
				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef	typename allocator_type::const_reference				const_reference;
				typedef	typename allocator_type::pointer						pointer;
				typedef	typename allocator_type::const_pointer				const_pointer;


				vector( void )
				{
					this->content = value_type();
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

		};
}

#endif
