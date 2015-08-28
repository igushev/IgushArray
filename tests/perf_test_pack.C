/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "perf_test_pack.h"

/*static*/ void PerfTestPack::compare(const Measure& cont_test_measure, const Measure& cont_baseline_measure)
{
    if (cont_baseline_measure.time() > cont_test_measure.time()) {
        std::cout.width(10);
        std::cout<<"Better: ";
        std::cout.precision(2);
        std::cout.width(10);
        if (cont_test_measure.time() != 0)
            std::cout<<std::left<<cont_baseline_measure.time()/(1.0*cont_test_measure.time());
        else
            std::cout<<std::left<<"Infinity";
    }
    else if (cont_test_measure.time() > cont_baseline_measure.time()) {
        std::cout.width(10);
        std::cout<<"Worse: ";
        std::cout.precision(2);
        std::cout.width(10);
        if (cont_baseline_measure.time() != 0)
            std::cout<<std::left<<cont_test_measure.time()/(1.0*cont_baseline_measure.time());
        else
            std::cout<<std::left<<"Infinity";
    }
    else {
        std::cout.width(20);
        std::cout<<"Same time";
    }
}

