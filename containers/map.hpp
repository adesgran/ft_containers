/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:32 by adesgran          #+#    #+#             */
/*   Updated: 2023/01/18 12:34:10 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# define RED 101
# define BLACK 42

# include "utils/pair.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/utils.hpp"
# include "utils/make_pair.hpp"

namespace ft
{
	template <class Arg1, class Arg2, class Result>
		struct binary_function {
			typedef Arg1 first_argument_type;
			typedef Arg2 second_argument_type;
			typedef Result result_type;
		};
	template <class T> struct less : binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};


	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map
		{
			public :
				typedef struct s_node
				{
					ft::pair<const Key, T>	content;
					int						color;
					struct s_node			*parent;
					struct s_node			*right;
					struct s_node			*left;

					s_node(const ft::pair<const Key, T> &content): content(content), color(RED) {};
					//s_node(const struct s_node &nde) :content(nde.content), color(nde.color) {};
					const Key	&key( void ) {return (content.first);}
					T			&value( void ) {return (content.second);}

				}	node;

				typedef	Key											key_type;
				typedef	T											mapped_type;
				typedef	ft::pair<const key_type, mapped_type>		value_type;
				typedef	Compare										key_compare;


				class value_compare
				{
					public:
						friend class map;
						typedef	bool		result_type;
						typedef	value_type	first_argument_type;
						typedef	value_type	second_argument_type;

						bool	operator()( const value_type& lhs, const value_type& rhs ) const
						{
							return ( comp( lhs.first, rhs.first ) );
						}

					protected:
						Compare	comp;

						value_compare( Compare c ) : comp(c) {};

				};

				template <bool Const = false>
					class mapIterator  //RB Tree
					{
						public:
							typedef	ft::bidirectional_iterator_tag											iterator_category;
							typedef	typename Ternary<Const, const map::value_type, map::value_type>::type	value_type;
							typedef typename Ternary<Const, const map::node, map::node>::type				node_type;
							typedef	ptrdiff_t																difference_type;
							typedef	size_t																	size_type;
							typedef	value_type*																pointer;
							typedef	value_type&																reference;
							typedef	mapIterator<Const>														iterator;

							mapIterator() : _ptr(NULL) {};
							mapIterator(node_type *ptr) : _ptr(ptr) {};
							~mapIterator() {};

							node_type	*getPtr(void) const {return (_ptr);};

							iterator	operator= (iterator const & it) {_ptr = it._ptr;return (*this);};
							bool		operator== (iterator const & it) const {return (_ptr == it._ptr);};
							bool		operator!= (iterator const & it) const {return (_ptr != it._ptr);};

							reference	operator* (void) const {return (_ptr->content);}
							pointer		operator-> (void) const {return (&_ptr->content);};

							iterator	&operator++ (void) {this->next(); return ( *this );};
							iterator	operator++ (int) {iterator res = *this; this->next(); return (res);};
							iterator	&operator-- (void) {this->previous(); return ( *this );};
							iterator	operator-- (int) {iterator res = *this; this->previous(); return (res);};

						private:
							node_type	*_ptr;

							void	next( void ) {
								if ( _ptr == _ptr->left )
									return ;
								if ( _ptr->right != _ptr->right->left )
								{
									_ptr = _ptr->right;
									while (_ptr->left != _ptr->left->left)
										_ptr = _ptr->left;
								}
								else
								{
									while ( _ptr->parent != _ptr && _ptr->parent->right == _ptr )	
										_ptr = _ptr->parent;
									_ptr = _ptr->parent;
								}
							};

							void	previous( void ) {
								if (_ptr->left != _ptr->left->left )
								{
									_ptr = _ptr->left;
									while ( _ptr->right != _ptr->right->left )
										_ptr = _ptr->right;
								}
								else
								{
									while (_ptr->parent != _ptr && _ptr->parent->left == _ptr )
										_ptr = _ptr->parent;
									_ptr = _ptr->parent;
								}
							}
					};

				typedef	typename Alloc::template rebind<node>::other	allocator_type;
				typedef	typename allocator_type::reference				reference;
				typedef	typename allocator_type::const_reference		const_reference;
				typedef	typename allocator_type::pointer				pointer;
				typedef	typename allocator_type::const_pointer			const_pointer;
				typedef	mapIterator<false>								iterator;
				typedef	mapIterator<true>								const_iterator;
				typedef	ft::reverse_iterator<mapIterator<false> >			reverse_iterator;
				typedef	ft::reverse_iterator<mapIterator<true> >		const_reverse_iterator;
				typedef typename iterator::difference_type				difference_type;
				typedef	size_t											size_type;

			public :
				//////////MEMBER FUNCTIONS//////////
				
				explicit	map( const key_compare &comp = key_compare(), 
						const allocator_type& alloc = allocator_type() ) : _compare(comp) , _alloc(alloc) {
					this->_init_null_node();
				};

				template <class InputIterator>  
						map ( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), 
						const allocator_type& alloc = allocator_type() ) : _compare(comp), _alloc(alloc) {
					this->_init_null_node();
					this->insert<InputIterator>(first, last);
				};
				
				map ( const map &other ) : _compare(other._compare), _alloc(other._alloc)
				{
					this->_init_null_node();
					this->insert(other.begin(), other.end());
				}

				map	&operator=(const map& x)
				{
					clear();
					this->insert(x.begin(), x.end());
					return (*this);
				}

				~map() {clear();_free_node(_null);};
													 
				allocator_type	get_allocator ( void ) const
				{
					return (allocator_type());
				}

				void	print(void) {
					if ( _null != _null->right )
						printHelper(_null->right, "", true);
				};

				//////////ITERATORS//////////

				iterator	begin( void ) {
					node	*res = _null->right;
					while ( res->left != res->left->left )
						res = res->left;
					return (iterator( res ));
				}
					
				const_iterator	begin( void ) const {
					node	*res = _null->right;
					while ( res->left != res->left->left )
						res = res->left;
					return (const_iterator( res ));
				}

				iterator	end( void ) {
					return ( iterator(_null) );
				}

				const_iterator	end( void ) const {
					return ( const_iterator( _null ) );
				}
					
				reverse_iterator	rbegin( void ) {
					return ( reverse_iterator(_null) );
				}

				const_reverse_iterator	rbegin( void ) const {
					return ( const_reverse_iterator( _null ) );
				}

				reverse_iterator	rend( void ) {
					node	*res = _null->right;
					while ( res->left != res->left->left )
						res = res->left;
					return (reverse_iterator( res ));
				}
					
				const_reverse_iterator	rend( void ) const {
					node	*res = _null->right;
					while ( res->left != res->left->left )
						res = res->left;
					return (const_reverse_iterator( res ));
				}

				//////////CAPACITY//////////

				bool empty( void ) const {
					return ( _null != _null->right ? false : true );
				}

				size_type	size( void ) const {
					return ( _get_size(_null->right) );
				}

				size_type	max_size( void ) const {

					std::allocator<node> al;
					return ( _alloc.max_size());
				}

				//////////ELEMENT ACCESS//////////

				mapped_type	&operator[]( const key_type &k )
				{
					iterator	res = (this->insert(ft::make_pair(k,mapped_type()))).first;
					return (res->second);
				}

				mapped_type	&at( const key_type &k )
				{
					iterator	res = (this->insert(ft::make_pair(k,mapped_type()))).first;
					return (res->second);
				}

				const mapped_type	&at( const key_type &k ) const
				{
					iterator	res = find(k);
					if ( k != end() )
						return (k->second);
					throw ( std::out_of_range ("Out of Range") );
				}

				//////////MODIFIERS//////////

				ft::pair<iterator, bool> insert( const value_type & val )
				{
					node	*nde = _new_node( val );
					node	*res = insert_node( nde );
					if ( res != nde )
						_free_node(nde);
					return (ft::pair<iterator, bool>(iterator(res), true));
				};

				iterator	insert(iterator position, const value_type & val )
				{
					ft::pair<iterator, bool> res = this->insert(position, val);
					return (res.first);
				}

				template <class InputIterator> void insert (InputIterator first, InputIterator last)
				{
					while ( first != last )
					{
						node	*nde = _new_node( *first );
						node	*res = insert_node( nde );
						if (res != nde )
							_free_node(nde);
						first++;
					}
				}

				void	erase( iterator position )
				{
					remove_node( get_node( position->first ) );
				}

				size_type	erase ( const key_type& k )
				{
					node	*nde = get_node( k );
					if ( !nde )
						return 0;
					remove_node( nde );
					return ( 1 );
				}

				void erase ( iterator first, iterator last )
				{
					iterator	next;

					while ( first != last )
					{
						next = first;
						next++;
						erase( first );
						first = next;
					}
				}

				void	swap ( map & x )
				{
					node * tmp = _null;
					_null = x._null;
					x._null = tmp;
				}

				void	clear( void )
				{
					_free_all( _null->right );
					_null->right = _null;
				}

				//////////LOOKUP//////////

				size_type	count( const Key &key ) const
				{
					node	*tmp = _null->right;
					while ( tmp != tmp->left )
					{
						if ( key_compare(key, tmp->content.first) == false && key_compare(tmp->content.first, key) == false )
							return (1);
						if (key_compare(key, tmp->content.first))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return (0);
				}

				iterator find( const Key & key )
				{
					Compare	comp;
					node	*tmp = _null->right;
					while ( tmp != tmp->left )
					{
						if ( comp(key, tmp->content.first) == false && comp(tmp->content.first, key) == false )
							return ( iterator(tmp) );
						if (comp(key, tmp->content.first))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ( this->end() );
				}

				const_iterator find( const Key & key ) const
				{
					node	*tmp = _null->right;
					while ( tmp != tmp->left )
					{
						if ( key_compare(key, tmp->content.first) == false && key_compare(tmp->content.first, key) == false )
							return ( const_iterator(tmp) );
						if (key_compare(key, tmp->content.first))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return ( this->end() );
				}

				ft::pair<iterator, iterator> equal_rangel( const Key & key ) 
				{
					return ( ft::pair<iterator, iterator>( lower_bound( key ), upper_bound( key ) ) );
				}

				ft::pair<const_iterator, const_iterator> equal_range( const Key & key ) const
				{
					return ( ft::pair<const_iterator, const_iterator>( lower_bound( key ), upper_bound( key ) ) );
				}

				iterator	lower_bound( const Key &key )
				{
					node	*tmp = _null->right;

					while ( tmp != tmp->left )
					{
						if ( key_compare()( key, tmp->content.first ) == false && key_compare()( tmp->content.first, key ) == false )
							return ( iterator( tmp ) );
						else if ( key_compare()( key, tmp->content.first ) )
						{
							if ( tmp->left == _null )
								return ( iterator( tmp ) );
							tmp = tmp->left;
						}
						else
						{
							if ( tmp->right == _null )
								return ( ++iterator( tmp ) );
							tmp = tmp->right;
						}
					}
					return ( iterator( _null ) );
				}

				const_iterator	lower_bound( const Key &key ) const
				{
					node	*tmp = _null->right;

					while ( tmp != tmp->left )
					{
						if ( key_compare( key, tmp->content.first ) == false && key_compare( tmp->content.first, key ) == false )
							return ( const_iterator( tmp ) );
						else if ( key_compare( key, tmp->content.first ) )
						{
							if ( tmp->left == _null )
								return ( const_iterator( tmp ) );
							tmp = tmp->left;
						}
						else
						{
							if ( tmp->right == _null )
								return ( ++const_iterator( tmp ) );
							tmp = tmp->right;
						}
					}
					return ( const_iterator( _null ) );
				}

				iterator	upper_bound( const Key &key )
				{
					iterator	res = lower_bound( key );

					if ( key_compare( key, res->first ) == false && key_compare( res->first, key ) == false )
						res++;

					return ( res );
				}

				const_iterator	upper_bound( const Key &key ) const
				{
					const_iterator	res = lower_bound( key );

					if ( key_compare( key, res->first ) == false && key_compare( res->first, key ) == false )
						res++;

					return ( res );
				}

				//////////OBSERVERS//////////

				key_compare	key_comp() const
				{
					return (key_compare());
				};

				value_compare	value_comp() const
				{
					return (value_compare());
				};

			private :
				value_compare	_compare;
				allocator_type	_alloc;
				node			*_null;
				
				void	_init_null_node( void )
				{
					_null = _new_node();
					_null->color = BLACK;
					_null->parent = _null;
					_null->left = _null;
					_null->right = _null;
				}

				node	*_new_node( const value_type &content = value_type() )
				{
					node	*res = _alloc.allocate(1);
					node	tmp(content);

					tmp.parent = _null;
					tmp.left = _null;
					tmp.right = _null;
					_alloc.construct(res, tmp);
					return (res);
				}

				void	_free_all( node *nd )
				{
					if ( nd->right != _null )
						this->_free_all( nd->right);
					if ( nd->left != _null )
						this->_free_all( nd->left);
					if (nd != _null)
						this->_free_node( nd );
				}

				void	_free_node( node *nd )
				{
					_alloc.deallocate(nd, 1);
				}

				bool	_equal( node *lhs, node *rhs ) const
				{
					return ( _compare(lhs->content, rhs->content) == false && _compare(rhs->content, lhs->content) == false );
				}

				bool	_inferior( node *lhs, node *rhs ) const
				{
					return ( _compare(lhs->content, rhs->content) );
				}

				bool	_superior( node *lhs, node *rhs ) const
				{
					return ( _compare(rhs->content, lhs->content) );
				}

				bool	_equal( value_type lhs, value_type rhs ) const
				{
					return ( _compare(lhs, rhs) == false && _compare(rhs, lhs) == false );
				}

				bool	_inferior( value_type lhs, value_type rhs ) const
				{
					return ( _compare(lhs, rhs) );
				}

				bool	_superior( value_type lhs, value_type rhs ) const
				{
					return ( _compare(rhs, lhs) );
				}

				//////////OTHERS//////////

				void	printHelper(node *root, std::string indent, bool last) //TO REMOVE
				{
					if ( root != _null )
					{
						std::cout << indent;
						if (last) {
							std::cout << "R----";
							indent += "   ";
						}
						else
						{
							std::cout << "L----";
							indent += "|  ";
						}
						std::string sColor = root->color == RED ? "RED" : "BLACK";
						std::string Color = root->color == RED ? "\033[0;31m" : "\033[0;37m";
						std::cout << Color << root->content.first << "(" << sColor << ")\033[0m" << std::endl;
						printHelper(root->left, indent, false);
						printHelper(root->right, indent, true);
					}
				}

				size_t	_get_size( node * nde ) const
				{
					if ( nde == _null )
						return ( 0 );
					return ( 1 + _get_size(nde->right) + _get_size(nde->left) );
				}

				node	*get_node( key_type key )
				{
					node	*res = _null->right;
					value_type	val(key, mapped_type() );

					while ( res != _null )
					{
						if ( _inferior( res->content, val ) )
							res = res->right;
						else if ( _superior( res->content, val ) )
							res = res->left;
						else
							break;
					}
					return ( res );
				}

				void	rrotate_node( node *nde )
				{
					if (!nde->left)
						return ;
					node *z = nde->parent;
					node *y = nde->left;
					node *x = nde;
					node *b = nde->left->right;
					if (z->left == x)
						z->left = y;
					else
						z->right = y;
					y->right = x;
					x->left = b;
					if (b)
						b->parent = x;
					x->parent = y;
					y->parent = z;
				};

				void	lrotate_node( node *nde )
				{
					if (!nde->right)
						return ;
					node *z = nde->parent;
					node *y = nde->right;
					node *x = nde;
					node *b = nde->right->left;
					if (z->left == x)
						z->left = y;
					else
						z->right = y;
					y->left = x;
					x->right = b;
					if (b)
						b->parent = x;
					x->parent = y;
					y->parent = z;
				};

				void	lrrotate_node( node *nde )
				{
					rrotate_node(nde->left);
					lrotate(nde);
				};

				void	rlrotate_node( node *nde )
				{
					lrotate_node(nde->right);
					rrotate(nde);
				};

				bool	check_tree( node *nde, int &depth)
				{
					if (nde == _null)
						return true;
					if (nde->parent == _null && nde->color != BLACK)
						return false;
					if (nde->color == RED)
					{
						if ((nde->left != _null && nde->left->color == RED) || (nde->right != _null && nde->right->color == RED))
							return false;
					}
					else if (nde->color == BLACK)
						depth++;
					else
						return false;


					int d1 = depth;
					int d2 = depth;
					if ( !check_tree(nde->left, d1) || !check_tree(nde->right, d2) || d1 != d2)
						return false;
					depth = d1;
					return true;
				};

				void	insert_fix( node *nde )
				{
					node	*tmp;

					while ( nde->parent->color == RED )
					{
						if ( nde->parent == nde->parent->parent->right )
						{
							tmp = nde->parent->parent->left;
							if ( tmp->color == RED )
							{
								tmp->color = BLACK;
								nde->parent->color = BLACK;
								nde->parent->parent->color = RED;
								nde = nde->parent->parent;
							}
							else
							{
								if ( nde == nde->parent->left )
								{
									nde = nde->parent;
									rrotate_node(nde);
								}
								nde->parent->color = BLACK;
								nde->parent->parent->color = RED;
								lrotate_node( nde->parent->parent );
							}
						}
						else
						{
							tmp = nde->parent->parent->right;

							if ( tmp->color == RED )
							{
								tmp->color = BLACK;
								nde->parent->color = BLACK;
								nde->parent->parent->color = RED;
								nde = nde->parent->parent;
							}
							else
							{
								if (nde == nde->parent->right)
								{
									nde = nde->parent;
									lrotate_node( nde );
								}
								nde->parent->color = BLACK;
								nde->parent->parent->color = RED;
								rrotate_node( nde->parent->parent );
							}
						}
						if ( nde->parent == _null )
							break;
					}
					_null->right->color = BLACK;
					_null->parent = _null;
				};

				node	*insert_node( node *nde )
				{
					node	*y;

					y = _null;
					if ( y->right == y )
					{
						y->right = nde;
						nde->color = BLACK;
						return (nde);
					}
					y = y->right;
					while (1)
					{
						if ( _equal( nde, y ) ) 
							return ( y );
						else if ( _inferior( y, nde ) )
						{
							if ( y->right != _null )
								y = y->right;
							else
							{
								y->right = nde;
								nde->parent = y;
								break;
							}
						}
						else
						{
							if ( y->left != _null )
								y = y->left;
							else
							{
								y->left = nde;
								nde->parent = y;
								break;
							}
						}
					}
					insert_fix(nde);
					return (nde);
				};

				void	transplant_node( node *parent, node *child, node *new_child )
				{
					if ( parent->left == child )
					{
						parent->left = new_child;
						if ( new_child )
							new_child->parent = parent;
						child->parent = _null;
					}
					else if ( parent->right == child )
					{
						parent->right = new_child;
						if ( new_child )
							new_child->parent = parent;
						child->parent = _null;
					}
				}

				void	remove_node( node * nde ) //WIP
				{
					int y_originalColor = nde->color;
					node	* x;
					node	* y;
					node	* z;

					z = nde;
					y = z;
					x = z;

					if ( nde->left == _null )
					{
						x = nde->right;
						transplant_node( nde->parent, nde, nde->right);
					}
					else if ( nde->right== _null )
					{
						x = nde->left;
						transplant_node( nde->parent, nde, nde->left);
					}
					else
					{
						y = z->right;
						while ( y->left != _null )
							y = y->left;
						y_originalColor = y->color;
						x = y->right;
						if ( y->parent == z )
							x->parent = y;
						else
						{
							transplant_node( y->parent, y, y->right );
							y->right = z->right;
							y->right->parent = y;
						}
						transplant_node( z->parent, z, y );
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					_alloc.deallocate( z, 1 );
					if ( y_originalColor == BLACK )
						remove_fix(x);
				};

				void	remove_fix( node * x )
				{
					node	*s;
					while ( x != _null->right  && x->color == BLACK )
					{
						if ( x == x->parent->left )
						{
							s = x->parent->right;
							if ( s->color == RED )
							{
								s->color = BLACK;
								x->parent->color = 1;
								lrotate_node( x->parent );
								s = x->parent->right;
							}
							if ( s->left->color == BLACK && s->right->color == BLACK )
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if ( s->right->color == BLACK )
								{
									s->left->color = BLACK;
									s->color = RED;
									rrotate_node(s);
									s = x->parent->right;
								}
								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->right->color = BLACK;
								lrotate_node( x->parent );
								x = _null->right;
							}
						}
						else
						{
							s = x->parent->left;
							if ( s->color == RED )
							{
								s->color = BLACK;
								x->parent->color = RED;
								rrotate_node(x->parent);
								s = x->parent->left;
							}
							if (s->right->color == BLACK)
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if (s->left->color == BLACK)
								{
									s->right->color = BLACK;
									s->color = RED;
									lrotate_node(s);
									s = x->parent->left;
								}
								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->left->color = BLACK;
								rrotate_node(x->parent);
								x = _null->right;
							}
						}
					}
					x->color = BLACK;
				}
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			if ( lhs.size() != rhs.size() )
				return ( false );
			return ( ft::equal (lhs.begin(), lhs.end(), rhs.begin()) );
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return ( !(lhs == rhs) );
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return ( rhs < lhs );
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return ( !( lhs > rhs ) );
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
		{
			return ( !( lhs < rhs ) );
		}
}

#endif
