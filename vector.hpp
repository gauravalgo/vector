#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstdlib>
#include <stdexcept>

template<typename T>
class vector {
public:
    vector(){}
    explicit vector(size_t n = DEFAULT_MAX_NUMBER);
    explicit vector( const vector<T> & other);
    ~vector();

    void push_back(const T& val);
    void pop_back();
    void insert(size_t pos, const T & val);
    void erase(size_t pos);
    T & at(size_t n);
    T * const  data() const;
    void clear();
    size_t size() const;
    size_t capacity() const;
    void resize(size_t n);
    T& operator[](size_t pos);
//    T& operator=(vector<T> & other);
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
vector<T>::vector(size_t n) :
    m_maxNumber(n) {
    m_array = new T[n];
}

template<typename T>
vector<T>::vector(const vector<T> & other) {
    m_maxNumber = other.capacity();
    m_currentNumber = other.size();
    m_array = new T[m_maxNumber];
    for(int i = 0; i< m_currentNumber; ++ i) {
        m_array[i] = other.data()[i];
    }
}

template<typename T>
vector<T>::~vector() {
    delete [] m_array;
}

template<typename T>
void vector<T>::push_back(const T& val) {
    m_array[m_currentNumber++] = val;
    tryResize();
}

template<typename T>
void vector<T>::pop_back() {
    if(!m_currentNumber) {
        throw std::out_of_range("Position is out of range!");
    }
    m_array[m_currentNumber - 1].~T();
    m_currentNumber--;
    tryResize();
}

template<typename T>
void vector<T>::insert(size_t pos, const T & val) {
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
void vector<T>::erase(size_t pos) {
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
T & vector<T>::at(size_t n) {
    if(n > m_currentNumber - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename T>
T * const  vector<T>::data() const {
    return m_array;
}

template<typename T>
void vector<T>::clear() {
    delete [] m_array;
    m_currentNumber = 0;
    m_maxNumber = DEFAULT_MAX_NUMBER;
    m_array = new T[m_maxNumber];
}

template<typename T>
void vector<T>::tryResize() {
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
size_t vector<T>::size() const {
    return m_currentNumber;
}

template<typename T>
size_t vector<T>::capacity() const {
    return m_maxNumber;
}

template<typename T>
void vector<T>::resize(size_t n) {
    T * tmp = new T[n];
    for(size_t i = 0; i < std::min(m_currentNumber, n); ++i) {
        tmp[i] = m_array[i];
    }
    delete [] m_array;
    m_array = tmp;
}

template<typename T>
T& vector<T>::operator[](size_t pos) {
    return m_array[pos];
}

//template<typename T>
//T& vector<T>::operator=(vector<T> & other) {
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
T& vector<T>::front() {
    return m_array[0];
}
template<typename T>
T& vector<T>::back() {
    return m_array[m_currentNumber - 1];
}
#endif
