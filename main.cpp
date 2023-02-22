/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:26:21 by adesgran          #+#    #+#             */
/*   Updated: 2023/02/22 17:27:22 by adesgran         ###   ########.fr       */
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

template <class T>
	void	printvec(const ft::vector<T> vec)
{
	std::cout << "Vector Size:" << std::endl;
	std::cout << vec.size() << std::endl;
	std::cout << "Vector Capacity:" << std::endl;
	std::cout << vec.capacity() << std::endl;

	std::cout << "Vector Print:" << std::endl;
	for (ft::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "Vector Reverse Print:" << std::endl;
	for (ft::vector<int>::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << *it << std::endl;
}


int main(void)
{
	ft::vector<int> vec(5, 100);
	ft::vector<int> vec2(50, 101);
	ft::vector<int> vec3(vec);
	const ft::vector<int> veve(vec3);
	

	vec.insert(vec.begin()+1, 3, 99);
	vec.insert(vec.end(), vec2.begin()+2, vec2.end());
	vec.reserve(2);
	printvec(vec);
	vec.insert(vec.begin()+2, 12);
	printvec(vec);
	vec.erase(vec.begin()+12);
	printvec(vec);
	std::cerr << "HERE1" << std::endl;
	vec.erase(vec.begin()+12, vec.end()-3);
	std::cerr << "HERE1" << std::endl;
	printvec(vec);
	vec.clear();
	printvec(vec);
	vec3.clear();
	printvec(vec3);
	std::cout << "Swap" << std::endl;
	vec.swap(vec2);
	printvec(vec);
	printvec(vec2);
	vec2.insert(vec2.begin(), 12, 12);
	vec.swap(vec2);
	printvec(vec);
	printvec(vec2);
	

	return (0);
}

	/*
int main(void) //MAP
{
	typedef ft::map<std::string, std::string> type;
	type mp;

	 mp.insert(ft::pair<std::string, std::string>("amigo de la tornada","apicf"));
 mp.insert(ft::pair<std::string, std::string>("eqaha",""));
 mp.insert(ft::pair<std::string, std::string>("frila",""));
 mp.insert(ft::pair<std::string, std::string>("hasrb","un"));
 mp.insert(ft::pair<std::string, std::string>("pgtrb","ijxna"));
 mp.insert(ft::pair<std::string, std::string>("qyvtb",""));
 mp.insert(ft::pair<std::string, std::string>("epbwc",""));
 mp.insert(ft::pair<std::string, std::string>("lbzpd",""));
 mp.insert(ft::pair<std::string, std::string>("tqdjg","pbjuo"));
 mp.insert(ft::pair<std::string, std::string>("ezvxi","hkezj"));
 mp.insert(ft::pair<std::string, std::string>("apegj","qzdjf"));
 mp.insert(ft::pair<std::string, std::string>("ewrpj","wkwin"));
 mp.insert(ft::pair<std::string, std::string>("wplzk",""));
 mp.insert(ft::pair<std::string, std::string>("ujxwl","eebzm"));
 mp.insert(ft::pair<std::string, std::string>("urqfn","blwpm"));
 mp.insert(ft::pair<std::string, std::string>("atencion","jkayp"));
 mp.insert(ft::pair<std::string, std::string>("hola amigo","aaloa"));
 mp.insert(ft::pair<std::string, std::string>("amigo de pepito",""));
 mp.insert(ft::pair<std::string, std::string>("exnwo","ggvzd"));
 mp.insert(ft::pair<std::string, std::string>("rfecq",""));
 mp.insert(ft::pair<std::string, std::string>("kxfbs","nfwsz"));
 mp.insert(ft::pair<std::string, std::string>("omylt","uamyw"));
 mp.insert(ft::pair<std::string, std::string>("trjqt",""));
 mp.insert(ft::pair<std::string, std::string>("txpjw",""));
 mp.insert(ft::pair<std::string, std::string>("shwtx",""));
 mp.insert(ft::pair<std::string, std::string>("mnawx","un dos tres quatro"));
 mp.print();
 unsigned int ret = mp.erase("apeg");
 std::cout << "res = " << ret << std::endl;
 mp.print();


	return (0);
}
*/
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
