/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "test_pack.h"
#include <iostream>

unsigned TestPack::TypeTest::_count = 0;
unsigned TestPack::TypeBaseline::_count = 0;

void TestPack::ExecuteTests()
{
    PrintHead();
    Pack();
    PrintFoot();
}

void TestPack::PrintHead()
{
    PrintDelim();
    PrintPackName();
}

void TestPack::PrintFoot()
{
    PrintDelim();
}

void TestPack::PrintDelim()
{
    for (int i = 0; i < 75; ++i) std::cout<<'-';
    std::cout<<std::endl;
}

void TestPack::PrintPackName()
{
    std::cout<<GetTestPackName()<<std::endl;
}

