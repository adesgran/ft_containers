/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2023/02/15 14:46:36 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP


# include <iostream>
# include <string>
# include <iterator>
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/utils.hpp"

void error_log(std::string str) { std::cerr << str << std::endl;};

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				template <class Vt>
					class vecIterator
				{

					public:
						typedef	Vt																			value_type;
						typedef typename ft::iterator<std::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
						typedef	ptrdiff_t																	difference_type;
						typedef	value_type*																	pointer;
						typedef	value_type&																	reference;
						typedef	vecIterator																	iterator;

						vecIterator() : _ptr(NULL) {};
						vecIterator( vecIterator const & it ) : _ptr( it.getPtr() ) {};
						vecIterator(pointer const ptr) : _ptr(ptr) {};
						//vecIterator(const vecIterator<Const> &it) : _ptr(it._ptr) {};
						~vecIterator() {};

						operator	vecIterator<const Vt> () {
							return (vecIterator<const Vt>(_ptr));
						}

						pointer	getPtr(void) const {return (_ptr);};

						iterator	operator= (iterator const & it) {_ptr = it._ptr;return (*this);};
						bool		operator== (vecIterator const & it) const {return (_ptr == it._ptr);};
						bool		operator!= (vecIterator const & it) const {return (_ptr != it._ptr);};
						bool		operator> (vecIterator const & it) const {return (_ptr > it._ptr);};
						bool		operator>= (vecIterator const & it) const {return (_ptr >= it._ptr);};
						bool		operator< (vecIterator const & it) const {return (_ptr < it._ptr);};
						bool		operator<= (vecIterator const & it) const {return (_ptr <= it._ptr);};

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
				typedef	vecIterator<value_type>						iterator;
				typedef	vecIterator<const value_type>				const_iterator;
				typedef	ft::reverse_iterator<iterator>				reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef typename iterator::difference_type			difference_type;
				typedef	size_t										size_type;


				//////////CONSTRUCTORS//////////
				explicit vector (const allocator_type& alloc = allocator_type())
				{
					error_log("Vector contructor 1");
					_alloc = alloc;
					_begin = NULL;
					_size = 0;
					_capacity = 0;
					
				};

				explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				{
					error_log("Vector contructor 2");
					
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
					error_log("Vector contructor 3");
					_alloc = alloc;

					if (last == first) //ancient : last <= first
					{
						_size = 0;
						_capacity = 0;
						_begin = NULL;
						return ;
					}
					size_type n = difference(first, last);//last - first;

					_capacity = n;
					_size = n;
					_begin = _alloc.allocate(_capacity);
					pointer _begin_cpy = _begin;
					
					for ( ; first != last; first++)
					{
						*_begin_cpy = (T)*first;
						_begin_cpy++;
					}

				}

				vector( const vector &cpy )
				{
					error_log("Vector contructor 4");
					_alloc = cpy._alloc;
					_capacity = cpy._capacity;
					_size = cpy._size;
					_begin = _alloc.allocate(_capacity);

					for (size_type n = 0; n < _size; n++)
						(*this)[n] = cpy[n];
				};

				vector &operator=( const vector &cpy )
				{
					error_log("Vector copy operator");
					if (cpy._size > _capacity)
					{
						error_log("Cond 1");
						if (_begin)
							_alloc.deallocate(_begin, _capacity);
						_alloc = cpy._alloc;
						_capacity = cpy._size;
						_size = cpy._size;
						_begin = _alloc.allocate(_capacity);

						for (size_type n = 0; n < _size; n++)
						{
							error_log("Loop1");
							(*this)[n] = cpy[n];
						}
					}
					else
					{
						error_log("Cond 2");
						_size = cpy._size;
						for (size_type n = 0; n < _size; n++)
						{
							error_log("Loop2");
							(*this)[n] = cpy[n];
						}
					}
					error_log("Vector copy operator End");
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
				reference		operator[](size_type n) {return (_begin[n]);};
				const_reference	operator[](size_type n) const {return (_begin[n]);};
				reference		at(size_type n) 
				{ 
					if (n >= _size)
						throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
					return ((*this)[n]);
				};
				const_reference	at(size_type n) const
				{ 
					if (n >= _size)
						throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
					return ((*this)[n]);
				};
				reference		front() { return (*_begin);};
				const_reference	front() const { return (*_begin);};
				reference		back() { return ((_size > 1) ? (*this)[_size - 1] : *_begin);};
				const_reference	back() const { return ((_size > 1) ? (*this)[_size - 1] : *_begin);};
				pointer			data() { return (_begin);};
				const_pointer	data() const { return (_begin);};

				//////////MODIFIERS//////////
				template <class InputIterator>  void assign (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				{
					vector tmp(first, last);
					tmp._alloc = _alloc;
					*this = tmp;
				};
				void assign (size_type n, const value_type& val)
				{
					vector tmp(n, val, _alloc);
					*this = tmp;
				};

				void push_back (const value_type& val)
				{
					if (_size == _capacity)
					{
						vector tmp(*this);
						*this = (_capacity == 0) ? vector(1) : vector(_capacity * 2);
						*this = tmp;
					}
					(*this)[_size] = val;
					_size++;
				};
				void	pop_back ( void )
				{
					if (_size)
					{
						(*this)[_size - 1] = value_type();
						_size--;
					}
				};

				iterator insert (iterator position, const value_type& val) //NEED TO SEGFAULT IF (POSITION ++ THIS->END())
				{
					error_log("Insert 1");
					if (_size == _capacity)
					{
						vector tmp(*this);
						*this = (_capacity == 0) ? vector(1) : vector(_capacity * 2);
						*this = tmp;
					}
					iterator	tmp = this->end();
					while (tmp > position)
					{
						*tmp = *(tmp - 1);
						tmp--;
					}
					*position = val;
					_size++;
					return (position);
				};
				void insert (iterator position, size_type n, const value_type& val)
				{
					error_log("Insert 2");
					iterator	tmp = position;
					for (size_type s = 0; s < n && tmp != iterator(); s++)
						tmp = this->insert(tmp, val);
				};
				template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				{
					error_log("Insert 3");
					iterator	tmp = position;
					for (InputIterator it = first; it != last; it++)
						tmp = this->insert(tmp, *it);
				};

				iterator erase (iterator position)
				{
					for (iterator it = position; it < this->end() - 1; it++)
						*it = *(it + 1);
					*(this->end() - 1) = value_type();
					_size--;
					return (position);
				};
				iterator erase (iterator first, iterator last)
				{
					size_type	n = last - first;
					for (iterator it = first; it < this->end(); it++)
					{
						if (it + n < this->end().getPtr())
							*it = *(it + n);
						else
							*it = value_type();
					}
					_size -= n;
					return (first);

				};

				void swap (vector& x)
				{
					allocator_type	talloc = x._alloc;
					pointer			tbegin = x._begin;
					size_type		tsize = x._size;
					size_type		tcapacity = x._capacity;

					x._alloc = _alloc;
					x._begin = _begin;
					x._size = _size;
					x._capacity = _capacity;

					_alloc = talloc;
					_begin = tbegin;
					_size = tsize;
					_capacity = tcapacity;
				}

				void clear()
				{
					for (iterator it = this->begin(); it < this->end(); it++)
						*it = value_type();
					_size = 0;
				};
				 
				//////////ALLOCATOR//////////
				allocator_type get_allocator() const {return (_alloc);};



			private:
				allocator_type	_alloc;
				pointer			_begin;
				size_type		_size;
				size_type		_capacity;

				template < class InputIterator >
					difference_type	difference( InputIterator begin, InputIterator end )
					{
						difference_type	res = difference_type();
						while ( begin != end )
						{
							res++;
							begin++;
						}
						return (res);
					}
				

		};

	template< class T, class Alloc >
		bool operator==( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			if ( lhs.size() != rhs.size() )
				return ( false );
			return ( ft::equal (lhs.begin(), lhs.end(), rhs.begin()) );
		}

	template< class T, class Alloc >
		bool operator!=( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			return ( !(lhs == rhs) );
		}

	template< class T, class Alloc >
		bool operator<( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
		}

	template< class T, class Alloc >
		bool operator>( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			return ( rhs < lhs );
		}

	template< class T, class Alloc >
		bool operator<=( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			return ( !( lhs > rhs ) );
		}

	template< class T, class Alloc >
		bool operator>=( const vector< T, Alloc >& lhs,
				const vector< T, Alloc >& rhs )
		{
			return ( !( lhs < rhs ) );
		}

}

#endif
