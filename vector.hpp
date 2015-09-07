#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstdlib>
#include <stdexcept>
#include <iterator>


template<typename T>
class vector {
public:
    typedef size_t size_type;
    vector(){}
    explicit vector(size_type n = DEFAULT_MAX_NUMBER);
    explicit vector( const vector<T> & other);
    ~vector();

    void push_back(const T& val);
    void pop_back();
    void insert(size_type pos, const T & val);
    void erase(size_type pos);
    T & at(size_type n);
    T * const  data() const;
    void clear();
    size_type size() const;
    size_type capacity() const;
    void resize(size_type n);
    T& operator[](size_type pos);
    T& operator=(const vector<T> & other);
    T& front();
    T& back();

    constexpr static size_type DEFAULT_MAX_NUMBER {32};

    class iterator
    {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        iterator(size_type idx, vector<T> & data) :
            m_index(idx),
            m_data(data) {}

        iterator(const self_type & other) :
            m_data(other.m_data),
            m_index(other.m_index) {}

        self_type & operator++() {
            m_index++;
            return *this;
        }

        self_type operator++(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_index++;
            return tmp;
        }

        self_type & operator--() {
            m_index--;
            return *this;
        }

        self_type operator--(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_index--;
            return tmp;
        }

        reference operator*() {
            return m_data[m_index];
        }

        bool operator==(const self_type & rhs) const {
            return m_index == rhs.m_index;
        }

        bool operator!=(const self_type & rhs) const {
            return !this->operator==(rhs);
        }

        self_type operator+=(const difference_type & n) {

        }
        self_type operator+(const difference_type & n) {

        }

    private:
        size_type      m_index;
        vector<T> & m_data;
    };

private:
    T * m_array {nullptr};
    size_type m_maxNumber{0};
    size_type m_currentNumber{0};
    void tryResize();

};

template<typename T>
vector<T>::vector(size_type n) :
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
    tryResize();
    m_array[m_currentNumber++] = val;
}

template<typename T>
void vector<T>::pop_back() {
    if(!m_currentNumber) {
        throw std::out_of_range("Position is out of range!");
    }
    m_array[m_currentNumber - 1].~T();
    m_currentNumber--;
}

template<typename T>
void vector<T>::insert(size_type pos, const T & val) {
    if(pos > m_currentNumber){
        throw std::out_of_range("Position is out of range!");
    }

    tryResize();

    for(size_type i = m_currentNumber; i > pos;i--) {
        m_array[i] = m_array[i-1];
    }

    m_array[pos] = val;
    m_currentNumber++;
}

template<typename T>
void vector<T>::erase(size_type pos) {
    if(pos > m_currentNumber){
        throw std::out_of_range("Position is out of range!");
    }

    for(size_type i = pos; i < m_currentNumber;++i) {
        m_array[i] = m_array[i+1];
    }
    m_array[m_currentNumber - 1].~T();
    m_currentNumber--;
}

template<typename T>
T & vector<T>::at(size_type n) {
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
    for(int i = 0; i < m_currentNumber; ++i) {
        m_array[i].~T();
    }
    m_currentNumber = 0;
}

template<typename T>
void vector<T>::tryResize() {
    if(m_currentNumber > m_maxNumber) {
        m_maxNumber *= 2;
        resize(m_maxNumber);
    }
}

template<typename T>
size_type vector<T>::size() const {
    return m_currentNumber;
}

template<typename T>
size_type vector<T>::capacity() const {
    return m_maxNumber;
}

template<typename T>
void vector<T>::resize(size_type n) {
    T * tmp = new T[n];
    if (m_array) {
        for(size_type i = 0; i < std::min(m_currentNumber, n); ++i) {
            tmp[i] = m_array[i];
        }
        delete [] m_array;
    }
    m_array = tmp;
}

template<typename T>
T& vector<T>::operator[](size_type pos) {
    return m_array[pos];
}

template<typename T>
T& vector<T>::operator=(const vector<T> & other) {
   if(other != *this) {
       if(m_maxNumber < other.capacity()) {
           resize(other.capacity());
       }
       m_maxNumber = other.capacity();
       m_currentNumber = other.size();

       for(int i = 0; i< m_currentNumber; ++ i) {
           m_array[i] = other.data()[i];
       }
   }
   return *this;
}

template<typename T>
T& vector<T>::front() {
    return m_array[0];
}

template<typename T>
T& vector<T>::back() {
    return m_array[m_currentNumber - 1];
}

#endif
