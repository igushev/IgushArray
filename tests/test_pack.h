/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _TEST_PACK_H
#define _TEST_PACK_H

#include <string>

class TestPack {
public:
    virtual ~TestPack() {}
    void ExecuteTests();

protected:
    virtual void Pack() = 0;

    typedef int TestType;

    class TypeTest {
    public:
        TypeTest():_i(0) { ++_count; }
        TypeTest(const TypeTest& _obj):_i(_obj._i) { ++_count; }
        TypeTest(TestType i):_i(i) { ++_count; }
        ~TypeTest() { --_count; }
        operator TestType() const { return _i; }
        bool operator ==(const TypeTest& _obj) const { return _i == _obj._i; }
        bool operator !=(const TypeTest& _obj) const { return !(*this == _obj); }
        bool operator <(const TypeTest& _obj) const { return _i < _obj._i; }
        bool operator >(const TypeTest& _obj) const { return _i > _obj._i; }
        static unsigned count() { return _count; }
    private:
        static unsigned _count;
        TestType _i;
    };

    class TypeBaseline {
    public:
        TypeBaseline():_i(0) { ++_count; }
        TypeBaseline(const TypeBaseline& _obj):_i(_obj._i) { ++_count; }
        TypeBaseline(TestType i):_i(i) { ++_count; }
        ~TypeBaseline() { --_count; }
        operator TestType() const { return _i; }
        bool operator ==(const TypeBaseline& _obj) const { return _i == _obj._i; }
        bool operator !=(const TypeBaseline& _obj) const { return !(*this == _obj); }
        bool operator <(const TypeBaseline& _obj) const { return _i < _obj._i; }
        bool operator >(const TypeBaseline& _obj) const { return _i > _obj._i; }
        static unsigned count() { return _count; }
    private:
        static unsigned _count;
        TestType _i;
    };

    virtual std::string GetTestPackName() const = 0;
    void PrintHead();
    void PrintFoot();
    void PrintDelim();
    void PrintPackName();
};

#endif
