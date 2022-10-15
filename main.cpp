/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:21 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/15 19:06:23 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.hpp>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <iterator>
#include <stack.hpp>
//#include <tuple>
#include "containers/utils/iterator_traits.hpp"
#include "containers/utils/iterator_tag.hpp"
#include "containers/utils/reverse_iterator.hpp"
#include "containers/utils/enable_if.hpp"
#include "containers/utils/is_integral.hpp"
#include "containers/utils/equal.hpp"
#include "containers/utils/lexicographical_compare.hpp"
#include "containers/utils/pair.hpp"
#include "containers/utils/make_pair.hpp"
#include "containers/utils/iterator.hpp"
//#include <type_traits>

bool	comparator(int a, int b)
{
	return ((a == b)?true:false);
}

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
	is_odd (T i) {return bool(i%2);}

int main(void)
{
	std::vector<int> ve(10, 2);
	ft::vector<int> v(ve.begin(), ve.end());
	ft::vector<int> vec(v);

	for (int i = 0; i < 11; i++)
		std::cout << i << " : " << vec[i] << std::endl;
	return (0);
}

/* --MAIN UTILS--
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

	int i = 2;
	std::cout << std::boolalpha << "i is odd: " << is_odd(i) << std::endl;

	std::cout << "is_integral : " << ft::is_integral<int>::value << std::endl;
	std::cout << "is_integral : " << ft::is_integral<char>::value << std::endl;
	std::cout << "is_integral : " << ft::is_integral<float>::value << std::endl;

	int tab[] = {20, 40, 60, 80, 100};

	std::vector<int> myvector(tab, tab + 5);
	std::vector<int> myvector2(tab, tab + 5);
	for (std::vector<int>::iterator it=myvector2.begin(); it < myvector2.end(); it++)
		(*it)--;
	std::cout << "Tab comparaison : " << std::boolalpha << equal(myvector.begin(), myvector.end(), tab, comparator) << std::endl;
	tab[0] = 10;
	std::cout << "Tab comparaison : " << std::boolalpha << equal(myvector.begin(), myvector.end(), tab) << std::endl;
	std::cout << "Vector comparaison : " << std::boolalpha << lexicographical_compare(myvector.begin(), myvector.end(), myvector2.begin(), myvector2.end()) << std::endl;

	ft::pair<int, char> foo (100, 'a');
	ft::pair<int, char> bar (90, 'z');
	std::cout << foo.first << " " << foo.second << std::endl;
	foo.swap(bar);

	//char &ref = foo.first;
	//std::cout << ref << std::endl;
	std::cout << foo.first << " " << foo.second << std::endl;
	std::cout << std::boolalpha << (foo < bar) << std::endl;
	std::cout << ft::get<1>(foo) << std::endl;
	const ft::pair<const int, const char> fooc (100, 'a');
	std::cout << ft::get<0>(fooc) << std::endl;
	ft::pair <int, int> fooint (1,1);
	fooint = ft::make_pair (10.5, 'A');
	std::cout << fooint.first << " " << fooint.second << std::endl;
	return (0);
}
*/
