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
#include <cstddef>
#include <limits>
#include <initializer_list>

template<typename T>
class vector {
public:
    typedef size_t size_type;
    typedef T value_type;

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

        self_type operator+(const difference_type & n) const {
            self_type tmp(*this);
            tmp.operator+=(n);
            return tmp;
        }

        self_type operator-(const difference_type & n) const {
            self_type tmp(*this);
            tmp.operator-=(n);
            return tmp;
        }

        difference_type operator-(const self_type & rhs) {
            return m_ptr - rhs.m_ptr;
        }

        reference operator[](difference_type n) {
            return *(m_ptr + n);
        }

        friend self_type operator+(difference_type lhs, const self_type & rhs) {
            return self_type(lhs+rhs.m_ptr);
        }

        operator pointer() {
            return m_ptr;
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

        self_type operator+(const difference_type & n) const {
            self_type tmp(*this);
            tmp.operator+=(n);
            return tmp;
        }

        self_type operator-(const difference_type & n) const {
            self_type tmp(*this);
            tmp.operator-=(n);
            return tmp;
        }

        difference_type operator-(const self_type & rhs) const{
            return m_ptr - rhs.m_ptr;
        }

        reference operator[](difference_type n) {
            self_type tmp  = *this;
            return *(tmp.operator+=(n));
        }

        friend self_type operator+(difference_type lhs, const self_type & rhs){
            return self_type(lhs+rhs.m_ptr);
        }
        operator iterator()  {
            return iterator(const_cast<typename iterator::pointer>(m_ptr) );
        }
        operator pointer() {
            return m_ptr;
        }

    private:
        pointer m_ptr;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

public:

    vector(){}
    explicit vector(size_type n);
    explicit vector( const vector<value_type> & other);
    explicit vector( vector<value_type> && other);
    template <class InputIterator>
    vector (InputIterator first, InputIterator last);

    vector (std::initializer_list<value_type> il);
    ~vector();

    void push_back(const value_type& val);
    void push_back(value_type&& val);
    void pop_back();
    iterator insert (const_iterator position, const value_type& val);
    iterator insert (const_iterator position, value_type&& val);
    iterator insert (const_iterator position, std::initializer_list<value_type> il);
    template <class InputIterator>
    iterator insert (const_iterator position, InputIterator first, InputIterator last);
    iterator erase (const_iterator position);
    iterator erase (const_iterator first, const_iterator last);
    value_type & at(size_type n);
    const value_type & at(size_type n) const;
    const value_type * const  data() const;
    value_type * data();
    void clear();
    size_type size() const;
    size_type capacity() const;
    bool empty() const noexcept;
    void resize(size_type n);
    void reserve(size_type n);
    void shrink_to_fit();
    value_type& operator[](size_type pos);
    const value_type& operator[](size_type pos) const;
    vector<value_type>& operator=(const vector<value_type> & other);
    vector<value_type>& operator=(vector<value_type> && other);
    bool operator==(const vector<value_type> & other) const;
    bool operator!=(const vector<value_type> & other) const;
    value_type& front();
    const value_type& front() const ;
    value_type& back();
    const value_type& back() const;
    void swap (vector<value_type> & other);

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
    value_type * allocate(size_type n);
    void force_reserve(size_type n);


private:
    value_type * m_array {nullptr};
    size_type m_max_number{0};
    size_type m_current_number{0};
    void try_reserve();

};

template<typename value_type>
vector<value_type>::vector(size_type n) :
    m_max_number(n),m_current_number(m_max_number) {
    m_array = allocate(m_max_number);
    for(int i = 0; i< m_current_number; ++ i) {
        (void) new (m_array + i) value_type();
    }
}

template<typename value_type>
vector<value_type>::vector(const vector<value_type> & other) {
    m_max_number = other.size();
    m_current_number = m_max_number;
    m_array = allocate(m_max_number);
    for(int i = 0; i< m_current_number; ++ i) {
        (void) new (m_array + i) value_type(other[i]);
    }
}

template<typename value_type>
vector<value_type>::vector( vector<value_type> && other) {
     std::swap(m_array, other.m_array);
     std::swap(m_current_number,other.m_current_number);
     std::swap(m_max_number,other.m_max_number);
     other.m_array = nullptr;
     other.m_current_number = 0;
     other.m_max_number = 0;
}
template<typename value_type>
template <class InputIterator>
vector<value_type>::vector (InputIterator first, InputIterator last) {
    insert(cbegin(),first,last);
}

template<typename value_type>
vector<value_type>::vector (std::initializer_list<value_type> il) {
    insert(cbegin(),il);
}

template<typename value_type>
vector<value_type>::~vector() {
    if(m_array) {
        for(size_type i = 0; i< m_current_number; ++ i) {
            m_array[i].~value_type();
        }
        free(m_array);
        m_array = nullptr;
    }
}

template<typename value_type>
void vector<value_type>::push_back(const value_type& val) {
    insert(cend(), val);
}

template<typename value_type>
void vector<value_type>::push_back( value_type&& val) {
    insert(cend(), val);
}

template<typename value_type>
void vector<value_type>::pop_back() {
    if(!m_current_number) {
        throw std::out_of_range("Position is out of range!");
    }
    erase(cend() - 1);
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert (
    const_iterator position, const value_type& val) {
    if(position > cend() || position < cbegin()){
        throw std::out_of_range("Position is out of range!");
    }
    auto pos = position - cbegin();
    try_reserve();
    for(size_type i = m_current_number; i > pos;i--) {
        std::swap(m_array[i],m_array[i - 1]);
    }
    (void) new (m_array + pos) value_type(val);
    m_current_number++;
    return begin() + pos;
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert (
    const_iterator position, value_type&& val) {
    if(position > cend() || position < cbegin()){
        throw std::out_of_range("Position is out of range!");
    }
    auto pos = position - cbegin();
    try_reserve();
    for(size_type i = m_current_number; i > pos;i--) {
        std::swap(m_array[i],m_array[i - 1]);
    }
    (void) new (m_array + pos) value_type(std::forward<value_type>(val));
    m_current_number++;
    return begin() + pos;
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert (
    const_iterator position, std::initializer_list<value_type> il) {
    int distance = il.size();
    auto from = position - cbegin();

    if(position > cend() || position < cbegin() || (distance < 0)){
        throw std::out_of_range("Position is out of range!");
    }

    if(m_current_number + distance > m_max_number) {
        auto reserve_up_to = std::max(m_current_number + distance, 2 * m_max_number);
        reserve(reserve_up_to);
    }

    for(size_type i = 0; i < m_current_number - from; ++i) {
        auto dest = m_current_number + distance - i - 1;
        auto src = m_current_number - i - 1;
        std::swap(m_array[dest],m_array[src]);
    }

    for(size_type i = 0; i < distance; ++i) {
//         m_array[from+i].~value_type();
        (void) new (m_array + from + i) value_type(*(il.begin() + i));
    }

    m_current_number += distance;
    return begin() + from;
}

template<typename value_type>
template <class InputIterator>
typename vector<value_type>::iterator vector<value_type>::insert (
    const_iterator position, InputIterator first, InputIterator last) {
    int distance = last - first;
    auto from = position - cbegin();

    if(position > cend() || position < cbegin() || (distance < 0)){
        throw std::out_of_range("Position is out of range!");
    }

    if(m_current_number + distance > m_max_number) {
        auto reserve_up_to = std::max(m_current_number + distance, 2 * m_current_number);
        reserve(reserve_up_to);
    }

    for(size_type i = 0; i < m_current_number - from; ++i) {
        auto dest = m_current_number + distance - i - 1;
        auto src = m_current_number - i - 1;
        std::swap(m_array[dest],m_array[src]);
    }

    for(size_type i = 0; i < distance; ++i) {
        m_array[from+i].~value_type();
        (void) new (m_array + from + i) value_type(first[i]);
    }

    m_current_number += distance;
    return begin() + from;
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::erase (const_iterator position) {
    return erase(position, position+1);
}
template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::erase (const_iterator first, const_iterator last) {
    int distance = last - first;
    auto from = first - cbegin();

    if(first > cend() || first < cbegin() || (distance < 0)){
        throw std::out_of_range("Position is out of range!");
    }

    auto to = std::min(m_current_number, (size_type)(last - cbegin()));
    auto true_distance = to - from;

    for(size_type i = to; i < m_current_number; ++i) {
        std::swap(m_array[i - true_distance],m_array[i]);
    }

    for(size_type i = m_current_number - true_distance; i < m_current_number; ++i) {
        m_array[i].~value_type();
    }

    m_current_number -= true_distance;

    return begin() + from;
}

template<typename value_type>
value_type & vector<value_type>::at(size_type n) {
    if(n > m_current_number - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename value_type>
const value_type & vector<value_type>::at(size_type n) const {
    if(n > m_current_number - 1){
        throw std::out_of_range("Position is out of range!");
    }
    return m_array[n];
}

template<typename value_type>
const value_type * const  vector<value_type>::data() const {
    return m_array;
}

template<typename value_type>
value_type * vector<value_type>::data() {
    return m_array;
}

template<typename value_type>
void vector<value_type>::clear() {
    for(size_type i = 0; i < m_current_number; ++i) {
        m_array[i].~value_type();
    }
    m_current_number = 0;
}

template<typename value_type>
void vector<value_type>::try_reserve() {
    if(m_max_number == 0 && !m_array) {
        m_max_number = 1;
        m_array = allocate(m_max_number);
    }

    if(m_current_number >= m_max_number) {
        auto n = m_max_number * 2;
        reserve(n);
    }
}

template<typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
    return m_current_number;
}

template<typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
    return m_max_number;
}
template<typename value_type>
bool vector<value_type>::empty() const noexcept {
    return size() == 0;
}

template<typename value_type>
void vector<value_type>::resize(size_type n) {
    if(n == size()) {
        return;
    } else if(n < size()) {
        for(size_type i = n; i < size(); ++i) {
           m_array[i].~value_type();
        }
        m_current_number = n;
    } else {
        if(n > m_max_number) {
            reserve(n);
        } else {
            for(size_type i = size(); i <  n; ++i) {
                (void) new (m_array+i) value_type();
            }
        }
        m_current_number = n;
    }
}

template<typename value_type>
value_type * vector<value_type>::allocate(size_type n) {
    return reinterpret_cast<value_type*>(malloc(n * sizeof(value_type)));
}

template<typename value_type>
void vector<value_type>::reserve(size_type n) {
        if (n > max_size()) {
        throw std::length_error("max_size() exceeded!");
    }
    if(m_max_number == 0 && !m_array) {
        m_max_number = 1;
        m_array = allocate(m_max_number);
    }
    if (n > m_max_number) {
        value_type * tmp  = allocate(n);
        if (m_array) {
            for(size_type i = 0; i < std::min(m_current_number, n); ++i) {
                std::swap(tmp[i], m_array[i]);
            }
            free(m_array);
        }
        m_array = tmp;
        m_max_number = n;
    }
}
template<typename value_type>
void vector<value_type>::force_reserve(size_type n) {
    if (n > max_size()) {
        throw std::length_error("max_size() exceeded!");
    }
    value_type * tmp  = allocate(n);
    if (m_array) {
        for(size_type i = 0; i < std::min(m_current_number, n); ++i) {
            std::swap(tmp[i], m_array[i]);
        }
        free(m_array);
    }
    m_array = tmp;
    m_max_number = n;
}

template<typename value_type>
void vector<value_type>::shrink_to_fit() {
    force_reserve(size());
}

template<typename value_type>
value_type& vector<value_type>::operator[](size_type pos) {
    return m_array[pos];
}

template<typename value_type>
const value_type& vector<value_type>::operator[](size_type pos) const {
    return m_array[pos];
}

template<typename value_type>
vector<value_type> & vector<value_type>::operator=(const vector< value_type >& other) {
    if(other != *this) {
        bool need_realloc = false;
        size_type old_size(size());
        if(m_max_number < other.size()) {
            need_realloc = true;
            m_max_number = other.size();
        }
        value_type * destination = (need_realloc || !m_array) ? allocate(m_max_number) : m_array;
        m_current_number = other.size();

       for(int i = 0; i< m_current_number; ++ i) {
           (void) new (destination + i) value_type(other[i]);
       }

       if(need_realloc) {
           if(m_array) {
               for(int i = 0; i < old_size; ++ i) {
                   m_array[i].~value_type();
               }
               free(m_array);
           }
           m_array = destination;
       }
   }
   return *this;
}

template<typename value_type>
vector<value_type>& vector<value_type>::operator=(vector<value_type> && other) {
     std::swap(m_array, other.m_array);
     std::swap(m_current_number,other.m_currentNumber);
     std::swap(m_max_number,other.m_maxNumber);
     other.m_array = nullptr;
     other.m_current_number = 0;
     other.m_max_number = 0;
}


template<typename value_type>
bool vector<value_type>::operator==(const vector<value_type> & other) const {
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

template<typename value_type>
bool vector<value_type>::operator!=(const vector< value_type >& other) const {
    return !this->operator==(other);
}

template<typename value_type>
value_type& vector<value_type>::front() {
    return m_array[0];
}

template<typename value_type>
value_type& vector<value_type>::back() {
    return m_array[m_current_number - 1];
}

template<typename value_type>
const value_type& vector<value_type>::front() const  {
    return m_array[0];
}

template<typename value_type>
const value_type & vector<value_type>::back() const {
    return m_array[m_current_number - 1];
}

template<typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
    return std::numeric_limits<size_type>::max() - 1;
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin()
{
    return iterator(m_array);
}

template<typename value_type>
typename vector<value_type>::iterator vector<value_type>::end()
{
    return iterator(m_array) + m_current_number;
}

template<typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin()
{
    return const_iterator(m_array);
}

template<typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() {
    return const_iterator(m_array) + m_current_number;
}

template<typename value_type>
typename vector<value_type>::reverse_iterator vector<value_type>::rbegin() {
    return reverse_iterator(end());
}
template<typename value_type>
typename vector<value_type>::reverse_iterator vector<value_type>::rend() {
    return reverse_iterator(begin());
}

template<typename value_type>
typename vector<value_type>::const_reverse_iterator vector<value_type>::crbegin() {
    return const_reverse_iterator(cend());
}

template<typename value_type>
typename vector<value_type>::const_reverse_iterator vector<value_type>::crend() {
    return const_reverse_iterator(cbegin());
}

template<typename value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::emplace (
    const_iterator position,
    Args&&... args) {
    auto pos = position - cbegin();
    try_reserve();
    for(auto i = m_current_number; i > pos; --i) {
        std::swap(m_array[i],m_array[i-1]);
    }
    m_current_number++;
//     m_array[pos].~value_type();
    return iterator(new (m_array + pos) value_type(args ...));
}

template<typename value_type>
template <class... Args>
void vector<value_type>::emplace_back (Args&&... args) {
    emplace(cend(),args...);
}

template<typename value_type>
void vector<value_type>::swap (vector<value_type> & other) {
     std::swap(m_array, other.m_array);
     std::swap(m_current_number,other.m_current_number);
     std::swap(m_max_number,other.m_max_number);
}

#endif
