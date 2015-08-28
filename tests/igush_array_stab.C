/**
    @author Eduard Igushev visit <www.igushev.com> e-mail <eduard@igushev.com>
    @brief Stability test pack for fixed deque

    Warranty and license
    The implementation is provided “as it is” with no warranty.
    Any private and commercial usage is allowed.
    Keeping the original name and link to the source is required.
    Any feedback is welcomed :-)
*/

#include "igush_array_stab.h"

#include <iostream>
#include <list>
#include <vector>

using namespace std;

void IgushArrayStabTestPack::Pack()
{
    SizeConstr size_costr(this);
    perform_test(size_costr);
    ForwardIteratorConstructor forw_iter_costr(this);
    perform_test(forw_iter_costr);
    RandomIteratorConstructor rand_iter_costr(this);
    perform_test(rand_iter_costr);
    OperatorAssign oper_assign(this);
    perform_test(oper_assign);
    ResizeFunction resize_func(this);
    perform_test(resize_func);
    ReserveFunction reserve_func(this);
    perform_test(reserve_func);
    AssignOneValue assign_one_value_func(this);
    perform_test(assign_one_value_func);
    AssignForwardIterator assign_forw_iter_func(this);
    perform_test(assign_forw_iter_func);
    AssignRandomIterator assign_rand_iter_func(this);
    perform_test(assign_rand_iter_func);
    PushPopFunctions push_pop_funcs(this);
    perform_test(push_pop_funcs);
    InsertOneFunction insert_one_func(this);
    perform_test(insert_one_func);
    InsertNumFunction insert_num_func(this);
    perform_test(insert_num_func);
    InsertForwardIterator insert_forw_iter_func(this);
    perform_test(insert_forw_iter_func);
    InsertRandomIterator insert_rand_iter_func(this);
    perform_test(insert_rand_iter_func);
    EraseOneFunction erase_one_func(this);
    perform_test(erase_one_func);
    EraseIteratorFunction erase_iter_func(this);
    perform_test(erase_iter_func);
    Iterators iterators(this);
    perform_test(iterators);
}

void IgushArrayStabTestPack::SizeConstr::Execute() const
{
    for (unsigned test = 0; test < _test_pack->_count; ++test) {
        IgushArrayTest igush_array_test(test);
        VectorBaseline vector_baseline(test);
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        _push_back(igush_array_test, test);
        _push_back(vector_baseline, test);
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::ForwardIteratorConstructor::Execute() const
{
    for (unsigned test = 0; test < _test_pack->_count; ++test) {
        list<TestType> elem_list;
        _push_back(elem_list, test);

        IgushArrayTest igush_array_test(elem_list.begin(), elem_list.end());
        VectorBaseline vector_baseline(elem_list.begin(), elem_list.end());
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::RandomIteratorConstructor::Execute() const
{
    for (unsigned test = 0; test < _test_pack->_count; ++test) {
        vector<TestType> elem_vecotr;
        _push_back_reserve(elem_vecotr, test);

        IgushArrayTest igush_array_test(elem_vecotr.begin(), elem_vecotr.end());
        VectorBaseline vector_baseline(elem_vecotr.begin(), elem_vecotr.end());
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::OperatorAssign::Execute() const
{
    for (unsigned test = 0; test < _test_pack->_count; ++test) {
        IgushArrayTest igush_array_test;
        VectorBaseline vector_baseline;
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        _push_back_reserve(igush_array_test, test);
        _push_back_reserve(vector_baseline, test);
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        IgushArrayTest igush_array_test_sc;
        VectorBaseline vector_baseline_sc;
        StabTestPack::check_consistency(igush_array_test_sc, vector_baseline_sc);

        igush_array_test_sc = igush_array_test;
        vector_baseline_sc = vector_baseline;
        StabTestPack::check_consistency(igush_array_test_sc, vector_baseline_sc);

        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::ResizeFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned new_size = 0; new_size < _test_pack->_count*2; ++new_size) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.resize(new_size);
            vector_baseline.resize(new_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back(igush_array_test, new_size);
            _push_back(vector_baseline, new_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::ReserveFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned new_capacity = 0; new_capacity < _test_pack->_count*2; ++new_capacity) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.reserve(init_size);
            vector_baseline.reserve(init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back(igush_array_test, init_size);
            _push_back(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.reserve(new_capacity);
            vector_baseline.reserve(new_capacity);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back(igush_array_test, new_capacity);
            _push_back(vector_baseline, new_capacity);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::AssignOneValue::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned new_size = 0; new_size < _test_pack->_count*2; ++new_size) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.assign(new_size, TestType());
            vector_baseline.assign(new_size, TestType());
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::AssignForwardIterator::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned new_size = 0; new_size < _test_pack->_count*2; ++new_size) {
            list<TestType> elem_list;
            _push_back(elem_list, new_size);

            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.assign(elem_list.begin(), elem_list.end());
            vector_baseline.assign(elem_list.begin(), elem_list.end());
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::AssignRandomIterator::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned new_size = 0; new_size < _test_pack->_count*2; ++new_size) {
            vector<TestType> elem_vector;
            _push_back_reserve(elem_vector, new_size);

            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.assign(elem_vector.begin(), elem_vector.end());
            vector_baseline.assign(elem_vector.begin(), elem_vector.end());
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::PushPopFunctions::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned elem_count = 0; elem_count < _test_pack->_count*2; ++elem_count) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            igush_array_test.reserve(init_size);
            vector_baseline.reserve(init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            for (unsigned i = 0; i < elem_count; ++i) {
                igush_array_test.push_back(i);
                vector_baseline.push_back(i);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }

            for (unsigned i = 0; i < elem_count; ++i) {
                igush_array_test.pop_back();
                vector_baseline.pop_back();
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::InsertOneFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned insert_pos = 0; insert_pos <= init_size; ++insert_pos) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            IgushArrayTest::iterator ia_insert_to = igush_array_test.begin()+insert_pos;
            VectorBaseline::iterator vb_insert_to = vector_baseline.begin()+insert_pos;
            StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_insert_to, vb_insert_to);

            IgushArrayTest::iterator ia_new_it = igush_array_test.insert(ia_insert_to, TestType());
            VectorBaseline::iterator vb_new_it = vector_baseline.insert(vb_insert_to, TestType());
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
            StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_new_it, vb_new_it);

            _push_back(igush_array_test, init_size);
            _push_back(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::InsertNumFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned insert_count = 0; insert_count < _test_pack->_count*2; ++insert_count) {
            for (unsigned insert_pos = 0; insert_pos <= init_size; ++insert_pos) {
                IgushArrayTest igush_array_test;
                VectorBaseline vector_baseline;
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back_reserve(igush_array_test, init_size);
                _push_back_reserve(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                IgushArrayTest::iterator ia_insert_to = igush_array_test.begin()+insert_pos;
                VectorBaseline::iterator vb_insert_to = vector_baseline.begin()+insert_pos;
                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_insert_to, vb_insert_to);

                igush_array_test.insert(ia_insert_to, insert_count, TestType());
                vector_baseline.insert(vb_insert_to, insert_count, TestType());
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back(igush_array_test, init_size);
                _push_back(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::InsertForwardIterator::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned insert_count = 0; insert_count < _test_pack->_count*2; ++insert_count) {
            list<TestType> elem_list;
            _push_back(elem_list, insert_count);

            for (unsigned insert_pos = 0; insert_pos <= init_size; ++insert_pos) {
                IgushArrayTest igush_array_test;
                VectorBaseline vector_baseline;
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back_reserve(igush_array_test, init_size);
                _push_back_reserve(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                IgushArrayTest::iterator ia_insert_to = igush_array_test.begin()+insert_pos;
                VectorBaseline::iterator vb_insert_to = vector_baseline.begin()+insert_pos;
                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_insert_to, vb_insert_to);

                igush_array_test.insert(ia_insert_to, elem_list.begin(), elem_list.end());
                vector_baseline.insert(vb_insert_to, elem_list.begin(), elem_list.end());
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back(igush_array_test, init_size);
                _push_back(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::InsertRandomIterator::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned insert_count = 0; insert_count < _test_pack->_count*2; ++insert_count) {
            vector<TestType> elem_vector;
            _push_back_reserve(elem_vector, insert_count);

            for (unsigned insert_pos = 0; insert_pos <= init_size; ++insert_pos) {
                IgushArrayTest igush_array_test;
                VectorBaseline vector_baseline;
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back_reserve(igush_array_test, init_size);
                _push_back_reserve(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                IgushArrayTest::iterator ia_insert_to = igush_array_test.begin()+insert_pos;
                VectorBaseline::iterator vb_insert_to = vector_baseline.begin()+insert_pos;
                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_insert_to, vb_insert_to);

                igush_array_test.insert(ia_insert_to, elem_vector.begin(), elem_vector.end());
                vector_baseline.insert(vb_insert_to, elem_vector.begin(), elem_vector.end());
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back(igush_array_test, init_size);
                _push_back(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::EraseOneFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned erase_func_pos = 0; erase_func_pos < init_size; ++erase_func_pos) {
            IgushArrayTest igush_array_test;
            VectorBaseline vector_baseline;
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            _push_back_reserve(igush_array_test, init_size);
            _push_back_reserve(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);

            IgushArrayTest::iterator ia_erase_func = igush_array_test.begin()+erase_func_pos;
            VectorBaseline::iterator vb_erase_func = vector_baseline.begin()+erase_func_pos;
            StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_erase_func, vb_erase_func);

            IgushArrayTest::iterator ia_after_erase_func = igush_array_test.erase(ia_erase_func);
            VectorBaseline::iterator vb_after_erase_func = vector_baseline.erase(vb_erase_func);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
            StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_after_erase_func, vb_after_erase_func);

            _push_back(igush_array_test, init_size);
            _push_back(vector_baseline, init_size);
            StabTestPack::check_consistency(igush_array_test, vector_baseline);
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::EraseIteratorFunction::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        for (unsigned erase_func_count = 0; erase_func_count <= init_size; ++erase_func_count) {
            for (unsigned erase_func_pos = 0; erase_func_pos <= init_size-erase_func_count; ++erase_func_pos) {
                IgushArrayTest igush_array_test;
                VectorBaseline vector_baseline;
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                _push_back_reserve(igush_array_test, init_size);
                _push_back_reserve(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);

                IgushArrayTest::iterator ia_erase_func = igush_array_test.begin()+erase_func_pos;
                VectorBaseline::iterator vb_erase_func = vector_baseline.begin()+erase_func_pos;
                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_erase_func, vb_erase_func);

                IgushArrayTest::iterator ia_after_erase_func =
                    igush_array_test.erase(ia_erase_func, ia_erase_func+erase_func_count);
                VectorBaseline::iterator vb_after_erase_func =
                    vector_baseline.erase(vb_erase_func, vb_erase_func+erase_func_count);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_after_erase_func, vb_after_erase_func);

                _push_back(igush_array_test, init_size);
                _push_back(vector_baseline, init_size);
                StabTestPack::check_consistency(igush_array_test, vector_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void IgushArrayStabTestPack::Iterators::Execute() const
{
    for (unsigned init_size = 0; init_size < _test_pack->_count; ++init_size) {
        IgushArrayTest igush_array_test;
        VectorBaseline vector_baseline;
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        _push_back_reserve(igush_array_test, init_size);
        _push_back_reserve(vector_baseline, init_size);
        StabTestPack::check_consistency(igush_array_test, vector_baseline);

        IgushArrayTest::iterator ia_it1 = igush_array_test.begin();
        VectorBaseline::iterator vb_it1 = vector_baseline.begin();
        while (ia_it1 != igush_array_test.end()) {

            IgushArrayTest::iterator ia_it2 = igush_array_test.begin();
            VectorBaseline::iterator vb_it2 = vector_baseline.begin();
            while (ia_it2 != igush_array_test.end()) {

                if ((ia_it1 == ia_it2) ^ (vb_it1 == vb_it2))
                    throw std::logic_error("Different result of operator==");
                if ((ia_it1 != ia_it2) ^ (vb_it1 != vb_it2))
                    throw std::logic_error("Different result of operator!=");
                if ((ia_it1 < ia_it2) ^ (vb_it1 < vb_it2))
                    throw std::logic_error("Different result of operator<");
                if ((ia_it1 <= ia_it2) ^ (vb_it1 <= vb_it2))
                    throw std::logic_error("Different result of operator<=");
                if ((ia_it1 > ia_it2) ^ (vb_it1 > vb_it2))
                    throw std::logic_error("Different result of operator>");
                if ((ia_it1 >= ia_it2) ^ (vb_it1 >= vb_it2))
                    throw std::logic_error("Different result of operator>=");
                if ((ia_it1 - ia_it2) != (vb_it1 - vb_it2))
                    throw std::logic_error("Different result of operator-");
                if ((ia_it2 - ia_it1) != (vb_it2 - vb_it1))
                    throw std::logic_error("Different result of operator-");

                StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_it2, vb_it2);
                ++ia_it2;
                ++vb_it2;
            }

            StabTestPack::check_consistency(igush_array_test, vector_baseline, ia_it1, vb_it1);
            ++ia_it1;
            ++vb_it1;
        }
        cout<<'.';
        cout.flush();
    }
}

