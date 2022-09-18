/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:35:47 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/18 15:53:16 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include <tuple>

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
		template<class U, class V> pair(const pair<U, V> &pr) : first(pr), second(pr){};
		pair(const first_type& a, const second_type &b) : first(a), second(b){};
		pair (std::piecewise_construct_t pwc, std::tuple<T1> first_args,
                                   std::tuple<T2> second_args) : first(first_args), second(second_args) {} ;

		template <class T> void swap(T &a, T &b)
		{
			T c(a);
			a = b;
			b = c;
		}
		pair	&operator=(const pair &pr) {this->first = pr.first; this->second = pr.second;};
		void	swap(pair &pr) noexcept (noexcept(swap(first,pr.first)) && noexcept(swap(second,pr.second))){
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

	template <size_t I, class T1, class T2>
		typename std::tuple_element<I,ft::pair<T1,T2>>::type &  get(ft::pair<T1,T2>&  pr) noexcept;
	/*
		{
			if (I == 0)
				return (pr.first);
			else if (I == 1)
				return (pr.second);
		};
		*/
/*
	template <size_t I, class T1, class T2>
		typename std::tuple_element<I,pair<T1,T2> >::type&&  get (pair<T1,T2>&&  pr) noexcept
		{
			if (I == 0)
				return (pr.first);
			else if (I == 1)
				return (pr.second);
		};

	template <size_t I, class T1, class T2>
		const typename std::tuple_element< I, pair<T1,T2> >::type&
		get (const pair<T1,T2>& pr) noexcept
		{
			if (I == 0)
				return (pr.first);
			else if (I == 1)
				return (pr.second);
		};

		*/
};

#endif
