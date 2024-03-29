/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:35:47 by adesgran          #+#    #+#             */
/*   Updated: 2023/02/03 11:26:53 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include "is_integral.hpp"

template <class T> static void swap(T &a, T &b)
{
	T c(a);
	a = b;
	b = c;
}

namespace ft
{
	template <class T1, class T2> struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;
		first_type	first;
		second_type	second;

		pair() : first(), second(){};
		template<class U, class V> pair(const pair<U, V> &pr) : first(pr.first), second(pr.second){};
		pair(const first_type& a, const second_type &b) : first(a), second(b){};

		template <class T> void swap(T &a, T &b)
		{
			T c(a);
			a = b;
			b = c;
		}
		pair	&operator=(const pair &pr) {this->first = (first_type)pr.first; this->second = (second_type)pr.second; return (*this);};
		void	swap(pair &pr){
			swap(first,pr.first);
			swap(second,pr.second);
		};
	};

	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); };

};

#endif
