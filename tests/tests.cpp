//     Yet another attempt to implement STL-style vector
//     Copyright (C) 2015  Anton V. Krishtof
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "vector.hpp"
#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <functional>

#define PASS true
#define FAIL false

#define START() bool ret(PASS);\
                {
#define EXPECT(condition) if (!(condition)) { std::cout << "[Error] " #condition " -> false" << std::endl; ret = FAIL;}
#define STOP() }\
               std::cout << "Balance" << Foo::balance << std::endl;\
               return ret;
               

namespace test{

namespace{
using namespace std;
struct Foo {
    static int balance;
    Foo() {balance++;}
    Foo(int i) : m_i(i) {balance++;}
    Foo(const Foo &  f) : m_i(f.m_i) {balance++;}
//     Foo(Foo&&  f) {std::swap(m_i, f.m_i); balance++;}
    Foo & operator=(const Foo &  f) {
        m_i = f.m_i;
        return *this;
    }
//     Foo & operator=(Foo &&  f) {
//         std::swap(m_i, f.m_i);
//         return *this;
//     }
    operator int() const{
        return m_i;
    }
    ~Foo() {balance--;}
private:
    int m_i;
};

int Foo::balance = 0;

}
bool test_default_constructor() {
    START()
    vector<Foo> v;
    EXPECT(v.empty())
    EXPECT(v.size() == 0)
    EXPECT(v.capacity() == 0)
    EXPECT(v.begin() == v.end())
    EXPECT(v.cbegin() == v.cend())
    EXPECT(v.rbegin() == v.rend())
    EXPECT(v.crbegin() == v.crend())
    STOP()
}

bool test_fill_constructor_size_0() {
    START()
    vector<Foo> v(0);
    EXPECT(v.empty())
    EXPECT(v.size() == 0)
    EXPECT(v.capacity() == 0)
    EXPECT(v.begin() == v.end())
    EXPECT(v.cbegin() == v.cend())
    EXPECT(v.rbegin() == v.rend())
    EXPECT(v.crbegin() == v.crend())
    STOP();
}

bool test_fill_constructor_size_5() {
    START()
    vector<Foo> v(5);
    EXPECT(!v.empty())
    EXPECT(v.size() == 5)
    EXPECT(v.capacity() == 5)
    EXPECT(v.begin() + 5 == v.end())
    EXPECT(v.cbegin() + 5 == v.cend())
    EXPECT(v.rbegin() + 5 == v.rend())
    EXPECT(v.crbegin() + 5 == v.crend())
    STOP()
}

bool test_constructor_with_initializer_list() {
    START()
    vector<Foo> v({1, 2, 3, 4, 5});
    EXPECT(!v.empty())
    EXPECT(v.size() == 5)
    EXPECT(v.capacity() == 5)
    EXPECT(v.begin() + 5 == v.end())
    EXPECT(v.cbegin() + 5 == v.cend())
    EXPECT(v.rbegin() + 5 == v.rend())
    EXPECT(v.crbegin() + 5 == v.crend())
    EXPECT(v[0] == 1)
    EXPECT(v[1] == 2)
    EXPECT(v[2] == 3)
    EXPECT(v[3] == 4)
    EXPECT(v[4] == 5)
    STOP()
}

bool test_constructor_with_range() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2(v1.begin(),v1.begin() + 3);
    EXPECT(!v2.empty())
    EXPECT(v2.size() == 3)
    EXPECT(v2.capacity() == 3)
    EXPECT(v2.begin() + 3 == v2.end())
    EXPECT(v2.cbegin() + 3 == v2.cend())
    EXPECT(v2.rbegin() + 3 == v2.rend())
    EXPECT(v2.crbegin() + 3 == v2.crend())
    EXPECT(v2[1] == v1[1])
    EXPECT(v2[2] == v1[2])
    EXPECT(v2[0] == v1[0])
    STOP()
}

bool test_copy_constructor() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2(v1);
    EXPECT(!v1.empty())
    EXPECT(!v2.empty())
    EXPECT(v1.size()      == v2.size())
    EXPECT(v1.capacity()  == v2.capacity())
    EXPECT(v1[0]          == v2[0])
    EXPECT(v1[1]          == v2[1])
    EXPECT(v1[2]          == v2[2])
    EXPECT(v1[3]          == v2[3])
    EXPECT(v1[4]          == v2[4])
    STOP()
}

bool test_move_constructor() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2(std::move(v1));
    EXPECT(v1.empty())
    EXPECT(!v2.empty())
    EXPECT(v1.size()      == 0)
    EXPECT(v1.capacity()  == 0)
    EXPECT(v2.size()      == 5)
    EXPECT(v2.capacity()  == 5)
    EXPECT(v2[0]          == 1)
    EXPECT(v2[1]          == 2)
    EXPECT(v2[2]          == 3)
    EXPECT(v2[3]          == 4)
    EXPECT(v2[4]          == 5)
    STOP()
}

bool test_push_back() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2;
    v1.push_back(42);
    v2.push_back(42);
    EXPECT(!v1.empty())
    EXPECT(!v2.empty())
    EXPECT(v1.size()      == 6)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v2.size()      == 1)
    EXPECT(v2.capacity()  == 1)
    EXPECT(v1.back()      == 42)
    EXPECT(v2.back()      == 42)
    STOP()
}

bool test_pop_back() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.pop_back();
    EXPECT(v1.back()      == 4)
    EXPECT(v1.size()      == 4)
    EXPECT(v1.capacity()  == 5)
    STOP()
}

bool test_insert_by_copy() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    Foo item = Foo(42);
    v1.insert(v1.cbegin() + 2, item);
    EXPECT(v1.size()      == 6)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 42)
    EXPECT(v1[3]          == 3)
    EXPECT(v1[4]          == 4)
    EXPECT(v1[5]          == 5)
    STOP()
}

bool test_insert_by_move() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.insert(v1.cbegin() + 2,Foo(42));
    EXPECT(v1.size()      == 6)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 42)
    EXPECT(v1[3]          == 3)
    EXPECT(v1[4]          == 4)
    EXPECT(v1[5]          == 5)
    STOP()
}

bool test_insert_by_initializer_list() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.insert(v1.cbegin() + 2,{42, 42});
    EXPECT(v1.size()      == 7)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 42)
    EXPECT(v1[3]          == 42)
    EXPECT(v1[4]          == 3)
    EXPECT(v1[5]          == 4)
    EXPECT(v1[6]          == 5)
    STOP()
}

bool test_insert_by_iterator() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2({42,42});
    v1.insert(v1.cbegin() + 2,v2.begin(), v2.end());
    EXPECT(v1.size()      == 7)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 42)
    EXPECT(v1[3]          == 42)
    EXPECT(v1[4]          == 3)
    EXPECT(v1[5]          == 4)
    EXPECT(v1[6]          == 5)
    STOP()
}

bool test_erase_single() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.erase(v1.cbegin() + 2);
    EXPECT(v1.size()      == 4)
    EXPECT(v1.capacity()  == 5)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 4)
    EXPECT(v1[3]          == 5)
    STOP()
}

bool test_erase_range() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.erase(v1.cbegin() + 2,v1.cbegin() + 4);
    EXPECT(v1.size()      == 3)
    EXPECT(v1.capacity()  == 5)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 5)
    STOP()
}

bool test_emplace_back() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.emplace_back(42);
    EXPECT(v1.size()      == 6)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 3)
    EXPECT(v1[3]          == 4)
    EXPECT(v1[4]          == 5)
    EXPECT(v1[5]          == 42)
    STOP()
}

bool test_emplace() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    v1.emplace(v1.cbegin() + 2,42);
    EXPECT(v1.size()      == 6)
    EXPECT(v1.capacity()  == 10)
    EXPECT(v1[0]          == 1)
    EXPECT(v1[1]          == 2)
    EXPECT(v1[2]          == 42)
    EXPECT(v1[3]          == 3)
    EXPECT(v1[4]          == 4)
    EXPECT(v1[5]          == 5)
    STOP()
}

bool test_iterator_read() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto it = v1.begin();
    EXPECT(it[0] == 1)
    EXPECT(it[1] == 2)
    EXPECT(it[2] == 3)
    EXPECT(it[3] == 4)
    EXPECT(it[4] == 5)
    EXPECT(*(it + 0) == 1)
    EXPECT(*(it + 1) == 2)
    EXPECT(*(it + 2) == 3)
    EXPECT(*(it + 3) == 4)
    EXPECT(*(it + 4) == 5)
    EXPECT(*it++  == 1)
    EXPECT(*it++  == 2)
    EXPECT(*it++  == 3)
    EXPECT(*it++  == 4)
    EXPECT(*it++  == 5)
    STOP()
}

bool test_c_iterator_read() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto it = v1.cbegin();
    EXPECT(it[0] == 1)
    EXPECT(it[1] == 2)
    EXPECT(it[2] == 3)
    EXPECT(it[3] == 4)
    EXPECT(it[4] == 5)
    EXPECT(*(it + 0) == 1)
    EXPECT(*(it + 1) == 2)
    EXPECT(*(it + 2) == 3)
    EXPECT(*(it + 3) == 4)
    EXPECT(*(it + 4) == 5)
    EXPECT(*it++  == 1)
    EXPECT(*it++  == 2)
    EXPECT(*it++  == 3)
    EXPECT(*it++  == 4)
    EXPECT(*it++  == 5)
    STOP()
}

bool test_r_iterator_read() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto it = v1.rbegin();
    EXPECT(it[0] == 5)
    EXPECT(it[1] == 4)
    EXPECT(it[2] == 3)
    EXPECT(it[3] == 2)
    EXPECT(it[4] == 1)
    EXPECT(*(it + 0) == 5)
    EXPECT(*(it + 1) == 4)
    EXPECT(*(it + 2) == 3)
    EXPECT(*(it + 3) == 2)
    EXPECT(*(it + 4) == 1)
    EXPECT(*it++  == 5)
    EXPECT(*it++  == 4)
    EXPECT(*it++  == 3)
    EXPECT(*it++  == 2)
    EXPECT(*it++  == 1)
    STOP()
}

bool test_cr_iterator_read() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto it = v1.crbegin();
    EXPECT(it[0] == 5)
    EXPECT(it[1] == 4)
    EXPECT(it[2] == 3)
    EXPECT(it[3] == 2)
    EXPECT(it[4] == 1)
    EXPECT(*(it + 0) == 5)
    EXPECT(*(it + 1) == 4)
    EXPECT(*(it + 2) == 3)
    EXPECT(*(it + 3) == 2)
    EXPECT(*(it + 4) == 1)
    EXPECT(*it++  == 5)
    EXPECT(*it++  == 4)
    EXPECT(*it++  == 3)
    EXPECT(*it++  == 2)
    EXPECT(*it++  == 1)
    STOP()
}

bool test_iterator_write() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto it = v1.begin();

    it[0] = 42;
    it[1] = 42;
    it[3] = 42;
    it[4] = 42;
    EXPECT(it[0] == 42)
    EXPECT(it[1] == 42)
    EXPECT(it[2] == 3)
    EXPECT(it[3] == 42)
    EXPECT(it[4] == 42)
    STOP()
}

bool test_r_iterator_write() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    auto itr = v1.rbegin();
    auto it = v1.begin();

    itr[0] = 40;
    itr[1] = 41;
    itr[2] = 42;
    itr[3] = 43;
    itr[4] = 44;

    EXPECT(it[0] == 44)
    EXPECT(it[1] == 43)
    EXPECT(it[2] == 42)
    EXPECT(it[3] == 41)
    EXPECT(it[4] == 40)
    STOP()
}

bool test_constructors_destructors_match() {
    START()
//         vector<Foo> v;
//         for(int i = 0; i < 1000;++i) {
//             auto item = Foo(i);
//             v.insert(v.cbegin(),item);
//         }
//         for(int i = 0; i < 1000;++i) {
//             v.pop_back();
//         }
    EXPECT(Foo::balance == 0)
    STOP()
}

bool test_shrink_resize_reserve() {
    START()
    vector<Foo> v;

    v.reserve(10);
    v.insert(v.cbegin(), {1,2,3,4,5});

    EXPECT(v.capacity() == 10)
    EXPECT(v.size()     == 5)

    v.shrink_to_fit();

    EXPECT(v.capacity() == 5)
    EXPECT(v.size()     == 5)

    v.resize(3);

    EXPECT(v.capacity() == 5)
    EXPECT(v.size()     == 3)
    STOP()
}

bool test_doubling() {
    START()
    vector<Foo> v;

    v.reserve(5);
    v.insert(v.cbegin(), {1,2,3,4,5,6,7});

    EXPECT(v.capacity() == 10)
    EXPECT(v.size()     == 7)
    STOP()
}

bool test_swap() {
    START()
    vector<Foo> v1({1, 2, 3, 4, 5});
    vector<Foo> v2({6, 7, 8 ,9});
    auto old_v1_size = v1.size();
    auto old_v1_capacity = v1.capacity();
    auto old_v2_size = v2.size();
    auto old_v2_capacity = v2.capacity();

    v1.swap(v2);

    EXPECT(v1.size()      == old_v2_size)
    EXPECT(v1.capacity()  == old_v2_capacity)
    EXPECT(v2.size()      == old_v1_size)
    EXPECT(v2.capacity()  == old_v1_capacity)

    EXPECT(v1[0]          == 6)
    EXPECT(v1[1]          == 7)
    EXPECT(v1[2]          == 8)
    EXPECT(v1[3]          == 9)

    EXPECT(v2[0]          == 1)
    EXPECT(v2[1]          == 2)
    EXPECT(v2[2]          == 3)
    EXPECT(v2[3]          == 4)
    EXPECT(v2[4]          == 5)
    STOP()
}

struct test_type {
    std::string name;
    std::function<bool()> action;
};

std::list<test_type> tests;

void init() {
    tests.push_back({"test_default_constructor",               test_default_constructor});
    tests.push_back({"test_fill_constructor_size_0",           test_fill_constructor_size_0});
    tests.push_back({"test_fill_constructor_size_5",           test_fill_constructor_size_5});
    tests.push_back({"test_constructor_with_initializer_list", test_constructor_with_initializer_list});
    tests.push_back({"test_constructor_with_range",            test_constructor_with_range});
    tests.push_back({"test_copy_constructor",                  test_copy_constructor});
    tests.push_back({"test_move_constructor",                  test_move_constructor});
    tests.push_back({"test_push_back",                         test_push_back});
    tests.push_back({"test_pop_back",                          test_pop_back});
    tests.push_back({"test_insert_by_copy",                    test_insert_by_copy});
    tests.push_back({"test_insert_by_move",                    test_insert_by_move});
    tests.push_back({"test_insert_by_initializer_list",        test_insert_by_initializer_list});
    tests.push_back({"test_insert_by_iterator",                test_insert_by_iterator});
    tests.push_back({"test_erase_single",                      test_erase_single});
    tests.push_back({"test_erase_range",                       test_erase_range});
    tests.push_back({"test_emplace",                           test_emplace});
    tests.push_back({"test_emplace_back",                      test_emplace_back});
    tests.push_back({"test_iterator_read",                     test_iterator_read});
    tests.push_back({"test_c_iterator_read",                   test_c_iterator_read});
    tests.push_back({"test_r_iterator_read",                   test_r_iterator_read});
    tests.push_back({"test_cr_iterator_read",                  test_cr_iterator_read});
    tests.push_back({"test_iterator_write",                    test_iterator_write});
    tests.push_back({"test_r_iterator_write",                  test_r_iterator_write});
    tests.push_back({"test_shrink_resize_reserve",             test_shrink_resize_reserve});
    tests.push_back({"test_doubling",                          test_doubling});
    tests.push_back({"test_swap",                              test_swap});
    tests.push_back({"test_constructors_destructors_match",    test_constructors_destructors_match});
}
}

int main(int argc, const char * argv[]) {
    test::init();

    for(auto & item : test::tests) {
        std::cout << "["
                  << std::setw(50) << std::left<< std::setfill(' ')
                  << item.name
                  << "]"
                  << std::setw(30)<< std::setfill('.') << std::right
                  << "[START]"
                  << std::endl;

        auto result = item.action();

        std::cout << "["
                  << std::setw(50) << std::left<< std::setfill(' ')
                  << item.name
                  << "]"
                  << std::setw(30)<< std::setfill('.') << std::right
                  << (result ? "[ PASS]" : "[ FAIL]")
                  << std::endl;
    }
}
