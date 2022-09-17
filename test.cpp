/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:18:08 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/17 00:22:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid
#include <vector>

int main() {
  typedef std::iterator_traits<std::vector<int>*> traits;
  if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator" << std::endl;
  if (typeid(traits::iterator_category)==typeid(std::forward_iterator_tag))
    std::cout << "int* is a forward-access iterator" << std::endl;
  return 0;
}
