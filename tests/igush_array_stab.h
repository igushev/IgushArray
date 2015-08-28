/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _IGUSH_ARRAY_STAB_H
#define _IGUSH_ARRAY_STAB_H

#include "stab_test_pack.h"
#include "igush_array.h"
#include <vector>

class IgushArrayStabTestPack : public StabTestPack {
public:
    IgushArrayStabTestPack(unsigned count):StabTestPack(count) {}
    void Pack();

private:
    typedef IgushArray<TypeTest> IgushArrayTest;
    typedef std::vector<TypeBaseline> VectorBaseline;

    class SizeConstr : public Test {
    public:
        SizeConstr(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Size costructor"; }
        void Execute() const;
    };

    class ForwardIteratorConstructor : public Test {
    public:
        ForwardIteratorConstructor(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Forward iterator costructor"; }
        void Execute() const;
    };

    class RandomIteratorConstructor : public Test {
    public:
        RandomIteratorConstructor(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Random iterator costructor"; }
        void Execute() const;
    };

    class OperatorAssign : public Test {
    public:
        OperatorAssign(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Assignment operator"; }
        void Execute() const;
    };

    class ResizeFunction : public Test {
    public:
        ResizeFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Resize function"; }
        void Execute() const;
    };

    class ReserveFunction : public Test {
    public:
        ReserveFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Reserve function"; }
        void Execute() const;
    };

    class AssignOneValue : public Test {
    public:
        AssignOneValue(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Assign one value function"; }
        void Execute() const;
    };

    class AssignForwardIterator : public Test {
    public:
        AssignForwardIterator(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Assign forward iterator function"; }
        void Execute() const;
    };

    class AssignRandomIterator : public Test {
    public:
        AssignRandomIterator(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Assign random iterator function"; }
        void Execute() const;
    };

    class PushPopFunctions : public Test {
    public:
        PushPopFunctions(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Push/pop functions"; }
        void Execute() const;
    };

    class InsertOneFunction : public Test {
    public:
        InsertOneFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert one element function"; }
        void Execute() const;
    };

    class InsertNumFunction : public Test {
    public:
        InsertNumFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert a number of elements function"; }
        void Execute() const;
    };

    class InsertForwardIterator : public Test {
    public:
        InsertForwardIterator(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert elements by forward iterator function"; }
        void Execute() const;
    };

    class InsertRandomIterator : public Test {
    public:
        InsertRandomIterator(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Insert elements by random iterator function"; }
        void Execute() const;
    };

    class EraseOneFunction : public Test {
    public:
        EraseOneFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Erase one element function"; }
        void Execute() const;
    };

    class EraseIteratorFunction : public Test {
    public:
        EraseIteratorFunction(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Erase a number of elements function"; }
        void Execute() const;
    };

    class Iterators : public Test {
    public:
        Iterators(IgushArrayStabTestPack* test_pack):Test(test_pack) {}
        std::string TestName() const { return "Iterators"; }
        void Execute() const;
    };

    std::string GetTestPackName() const { return "IgushArray stability test pack"; }

    template <class Cont>
    static inline void _push_back(Cont& container, unsigned push_count);
    template <class Cont>
    static inline void _push_back_reserve(Cont& container, unsigned push_count);
};

template <class Cont>
/*static inline*/ void IgushArrayStabTestPack::_push_back(Cont& container, unsigned push_count)
{
    TestType num = 0;
    for (unsigned i = 0; i < push_count; ++i)
        container.push_back(num++);
}

template <class Cont>
/*static inline*/ void IgushArrayStabTestPack::_push_back_reserve(Cont& container, unsigned push_count)
{
    container.reserve(push_count);
    _push_back(container, push_count);
}

#endif
