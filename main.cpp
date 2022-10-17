/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:21 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/17 14:56:35 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>
#include <vector>
#include <iterator>
#include <map>

#ifdef STL
	namespace ft = std;
# else
# include <stack.hpp>
# include <vector.hpp>
# include <map.hpp>
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


int main(void) //MAP
{
	ft::map<std::string, int> mp;
	return (0);
}

/*
int main(void) //VECTOR
{
	ft::vector<int> tmp(5, 4);
	ft::vector<int> vec(10, 3);
	vec = tmp;

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

	std::vector<int> vec2(2,4);
	
	vec.assign(vec2.begin(), vec2.end());

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	std::vector<int> vec3(20,5);
	
	vec.assign(vec3.begin(), vec3.end());

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.assign(7, 12);

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.assign(20, 20);
	vec.push_back(11);
	vec.push_back(11);
	vec.pop_back();
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	ft::vector<int>::iterator it_tmp = vec.insert(vec.begin() + 21, 42);
	std::cout << "New it : " << *it_tmp << std::endl;
	vec.insert(vec.end() - 1 ,5, 12);
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	std::vector<int> ttt(10, 54);
	vec.insert(vec.begin() + 3, ttt.begin(), ttt.end());
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.erase(vec.begin() + 3);
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.erase(vec.begin() + 3, vec.begin() + 26);
	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	ft::vector<int> swp(12, 13);
	vec.swap(swp);

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	for (ft::vector<int>::iterator it = swp.begin(); it < swp.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << swp.size() << std::endl;
	std::cout << "Max Size : " << swp.max_size() << std::endl;
	std::cout << "Capacity : " << swp.capacity() << std::endl;

	vec.clear();

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;

	vec.push_back(12);

	for (ft::vector<int>::iterator it = vec.begin(); it < vec.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Max Size : " << vec.max_size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << std::endl;
	return (0);
}
*/
