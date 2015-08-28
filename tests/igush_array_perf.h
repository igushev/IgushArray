/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#ifndef _IGUSH_ARRAY_PERF_H
#define _IGUSH_ARRAY_PERF_H

#include "perf_test_pack.h"
#include "igush_array.h"
#include <vector>

class IgushArrayPerfTestPack : public PerfTestPack {
public:
    IgushArrayPerfTestPack(unsigned start_count, unsigned mult, unsigned stop_count)
        : _start_count(start_count), _mult(mult), _stop_count(stop_count) {}
    void Pack();

private:

    typedef IgushArray<TypeTest> IgushArrayTest;
    typedef std::vector<TypeBaseline> VectorBaseline;

    class Test {
    public:
        Test(IgushArrayPerfTestPack* test_pack):_test_pack(test_pack), _finished(false) {}
        virtual std::string TestName() const = 0;
        virtual void PrintDims() const = 0;
        virtual Measure Execute(IgushArrayTest&) const = 0;
        virtual Measure Execute(VectorBaseline&) const = 0;
        virtual void Next() = 0;
        bool Finished() const { return _finished; }
    protected:
        IgushArrayPerfTestPack* _test_pack;
        bool _finished;
    };

    class Test1Dim : public Test {
    public:
        Test1Dim(IgushArrayPerfTestPack* test_pack):Test(test_pack),
            _dim1(test_pack->_start_count) {}
        void PrintDims() const ;
        virtual std::string Dim1Name() const = 0;
        void Next();
        
    protected:
        unsigned _dim1;
    };

    class Test2Dim : public Test {
    public:
        Test2Dim(IgushArrayPerfTestPack* test_pack):Test(test_pack),
            _dim1(test_pack->_start_count), _dim2(1) {}
        void PrintDims() const;
        virtual std::string Dim1Name() const = 0;
        virtual std::string Dim2Name() const = 0;
        void Next();
        
    protected:
        unsigned _dim1;
        unsigned _dim2;
    };

    class AccessByNumber : public Test1Dim {
    public:
        AccessByNumber(IgushArrayPerfTestPack* test_pack):Test1Dim(test_pack) {}
        std::string TestName() const { return "Accessing elements by number"; }
        std::string Dim1Name() const { return "Size"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned count = _dim1;
            IgushArrayPerfTestPack::_push_back_reserve<Cont>(container, count);
            Measure measure;
            measure.start();
            for (unsigned test = 0; test < IgushArrayPerfTestPack::_test_iterations; ++test) {
                TestType sum = 0;
                for (unsigned i = 0; i < count; ++i)
                    sum += container[i];
            }
            measure.stop();
            return measure;
        }
    };

    class AccessByIterator : public Test1Dim {
    public:
        AccessByIterator(IgushArrayPerfTestPack* test_pack):Test1Dim(test_pack) {}
        std::string TestName() const { return "Accessing elements by iterator"; }
        std::string Dim1Name() const { return "Size"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned count = _dim1;
            IgushArrayPerfTestPack::_push_back_reserve<Cont>(container, count);
            Measure measure;
            measure.start();
            for (unsigned test = 0; test < IgushArrayPerfTestPack::_test_iterations; ++test) {
                TestType sum = 0;
                for (typename Cont::iterator it = container.begin(); it != container.end(); ++it)
                    sum += *it;
            }
            measure.stop();
            return measure;
        }
    };

    class InsertOne : public Test1Dim {
    public:
        InsertOne(IgushArrayPerfTestPack* test_pack):Test1Dim(test_pack) {}
        std::string TestName() const { return "Inserting one element int the middle"; }
        std::string Dim1Name() const { return "Size"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned count = _dim1;
            container.reserve(count);
            IgushArrayPerfTestPack::_push_back<Cont>(container, count - 1);
            Measure measure;
            for (unsigned test = 0; test < IgushArrayPerfTestPack::_test_iterations; ++test) {
                measure.start();
                typename Cont::iterator it =
                    container.insert(container.begin() + container.size()/2, TestType());
                measure.stop();
                container.erase(it);
            }
            return measure;
        }
    };

    class EraseOne : public Test1Dim {
    public:
        EraseOne(IgushArrayPerfTestPack* test_pack):Test1Dim(test_pack) {}
        std::string TestName() const { return "Erasing one element from the middle"; }
        std::string Dim1Name() const { return "Size"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned count = _dim1;
            IgushArrayPerfTestPack::_push_back_reserve<Cont>(container, count);
            Measure measure;
            for (unsigned test = 0; test < IgushArrayPerfTestPack::_test_iterations; ++test) {
                measure.start();
                typename Cont::iterator it =
                    container.erase(container.begin() + container.size()/2);
                measure.stop();
                container.insert(it, TestType());
            }
            return measure;
        }
    };

    class InsertNum : public Test2Dim {
    public:
        InsertNum(IgushArrayPerfTestPack* test_pack):Test2Dim(test_pack) {}
        std::string TestName() const { return "Inserting a number of elements at the middle"; }
        std::string Dim1Name() const { return "Size"; }
        std::string Dim2Name() const { return "Count"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned init_count = _dim1;
            unsigned insert_count = _dim2;
            std::vector<TestType> elem_vector;
            _push_back_reserve<std::vector<TestType> >(elem_vector, insert_count);

            container.reserve(init_count);
            _push_back<Cont>(container, init_count - insert_count);
            typename Cont::size_type insert_pos = container.size()/2;
            Measure measure;
            for (unsigned test = 0; test < _test_iterations; ++test) {
                measure.start();
                container.insert(container.begin() + insert_pos, elem_vector.begin(), elem_vector.end());
                measure.stop();
                container.erase(container.begin() + insert_pos, container.begin() + insert_pos + insert_count);
            }
            return measure;
        }
    };

    class EraseNum : public Test2Dim {
    public:
        EraseNum(IgushArrayPerfTestPack* test_pack):Test2Dim(test_pack) {}
        std::string TestName() const { return "Erasing a number of elements from the middle"; }
        std::string Dim1Name() const { return "Size"; }
        std::string Dim2Name() const { return "Count"; }
        Measure Execute(IgushArrayTest& container) const { return ExecuteBody(container); }
        Measure Execute(VectorBaseline& container) const { return ExecuteBody(container); }
    private:
        template <class Cont>
        Measure ExecuteBody(Cont& container) const
        {
            unsigned init_count = _dim1;
            unsigned erase_count = _dim2;
            std::vector<TestType> elem_vector;
            _push_back_reserve<std::vector<TestType> >(elem_vector, erase_count);

            _push_back_reserve<Cont>(container, init_count);
            typename Cont::size_type erase_pos = (init_count - erase_count)/2;
            Measure measure;
            for (unsigned test = 0; test < _test_iterations; ++test) {
                measure.start();
                container.erase(container.begin() + erase_pos, container.begin() + erase_pos + erase_count);
                measure.stop();
                container.insert(container.begin() + erase_pos, elem_vector.begin(), elem_vector.end());
            }
            return measure;
        }
    };

    void perform_test(Test&);

    std::string GetTestPackName() const { return "IgushArray performance test pack"; }

    template <class Cont>
    static inline void _push_back(Cont& container, unsigned count);
    template <class Cont>
    static inline void _push_back_reserve(Cont& container, unsigned count);

    unsigned _start_count;
    unsigned _mult;
    unsigned _stop_count;

    static const unsigned _test_iterations;
};

template <class Cont>
/*static inline*/ void IgushArrayPerfTestPack::_push_back(Cont& container, unsigned count)
{
    TestType num = 0;
    for (unsigned i = 0; i < count; ++i)
        container.push_back(num++);
}

template <class Cont>
/*static inline*/ void IgushArrayPerfTestPack::_push_back_reserve(Cont& container, unsigned count)
{
    container.reserve(count);
    _push_back(container, count);
}

#endif
