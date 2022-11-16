/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:18:08 by adesgran          #+#    #+#             */
/*   Updated: 2022/11/16 16:22:02 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid
#include <vector>
#include <map>

int main() {
	std::map<std::string, int> m;
	m.insert(std::pair<std::string, int>("Pizza", 2));	
	m.insert(std::pair<std::string, int>("Pizza2", 2));	
	m.insert(std::pair<std::string, int>("Aizza", 2));	
	//for (std::map<std::string, int>::iterator it = m.begin(); it < m.end(); it++)
		//std::cout << it->first << std::endl;
	try
	{
		std::cout << m.begin()->first <<  std::endl;
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	
  return 0;
}
