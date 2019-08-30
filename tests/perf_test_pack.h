/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _PERF_TEST_PACK_H
#define _PERF_TEST_PACK_H

#include "test_pack.h"
#include <iostream>
#include <time.h>

class PerfTestPack : public TestPack {
public:
    ~PerfTestPack() {}
protected:
    class Measure {
    public:
        Measure():_start(0),_sum(0) {}
        void start() { _start = clock(); }
        void stop() { _sum += (clock() - _start)/(1.0*CLOCKS_PER_SEC)*1000; }
        unsigned long time() const { return _sum; }
    private:
        clock_t _start;
        unsigned long _sum;
    };

    template <class Field>
    static void PrintField(const std::string& name, const Field& value);
    static void compare(const Measure& cont_test_measure, const Measure& cont_baseline_measure);
};


template <class Field>
/*static*/ void PerfTestPack::PrintField(const std::string& name, const Field& value)
{
    std::cout<<name<<": ";
    std::cout.width(10);
    std::cout<<std::left<<value;
    std::cout.flush();
}

#endif
