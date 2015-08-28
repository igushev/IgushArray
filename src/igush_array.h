/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    The IgushArray class totally implements std::vector interface.
    IgushArray class totally provides iterator mechanism,
    but this mechanism does not guarantee an iterator consistence after modifying operations
    such as insert/erase, push back/pop back and so on.

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _IgushArray_h
#define _IgushArray_h

#define USE_FIXED_DEQUE

#include <vector>
#ifdef USE_FIXED_DEQUE
#include "fixed_deque.h"
#else
#endif
#include <deque>
#include <iterator>
#include <math.h>
#include "size_helper.h"

template <class T, class Alloc = std::allocator<T> >
class IgushArray {

    #ifdef USE_FIXED_DEQUE
    typedef FixedDeque<T, Alloc> DeqT;
    #else
    typedef std::deque<T, Alloc> DeqT;
    #endif
    typedef typename DeqT::iterator DeqTIter;
    typedef typename DeqT::const_iterator DeqTConstIter;
    typedef DeqT* DeqTPtr; 

    typedef std::vector<DeqTPtr> DeqTPtrVec;
    typedef typename DeqTPtrVec::iterator DeqTPtrVecIter;
    typedef typename DeqTPtrVec::const_iterator DeqTPtrVecConstIter;
    typedef DeqTPtrVec* DeqTPtrVecPtr;

    typedef IgushArray<T, Alloc>* IgushArrayTPtr;
    typedef const IgushArray<T, Alloc>* IgushArrayTConstPtr;
    
    class OneValueIterator {
    
    public:

        typedef std::random_access_iterator_tag iterator_category;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;

        OneValueIterator(int n, const T& value):  _n(n), _value(value) {}

        inline OneValueIterator& operator++()
            { ++_n; return *this; }
        inline OneValueIterator operator++(int)
            { OneValueIterator ovi = *this; ++*this; return ovi; }
        inline OneValueIterator& operator--()
            { --_n; return *this; }
        inline OneValueIterator operator--(int)
            { OneValueIterator ovi = *this; --*this; return ovi; }

        inline OneValueIterator& operator+=(difference_type incr)
            { _n += incr; return *this; }
        inline OneValueIterator operator+(difference_type incr) const
            { OneValueIterator ovi = *this; ovi += incr; return ovi; }
        inline OneValueIterator& operator-=(difference_type decr)
            { _n -= decr; return *this; }
        inline OneValueIterator operator-(difference_type decr) const
            { OneValueIterator ovi = *this; ovi -= decr; return ovi; }

        inline difference_type operator-(const OneValueIterator& ovi) const
            { return _n - ovi._n; }

        inline const T& operator*() const
            { return _value; }
        inline const T* operator->() const
            { return &_value; }

        inline bool operator==(const OneValueIterator& ovi) const
            { return _n == ovi._n; }
        inline bool operator!=(const OneValueIterator& ovi) const
            { return !(*this == ovi); }
        inline bool operator<(const OneValueIterator& ovi) const
            { return _n < ovi._n; }
        inline bool operator<=(const OneValueIterator& ovi) const
            { return (*this < ovi || *this == ovi); }
        inline bool operator>(const OneValueIterator& ovi) const
            { return _n > ovi._n; }
        inline bool operator>=(const OneValueIterator& ovi) const
            { return (*this > ovi || *this == ovi); }

    private:

        size_type _n;
        const T& _value;
    };

public:

    enum ReserveMode {NO, IF_NEEDED, YES};

    typedef Alloc allocator_type;

    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::difference_type difference_type;
    typedef T value_type;
    typedef const T const_value_type;

    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;

    template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
    class IgushArrayIterator {

        typedef IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter> Self;
        typedef IgushArrayIterator<const T, IgushArrayTConstPtr, DeqTPtrVecConstIter, DeqTConstIter> SelfConst;

        IgushArrayIterator(IgushArrayPtr ia, VecIter vec_it, DeqIter deq_it)
            :_ia(ia), _vec_it(vec_it), _deq_it(deq_it) {}
    
    public:

        typedef std::random_access_iterator_tag iterator_category;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef U value_type;
        typedef U& reference;
        typedef U* pointer;

        Self& operator++();
        Self operator++(int);
        Self& operator--();
        Self operator--(int);

        Self& operator+=(difference_type);
        Self operator+(difference_type) const;
        Self& operator-=(difference_type);
        Self operator-(difference_type) const;

        difference_type operator-(const Self& iai) const;

        inline U& operator*()
            { return *_deq_it; }
        inline U* operator->()
            { return &(*_deq_it); }

        inline bool operator==(const Self& iai) const
            { return _vec_it == iai._vec_it && _deq_it == iai._deq_it; }
        inline bool operator!=(const Self& iai) const
            { return !(*this == iai); }
        inline bool operator<(const Self& iai) const
            { return (_vec_it < iai._vec_it) || (_vec_it == iai._vec_it && _deq_it < iai._deq_it); }
        inline bool operator<=(const Self& iai) const
            { return (*this < iai || *this == iai); }
        inline bool operator>(const Self& iai) const
            { return (_vec_it > iai._vec_it) || (_vec_it == iai._vec_it && _deq_it > iai._deq_it); }
        inline bool operator>=(const Self& iai) const
            { return (*this > iai || *this == iai); }

        inline operator SelfConst()
            { return SelfConst(_ia, _vec_it, _deq_it); }

    private:

        IgushArrayPtr _ia;
        VecIter _vec_it;
        DeqIter _deq_it;

        friend class IgushArray<T, Alloc>;
    };

    typedef IgushArrayIterator<T, IgushArrayTPtr, DeqTPtrVecIter, DeqTIter> iterator;
    typedef IgushArrayIterator<const T, IgushArrayTConstPtr, DeqTPtrVecConstIter, DeqTConstIter> const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    
    explicit IgushArray(const Alloc& a = Alloc());
    explicit IgushArray(size_type n, const T& value = T(), const Alloc& a = Alloc());
    template <class InputIterator>
    IgushArray(InputIterator first, InputIterator last, const Alloc& a = Alloc());
    IgushArray(IgushArray<T, Alloc>& ia);
    ~IgushArray();
    void operator=(IgushArray<T, Alloc>& ia) { IgushArray<T, Alloc>(ia).swap(*this); }
    
    inline bool empty() const
        { return (_v->size() == 1 && _v->back()->empty()); }
    inline size_type size() const
        { return (_v->size()?((_v->size() - 1)*_deq_size + _v->back()->size()):0); }
    void resize(size_type n, const T& value = T(), ReserveMode reserve_mode = NO);
    inline size_type capacity() const
        { return _capacity; }
    void reserve(size_type n);

    inline iterator begin()
        { return iterator(this, _v->begin(), _v->front()->begin()); }
    inline const_iterator begin() const
        { return const_iterator(this, _v->begin(), _v->front()->begin()); }
    inline iterator end()
        { return iterator(this, _v->end() - 1, _v->back()->end()); }
    inline const_iterator end() const
        { return const_iterator(this, _v->end() - 1, _v->back()->end()); }

    inline reverse_iterator rbegin()
        { return reverse_iterator(end()); }
    inline const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }
    inline reverse_iterator rend()
        { return reverse_iterator(begin()); }
    inline const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference at(size_type);
    const_reference at(size_type) const;

    inline reference front()
        { return _v->front()->front(); }
    inline const_reference front() const
        { return _v->front()->front(); }
    inline reference back()
        { return _v->back()->back(); }
    inline const_reference back() const
        { return _v->back()->back(); }

    void assign(size_type n, const T& value, ReserveMode reserve_mode = NO)
        { assign(OneValueIterator(0, value), OneValueIterator(n, value), reserve_mode); }
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last, ReserveMode reserve_mode = NO);

    void push_back(const T&);
    void pop_back();

    iterator insert(iterator, const T&);
    iterator insert(iterator it, size_type n, const T& value, ReserveMode reserve_mode = NO)
        { return insert(it, OneValueIterator(0, value), OneValueIterator(n, value), reserve_mode); }
    template <class InputIterator>
    iterator insert(iterator, InputIterator first, InputIterator last, ReserveMode reserve_mode = NO);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    
    void swap(IgushArray<T, Alloc>&);
    void clear();
    inline Alloc get_allocator()
        { return _a; }

private:

    void _reserve(size_type n);
    void _decrease_size(size_type n);
    void _delete_deques();

    template <class InputIterator>
    void _push_back(InputIterator first, InputIterator last);
    template <class InputIterator>
    void _push_back(InputIterator& first, size_type n);

    template <class InputIterator>
    iterator _fill(iterator, InputIterator first, InputIterator last);
    template <class InputIterator>
    iterator _fill(iterator, InputIterator& first, size_type n);

    size_type _capacity;
    DeqTPtrVecPtr _v;
    typename DeqT::size_type _deq_size;
    typename DeqTPtrVec::size_type _vec_size;
    Alloc _a;
};
 
template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>&
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator+=(difference_type incr)
{
    if (!incr)
        return *this;

    if (incr < 0)
        return (*this -= (-incr));

    if (incr >= (*_vec_it)->end() - _deq_it && _vec_it != _ia->_v->end()-1) {
        incr -= ((*_vec_it)->end() - _deq_it);
        ++_vec_it;

        typename DeqTPtrVec::size_type incr_vec = floor(incr/_ia->_deq_size);
        if (_vec_it + incr_vec >= _ia->_v->end())
            incr_vec = _ia->_v->end() - _vec_it - 1;

        incr -= incr_vec * _ia->_deq_size;
        _vec_it += incr_vec;
        _deq_it = (*_vec_it)->begin();
    }
    
    _deq_it += incr;
    return *this;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator+(difference_type incr) const
{
    Self temp = *this;
    temp += incr;
    return temp;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>&
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator-=(difference_type decr)
{
    if (!decr)
        return *this;

    if (decr < 0)
        return (*this += (-decr));

    if (decr > _deq_it - (*_vec_it)->begin()) {
        decr -= (_deq_it - (*_vec_it)->begin() + 1);
        --_vec_it;

        typename DeqTPtrVec::size_type decr_vec = floor(decr/_ia->_deq_size);
        if (_vec_it - decr_vec < _ia->_v->begin())
            decr_vec = _vec_it - _ia->_v->begin();

        decr -= decr_vec * _ia->_deq_size;
        _vec_it -= decr_vec;
        _deq_it = (*_vec_it)->end() - 1;
    }
    
    _deq_it -= decr;
    return *this;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator-(difference_type decr) const
{
    Self temp = *this;
    temp -= decr;
    return temp;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>&
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator++()
{
    ++_deq_it;
    if (_deq_it == (*_vec_it)->end() && _vec_it < _ia->_v->end() - 1) {
        ++_vec_it;
        _deq_it = (*_vec_it)->begin();
    }
    return *this;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator++(int)
{
    Self temp = *this;
    ++*this;
    return temp;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>&
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator--()
{
    if (_deq_it == (*_vec_it)->begin() && _vec_it != _ia->_v->begin()) {
        --_vec_it;
        _deq_it = (*_vec_it)->end();
    }
    --_deq_it;

    return *this;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>
IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator--(int)
{
    Self temp = *this;
    --*this;
    return temp;
}

template <class T, class Alloc>
template <class U, class IgushArrayPtr, class VecIter, class DeqIter>
typename IgushArray<T, Alloc>::template IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::difference_type IgushArray<T, Alloc>::IgushArrayIterator<U, IgushArrayPtr, VecIter, DeqIter>::operator-(const Self& iai) const
{
    if (*this < iai)
        return -(iai - *this);

    if (_vec_it > iai._vec_it)
        return (_vec_it - iai._vec_it - 1)*_ia->_deq_size +
            (_deq_it - (*_vec_it)->begin()) +
            ((DeqIter)(*iai._vec_it)->end() - iai._deq_it);
    else
        return (_deq_it - iai._deq_it);
}

template <class T, class Alloc>
IgushArray<T, Alloc>::IgushArray(const Alloc& a)
: _a(a)
{
    _reserve(0);
}

template <class T, class Alloc>
IgushArray<T, Alloc>::IgushArray(size_type n, const T& value, const Alloc& a)
: _a(a)
{
    _reserve(n);
    _push_back(OneValueIterator(0, value), OneValueIterator(n, value));
}

template <class T, class Alloc>
template <class InputIterator>
IgushArray<T, Alloc>::IgushArray(InputIterator first, InputIterator last, const Alloc& a)
: _a(a)
{
    size_type n = data_size(first, last);
    _reserve(n);
    _push_back(first, last);
}

template <class T, class Alloc>
IgushArray<T, Alloc>::IgushArray(IgushArray<T, Alloc>& ia)
: _a(ia._a)
{
    _reserve(ia.capacity());
    _push_back(ia.begin(), ia.end());
}

template <class T, class Alloc>
IgushArray<T, Alloc>::~IgushArray()
{
    _delete_deques();
    delete _v;
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::resize(size_type n, const T& value, ReserveMode reserve_mode)
{
    size_type current_size = size();

    if ((n > _capacity && reserve_mode) == IF_NEEDED || reserve_mode == YES) {
        //we have to recalculate sizes

        IgushArray ia;
        ia._reserve(n);
        if (n >= current_size) {     //we have to add new elements
            ia._push_back(begin(), end());
            ia._push_back(OneValueIterator(0, value), OneValueIterator(n - current_size, value));
        }
        else if (n < current_size) {    //we have to remove spare elements
            iterator first = begin();
            ia._push_back(first, n);
        }
        swap(ia);
    }
    else {

        //we have change the size only

        if (n >= current_size)       //we have to add new elements
            _push_back(OneValueIterator(0, value), OneValueIterator(n - current_size, value));
        else if (n < current_size)  //we have to remove spare elements
            _decrease_size(n);
    }
}


template <class T, class Alloc>
void IgushArray<T, Alloc>::reserve(size_type n)
{
    if (n <= _capacity)
        return;

    IgushArray ia;
    ia._reserve(n);
    ia._push_back(begin(), end());
    swap(ia);
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::reference IgushArray<T, Alloc>::operator[](size_type n)

{
    typename DeqTPtrVec::size_type vec_n = floor(n/_deq_size);
    DeqTPtr deq_ptr = _v->operator[](vec_n);
    return deq_ptr->operator[](n-vec_n*_deq_size);
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::const_reference IgushArray<T, Alloc>::operator[](size_type n) const
{
    typename DeqTPtrVec::size_type vec_n = floor(n/_deq_size);
    const DeqTPtr deq_ptr = _v->operator[](vec_n);
    return deq_ptr->operator[](n-vec_n*_deq_size);
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::reference IgushArray<T, Alloc>::at(size_type n)
{
    typename DeqTPtrVec::size_type vec_n = floor(n/_deq_size);
    DeqTPtr deq_ptr = _v->at(vec_n);
    return deq_ptr->at(n-vec_n*_deq_size);
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::const_reference IgushArray<T, Alloc>::at(size_type n) const
{
    typename DeqTPtrVec::size_type vec_n = floor(n/_deq_size);
    const DeqTPtr deq_ptr = _v->at(vec_n);
    return deq_ptr->at(n-vec_n*_deq_size);
}

template <class T, class Alloc>
template <class InputIterator>
void IgushArray<T, Alloc>::assign(InputIterator first, InputIterator last, ReserveMode reserve_mode)
{
    size_type current_size = size();
    size_type n = data_size(first, last);

    if ((n > _capacity && reserve_mode) == IF_NEEDED || reserve_mode == YES) {
        //we have to recalculate sizes

        IgushArray ia;
        ia._reserve(n);
        ia._push_back(first, last);
        swap(ia);
    }
    else {
        //we have change the size only

        if (n >= current_size) {
            _fill(begin(), first, current_size);
            _push_back(first, last);
        }
        else if (n < current_size) {
            _decrease_size(n);
            _fill(begin(), first, last);
        }
    }
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::push_back(const T& val)
{
    if (_v->back()->size() == _deq_size)
        #ifdef USE_FIXED_DEQUE
        _v->push_back(new DeqT(_deq_size, _a));
        #else
        _v->push_back(new DeqT(_a));
        #endif
    _v->back()->push_back(val);
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::pop_back()
{
    _v->back()->pop_back();
    if (_v->back()->empty() && _v->size() > 1) {
        delete _v->back();
        _v->back() = 0;
        _v->pop_back();
    }
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::insert(iterator it, const T& val)
{
    size_type result = it-begin();
    T temp1, temp2;

    //If the iterator points to end
    if (it._deq_it == (*it._vec_it)->end()) {
        temp2 = val;
    }
    //If the iterator points to last element in the deque
    else if (it._deq_it == (*it._vec_it)->end()-1) {
        temp2 = (*it._vec_it)->back();
        (*it._vec_it)->pop_back();
        (*it._vec_it)->push_back(val);
    }
    //If no, just insert new element to its place
    else {
        temp2 = (*it._vec_it)->back();
        (*it._vec_it)->pop_back();
        (*it._vec_it)->insert(it._deq_it, val);
    }

    ++it._vec_it;

    //Move the rest of elements to the end
    for (DeqTPtrVecIter _vec_it = it._vec_it; _vec_it < _v->end(); ++_vec_it) {
        temp1 = (*_vec_it)->back();
        (*_vec_it)->pop_back();
        (*_vec_it)->push_front(temp2);
        temp2 = temp1;
    }
    
    push_back(temp2);

    return begin()+result;
}

template <class T, class Alloc>
template <class InputIterator>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::insert(iterator it, InputIterator first, InputIterator last, ReserveMode reserve_mode)
{
    size_type result = it-begin();
    std::deque<T> temp1, temp2;

    //Define how many new elements should be inserted
    size_type n = data_size(first, last);

    //Define total new size
    size_type total_new_size = size() + n;
    
    if ((total_new_size > _capacity && reserve_mode == IF_NEEDED) || reserve_mode == YES) {
        //we have to recalculate sizes

        IgushArray ia;
        ia._reserve(total_new_size);
        ia._push_back(begin(), it);
        ia._push_back(first, last);
        ia._push_back(it, end());
        swap(ia);
    }
    else {
        //Define important values in it queue
        typename DeqT::size_type size_to_end = (*it._vec_it)->end() - it._deq_it;
        typename DeqT::size_type empty_to_end = _deq_size - (*it._vec_it)->size();
        typename DeqT::size_type capacity_to_end = size_to_end + empty_to_end;

        if (n > capacity_to_end) {
            //Save the end of the current deque by adding them info the temp deque
            for (size_type i = 0; i < size_to_end; ++i) {
                temp1.push_front((*it._vec_it)->back());
                (*it._vec_it)->pop_back();
            }
    
            //And fill this end with the first portion of the new elements
            for (size_type i = 0; i < capacity_to_end; ++i)
                (*it._vec_it)->push_back(*first++);
            n -= capacity_to_end;
    
            ++it._vec_it;

            //Define how many new structural deques should to be inserted and insert them
            typename DeqTPtrVec::size_type insert_vectors = floor(n/_deq_size);
            typename DeqTPtrVec::size_type cur_vec_pos = it._vec_it-_v->begin();
            _v->insert(it._vec_it, insert_vectors, 0);
            it._vec_it = _v->begin() + cur_vec_pos;

            //Fill new deques
            for (typename DeqTPtrVec::size_type vec_i = 0; vec_i < insert_vectors; ++vec_i) {
                #ifdef USE_FIXED_DEQUE
                (*it._vec_it) = new DeqT(_deq_size, _a);
                #else
                (*it._vec_it) = new DeqT(_a);
                #endif
                for (size_type i = 0; i < _deq_size; ++i)
                    (*it._vec_it)->push_back(*first++);
                ++it._vec_it;
                n -= _deq_size;
            }

            //Just add rest of the new elements to the deque
            for (size_type i = 0; i < n; ++i)
                temp1.push_front(*--last);
        }
        else {
            //Save the end of the current deque by adding them info the temp deque
            if (n > empty_to_end)
                for (size_type i = 0; i < n - empty_to_end; ++i) {
                    temp1.push_front((*it._vec_it)->back());
                    (*it._vec_it)->pop_back();
                }

            //Insert the new elements
            (*it._vec_it)->insert(it._deq_it, first, last);
    
            ++it._vec_it;
        }

        size_type move = temp1.size();

        //If the temp deque there are more elements than the structural deque size, just insert the new one
        if (move >= _deq_size) {
            #ifdef USE_FIXED_DEQUE
            it._vec_it = _v->insert(it._vec_it, new DeqT(_deq_size, _a));
            #else
            it._vec_it = _v->insert(it._vec_it, new DeqT(_a));
            #endif
            for (size_type i = 0; i < _deq_size; ++i) {
                (*it._vec_it)->push_back(temp1.front());
                temp1.pop_front(); 
            }
            ++it._vec_it;
            move -= _deq_size;
        }

        //Move the rest of elements to the end
        //Same logic as for one element
        for (DeqTPtrVecIter _vec_it = it._vec_it; _vec_it != _v->end(); ++_vec_it) {
            for (size_type i = 0; i < move && (*_vec_it)->size(); ++i) {
                temp2.push_front((*_vec_it)->back());
                (*_vec_it)->pop_back();
            }
            for (size_type i = 0; i < move; ++i) {
                (*_vec_it)->push_front(temp1.back());
                temp1.pop_back();
            }
            temp2.swap(temp1);
        }
   
        _push_back(temp1.begin(), temp1.end());
    }
    return begin()+result;
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::erase(iterator it)
{
    size_type result = it-begin();
    T temp1, temp2;

    //Move one element up
    for (DeqTPtrVecIter _vec_it = _v->end() - 1; _vec_it >= it._vec_it; --_vec_it) {
        temp1 = (*_vec_it)->front();
        if (_vec_it == it._vec_it)
            (*_vec_it)->erase(it._deq_it);
        else
            (*_vec_it)->pop_front();
        if (_vec_it != _v->end() - 1)
            (*_vec_it)->push_back(temp2);
        temp2 = temp1;
    }

    //Check last queue if it's empty
    if (_v->back()->empty() && _v->size() > 1) {
        delete _v->back();
        _v->back() = 0;
        _v->pop_back();
    }

    return begin()+result;
}

template <class T, class Alloc>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::erase(iterator it_first, iterator it_last)
{
    if (it_first >= it_last)
        return it_first;

    size_type result = it_first-begin();
    std::deque<T> temp1, temp2;

    //Define how many new elements should be erased and how many after erased
    size_type n = it_last - it_first;
    typename DeqTPtrVec::size_type erase_vectors = floor(n/_deq_size);
    size_type erase_elements = n - erase_vectors*_deq_size;
    size_type total_to_end = end() - it_last;
    size_type move = (erase_elements<total_to_end)?erase_elements:total_to_end;

    if (it_last._deq_it == (*it_last._vec_it)->begin()){
        --it_last._vec_it;
        it_last._deq_it = (*it_last._vec_it)->end();
    }

    //Move some elements up
    DeqTPtrVecIter _vec_it = _v->end() - 1;
    for (;_vec_it > it_last._vec_it; --_vec_it) {
        for (size_type i = 0; i < move && (*_vec_it)->size(); ++i) {
            temp2.push_back((*_vec_it)->front());
            (*_vec_it)->pop_front();
        }
        for (size_type i = 0; i < move && temp1.size(); ++i) {
            (*_vec_it)->push_back(temp1.front());
            temp1.pop_front();
        }
        if ((*_vec_it)->empty() && _v->size() > 1) {
            delete *_vec_it;
            *_vec_it = 0;
            _vec_it = _v->erase(_vec_it);
        }
        temp2.swap(temp1);
    }

    //Save the rest of elements in the last erased queue
    for (DeqTIter deq_it = (*it_last._vec_it)->end(); deq_it-- != it_last._deq_it;)
        temp1.push_front(*deq_it);

    //Save the rest of elements in the first erased queue
    for (DeqTIter deq_it = it_first._deq_it; deq_it-- != (*it_first._vec_it)->begin();)
        temp1.push_front(*deq_it);

    //Define erased deques
    typename DeqTPtrVec::size_type to_safe = ceil((double)temp1.size()/_deq_size);
    DeqTPtrVecIter first_to_be_erased = it_first._vec_it + to_safe;
    DeqTPtrVecIter last_to_be_erased = it_last._vec_it + 1;
    typename DeqTPtrVec::size_type to_delete = last_to_be_erased - first_to_be_erased;
    bool all_vectors = (to_delete >= _v->size());
    for (DeqTPtrVecIter to_be_erased = first_to_be_erased; to_be_erased != last_to_be_erased; ++to_be_erased) {
        if (to_be_erased == first_to_be_erased && all_vectors)
            (*to_be_erased)->clear();
        else
            delete *to_be_erased;
    }

    //Erase deques
    if (last_to_be_erased - (first_to_be_erased + all_vectors) > 0)
        _vec_it = _v->erase(first_to_be_erased + all_vectors, last_to_be_erased);
    else
        _vec_it = first_to_be_erased;
    _vec_it -= to_safe;

    //Put elements that have been moved up
    if (temp1.size()) {
        (*_vec_it)->clear();
        while (temp1.size()) {
            (*_vec_it)->push_back(temp1.front());
            temp1.pop_front();
            if ((*_vec_it)->size() == _deq_size && temp1.size()) {
                ++_vec_it;
                (*_vec_it)->clear();
            }
        }
    }

    return begin()+result;
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::swap(IgushArray<T, Alloc>& ia)
{
    std::swap(_capacity, ia._capacity);
    std::swap(_v, ia._v);
    std::swap(_deq_size, ia._deq_size);
    std::swap(_vec_size, ia._vec_size);
    std::swap(_a, ia._a);
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::clear()
{
    _delete_deques();
    _v->resize(0);
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::_reserve(size_type n)
{
    //Calculate sizes
    _deq_size = (typename DeqT::size_type) sqrt((double)n);
    if (!_deq_size)
        _deq_size = 1;
    _vec_size = (typename DeqTPtrVec::size_type) ceil((double)n/_deq_size);
    if (!_vec_size)
        _vec_size = 1;
    _capacity = _vec_size*_deq_size;

    //Create vector, reserve and create first empty deque for "end" element
    _v = new DeqTPtrVec();
    _v->reserve(_vec_size);
    #ifdef USE_FIXED_DEQUE
    _v->push_back(new DeqT(_deq_size, _a));
    #else
    _v->push_back(new DeqT(_a));
    #endif
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::_decrease_size(size_type n)
{
    typename DeqTPtrVec::size_type vec_size = (typename DeqTPtrVec::size_type) ceil((double)n/_deq_size);
    if (!vec_size)
        vec_size = 1;
    for (DeqTPtrVecIter _v_it = _v->begin()+vec_size; _v_it != _v->end(); ++_v_it)
        delete *_v_it;

    _v->resize(vec_size);
    _v->back()->resize( n - (_v->size()-1)*_deq_size );
}

template <class T, class Alloc>
void IgushArray<T, Alloc>::_delete_deques()
{
    for (DeqTPtrVecIter _v_it = _v->begin(); _v_it != _v->end(); ++_v_it)
        delete *_v_it;
}

template <class T, class Alloc>
template <class InputIterator>
void IgushArray<T, Alloc>::_push_back(InputIterator first, InputIterator last)
{
    while (first != last)
        push_back(*first++);
}

template <class T, class Alloc>
template <class InputIterator>
void IgushArray<T, Alloc>::_push_back(InputIterator& first, size_type n)
{
    for (size_type i = 0; i < n; ++i)
        push_back(*first++);
}

template <class T, class Alloc>
template <class InputIterator>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::_fill(iterator where, InputIterator first, InputIterator last)
{
    while (first != last)
        *where++ = *first++;
    return where;
}

template <class T, class Alloc>
template <class InputIterator>
typename IgushArray<T, Alloc>::iterator IgushArray<T, Alloc>::_fill(iterator where, InputIterator& first, size_type n)
{
    for (size_type i = 0; i < n; ++i)
        *where++ = *first++;
    return where;
}

#endif
