#include <iostream>

#include "vector.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Vector<int> v(8);
 
    try {
        v.pushBack(0);
        v.pushBack(1);
        v.pushBack(2);
        v.pushBack(3);
        v.pushBack(4);
        v.pushBack(5);
        v.pushBack(6);
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;
        v.pushBack(7);
        
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;
        
        for(int i = 0; i < 6; ++i){
            v.popBack();
        }
        std::cout << "Vector size " << v.size() << " and capacity " << v.capacity() << std::endl;
        
        std::cout << v.size() << std::endl;
        v.pushBack(7);
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
        Vector<int> v1(v);
        for(int i = 0; i< v1.size();++i) {
            std::cout << v1[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Vector size " << v1.size() << " and capacity " << v1.capacity() << std::endl;
        Vector<int> v2(8);
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
