/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _FIXED_DEQUE_STAB_H
#define _FIXED_DEQUE_STAB_H

#include "stab_test_pack.h"
#include "fixed_deque.h"
#include <deque>

class FixedDequeStabTestPack : public StabTestPack {
public:
    ~FixedDequeStabTestPack() {}
    FixedDequeStabTestPack(unsigned count):StabTestPack(count) {}
    void Pack();

private:
    typedef FixedDeque<TypeTest> FixedDequeTest;
    typedef std::deque<TypeBaseline> DequeBaseline;

    class PushPopFunctions : public Test {
    public:
        PushPopFunctions(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Push/pop functions"; }
        void Execute() const;
    };

    class ResizeFunction : public Test {
    public:
        ResizeFunction(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Resize function"; }
        void Execute() const;
    };

    class InsertOneFunction : public Test {
    public:
        InsertOneFunction(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert one element function"; }
        void Execute() const;
    };

    class InsertForwardIterator : public Test {
    public:
        InsertForwardIterator(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert elements by forward iterator function"; }
        void Execute() const;
    };

    class InsertRandomIterator : public Test {
    public:
        InsertRandomIterator(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert elements by random iterator function"; }
        void Execute() const;
    };

    class EraseOneFunction : public Test {
    public:
        EraseOneFunction(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Erase one element function"; }
        void Execute() const;
    };

    class EraseIteratorFunction : public Test {
    public:
        EraseIteratorFunction(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Erase a number of elements function"; }
        void Execute() const;
    };

    class Iterators : public Test {
    public:
        Iterators(FixedDequeStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Iterators"; }
        void Execute() const;
    };

    std::string GetTestPackName() const { return "FixedDeque stability test pack"; }

    template <class Container>
    static inline void _push_back(Container& container, unsigned push_count, TestType num);
    template <class Container>
    static inline void _push_front(Container& container, unsigned push_count, TestType num);
    template <class Container>
    static inline void _push_back_reserve(Container& container, unsigned push_count, TestType num);
    template <class Container>
    static inline void _push_front_reserve(Container& container, unsigned push_count, TestType num);
};

template <class Container>
/*static inline*/ void FixedDequeStabTestPack::_push_back(Container& container, unsigned push_count, TestType num)
{
    for (unsigned i = 0; i < push_count; ++i)
        container.push_back(num++);
}

template <class Container>
/*static inline*/ void FixedDequeStabTestPack::_push_front(Container& container, unsigned push_count, TestType num)
{
    for (unsigned i = 0; i < push_count; ++i)
        container.push_front(num++);
}

template <class Container>
/*static inline*/ void FixedDequeStabTestPack::_push_back_reserve(Container& container, unsigned push_count, TestType num)
{
    container.reserve(push_count);
    _push_back(container, push_count, num);
}

template <class Container>
/*static inline*/ void FixedDequeStabTestPack::_push_front_reserve(Container& container, unsigned push_count, TestType num)
{
    container.reserve(push_count);
    _push_front(container, push_count, num);
}

#endif
