/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:35:47 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/17 14:26:02 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
//# include <tuple>

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
		pair	&operator=(const pair &pr) {this->first = (T1)pr.first; this->second = (T2)pr.second; return (*this);};
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

	template <size_t I, class Tpl> class tuple_element;

	template <class T1, class T2> class tuple_element <0, ft::pair<T1,T2> >
	{ typedef T1 type; };

	template <class T1, class T2> class tuple_element <1, ft::pair<T1,T2> >
	{ typedef T2 type; };

	template <class Tpl> class tuple_size;

	template <class T1, class T2>
		class tuple_size< pair<T1,T2> > : integral_constant<size_t,2> {};

	template <size_t I>
		struct _pair_get;

	template<>
		struct _pair_get<0>
		{
			template <class T1, class T2>
				static T1 &_move_get(pair<T1, T2> &pr) {return (pr.first);};
			template <class T1, class T2>
				static const T1 &_const_get(const pair<T1, T2> &pr) {return (pr.first);};
		};

	template<>
		struct _pair_get<1>
		{
			template <class T1, class T2>
				static T2 &_get(pair<T1, T2> &pr) {return (pr.second);};
			template <class T1, class T2>
				static const T2 &_const_get(const pair<T1, T2> &pr) {return (pr.second);};
		};

	template <size_t I, class T1, class T2>
		typename tuple_element< I, ft::pair< T1, T2 > >::type &get(ft::pair< T1, T2 > &pr)
		{
			return (_pair_get<I>::_get(pr));
		};

	template <size_t I, class T1, class T2>
		const typename tuple_element< I, pair<T1,T2> >::type& get (const pair<T1,T2>& pr)
		{
			return (_pair_get<I>::_const_get(pr));
		};

};

#endif
