/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_tag.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:14:22 by adesgran          #+#    #+#             */
/*   Updated: 2023/01/18 10:57:44 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TAG_HPP
# define ITERATOR_TAG_HPP

# include <iostream>
# include <string>

namespace ft
{
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag {};
	class bidirectional_iterator_tag {};
	class random_access_iterator_tag {};
};

#endif
