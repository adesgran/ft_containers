/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2022/10/16 00:06:53 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEBUG 1

# include <iostream>
# include <string>
# include <iterator>
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"

namespace ft
{
	template <bool Cond, class Res1, class Res2> class Ternary;
	template <class Res1, class Res2> class Ternary <false, Res1, Res2 >
	{ public : typedef Res2 type; };
	template <class Res1, class Res2> class Ternary <true, Res1, Res2 >
	{ public : typedef Res1 type; };

	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				template <bool Const = false>
					class vecIterator
				{

					public:
						typedef	ft::random_access_iterator_tag				iterator_category;
						typedef	typename Ternary<Const, const T, T>::type	value_type;
						typedef	ptrdiff_t									difference_type;
						typedef	value_type*									pointer;
						typedef	value_type&									reference;
						typedef	vecIterator									iterator;

						vecIterator() : _ptr(NULL) {};
						vecIterator(pointer const ptr) : _ptr(ptr) {};
						//vecIterator(const vecIterator<Const> &it) : _ptr(it._ptr) {};
						~vecIterator() {};

						pointer	getPtr(void) const {return (_ptr);};

						iterator	operator= (iterator const & it) {_ptr = it._ptr;return (*this);};
						bool		operator== (iterator const & it) const {return (_ptr == it._ptr);};
						bool		operator!= (iterator const & it) const {return (_ptr != it._ptr);};
						bool		operator> (iterator const & it) const {return (_ptr > it._ptr);};
						bool		operator>= (iterator const & it) const {return (_ptr >= it._ptr);};
						bool		operator< (iterator const & it) const {return (_ptr < it._ptr);};
						bool		operator<= (iterator const & it) const {return (_ptr <= it._ptr);};

						pointer		operator+ (int i) const {return (_ptr + i);};
						pointer		operator- (int i) const {return (_ptr - i);};
						difference_type	operator- (const vecIterator& it) const {return (_ptr - it.getPtr());};
						iterator	&operator+= (int i) {_ptr += i; return (*this);};
						iterator	&operator-= (int i) {_ptr -= i; return (*this);};

						reference	operator[] (size_t n) const {return (_ptr + n);};
						reference	operator* (void) const {return (*_ptr);};
						pointer		operator-> (void) const {return (_ptr);};
						
						iterator	&operator++ (void) {_ptr++; return (*this);};
						iterator	operator++ (int) {iterator res = *this; _ptr++; return (res);};
						iterator	&operator-- (void) {_ptr--; return (*this);};
						iterator	operator-- (int) {iterator res = *this; _ptr--; return (res);};

					private:
						pointer	_ptr;
				};
				typedef	T											value_type;
				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference			reference;
				typedef	typename allocator_type::const_reference	const_reference;
				typedef	typename allocator_type::pointer			pointer;
				typedef	typename allocator_type::const_pointer		const_pointer;
				typedef	vecIterator<>								iterator;
				typedef	vecIterator<true>							const_iterator;
				typedef	ft::reverse_iterator<vecIterator<> >		reverse_iterator;
				typedef	ft::reverse_iterator<vecIterator<true> >	const_reverse_iterator;
				typedef typename iterator::difference_type			difference_type;
				typedef	size_t										size_type;


				//////////CONSTRUCTORS//////////
				explicit vector (const allocator_type& alloc = allocator_type())
				{
					_alloc = alloc;
					_begin = NULL;
					_size = 0;
					_capacity = 0;
					std::cout << "Adress : " << _begin << std::endl;
					
				};

				explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				{
					_alloc = alloc;
					//_capacity = _required_capacity(n);
					_capacity = n;
					_size = n;
					_begin = _alloc.allocate(_capacity);
					for (size_type i = 0; i < n; i++)
						(*this)[i] = val;
				}

				template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				{
					_alloc = alloc;

					InputIterator first_cpy = first;
					size_type n = 0;
					while (first_cpy < last)
					{
						n++;
						first_cpy++;
					}

					_capacity = _required_capacity(n);
					_size = n;
					_begin = _alloc.allocate(_capacity);
					pointer _begin_cpy = _begin;
					
					for ( ; first < last; first++)
					{
						*_begin_cpy = (T)*first;
						_begin_cpy++;
					}

				}

				vector( const vector &cpy )
				{
					_alloc = cpy._alloc;
					_capacity = cpy._capacity;
					_size = cpy._size;
					_begin = _alloc.allocate(_capacity);

					for (size_type n = 0; n < _size; n++)
						(*this)[n] = cpy[n];
				};

				vector &operator=( const vector &cpy)
				{
					if (_begin)
						_alloc.dealloc(_begin, _capacity);
					_alloc = cpy._alloc;
					_capacity = cpy._capacity;
					_size = cpy._size;
					_begin = _alloc.allocate(_capacity);

					for (size_type n = 0; n < _size; n++)
						(*this)[n] = cpy[n];
					return (*this);
				};

				//////////DESTRUCTOR//////////
				~vector( void )
				{
					_alloc.deallocate(_begin, _capacity);
				};

				//////////ITERATORS///////////
				iterator		begin() { return (iterator(_begin));};
				const_iterator	begin() const { return (const_iterator(_begin));};
				iterator		end() { return (iterator(_begin + _size));};
				const_iterator	end() const { return (const_iterator(_begin + _size));};
						
				reverse_iterator		rbegin() { return (reverse_iterator(_begin + _size));};
				const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_begin + _size));};
				reverse_iterator		rend() { return (reverse_iterator(_begin));};
				const_reverse_iterator	rend() const { return (const_reverse_iterator(_begin));};

				//////////CAPACITY//////////
				size_type	size() const {return (_size);};
				size_type	max_size() const {return (_alloc.max_size());};
				void		resize(size_type n, value_type val = value_type()) {
					if (n == _size || n > this->max_size())
						return ;
					if (n < _size)
					{
						for (size_type s = n; s < _size; s++)
							(*this)[s] = value_type();
						_size = n;
					}
					else if (n <= _capacity)
					{
						for (size_type s = _size; s < n; s++)
							(*this)[s] = val;
						_size = n;
					}
					else
					{
						pointer	res = _alloc.allocate(n);
						pointer	tmp = res;
						size_t	s = 0;
						while (s < _size)
						{
							*tmp = (*this)[s];
							tmp++;
							s++;
						}
						while (s < n)
						{
							*tmp = val;
							tmp++;
							s++;
						}
						_alloc.deallocate(_begin, _capacity);
						_begin = res;
						_size = n;
						_capacity = n;
					}
				}
				size_type	capacity() const {return (_capacity);};
				bool		empty() const { return (_size == 0);};
				void		reserve(size_type n)
				{
					if (n > _capacity)
					{
						pointer	res = _alloc.allocate(n);
						pointer	tmp = res;
						for (size_type s = 0; s < _size; s++)
						{
							*tmp = (*this)[s];
							tmp++;
						}
						_alloc.deallocate(_begin, _capacity);
						_begin = res;
						_capacity = n;
					}
				}

				//////////ELEMENT ACCESS//////////
				reference	operator[](size_type n) const {return (_begin[n]);};


			private:
				allocator_type	_alloc;
				pointer			_begin;
				size_type		_size;
				size_type		_capacity;
				
				size_type	_required_capacity(size_type size, size_type min = 1)
				{
					if (size == 0)
						return (0);
					while (min < size)
					{
						min *= 2;
					}
					return (min);
				}

				//bool	_is_
		};
}

#endif
