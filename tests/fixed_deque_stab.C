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

#include <iostream>
#include <list>
#include <vector>

using namespace std;

void FixedDequeStabTestPack::Pack()
{
    PushPopFunctions push_pop_funcs(this);
    perform_test(push_pop_funcs);
    ResizeFunction resize_func(this);
    perform_test(resize_func);
    InsertOneFunction insert_one_func(this);
    perform_test(insert_one_func);
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

void FixedDequeStabTestPack::PushPopFunctions::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned pop_back = 0; pop_back < total_count; ++pop_back) {
                for (unsigned pop_front = 0; pop_front < total_count - pop_back; ++pop_front) {
                    TestType num = 0;
                    FixedDequeTest fixed_deque_test(total_count);
                    DequeBaseline deque_baseline;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                    for (unsigned i = 0; i < push_back; ++i) {
                        fixed_deque_test.push_back(num);
                        deque_baseline.push_back(num);
                        StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                        ++num;
                    }

                    for (unsigned i = 0; i < push_front; ++i) {
                        fixed_deque_test.push_front(num);
                        deque_baseline.push_front(num);
                        StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                        ++num;
                    }

                    for (unsigned i = 0; i < pop_back; ++i) {
                        fixed_deque_test.pop_back();
                        deque_baseline.pop_back();
                        StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    }

                    for (unsigned i = 0; i < pop_front; ++i) {
                        fixed_deque_test.pop_front();
                        deque_baseline.pop_front();
                        StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    }
                }
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::ResizeFunction::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned new_size = 0; new_size < total_count; ++new_size) {
                TestType num = 0;
                FixedDequeTest fixed_deque_test(total_count);
                DequeBaseline deque_baseline;
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                _push_back(fixed_deque_test, push_back, num);
                _push_back(deque_baseline, push_back, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_back;

                _push_front(fixed_deque_test, push_front, num);
                _push_front(deque_baseline, push_front, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_front;

                fixed_deque_test.resize(new_size);
                deque_baseline.resize(new_size);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::InsertOneFunction::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned insert_pos = 0; insert_pos <= total_count; ++insert_pos) {
                TestType num = 0;
                FixedDequeTest fixed_deque_test(total_count + 1);
                DequeBaseline deque_baseline;
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                _push_back(fixed_deque_test, push_back, num);
                _push_back(deque_baseline, push_back, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_back;

                _push_front(fixed_deque_test, push_front, num);
                _push_front(deque_baseline, push_front, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_front;

                FixedDequeTest::iterator dt_insert_to = fixed_deque_test.begin()+insert_pos;
                DequeBaseline::iterator deque_baseline_insert_to = deque_baseline.begin()+insert_pos;
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_insert_to, deque_baseline_insert_to);

                FixedDequeTest::iterator dt_after_insert =
                    fixed_deque_test.insert(dt_insert_to, num);
                DequeBaseline::iterator deque_baseline_after_insert =
                    deque_baseline.insert(deque_baseline_insert_to, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_after_insert, deque_baseline_after_insert);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::InsertForwardIterator::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned insert_count = 0; insert_count < _test_pack->_count*2; ++insert_count) {
                TestType num_insert = 0;
                list<TestType> elem_list;
                _push_back(elem_list, insert_count, num_insert);
                num_insert += insert_count;

                for (unsigned insert_pos = 0; insert_pos <= total_count; ++insert_pos) {
                    TestType num = num_insert;
                    FixedDequeTest fixed_deque_test(total_count + insert_count);
                    DequeBaseline deque_baseline;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                    _push_back(fixed_deque_test, push_back, num);
                    _push_back(deque_baseline, push_back, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_back;

                    _push_front(fixed_deque_test, push_front, num);
                    _push_front(deque_baseline, push_front, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_front;

                    FixedDequeTest::iterator dt_insert_to = fixed_deque_test.begin()+insert_pos;
                    DequeBaseline::iterator deque_baseline_insert_to = deque_baseline.begin()+insert_pos;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_insert_to, deque_baseline_insert_to);

                    fixed_deque_test.insert(dt_insert_to, elem_list.begin(), elem_list.end());
                    deque_baseline.insert(deque_baseline_insert_to, elem_list.begin(), elem_list.end());
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                }
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::InsertRandomIterator::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned insert_count = 0; insert_count < _test_pack->_count*2; ++insert_count) {
                TestType num_insert = 0;
                vector<TestType> elem_vector;
                _push_back_reserve(elem_vector, insert_count, num_insert);
                num_insert += insert_count;

                for (unsigned insert_pos = 0; insert_pos <= total_count; ++insert_pos) {
                    TestType num = num_insert;
                    FixedDequeTest fixed_deque_test(total_count + insert_count);
                    DequeBaseline deque_baseline;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                    _push_back(fixed_deque_test, push_back, num);
                    _push_back(deque_baseline, push_back, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_back;

                    _push_front(fixed_deque_test, push_front, num);
                    _push_front(deque_baseline, push_front, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_front;

                    FixedDequeTest::iterator dt_insert_to = fixed_deque_test.begin()+insert_pos;
                    DequeBaseline::iterator deque_baseline_insert_to = deque_baseline.begin()+insert_pos;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_insert_to, deque_baseline_insert_to);

                    fixed_deque_test.insert(dt_insert_to, elem_vector.begin(), elem_vector.end());
                    deque_baseline.insert(deque_baseline_insert_to, elem_vector.begin(), elem_vector.end());
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                }
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::EraseOneFunction::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned erase_func_pos = 0; erase_func_pos < total_count; ++erase_func_pos) {
                TestType num = 0;
                FixedDequeTest fixed_deque_test(total_count + 1);
                DequeBaseline deque_baseline;
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                _push_back(fixed_deque_test, push_back, num);
                _push_back(deque_baseline, push_back, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_back;

                _push_front(fixed_deque_test, push_front, num);
                _push_front(deque_baseline, push_front, num);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                num += push_front;

                FixedDequeTest::iterator dt_erase_func = fixed_deque_test.begin()+erase_func_pos;
                DequeBaseline::iterator deque_baseline_erase_func = deque_baseline.begin()+erase_func_pos;
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_erase_func, deque_baseline_erase_func);

                FixedDequeTest::iterator dt_after_erase_func = fixed_deque_test.erase(dt_erase_func);
                DequeBaseline::iterator deque_baseline_after_erase_func = deque_baseline.erase(deque_baseline_erase_func);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_after_erase_func, deque_baseline_after_erase_func);
                StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::EraseIteratorFunction::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;

            for (unsigned erase_func_count = 0; erase_func_count <= total_count; ++erase_func_count) {
                for (unsigned erase_func_pos = 0; erase_func_pos <= total_count-erase_func_count; ++erase_func_pos) {

                    TestType num = 0;
                    FixedDequeTest fixed_deque_test(total_count + 1);
                    DequeBaseline deque_baseline;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

                    _push_back(fixed_deque_test, push_back, num);
                    _push_back(deque_baseline,         push_back, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_back;

                    _push_front(fixed_deque_test, push_front, num);
                    _push_front(deque_baseline, push_front, num);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    num += push_front;

                    FixedDequeTest::iterator dt_erase_func = fixed_deque_test.begin()+erase_func_pos;
                    DequeBaseline::iterator deque_baseline_erase_func = deque_baseline.begin()+erase_func_pos;
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_erase_func, deque_baseline_erase_func);

                    FixedDequeTest::iterator dt_after_erase_func =
                        fixed_deque_test.erase(dt_erase_func, dt_erase_func+erase_func_count);
                    DequeBaseline::iterator deque_baseline_after_erase_func =
                        deque_baseline.erase(deque_baseline_erase_func, deque_baseline_erase_func+erase_func_count);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_after_erase_func, deque_baseline_after_erase_func);
                }
            }
        }
        cout<<'.';
        cout.flush();
    }
}

void FixedDequeStabTestPack::Iterators::Execute() const
{
    for (unsigned push_back = 0; push_back < _test_pack->_count; ++push_back) {
        for (unsigned push_front = 0; push_front < _test_pack->_count - push_back; ++push_front) {

            unsigned total_count = push_back + push_front;
            TestType num = 0;
            FixedDequeTest fixed_deque_test(total_count + 1);
            DequeBaseline deque_baseline;
            StabTestPack::check_consistency(fixed_deque_test, deque_baseline);

            _push_back(fixed_deque_test, push_back, num);
            _push_back(deque_baseline,         push_back, num);
            StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
            num += push_back;

            _push_front(fixed_deque_test, push_front, num);
            _push_front(deque_baseline, push_front, num);
            StabTestPack::check_consistency(fixed_deque_test, deque_baseline);
            num += push_front;

            typename FixedDequeTest::iterator dt_it1 = fixed_deque_test.begin();
            typename DequeBaseline::iterator db_it1 = deque_baseline.begin();
            while (dt_it1 != fixed_deque_test.end()) {

                typename FixedDequeTest::iterator dt_it2 = fixed_deque_test.begin();
                typename DequeBaseline::iterator db_it2 = deque_baseline.begin();
                while (dt_it2 != fixed_deque_test.end()) {

                    if ((dt_it1 == dt_it2) ^ (db_it1 == db_it2))
                        throw std::logic_error("Different result of operator==");
                    if ((dt_it1 != dt_it2) ^ (db_it1 != db_it2))
                        throw std::logic_error("Different result of operator!=");
                    if ((dt_it1 < dt_it2) ^ (db_it1 < db_it2))
                        throw std::logic_error("Different result of operator<");
                    if ((dt_it1 <= dt_it2) ^ (db_it1 <= db_it2))
                        throw std::logic_error("Different result of operator<=");
                    if ((dt_it1 > dt_it2) ^ (db_it1 > db_it2))
                        throw std::logic_error("Different result of operator>");
                    if ((dt_it1 >= dt_it2) ^ (db_it1 >= db_it2))
                        throw std::logic_error("Different result of operator>=");
                    if ((dt_it1 - dt_it2) != (db_it1 - db_it2))
                        throw std::logic_error("Different result of operator-");
                    if ((dt_it2 - dt_it1) != (db_it2 - db_it1))
                        throw std::logic_error("Different result of operator-");

                    StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_it2, db_it2);
                    ++dt_it2;
                    ++db_it2;
                }

                StabTestPack::check_consistency(fixed_deque_test, deque_baseline, dt_it1, db_it1);
                ++dt_it1;
                ++db_it1;
            }
        }
        cout<<'.';
        cout.flush();
    }
}

