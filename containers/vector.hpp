/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:28:01 by adesgran          #+#    #+#             */
/*   Updated: 2023/02/22 17:59:11 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <fstream>

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

void error_log(std::string str) {
	std::ofstream file;
	file.open("out");
	file << str << std::endl;
	file.close();
};

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				/*
				template <class Vt>
					class vecIterator
				{

					public:
						typedef	Vt																			value_type;
						typedef typename ft::iterator<std::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
						typedef	typename iterator_traits<vecIterator>::difference_type								difference_type;
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

						iterator	operator+ (difference_type i) const {return (iterator(_ptr + i));};
						iterator	operator- (difference_type i) const {return (iterator(_ptr - i));};
						difference_type	operator- (const vecIterator& it) const {return (_ptr - it.getPtr());};
						iterator	&operator+= (difference_type i) {_ptr += i; return (*this);};
						iterator	&operator-= (difference_type i) {_ptr -= i; return (*this);};

						reference	operator[] (difference_type n) const {return (*(_ptr + n));};
						reference	operator* (void) const {return (*_ptr);};
						pointer		operator-> (void) const {return (_ptr);};
						
						iterator	&operator++ (void) {_ptr++; return (*this);};
						iterator	operator++ (int) {iterator res = *this; _ptr++; return (res);};
						iterator	&operator-- (void) {_ptr--; return (*this);};
						iterator	operator-- (int) {iterator res = *this; _ptr--; return (res);};

					private:
						pointer	_ptr;
				};
				*/
				typedef	T											value_type;
				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference			reference;
				typedef	typename allocator_type::const_reference	const_reference;
				typedef	typename allocator_type::pointer			pointer;
				typedef	typename allocator_type::const_pointer		const_pointer;
				typedef std::ptrdiff_t								difference_type;
				typedef	size_t										size_type;
				/*
				typedef	vecIterator<value_type>						iterator;
				typedef	vecIterator<const value_type>				const_iterator;
				*/
				typedef	T*											iterator;
				typedef	const T*									const_iterator;
				typedef	ft::reverse_iterator<iterator>				reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;


				//////////CONSTRUCTORS//////////
				explicit vector (const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _begin(NULL), _size(0), _capacity(0)
				{
					error_log("Vector contructor 1");
				};

				explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
					_alloc(alloc), _begin(NULL), _size(n), _capacity(n)
				{
					error_log("Vector contructor 2");
					
					_begin = _alloc.allocate(_capacity);
					for (size_type i = 0; i < n; i++)
						_alloc.construct( _begin + i, val );
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
						//*_begin_cpy = (T)*first;
						_alloc.construct( _begin_cpy, *first );
						_begin_cpy++;
					}

				}

				vector( const vector<T, Alloc> &cpy )
				{
					error_log("Vector contructor 4");
					_alloc = cpy._alloc;
					_capacity = cpy._capacity;
					_size = cpy._size;
					_begin = _alloc.allocate(_capacity);

					for (size_type n = 0; n < _size; n++)
						_alloc.construct( _begin + n, cpy._begin[n] );
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
					bool	change = false;
					size_type	capacity = _capacity;

					if (n < _capacity)
						change = true;

					if (n <= _size)
					{
						if (n > 2 * _size)
							reserve(n);
						else
							reserve(2 * _size);

						for (size_type i = _size; i < n; i++)
							_alloc.construct(_begin + i, val);
					}
					else if (n < _size)
					{
						for (size_type i = _size; i < n; i++)
							_alloc.destroy(_begin + i);
					}
					if (change == true)
						_capacity = capacity;
					_size = n;
				}

				size_type	capacity() const {return (_capacity);};
				bool		empty() const { return (_size == 0);};
				void		reserve(size_type n)
				{
					if ( n > _alloc.max_size() )
						throw std::length_error("vector::reserve");
					if (n > _capacity)
					{
						pointer res = _alloc.allocate( n );
						for (size_type i = 0; i < _size; i++)
							_alloc.construct( res + i, _begin[i] );
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(_begin + i);
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
					iterator	begin = this->begin();
					size_type	pos = size_type();
					while ( begin++ != position )
						pos++;
					if (_size == _capacity)
						this->reserve(_capacity+1);
						//this->reserve((_capacity == 0) ? 1 : _capacity * 2);
					//iterator	tmp = this->end();
					for ( size_type i = _size; i > pos; i-- )
					{
						_alloc.construct(_begin + i, *(_begin + i - 1));
						_alloc.destroy(_begin + i - 1);
					}
					_alloc.construct(_begin + pos, val);
					_size++;
					return (iterator(&(*this)[pos]));
				};
				void insert (iterator position, size_type n, const value_type& val)
				{
					iterator	begin = _begin;
					size_type	i = 0;

					if ( n == 0 )
						return ;
					while ( begin++ != position )
						i++;
					if ( _size + n >= _capacity )
					{
						if ( _size + n > 2 * _capacity )
							reserve( _size + n );
						else
							reserve(2 * _size);
					}
					for ( size_type pos = _size; pos > i; pos-- )
					{
						_alloc.construct( _begin + (pos + n - 1), *(_begin + pos - 1) );
						_alloc.destroy(_begin + pos - 1);
					}
					for (size_type pos = i; pos < i + n; pos++)
						_alloc.construct(_begin + pos, val);
					_size += n;
				};

				template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				{
					size_type	i = 0;
					size_type	begin = position - _begin;
					size_type	n = size_type();
					for (InputIterator it = first; it != last; it++)
						n++;
					if ( _size + n >= _capacity )
					{
						if (_capacity * 2 > n + _size)
							reserve(_size * 2);
						else
							reserve(_size + n);
					}
					while (last != first)
						insert(_begin + begin + i++, *first++);
				};

				iterator erase (iterator position)
				{
					if ( position == this->end() )
						return ( this->end() );
					_alloc.destroy( position );
					for (iterator it = position; it < this->end() - 1; it++)
					{
						_alloc.construct( it, *(it + 1));
						_alloc.destroy( it + 1 );
					}
					_size--;
					return (position);
				};
				iterator erase (iterator first, iterator last)
				{
					size_type	n = last - first;
					if ( !n ) 
						return ( first );
					for (iterator it = first; it < last; it++)
						_alloc.destroy( it );

					for (iterator it = first; it < this->end() -n; it++)
					{
						/*
						if (it + n < this->end())
							*it = *(it + n);
						else
							*it = value_type();
						std::cerr<<"Here"<<std::endl;
						*/
						_alloc.construct(it, *(it + n));
						_alloc.destroy(it + n);
					}
					_size -= n;
					//this->reserve(_size);
					//vector tmp(_size);
					//tmp = *this;
					//this->clear();
					//*this = tmp;
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
						_alloc.destroy(it);
					_size = 0;
					//_alloc.deallocate(_begin, _capacity);
					//_capacity = 0;
					//_begin = NULL;
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
