/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _STAB_TEST_PACK_H
#define _STAB_TEST_PACK_H

#include "test_pack.h"
#include <stdexcept>

class StabTestPack : public TestPack {
public:
    ~StabTestPack() {}
    StabTestPack(unsigned count):_count(count) {}

protected:
    class Test {
    public:
        Test(StabTestPack* test_pack):_test_pack(test_pack) {}
        virtual std::string TestName() const = 0;
        virtual void Execute() const = 0;
    protected:
        StabTestPack* _test_pack;
    };

    void perform_test(Test& test);

    template <class ContainerTest, class ContainerBaseline>
    static void check_consistency(const ContainerTest& cont_test, const ContainerBaseline& cont_baseline);
    template <class ContainerTest, class ContainerBaseline>
    static void check_consistency(const ContainerTest& cont_test, const ContainerBaseline& cont_baseline,
        typename ContainerTest::const_iterator it_test, typename ContainerBaseline::const_iterator it_baseline);

public:
    unsigned _count;
};

template <class ContainerTest, class ContainerBaseline>
/*static*/ void StabTestPack::check_consistency(const ContainerTest& cont_test, const ContainerBaseline& cont_baseline)
{
    typename ContainerTest::size_type by_func = cont_test.size();
    typename ContainerTest::size_type by_iter = cont_test.end() - cont_test.begin();
    typename ContainerBaseline::size_type baseline_size = cont_baseline.size();
    if (by_func != by_iter)
        throw std::logic_error("Different sizes by iterators and direct fucntion");

    if (by_func != baseline_size)
        throw std::logic_error("Different sizes of baseline and test container");

    if (cont_test.empty() != cont_baseline.empty())
        throw std::logic_error("Different emptiness");

    if (cont_test.size()) {
        if (cont_test.front() != cont_baseline.front())
            throw std::logic_error("Different fronts");

        if (cont_test.back() != cont_baseline.back())
            throw std::logic_error("Different backs");
    }

    typename ContainerTest::size_type i = 0;
    typename ContainerTest::const_iterator it_test = cont_test.begin();
    typename ContainerBaseline::const_iterator it_baseline = cont_baseline.begin();

    while (it_baseline != cont_baseline.end() && it_test != cont_test.end()) {
        if (*it_test != cont_test[i])
            throw std::logic_error("Different values by iterator and operator");
        if (*it_test != cont_test.at(i))
            throw std::logic_error("Different values by iterator and function at()");
        if (*it_test != *it_baseline)
            throw std::logic_error("Different values in one position in baseline and test container");
        ++i;
        ++it_test;
        ++it_baseline;
    }
    
    if (it_baseline != cont_baseline.end() || it_test != cont_test.end())
        throw std::logic_error("Different ends for baseline and test container");
}

template <class ContainerTest, class ContainerBaseline>
/*static*/ void StabTestPack::check_consistency(const ContainerTest& cont_test, const ContainerBaseline& cont_baseline,
    typename ContainerTest::const_iterator it_test, typename ContainerBaseline::const_iterator it_baseline)
{
    if (it_test - cont_test.begin() != it_baseline - cont_baseline.begin())
        throw std::logic_error("Different positions of the elements");

    if (it_test != cont_test.end() && *it_test != *it_baseline)
        throw std::logic_error("Different values of the elements");

    if (TypeTest::count() != TypeBaseline::count())
        throw std::logic_error("Different type instances");
}

#endif
