/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:50:53 by adesgran          #+#    #+#             */
/*   Updated: 2023/01/18 13:17:23 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator> class reverse_iterator
	{
		public:
			//Member Type
			typedef				Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	iterator_traits<Iterator>::pointer				pointer;
			typedef typename	iterator_traits<Iterator>::reference			reference;

			//Constructors
			reverse_iterator() :
				_it() 
				{};

			explicit reverse_iterator(iterator_type it) :
				_it(it) 
				{};

			template <class Iter> reverse_iterator(const reverse_iterator<Iter> &rev_it) :
				_it(rev_it._it)
				{};

			virtual ~reverse_iterator() {};

			//Member Functions
			iterator_type		base() const {return (this->_it);};
			reference			operator*(void) const {iterator_type tmp = this->_it; return (*(--tmp));};
			reverse_iterator	&operator+(difference_type n) const {return (reverse_iterator(this->_it - n));}
			reverse_iterator	&operator++(void) {*this->_it--;return (*this);};
			reverse_iterator	operator++(int) {reverse_iterator tmp = *this;++(*this); return(tmp);};
			reverse_iterator	&operator+= (difference_type n) {this->_it -= n; return (*this);};
			reverse_iterator	&operator-(difference_type n) const {return (reverse_iterator(this->_it + n));}
			reverse_iterator	&operator--(void) {*this->_it++; return (*this);};
			reverse_iterator	operator--(int) {reverse_iterator tmp = *this;++(*this); return(tmp);};
			reverse_iterator	&operator-= (difference_type n) {this->_it += n; return (*this);};
			pointer				operator-> () const {return (&(operator*()));};
			reference			operator[] (difference_type n) const {return (this->base()[-n -1]);};

		private:
			iterator_type	_it;
	};

	//Non-Member function overloads
	template <class Iterator> bool operator== (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() == rhs.base());}

	template <class Iterator> bool operator!= (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() != rhs.base());}

	template <class Iterator> bool operator< (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() > rhs.base());}

	template <class Iterator> bool operator<= (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() >= rhs.base());}

	template <class Iterator> bool operator> (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() < rhs.base());}

	template <class Iterator> bool operator>= (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
				{return (lhs.base() <= rhs.base());}

	template <class Iterator>  reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
				{return (rev_it + n);};

	template <class Iterator>  reverse_iterator<Iterator> operator- (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
				{return (rev_it - n);};
};

#endif
