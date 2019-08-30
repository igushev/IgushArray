/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "fixed_deque_stab.h"
#include "igush_array_stab.h"
#include "igush_array_perf.h"

int main(int argc, char** args)
{
    std::unique_ptr<FixedDequeStabTestPack> fixed_deque_stab_test_pack(new FixedDequeStabTestPack(50));
    fixed_deque_stab_test_pack->ExecuteTests();
    std::unique_ptr<IgushArrayStabTestPack> igush_array_stab_test_pack(new IgushArrayStabTestPack(50));
    igush_array_stab_test_pack->ExecuteTests();
    std::unique_ptr<IgushArrayPerfTestPack> igush_array_perf_test_pack(new IgushArrayPerfTestPack(1000, 10, 10000000));
    igush_array_perf_test_pack->ExecuteTests();
}
