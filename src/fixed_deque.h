/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    The FixedDeque class is a simple double-ended queue which uses only one array in its implementation
    and requires its size during creation (in constructor).
    It does not totally implements std::deque interface
    and provides only functions needed by IgushArray implementation.

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _FixedDeque_h
#define _FixedDeque_h

#include <memory>
#include <stdexcept>
#include "size_helper.h"

template <class T, class Alloc = std::allocator<T> >
class FixedDeque {

    typedef T* TPtr;
    typedef const T* TPtrConst;
    typedef FixedDeque<T, Alloc>* SelfPtr;
    typedef const FixedDeque<T, Alloc>* SelfConstPtr;

public:

    typedef Alloc allocator_type;

    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::difference_type difference_type;
    typedef T value_type;
    typedef const T const_value_type;

    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;

    template <class U, class FixedDequePtr>
    class FixedDequeIterator {

        typedef U* UPtr;
        typedef FixedDequeIterator<U, FixedDequePtr> Self;
        typedef FixedDequeIterator<const T, SelfConstPtr> SelfConst;

        FixedDequeIterator(FixedDequePtr fd, UPtr u) :_fd(fd), _u(u) {}
    
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

        inline difference_type operator-(const Self& fdi) const;

        inline U& operator*()
            { return *_u; }
        inline U* operator->()
            { return &(*_u); }

        inline bool operator==(const Self& fdi) const
            { return _u == fdi._u; }
        inline bool operator!=(const Self& fdi) const
            { return !(*this == fdi); }
        inline bool operator<(const Self& fdi) const;
        inline bool operator<=(const Self& fdi) const
            { return (*this < fdi || *this == fdi); }
        inline bool operator>(const Self& fdi) const;
        inline bool operator>=(const Self& fdi) const
            { return (*this > fdi || *this == fdi); }

        inline operator SelfConst()
            { return SelfConst(_fd, _u); }

    private:

        static inline bool _special_lower(const Self& fdi1, const Self& fdi2)
            {
                return (fdi1._fd == fdi2._fd &&
                    fdi1._u >= fdi1._fd->_begin &&
                    fdi1._fd->_begin > fdi2._fd->_end &&
                    fdi2._fd->_end >= fdi2._u);
            }

        FixedDequePtr _fd;
        UPtr _u;

        friend class FixedDeque<T, Alloc>;
    };

    typedef FixedDequeIterator<T, SelfPtr> iterator;
    typedef FixedDequeIterator<const T, SelfConstPtr> const_iterator;
    //typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    //typedef std::reverse_iterator<iterator> reverse_iterator;
    
    explicit FixedDeque(size_type n, const Alloc& a = Alloc());
    ~FixedDeque();
    
    inline bool empty() const
        { return (_begin == _end); }
    inline size_type size() const;
    void resize(size_type n, const T& value = T());

    inline iterator begin()
        { return iterator(this, _begin); }
    inline const_iterator begin() const
        { return const_iterator(this, _begin); }
    inline iterator end()
        { return iterator(this, _end); }
    inline const_iterator end() const
        { return const_iterator(this, _end); }

    /*inline reverse_iterator rbegin()
        { return reverse_iterator(end()); }
    inline const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }
    inline reverse_iterator rend()
        { return reverse_iterator(begin()); }
    inline const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }*/

    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference at(size_type);
    const_reference at(size_type) const;

    inline reference front()
        { return *_begin; }
    inline const_reference front() const
        { return *_begin; }
    inline reference back()
        { return *(end()-1); }
    inline const_reference back() const
        { return *(end()-1); }

    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();

    iterator insert(iterator, const T&);
    template <class InputIterator>
    iterator insert(iterator, InputIterator first, InputIterator last);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    
    void clear();
    inline Alloc get_allocator()
        { return _alloc; }

private:
    void _destroy(TPtr begin, TPtr end)
        { while (begin != end) _alloc.destroy(begin++); }
    size_type _max_size() const
        { return (_storage_end - _storage_begin - 1); }
    void _move(iterator, const T&);
    void _increase_begin(difference_type n);
    void _increase_end(difference_type n);
    void _decrease_begin(difference_type n);
    void _decrease_end(difference_type n);

    TPtr _storage_begin;
    TPtr _storage_end;
    TPtr _begin;
    TPtr _end;
    Alloc _alloc;
};
 
template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>&
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator+=(difference_type incr)
{
    _u += incr;
    if (_u > _fd->_storage_end - 1)
        _u -= (_fd->_storage_end - _fd->_storage_begin);
    return *this;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator+(difference_type incr) const
{
    Self temp = *this;
    temp += incr;
    return temp;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>&
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator-=(difference_type decr)
{
    _u -= decr;
    if (_u < _fd->_storage_begin)
        _u += (_fd->_storage_end - _fd->_storage_begin);
    return *this;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator-(difference_type decr) const
{
    Self temp = *this;
    temp -= decr;
    return temp;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>&
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator++()
{
    ++_u;
    if (_u > _fd->_storage_end - 1)
        _u -= (_fd->_storage_end - _fd->_storage_begin);
    return *this;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator++(int)
{
    Self temp = *this;
    ++*this;
    return temp;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>&
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator--()
{
    --_u;
    if (_u < _fd->_storage_begin)
        _u += (_fd->_storage_end - _fd->_storage_begin);
    return *this;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator--(int)
{
    Self temp = *this;
    --*this;
    return temp;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
/*inline*/ typename FixedDeque<T, Alloc>::template FixedDequeIterator<U, FixedDequePtr>::difference_type
FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator-(const Self& fdi) const
{
    difference_type res = _u - fdi._u;
    if (_special_lower(*this, fdi))
        res -= (_fd->_storage_end - _fd->_storage_begin);
    else if (_special_lower(fdi, *this))
        res += (_fd->_storage_end - _fd->_storage_begin);
    return res;
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
/*inline*/ bool FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator<(const Self& fdi) const
{
    if (_special_lower(*this, fdi))
        return true;
    else if (_special_lower(fdi, *this))
        return false;
    else
        return (_u < fdi._u);
}

template <class T, class Alloc>
template <class U, class FixedDequePtr>
/*inline*/ bool FixedDeque<T, Alloc>::FixedDequeIterator<U, FixedDequePtr>::operator>(const Self& fdi) const
{
    if (_special_lower(*this, fdi))
        return false;
    else if (_special_lower(fdi, *this))
        return true;
    else
        return (_u > fdi._u);
}

template <class T, class Alloc>
/*explicit*/ FixedDeque<T, Alloc>::FixedDeque(size_type n, const Alloc& alloc)
    : _alloc(alloc)
{
    _begin = _end = _storage_begin = _alloc.allocate(n + 1);
    _storage_end = _storage_begin + n + 1;
}

template <class T, class Alloc>
FixedDeque<T, Alloc>::~FixedDeque()
{
    clear();
    _alloc.deallocate(_storage_begin, _storage_end - _storage_begin);
}

template <class T, class Alloc>
/*inline*/ typename FixedDeque<T, Alloc>::size_type FixedDeque<T, Alloc>::size() const
{
    difference_type result = _end - _begin;
    if (result < 0)
        result += _storage_end - _storage_begin;

    return result;
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::resize(size_type n, const T& value/* = T()*/)
{
    if (n > size()) {
        if (n > _max_size())
            throw std::out_of_range("resize(): The size has been exceeded");
        iterator it = end();
        unsigned new_elems = n - size();
        for (unsigned i = 0; i < new_elems; ++i)
            _move(it++, value);
        _increase_end(new_elems);
    }
    else if (n < size()) {
        iterator it = end();
        unsigned del_elems = size() - n;
        for (unsigned i = 0; i < del_elems; ++i)
            _alloc.destroy((--it)._u);
        _decrease_end(del_elems);
    }
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::reference FixedDeque<T, Alloc>::operator[](size_type n)
{
    TPtr result = _begin;
    result += n;
    if (result > _storage_end - 1)
        result -= (_storage_end - _storage_begin);
    return *result;
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::const_reference FixedDeque<T, Alloc>::operator[](size_type n) const
{
    TPtrConst result = _begin;
    result += n;
    if (result > _storage_end - 1)
        result -= (_storage_end - _storage_begin);
    return *result;
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::reference FixedDeque<T, Alloc>::at(size_type n)
{
    if (n >= size())
        throw std::out_of_range("at(): The size has been exceeded");
    return this->operator[](n);
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::const_reference FixedDeque<T, Alloc>::at(size_type n) const
{
    if (n >= size())
        throw std::out_of_range("at(): The size has been exceeded");
    return this->operator[](n);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::push_back(const T& val)
{
    if (size() == _max_size())
        throw std::out_of_range("push_back(): The size has been exceeded");

    _alloc.construct(_end, val);

    if (_end == _storage_end - 1)
        _end = _storage_begin;
    else
        ++_end;
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::pop_back()
{
    if (_begin == _end)
        throw std::out_of_range("pop_back(): The size has been exceeded");

    if (_end == _storage_begin)
        _end = _storage_end - 1;
    else
        --_end;

    _alloc.destroy(_end);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::push_front(const T& val)
{
    if (size() == _max_size())
        throw std::out_of_range("push_front(): Container is empty");

    if (_begin == _storage_begin)
        _begin = _storage_end - 1;
    else
        --_begin;

    _alloc.construct(_begin, val);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::pop_front()
{
    if (_begin == _end)
        throw std::out_of_range("pop_front(): Container is empty");

    _alloc.destroy(_begin);

    if (_begin == _storage_end - 1)
        _begin = _storage_begin;
    else
        ++_begin;
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::iterator FixedDeque<T, Alloc>::insert(iterator it, const T& val)
{
    if (size() + 1 > _max_size())
        throw std::out_of_range("insert(): The size has been exceeded");

    iterator to = end() + 1;
    iterator from = end();
    while (from != it)
        _move(--to, *--from);

    _move(from, val);

    if (_end == _storage_end - 1)
        _end = _storage_begin;
    else
        ++_end;

    return from;
}

template <class T, class Alloc>
template <class InputIterator>
typename FixedDeque<T, Alloc>::iterator FixedDeque<T, Alloc>::insert(iterator it, InputIterator first, InputIterator last)
{
    size_type n = data_size(first, last);
    if (size() + n > _max_size())
        throw std::out_of_range("insert(): The size has been exceeded");

    iterator to = end() + n;
    iterator from = end();
    while (from != it)
        _move(--to, *--from);

    iterator result = from;

    while (first != last)
        _move(from++, *first++);

    _increase_end(n);

    return result;
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::iterator FixedDeque<T, Alloc>::erase(iterator it)
{
    if (empty())
        throw std::out_of_range("erase(): Container is empty");

    iterator result = it;

    iterator to = it;
    iterator from = it + 1;
    while (from != end())
        *to++ = *from++;

    if (_end == _storage_begin)
        _end = _storage_end - 1;
    else
        --_end;

    _alloc.destroy(_end);

    return result;
}

template <class T, class Alloc>
typename FixedDeque<T, Alloc>::iterator FixedDeque<T, Alloc>::erase(iterator first, iterator last)
{
    size_type n = last - first;
    if (size() < n)
        throw std::out_of_range("erase(): The size is not enough");

    iterator result = first;
    iterator to = first;
    iterator from = last;
    while (from != end())
        *to++ = *from++;

    --to;
    while (++to != end())
        _alloc.destroy(to._u);
    
    _decrease_end(n);

    return result;
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::clear()
{
    if (_begin > _end) {
        _destroy(_begin, _storage_end);
        _destroy(_storage_begin, _end);
    }
    else {
        _destroy(_begin, _end);
    }
    _begin = _end = _storage_begin;
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::_move(iterator it, const T& val)
{
    if (it >= end())
        _alloc.construct(it._u, val);
    else
        *it._u = val;
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::_increase_begin(difference_type n)
{
    _begin -= n;
    if (_begin < _storage_begin)
        _begin += (_storage_end - _storage_begin);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::_increase_end(difference_type n)
{
    _end += n;
    if (_end > _storage_end - 1)
        _end -= (_storage_end - _storage_begin);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::_decrease_begin(difference_type n)
{
    _begin += n;
    if (_begin > _storage_end - 1)
        _begin -= (_storage_end - _storage_begin);
}

template <class T, class Alloc>
void FixedDeque<T, Alloc>::_decrease_end(difference_type n)
{
    _end -= n;
    if (_end < _storage_begin)
        _end += (_storage_end - _storage_begin);
}

#endif
