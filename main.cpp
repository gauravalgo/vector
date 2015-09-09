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

#include <iostream>

#include "vector.hpp"
// #include <vector>

namespace std{

struct Foo {
    Foo() {
        cout << "Foo()" << endl;
    }

    Foo(int i) :
    m_i(i) {
        cout << "Foo(int)" << endl;
    }
    Foo(const Foo &  f) : m_i(f.m_i){
        cout << "Foo(&)" << endl;
    }
    Foo(Foo&&  f) : m_i(f.m_i){
        cout << "Foo(&&)" << endl;
    }
    Foo & operator=(const Foo &  f) {
        cout << "=&" << endl;
        return *this;
    }
    Foo & operator=(Foo &&  f) {
        cout << "=&&" << endl;
        return *this;
    }
    operator int() const{
        return m_i;
    }
    ~Foo() {
        cout << "~Foo()" << endl;
    }
private:
    int m_i;

};
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    vector<int> v(8);

    try {
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
        v.push_back(6);
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;
        v.push_back(7);

        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;

        for(int i = 0; i < 6; ++i){
            v.pop_back();
        }
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;

        std::cout << v.size() << std::endl;
        v.push_back(7);
        std::cout << v.size() << std::endl;
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;

        for(int i = 0; i< v.size();++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;


//        v.clear();
//
//        std::cout << v.size() << std::endl;
//        v.popBack();
//        std::cout << v.size() << std::endl;
        vector<int> v1(v);
        for(int i = 0; i< v1.size();++i) {
            std::cout << v1[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Vector size " << v1.size() << " and capacity " << v1.capacity() << std::endl;
        vector<int> v2(8);
        v2 = v1;
        for(int i = 0; i< v2.size();++i) {
            std::cout << v2[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Vector size " << v2.size() << " and capacity " << v2.capacity() << std::endl;


        std::cout << "<<<<<<ITERATORS TEST>>>>>>>" << std::endl;

        for(auto i = v1.begin(); i != v1.end(); ++i) {
            std::cout << *i << " ";
        }
        std::cout << std::endl;

        auto iter = v1.begin();
        for(int i = 0; i< v1.size();++i) {
            std::cout << iter[i] << " ";
        }
        std::cout << std::endl;

        vector<std::Foo> v3;

        v3.push_back(std::Foo(1));
        v3.push_back(std::Foo(2));
        v3.push_back(std::Foo(3));
        std::cout << "Vector size " << v3.size() << " and capacity " << v3.capacity() << std::endl;
        for(auto i = v3.begin(); i != v3.end(); ++i) {
            int item(*i);
            std::cout << item << " ";
        }
        std::cout << std::endl;

        vector<std::Foo> v4(v3);
        std::cout << "\n\n\n v4 <- v3" << std::endl;
        std::cout << "Vector 4 size " << v4.size() << " and capacity " << v4.capacity() << std::endl;
        vector<std::Foo> v5(v3);
        std::cout << "\n\n\n v5 <- v3" << std::endl;
        std::cout << "Vector 5 size " << v5.size() << " and capacity " << v5.capacity() << std::endl;
//         vector<std::Foo> v5( std::forward<vector<std::Foo>>(v3));

//         v3.~vector();

        for(int i = 0; i< v4.size();++i) {
            std::cout << v4[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "\n\n\n emplace" << std::endl;

        v5.emplace(v5.cbegin(),42);
        v5.emplace(v5.cbegin(),43);
        v5.emplace(v5.cbegin(),44);
        v5.emplace(v5.cbegin(),45);
        v5.emplace(v5.cbegin(),46);
        v5.emplace(v5.cbegin(),47);
        v5.emplace_back(46);
        v5.emplace_back(47);
        v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
//         v5.emplace_back(47);
        for(int i = 0; i< v5.size();++i) {
            std::cout << v5[i] << " ";
        }
        std::cout << std::endl;


    } catch (std::out_of_range e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}
