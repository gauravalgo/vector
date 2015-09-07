//
//  main.cpp
//  test
//
//  Created by Guest User on 31/08/15.
//  Copyright (c) 2015 Guest User. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector(){}
    explicit Vector(size_t n = DEFAULT_MAX_NUMBER);
    explicit Vector( const Vector<T> & other);
    ~Vector();
    
    void pushBack(const T& val);
    void popBack();
    void insert(size_t pos, const T & val);
    void erase(size_t pos);
    T & at(size_t n);
    T * const  data() const;
    void clear();
    size_t size() const;
    size_t capacity() const;
    void resize(size_t n);
    T& operator[](size_t pos);
//    T& operator=(Vector<T> & other);
    T& front();
    T& back();
    
    constexpr static size_t DEFAULT_MAX_NUMBER {32};
    
private:
    T * m_array {nullptr};
    size_t m_maxNumber{0};
    size_t m_currentNumber{0};
    void tryResize();
    
};

template<typename T>
Vector<T>::Vector(size_t n) :
    m_maxNumber(n) {
    m_array = new T[n];
}

template<typename T>
Vector<T>::Vector(const Vector<T> & other) {
    m_maxNumber = other.capacity();
    m_currentNumber = other.size();
    m_array = new T[m_maxNumber];
    for(int i = 0; i< m_currentNumber; ++ i) {
        m_array[i] = other.data()[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete [] m_array;
}

template<typename T>
void Vector<T>::pushBack(const T& val) {
    m_array[m_currentNumber++] = val;
    tryResize();
}

template<typename T>
void Vector<T>::popBack() {
    if(!m_currentNumber) {
        throw std::out_of_range("Position is out of range!");
    }
    m_array[m_currentNumber - 1].~T();
    m_currentNumber--;
    tryResize();
}

template<typename T>
void Vector<T>::insert(size_t pos, const T & val) {
    if(pos > m_currentNumber){
        throw std::out_of_range("Position is out of range!");
    }
    
    for(size_t i = m_currentNumber; i > pos;i--) {
        m_array[i] = m_array[i-1];
    }
    m_array[pos] = val;
    m_currentNumber++;
    tryResize();
}

template<typename T>
void Vector<T>::erase(size_t pos) {
    if(pos > m_currentNumber){
        throw std::out_of_range("Position is out of range!");
    }
    
    for(size_t i = pos; i < m_currentNumber;++i) {
        m_array[i] = m_array[i+1];
    }
    m_array[m_currentNumber - 1].~T();
    m_currentNumber--;
    tryResize();
}

template<typename T>
T & Vector<T>::at(size_t n) {
    if(n > m_currentNumber - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename T>
T * const  Vector<T>::data() const {
    return m_array;
}

template<typename T>
void Vector<T>::clear() {
    delete [] m_array;
    m_currentNumber = 0;
    m_maxNumber = DEFAULT_MAX_NUMBER;
    m_array = new T[m_maxNumber];
}

template<typename T>
void Vector<T>::tryResize() {
    if(m_currentNumber >= m_maxNumber) {
        m_maxNumber *= 2;
        resize(m_maxNumber);
    } else if (m_currentNumber * 4 <= m_maxNumber) {
        m_maxNumber /= 4;
        resize(m_maxNumber);
    } else {
        return;
    }
}

template<typename T>
size_t Vector<T>::size() const {
    return m_currentNumber;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return m_maxNumber;
}

template<typename T>
void Vector<T>::resize(size_t n) {
    T * tmp = new T[n];
    for(size_t i = 0; i < std::min(m_currentNumber, n); ++i) {
        tmp[i] = m_array[i];
    }
    delete [] m_array;
    m_array = tmp;
}

template<typename T>
T& Vector<T>::operator[](size_t pos) {
    return m_array[pos];
}

//template<typename T>
//T& Vector<T>::operator=(Vector<T> & other) {
//    if(other != *this) {
//        m_maxNumber = other.capacity();
//        m_currentNumber = other.size();
//        if(m_array) {
//            delete [] m_array;
//        }
//        m_array = new T[m_maxNumber];
//        for(int i = 0; i< m_currentNumber; ++ i) {
//        m_array[i] = other.data()[i];
//        }
//    }
//    return *this;
//}

template<typename T>
T& Vector<T>::front() {
    return m_array[0];
}
template<typename T>
T& Vector<T>::back() {
    return m_array[m_currentNumber - 1];
}

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
