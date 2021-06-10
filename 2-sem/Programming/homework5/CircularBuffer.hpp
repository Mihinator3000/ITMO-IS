#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <iterator>
#include <string>

template<class T>
class MyIterator
{
private:
    T* buffer;
    int b;
    int capacity;
    int current;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    MyIterator(T* buffer_, int b_, int capacity_, int current_)
    {
        buffer = buffer_;
        b = b_;
        capacity = capacity_;
        current = current_;
    }
    reference operator * ()
    {
        return buffer[(b + current) % capacity];
    }
    MyIterator& operator ++ ()
    {
        current++;
        return *this;
    }
    bool operator == (const MyIterator& s) const
    {
        return (current == s.current);
    }
    bool operator != (const MyIterator& s) const
    {
        return !(*this == s);
    }
    MyIterator& operator -- ()
    {
        current--;
        return *this;
    }
    MyIterator& operator += (difference_type s)
    {
        current += s;
        return *this;
    }
    MyIterator& operator -= (difference_type s)
    {
        return *this += -s;
    }
    reference operator[] (difference_type s) const
    {
        MyIterator t = *this;
        t += s;
        return t;
    }
    pointer operator->() const
    {
        return current;
    }
    bool operator < (const MyIterator& s)
    {
        return (current < s.current);
    }
    bool operator > (const MyIterator& s)
    {
        return (s < *this);
    }
    bool operator <= (const MyIterator& s)
    {
        return !(*this > s);
    }
    bool operator >= (const MyIterator& s)
    {
        return !(*this < s);
    }

    friend MyIterator operator + (MyIterator i, difference_type s)
    {
        i += s;
        return i;
    }
    friend MyIterator operator + (difference_type s, MyIterator i)
    {
        return i + s;
    }
    friend MyIterator operator - (MyIterator i, difference_type s)
    {
        i -= s;
        return i;
    }
    friend difference_type operator - (const MyIterator& a, const MyIterator& b)
    {
        return a.current - b.current;
    }

};

template<class T>
class CircularBuffer
{
private:
    T* buffer;
    int capacity;
    int b;
    int s;
public:
    CircularBuffer(int c)
    {
        buffer = new T[c];
        capacity = c;
        b = 0;
        s = 0;
    }
    ~CircularBuffer()
    {
        delete[] buffer;
    }
    MyIterator<T> begin() const
    {
        return MyIterator<T>(buffer, b, capacity, 0);
    }
    MyIterator<T> end() const
    {
        return MyIterator<T>(buffer, b, capacity, s);
    }
    void addFirst(const T& t)
    {
        if (b == 0)
            b = capacity - 1;
        else
            b--;
        buffer[b] = t;
        if (s != capacity)
            s++;
    }
    void addLast(const T& t)
    {
        buffer[(b + s) % capacity] = t;
        if (s != capacity)
            s++;
    }
    T first()
    {
        return buffer[b];
    }
    T last()
    {
        return buffer[(b + s - 1) % capacity];
    }
    T& operator [](int i)
    {
        if (i < 0 || i >= s)
        {
            std::string exc = "Call to the " + std::to_string(i) + " element, buffer size is " + std::to_string(s);
            throw std::out_of_range(exc);
        }
        return buffer[(b + i) % capacity];
    }
    const T operator [](int i) const
    {
        if (i < 0 || i >= s)
        {
            std::string exc = "Call to the " + std::to_string(i) + " element, buffer size is " + std::to_string(s);
            throw std::out_of_range(exc);
        }
        return buffer[(b + i) % capacity];
    }
    void delFirst()
    {
        b = (b + 1) % capacity;
        if (s != 0)
            s--;
    }
    void delLast()
    {
        if (s != 0)
            s--;
    }
    void changeCapacity(int c)
    {
        T* new_buffer = new T[c];
        if (c < s)
            s = c;
        int cur = b;
        for (int i = 0; i < s; i++)
        {
            new_buffer[i] = buffer[cur];
            cur = (cur + 1) % capacity;
        }
        delete[] buffer;
        buffer = new_buffer;
        b = 0;
        capacity = c;
    }
};

#endif // CIRCULARBUFFER_HPP
