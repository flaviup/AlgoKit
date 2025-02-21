
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iterator>

template <class T>
class MyIterator: public std::iterator<std::input_iterator_tag, T>
{
  T* p;

public:
  MyIterator(T* x): p(x) {}
  MyIterator(const MyIterator& mit): p(mit.p) {}
  MyIterator& operator++ () { ++p; return *this; }
  MyIterator operator++ (int) { MyIterator tmp(*this); operator++(); return tmp; }
  bool operator== (const MyIterator& rhs) { return p == rhs.p; }
  bool operator!= (const MyIterator& rhs) { return p != rhs.p; }
  T& operator* () { return *p; }
  T* operator-> () { return p; }
};

template< class ValueType, class NodeType >
struct my_iterator
 : std::iterator< std::bidirectional_iterator_tag, ValueType > {
    ValueType &operator*() { return cur->payload; }

    template< class VT2, class NT2 >
    friend bool operator==
        ( my_iterator const &lhs, my_iterator< VT2, NT2 > const &rhs );

    // etc.

private:
    NodeType *cur;

    friend class my_container;
    my_iterator( NodeType * ); // private constructor for begin, end
};

typedef my_iterator< T, my_node< T > > iterator;
typedef my_iterator< T const, my_node< T > const > const_iterator;

#endif // __DFS_H__
