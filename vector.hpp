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

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstdlib>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <stddef.h>
#include <limits>


template<typename T>
class vector {
public:
    typedef size_t size_type;

    class iterator
    {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        iterator(pointer ptr) :
            m_ptr(ptr) {}

        iterator(const self_type & other) :
            m_ptr(other.m_ptr) {}

        self_type & operator++() {
            m_ptr++;
            return *this;
        }

        self_type operator++(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_ptr++;
            return tmp;
        }

        self_type & operator--() {
            m_ptr--;
            return *this;
        }

        self_type operator--(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_ptr--;
            return tmp;
        }

        reference operator*() {
            return *m_ptr;
        }

        bool operator==(const self_type & rhs) const {
            return m_ptr == rhs.m_ptr;
        }

        bool operator<(const self_type & rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator<=(const self_type & rhs) const {
            return m_ptr <= rhs.m_ptr;
        }
        bool operator>(const self_type & rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator>=(const self_type & rhs) const {
            return m_ptr >= rhs.m_ptr;
        }

        bool operator!=(const self_type & rhs) const {
            return !this->operator==(rhs);
        }

        self_type & operator+=(const difference_type & n) {
            m_ptr += n;
            return *this;
        }

        self_type & operator-=(const difference_type & n) {
            m_ptr -= n;
            return *this;
        }

        self_type operator+(const difference_type & n) {
            self_type tmp(*this);
            tmp.operator+=(n);
            return tmp;
        }

        self_type operator-(const difference_type & n) {
            self_type tmp(*this);
            tmp.operator-=(n);
            return tmp;
        }

        difference_type operator-(const self_type & rhs) {
            return m_ptr - rhs.m_ptr;
        }

        reference operator[](difference_type n) {
            self_type tmp  = *this;
            return *(tmp.operator+=(n));
        }

        friend self_type operator+(difference_type lhs, const self_type & rhs) {
            return self_type(lhs+rhs._ptr);
        }

    private:
        pointer      m_ptr;
    };

    class const_iterator
    {
    public:
        typedef const_iterator self_type;
        typedef const T value_type;
        typedef const T& reference;
        typedef const T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        const_iterator(pointer ptr) :
            m_ptr(ptr) {}

        const_iterator(const self_type & other) :
            m_ptr(other.m_ptr) {}

        self_type & operator++() {
            m_ptr++;
            return *this;
        }

        self_type operator++(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_ptr++;
            return tmp;
        }

        self_type & operator--() {
            m_ptr--;
            return *this;
        }

        self_type operator--(int foo) {
            (void)foo;
            self_type tmp(*this);
            m_ptr--;
            return tmp;
        }

        reference operator*() {
            return *m_ptr;
        }

        bool operator==(const self_type & rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator<(const self_type & rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator<=(const self_type & rhs) const {
            return m_ptr <= rhs.m_ptr;
        }
        bool operator>(const self_type & rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator>=(const self_type & rhs) const {
            return m_ptr >= rhs.m_ptr;
        }

        bool operator!=(const self_type & rhs) const {
            return !this->operator==(rhs);
        }

        self_type & operator+=(const difference_type & n) {
            m_ptr += n;
            return *this;
        }

        self_type & operator-=(const difference_type & n) {
            m_ptr -= n;
            return *this;
        }

        self_type operator+(const difference_type & n) {
            self_type tmp(*this);
            tmp.operator+=(n);
            return tmp;
        }

        self_type operator-(const difference_type & n) {
            self_type tmp(*this);
            tmp.operator-=(n);
            return tmp;
        }

        difference_type operator-(const self_type & rhs) {
            return m_ptr - rhs.m_ptr;
        }

        reference operator[](difference_type n) {
            self_type tmp  = *this;
            return *(tmp.operator+=(n));
        }

        friend self_type operator+(difference_type lhs, const self_type & rhs) {
            return self_type(lhs+rhs.m_ptr);
        }
        operator iterator()  {
//             typename vector<T>::iterator::pointer p = m_ptr;
            return iterator(const_cast<typename iterator::pointer>(m_ptr) );
        }

    private:
        pointer m_ptr;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

public:

    vector(){}
    explicit vector(size_type n);
    explicit vector( const vector<T> & other);
    explicit vector( vector<T> && other);
    ~vector();

    void push_back(const T& val);
    void push_back(T&& val);
    void pop_back();
    void insert(size_type pos, const T & val);
    void erase(size_type pos);
    T & at(size_type n);
    const T & at(size_type n) const;
    const T * const  data() const;
    T * data();
    void clear();
    size_type size() const;
    size_type capacity() const;
    bool empty() const noexcept;
    void resize(size_type n);
    void reserve(size_type n);
    T& operator[](size_type pos);
    const T& operator[](size_type pos) const;
    vector<T>& operator=(const vector<T> & other);
    vector<T>& operator=(vector<T> && other);
    bool operator==(const vector<T> & other) const;
    bool operator!=(const vector<T> & other) const;
    T& front();
    const T& front() const ;
    T& back();
    const T& back() const;

    size_type max_size() const;

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin();
    const_reverse_iterator crend();

    template <class... Args>
    iterator emplace (const_iterator position, Args&&... args);
    template <class... Args>
    void emplace_back (Args&&... args);

private:
    T * allocate(size_type n);

private:
    T * m_array {nullptr};
    size_type m_max_number{0};
    size_type m_current_number{0};
    void try_reserve();

};

template<typename T>
vector<T>::vector(size_type n) :
    m_max_number(n) {
    m_array = allocate(m_max_number);
}

template<typename T>
vector<T>::vector(const vector<T> & other) {
    m_max_number = other.size();
    m_current_number = m_max_number;
    m_array = allocate(m_max_number);
    for(int i = 0; i< m_current_number; ++ i) {
        (void) new (m_array + i) T(other[i]);
    }
}

template<typename T>
vector<T>::vector( vector<T> && other) {
     std::swap(m_array, other.m_array);
     std::swap(m_current_number,other.m_current_number);
     std::swap(m_max_number,other.m_max_number);
}

template<typename T>
vector<T>::~vector() {
    if(m_array) {
        for(size_type i = 0; i< m_current_number; ++ i) {
            m_array[i].~T();
        }
        free(m_array);
        m_array = nullptr;
    }
}

template<typename T>
void vector<T>::push_back(const T& val) {
    try_reserve();
    (void) new (m_array + m_current_number++) T(val);
}

template<typename T>
void vector<T>::push_back( T&& val) {
    try_reserve();
    (void) new (m_array + m_current_number++) T(std::forward<T>(val));
}

template<typename T>
void vector<T>::pop_back() {
    if(!m_current_number) {
        throw std::out_of_range("Position is out of range!");
    }
    m_array[m_current_number - 1].~T();
    m_current_number--;
}

template<typename T>
void vector<T>::insert(size_type pos, const T & val) {
    if(pos > m_current_number){
        throw std::out_of_range("Position is out of range!");
    }

    try_reserve();

    for(size_type i = m_current_number; i > pos;i--) {
        m_array[i] = m_array[i-1];
    }

    m_array[pos] = val;
    m_current_number++;
}

template<typename T>
void vector<T>::erase(size_type pos) {
    if(pos > m_current_number){
        throw std::out_of_range("Position is out of range!");
    }

    for(size_type i = pos; i < m_current_number;++i) {
        m_array[i] = m_array[i+1];
    }
    m_array[m_current_number - 1].~T();
    m_current_number--;
}

template<typename T>
T & vector<T>::at(size_type n) {
    if(n > m_current_number - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename T>
const T & vector<T>::at(size_type n) const {
    if(n > m_current_number - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename T>
const T * const  vector<T>::data() const {
    return m_array;
}

template<typename T>
T * vector<T>::data() {
    return m_array;
}

template<typename T>
void vector<T>::clear() {
    for(size_type i = 0; i < m_current_number; ++i) {
        m_array[i].~T();
    }
    m_current_number = 0;
}

template<typename T>
void vector<T>::try_reserve() {
    if(m_max_number == 0) {
        m_max_number = 1;
        m_array = allocate(m_max_number);
    }

    std::printf("===cur %lu max %lu\n",m_current_number, m_max_number);
    if(m_current_number >= m_max_number) {
        m_max_number *= 2;
        reserve(m_max_number);
    std::printf("===m_array -> %p\n",m_array);
    }
    std::printf("m_array -> %p\n",m_array);
}

template<typename T>
typename vector<T>::size_type vector<T>::size() const {
    return m_current_number;
}

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const {
    return m_max_number;
}
template<typename T>
bool vector<T>::empty() const noexcept {
    return size() == 0;
}

template<typename T>
void vector<T>::resize(size_type n) {
    if(n == size()) {
        return;
    } else if(n < size()) {
        for(size_type i = n; i < size(); ++i) {
           m_array[i].~T();
        }
        m_current_number = n;
    } else {
        if(n > m_max_number) {
            reserve(n);
            m_max_number = n;
        } else {
            for(size_type i = size(); i <  n; ++i) {
                (void) new (m_array+i) T();
            }
        }
        m_current_number = n;
    }
}

template<typename T>
T * vector<T>::allocate(size_type n) {
    return reinterpret_cast<T*>(malloc(n * sizeof(T)));
}

template<typename T>
void vector<T>::reserve(size_type n) {
    if (n > max_size()) {
        throw std::length_error("max_size() exceeded!");
    }

    if (n > m_max_number) {
        T * tmp  = allocate(n);
        std::printf("tmp -> %p\n",tmp);
        if (m_array) {
            for(size_type i = 0; i < std::min(m_current_number, n); ++i) {
                (void) new (tmp+i) T(m_array[i]);
            }
            free(m_array);
        }
        m_array = tmp;
    }
}

template<typename T>
T& vector<T>::operator[](size_type pos) {
    return m_array[pos];
}

template<typename T>
const T& vector<T>::operator[](size_type pos) const {
    return m_array[pos];
}

template<typename T>
vector<T> & vector<T>::operator=(const vector< T >& other) {
    if(other != *this) {
        bool need_realloc = false;
        size_type old_size(size());
        if(m_max_number < other.size()) {
            need_realloc = true;
            m_max_number = other.size();
        }
        T * destination = (need_realloc || !m_array) ? allocate(m_max_number) : m_array;
        m_current_number = other.size();

       //TODO Discuss element-wise copy
       for(int i = 0; i< m_current_number; ++ i) {
           (void) new (destination + i) T(other[i]);
       }

       if(need_realloc) {
           if(m_array) {
               for(int i = 0; i < old_size; ++ i) {
                   m_array[i].~T();
               }
               free(m_array);
           }
           m_array = destination;
       }
   }
   return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T> && other) {
     std::swap(m_array, other.m_array);
     std::swap(m_current_number,other.m_currentNumber);
     std::swap(m_max_number,other.m_maxNumber);
}


template<typename T>
bool vector<T>::operator==(const vector<T> & other) const {
    if (size() != other.size()) {
        return false;
    }
    for(size_type i = 0; i < m_current_number;++i) {
        if(m_array[i]!=other[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool vector<T>::operator!=(const vector< T >& other) const {
    return !this->operator==(other);
}

template<typename T>
T& vector<T>::front() {
    return m_array[0];
}

template<typename T>
T& vector<T>::back() {
    return m_array[m_current_number - 1];
}

template<typename T>
const T& vector<T>::front() const  {
    return m_array[0];
}

template<typename T>
const T & vector<T>::back() const {
    return m_array[m_current_number - 1];
}

template<typename T>
typename vector<T>::size_type vector<T>::max_size() const {
    return std::numeric_limits<size_type>::max() - 1;
}

template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return iterator(m_array);
}

template<typename T>
typename vector<T>::iterator vector<T>::end()
{
    return iterator(m_array) + m_current_number;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cbegin()
{
    return const_iterator(m_array);
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cend() {
    return const_iterator(m_array) + m_current_number;
}

template<typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin() {
    return reverse_iterator(end());
}
template<typename T>
typename vector<T>::reverse_iterator vector<T>::rend() {
    return reverse_iterator(begin());
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() {
    return const_reverse_iterator(end());
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crend() {
    return const_reverse_iterator(begin());
}

template<typename T>
template <class... Args>
typename vector<T>::iterator vector<T>::emplace (
    const_iterator position,
    Args&&... args) {
    auto pos = position - cbegin();
    try_reserve();
    for(auto i = m_current_number; i > pos; --i) {
//         (void)new (m_array + i) T(std::forward<T>(m_array[i-1]));
        (void)new (m_array + i) T(m_array[i-1]);
    }
    m_current_number++;
    std::printf("pos is %ld size %lu cap %lu\n",pos,size(),capacity());
    return iterator(new (m_array + pos) T(args ...));
}

template<typename T>
template <class... Args>
void vector<T>::emplace_back (Args&&... args) {
    emplace(cend(),args...);
}


#endif
