/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:15:33 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/03 17:41:54 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
	template <class T, T v> struct integral_constant
	{
		static const 		T						value = v;
		typedef				T						value_type;
		typedef				integral_constant<T, v> type;
		operator T() { return v; };
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T, bool is_int> struct is_integral_res
	{
		typedef			bool		value_type;
		typedef			integral_constant<bool, is_int>	type;
		static const bool			value=is_int;
	};


	template <typename N> struct is_integral_type : public is_integral_res<N, false>{};

	template <> struct is_integral_type<bool> :						public is_integral_res<bool, true>{};
	template <> struct is_integral_type<char> :						public is_integral_res<char, true>{};
	template <> struct is_integral_type<wchar_t> :					public is_integral_res<wchar_t, true>{};
	template <> struct is_integral_type<signed char> :				public is_integral_res<signed char, true>{};
	template <> struct is_integral_type<short int> :				public is_integral_res<short int, true>{};
	template <> struct is_integral_type<int> :						public is_integral_res<int, true>{};
	template <> struct is_integral_type<long int> :					public is_integral_res<long int, true>{};
	template <> struct is_integral_type<long long int> :			public is_integral_res<long long int, true>{};
	template <> struct is_integral_type<unsigned char> :			public is_integral_res<unsigned char, true>{};
	template <> struct is_integral_type<unsigned short int> :		public is_integral_res<unsigned short int, true>{};
	template <> struct is_integral_type<unsigned int> :				public is_integral_res<unsigned int, true>{};
	template <> struct is_integral_type<unsigned long int> :		public is_integral_res<unsigned long int, true>{};
	template <> struct is_integral_type<unsigned long long int> :	public is_integral_res<unsigned long long int, true>{};

	template <typename T> struct is_integral : public is_integral_type<T>{};

};


#endif
