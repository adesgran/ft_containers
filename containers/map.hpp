/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:32 by adesgran          #+#    #+#             */
/*   Updated: 2022/11/28 06:42:57 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# define RED 101
# define BLACK 42

# include "utils/pair.hpp"
# include "utils/iterator_traits.hpp"
# include "utils/iterator_tag.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/utils.hpp"

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


	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map
		{
			public :
				typedef struct s_node
				{
					ft::pair<const Key, T>	*content;
					int						color;
					struct s_node			*parent;
					struct s_node			*right;
					struct s_node			*left;

				}	node;

				typedef	Key											key_type;
				typedef	T											mapped_type;
				typedef	ft::pair<const key_type, mapped_type>		value_type;
				typedef	Compare										key_compare;
				template <bool Const = false>
					class mapIterator  //RB Tree
					{

						public:
							typedef	ft::bidirectional_iterator_tag											iterator_category;
							typedef	typename Ternary<Const, const map::value_type, map::value_type>::type	value_type;
							typedef typename Ternary<Const, const map::node, map::node						node_type;
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

							reference	operator* (void) const {return (_ptr->content);};
							pointer		operator-> (void) const {return (_ptr->content);};

							iterator	&operator++ (void) {_ptr++; return (this->next());};
							iterator	operator++ (int) {iterator res = *this; _ptr++; return (res);};
							iterator	&operator-- (void) {_ptr--; return (this->previous());};
							iterator	operator-- (int) {iterator res = *this; _ptr--; return (res);};

						private:
							node_type	*_ptr;

							iterator	next( void ) {
								node_type	*tmp = _ptr;

								if ( tmp->right != tmp->right->left )
								{
									tmp = tmp->right;
									while (tmp->left != tmp->left->left)
										tmp = tmp->left;
								}
								else
								{
									while ( tmp->parent != tmp && tmp->parent->right == tmp )	
										tmp = tmp->parent;
									tmp = tmp->parent;
								}
								return (tmp);
							};

							iterator	previous( void ) {
								node_type	*tmp = _ptr;

								if (tmp->left != tmp->left->right)
								{
									tmp = tmp->left;
									while ( tmp->right != tmp->right->right )
										tmp = tmp->right;
								}
								else
								{
									while (tmp->parent != tmp && tmp->parent->left == tmp )
										tmp = tmp->parent;
									tmp = tmp->parent;
								}
								return (tmp);
							}
					};


				class value_compare
				{
					friend class map;
					protected :
						Compare comp;
						value_compare (Compare c) : comp(c) {}
					public :
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;
						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						};
				};

				typedef	Alloc										allocator_type;
				typedef	typename allocator_type::reference			reference;
				typedef	typename allocator_type::const_reference	const_reference;
				typedef	typename allocator_type::pointer			pointer;
				typedef	typename allocator_type::const_pointer		const_pointer;
				typedef	mapIterator<>								iterator;
				typedef	mapIterator<true>							const_iterator;
				typedef	ft::reverse_iterator<mapIterator<> >		reverse_iterator;
				typedef	ft::reverse_iterator<mapIterator<true> >	const_reverse_iterator;
				typedef typename iterator::difference_type			difference_type;
				typedef	size_t										size_type;

			public :
				map() {
					_alloc = allocator_type();
					_size = 0;
					_root = NULL;
					this->_init_null_node();

				};
				~map() {}; //free all nodes

				void	print(void) {
					if (_begin) {
						printHelper(_root, "", true);
					}
				};

				//////////MODIFIERS//////////

				reference		operator[](size_type n) {return (_begin[n]);};
				ft::pair<iterator, bool> insert( const value_type & val )
				{
					reference ref(*this)[_size];
					pointer	addr = &(*this)[_size];
					_size++;
					ref = val;
					node_pointer	new_node = new node(addr);
					_root = insert_node(new_node);
					return (ft::pair<iterator, bool>(iterator(addr), true));

				};

			private :
				allocator_type	_alloc;
				size_type		_size;
				node_pointer	_root;
				node_pointer	_null;
				
				void	*_init_null_node( void )
				{
					_null = new node();

					_null->parent = _null;
					_null->left = _null;
					_null->right = _null;
					_null->color = BLACK;
					_null->content = NULL;
				}

				node	*_new_node( pointer content )
				{
					node	*res = new node();

					res->parent = _null;
					res->left = _null;
					res->right = _null;
					res->color = BLACK;
					res->content = content;
					return (res);
				}

				void	_free_all( node *nd = _null )
				{
					if ( nd->right != _null )
						this->_free_all( nd->right);
					if ( nd->left != _null )
						this->_free_all( nd->left);
					this->_free_node( nd );
				}

				void	_free_node( node *nd )
				{
					if ( nd->content )
						_alloc.deallocate(nd->content, 1);
					delete (nd);
				}

				void	printHelper(node *root, std::string indent, bool last) //TO REMOVE
				{
					if (root != _null)
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
						std::cout << root->content->first << "(" << sColor << ")" << std::endl;
						printHelper(root->left, indent, false);
						printHelper(root->right, indent, true);
					}
				};

				/*
				node	insert_node( node_pointer nde ) //TO FIX
				{
					node_pointer	x;
					node_pointer	y;

					y = _root;
					x = NULL;
					if (!y)
					{
						_root = nde;
						nde->color = BLACK;
						return (nde);
					}
					while (1)
					{
						//if (*nde == *y) //PARTICULAR CASE, TO SEE
							//return (y);
						if (nde->content < y->content)
						{
							if (y->right)
							{
								x = y;
								y = x->right;
							}
							else
							{
								y->right = nde;
								break;
							}
						}
						else
						{
							if (y->left)
							{
								x = y;
								y = x->left;
							}
							else
							{
								y->left = nde;
								break;
							}
						}
					}
					return (_root);
				};

				void	rrotate_node( node_pointer nde )
				{
					if (!nde->left)
						return ;
					node_pointer z = nde->parent;
					node_pointer y = nde->left;
					node_pointer x = nde;
					node_pointer b = nde->left->right;
					if (z)
					{
						if (z->left == x)
							z->left = y;
						else
							z->right = y;
					}
					else
						_begin = y;
					y->right = x;
					x->left = b;
					if (b)
						b->parent = x;
					x->parent = y;
					y->parent = z;
				};

				void	lrotate_node( node_pointer nde )
				{
					if (!nde->right)
						return ;
					node_pointer z = nde->parent;
					node_pointer y = nde->right;
					node_pointer x = nde;
					node_pointer b = nde->right->left;
					if (z)
					{
						if (z->left == x)
							z->left = y;
						else
							z->right = y;
					}
					else
						_begin = y;
					y->left = x;
					x->right = b;
					if (b)
						b->parent = x;
					x->parent = y;
					y->parent = z;
				};

				void	lrrotate_node( node_pointer nde )
				{
					rrotate_node(nde->left);
					lrotate(nde);
				};

				void	rlrotate_node( node_pointer nde )
				{
					lrotate_node(nde->right);
					rrotate(nde);
				};

				bool	check_tree( node_pointer nde, int &depth)
				{
					if (!nde)
						return true;
					if (!nde->parent && nde->color != BLACK)
						return false;
					if (nde->color == RED)
					{
						if ((nde->left && nde->left->color == RED) || (nde->right && nde->right->color == RED))
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
				*/
		};
};

#endif
