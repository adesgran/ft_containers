/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/22 11:23:21 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEBUG 1

# include <iostream>
# include <string>
# include <iterator>
# include "utils/iterator_traits.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
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
