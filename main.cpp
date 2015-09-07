#include <iostream>

#include "vector.hpp"

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
        //v2 = v1;
        for(int i = 0; i< v2.size();++i) {
            std::cout << v2[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Vector size " << v2.size() << " and capacity " << v2.capacity() << std::endl;

    } catch (std::out_of_range e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}
