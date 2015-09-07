#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

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
#endif
