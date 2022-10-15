/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:21 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/16 00:36:57 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>

#ifdef STL
	namespace ft = std;
# include <vector>
# include <iterator>
# else
# include <stack.hpp>
# include <vector.hpp>
# include "containers/utils/iterator_traits.hpp"
# include "containers/utils/iterator_tag.hpp"
# include "containers/utils/reverse_iterator.hpp"
# include "containers/utils/enable_if.hpp"
# include "containers/utils/is_integral.hpp"
# include "containers/utils/equal.hpp"
# include "containers/utils/lexicographical_compare.hpp"
# include "containers/utils/pair.hpp"
# include "containers/utils/make_pair.hpp"
# include "containers/utils/iterator.hpp"
#endif

int main(void)
{
	ft::vector<int> vec(10, 3);

	vec[0] = 1;
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end(); it++)
		std::cout << *it << std::endl;

	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.resize(5);
	vec.resize(8, 100);
	vec.resize(12);
	vec.reserve(20);
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.back() = 3;
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	try
	{
		vec.at(50);
	}
	catch (std::exception & s)
	{
		std::cout << s.what() << std::endl;
	}
	std::cout << "Front : " << vec.front() << std::endl << "Back : " << vec.back() << std::endl;
	return (0);
}

