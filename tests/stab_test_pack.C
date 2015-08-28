/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "stab_test_pack.h"
#include <iostream>

using namespace std;

void StabTestPack::perform_test(Test& test)
{
    PrintDelim();
    cout<<test.TestName()<<" (count is "<<_count<<")"<<endl;

    try {
        test.Execute();
        cout<<"OK"<<endl;
    }
    catch (const logic_error& error) {
        cerr<<endl<<error.what()<<endl;
    }
    catch (...) {
        cerr<<endl<<"Unknow error"<<endl;
    }
}

