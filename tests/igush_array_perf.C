/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "igush_array_perf.h"

using namespace std;

/*static*/ const unsigned IgushArrayPerfTestPack::_test_iterations = 1000;

void IgushArrayPerfTestPack::Pack()
{
    AccessByNumber access_by_number(this);
    perform_test(access_by_number);
    AccessByIterator access_by_iterator(this);
    perform_test(access_by_iterator);
    InsertOne insert_one(this);
    perform_test(insert_one);
    EraseOne erase_one(this);
    perform_test(erase_one);
    InsertNum insert_num(this);
    perform_test(insert_num);
    EraseNum erase_num(this);
    perform_test(erase_num);
}

void IgushArrayPerfTestPack::Test1Dim::PrintDims() const
{
    PrintField(Dim1Name(), _dim1);
}

void IgushArrayPerfTestPack::Test1Dim::Next()
{
    if (_dim1 == _test_pack->_stop_count) {
        _finished = true;
        return;
    }

    _dim1 *= _test_pack->_mult;
}

void IgushArrayPerfTestPack::Test2Dim::PrintDims() const
{
    PrintField(Dim1Name(), _dim1);
    PrintField(Dim2Name(), _dim2);
}

void IgushArrayPerfTestPack::Test2Dim::Next()
{
    if (_dim1 == _test_pack->_stop_count && _dim2 == _test_pack->_stop_count) {
        _finished = true;
        return;
    }

    if (_dim2 == _dim1) {
        _dim1 *= _test_pack->_mult;
        _dim2 = 1;
        return;
    }

    _dim2 *= _test_pack->_mult;
}

void IgushArrayPerfTestPack::perform_test(Test& test)
{
    PrintDelim();
    cout<<test.TestName()<<endl;

    try {
        while (!test.Finished()) {
            test.PrintDims();

            IgushArrayTest igush_array;
            Measure igush_array_measure = test.Execute(igush_array);
            PrintField("IgushArray", igush_array_measure.time());

            VectorBaseline vector_baseline;
            Measure vector_measure = test.Execute(vector_baseline);
            PrintField("vector", vector_measure.time());

            compare(igush_array_measure, vector_measure);
            cout<<"OK"<<endl;
            test.Next();
        }
    }
    catch (...) {
        cerr<<endl<<"Unknow error"<<endl;
    }
}

