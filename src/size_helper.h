/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _SIZE_HELPER_H
#define _SIZE_HELPER_H

#include <iterator>

template <class InputIterator>
size_t data_size(InputIterator first, InputIterator last)
{
    return size_helper(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
}

template <class InputIterator>
size_t size_helper(InputIterator first, InputIterator last, std::random_access_iterator_tag)
{
    return last - first;
}

template <class InputIterator>
size_t size_helper(InputIterator first, InputIterator last, std::input_iterator_tag)
{
    size_t n = 0;
    while (first++ != last) {
        ++n;
    }
    return n;
}

#endif
