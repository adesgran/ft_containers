/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:21 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/17 02:16:14 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.hpp>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "containers/utils/iterator_traits.hpp"
#include "containers/utils/iterator_tag.hpp"
#include "containers/utils/reverse_iterator.hpp"
#include "containers/utils/enable_if.hpp"
#include <type_traits>

template <class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type
	is_odd (T i) {return bool(i%2);}

int main(void)
{
	std::vector<int> vec;
	for (int i = 0; i < 10; i++) vec.push_back(i);
	typedef std::vector<int>::iterator iter;
	iter from(vec.begin());
	iter until(vec.end());
	typedef ft::reverse_iterator<iter> riter;
	riter runtil(from);
	riter rfrom(until);
	for (riter it = rfrom; it < runtil; it++)
		std::cout << *it << ' ';
	std::cout << std::endl;

	double i = 1;
	std::cout << std::boolalpha << "i is odd: " << is_odd(i) << std::endl;
	return (0);
}
