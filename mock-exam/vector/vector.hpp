#pragma once
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
namespace exercise {

template <typename T, typename Alloc = std::allocator<T>>
class vector
{
private:
    Alloc allocator;
    size_t _size;
    size_t _capacity;
    bool _empty;
    T* _data;

public:
    using value_type = T;
    using allocator_type = Alloc;

    // constructors
    explicit vector(Alloc alloc = std::allocator<T>()) : allocator(alloc), _size(0), _capacity(0) {}
    vector(std::initializer_list<T> l, Alloc alloc = std::allocator<T>())
    {
        allocator = alloc;
        _data = allocator.allocate(l.size());
        size_t index = 0;
        for (const auto& item : l) {
            new (_data + index) T(item); // Use placement new
            ++index;
        }
        _size = l.size();
        _capacity = l.size();
    }
    vector(size_t count, const T& value)
    {
        allocator = std::allocator<T>();
        _size = count;
        _capacity = count;
        _data = allocator.allocate(count);
        for (size_t i = 0; i < count; i++) {
            new (_data + i) T(value);
        }
    }

    // destructor
    ~vector() noexcept
    {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].~T(); // Explicitly call the destructor
        }
        allocator.deallocate(_data, _capacity); // Free allocated memor}
    }

    // copy constructors
    vector(const vector& other) noexcept
    {
        allocator = other.allocator;
        _data = allocator.allocate(other._size);
        for (size_t i = 0; i < other._size; i++) {
            new (_data + i) T(other._data[i]); // Use placement new
        }
        _size = other._size;
        _capacity = other._size;
    }
    vector& operator=(const vector& other) noexcept
    {
        // Destroy previously allocated memory
        for (size_t i = 0; i < _size; i++) {
            _data[i].~T();
        }
        allocator.deallocate(_data, _capacity);

        if (this != &other) {
            allocator = other.allocator;
            _data = allocator.allocate(other._size);
            for (size_t i = 0; i < other._size; i++) {
                new (_data + i) T(other._data[i]); // Use placement new
            }
            _size = other._size;
            _capacity = other._size;
        }
        return *this;
    }

    // move constructors
    vector(vector&& other) noexcept
    {
        // Steal the data pointer and metadata
        allocator = std::move(other.allocator); // Move allocator (if needed)
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        // Leave 'other' in a valid empty state
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    vector& operator=(vector&& other) noexcept
    {
        if (this != &other) {
            // Free existing resources
            for (size_t i = 0; i < _size; i++) {
                _data[i].~T();
            }
            allocator.deallocate(_data, _capacity);

            // Steal resources from 'other'
            allocator = std::move(other.allocator);
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;

            // Leave 'other' in an empty state
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // operators
    T& operator[](size_t idx) const noexcept
    {
        return _data[idx];
    } // reference to avoid unnecessary copy and allow change of value

    // getter
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }
    bool empty() const noexcept { return _empty; }
    T& at(size_t idx) const
    {
        if (idx < 0 || idx > _size - 1) {
            throw std::out_of_range("Index out of range");
        } else {
            return _data[idx];
        }
    }
    T* data() const noexcept { return _data; };
    T& front() const noexcept { return _data[0]; }
    T& back() const noexcept { return _data[_size - 1]; }

    // modifications
    void push_back(const T& element)
    {
        if (_size == _capacity) {
            size_t new_capacity = (_capacity + 1) * 2;
            T* new_data = allocator.allocate(new_capacity);

            for (size_t i = 0; i < _size; i++) {
                new (new_data + i) T(_data[i]);
            }

            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            allocator.deallocate(_data, _capacity);

            _data = new_data;
            _capacity = new_capacity;
        }
        new (_data + _size) T(element);
        _size++;
    }

    void push_back(T&& element)
    {
        if (_size == _capacity) {
            size_t new_capacity = (_capacity + 1) * 2;
            T* new_data = allocator.allocate(new_capacity);

            for (size_t i = 0; i < _size; i++) {
                new (new_data + i) T(std::move(_data[i]));
            }

            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            allocator.deallocate(_data, _capacity);

            _data = new_data;
            _capacity = new_capacity;
        }
        new (_data + _size) T(std::move(element));
        _size++;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args)
    {
        if (_size == _capacity) {
            size_t new_capacity = (_capacity + 1) * 2;
            T* new_data = allocator.allocate(new_capacity);

            for (size_t i = 0; i < _size; i++) {
                new (new_data + i) T(_data[i]);
            }

            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            allocator.deallocate(_data, _capacity);

            _data = new_data;
            _capacity = new_capacity;
        }
        new (_data + _size) T(std::forward<Args>(args)...);
        _size++;

        return _data[_size - 1];
    }

    void pop_back()
    {
        if (_size > 0) {
            _data[_size - 1].~T();
            --_size;
        }
    }

    void reserve(size_t capacity)
    {
        if (_capacity < capacity) {
            size_t new_capacity = capacity;
            T* new_data = allocator.allocate(new_capacity);

            for (size_t i = 0; i < _capacity; i++) {
                new (new_data + i) T(_data[i]);
            }

            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            allocator.deallocate(_data, _capacity);

            _data = new_data;
            _capacity = new_capacity;
        }
    }

    void clear()
    {
        if (_size > 0) {
            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T(); // Explicitly call the destructor
            }
        }
        _size = 0;
    }

    // iterators
    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit iterator(pointer p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }

        reference operator[](difference_type n) const { return *(ptr + n); }

        iterator& operator++()
        {
            ++ptr;
            return *this;
        } // Prefix increment
        iterator operator++(int)
        {
            iterator temp = *this;
            ++ptr;
            return temp;
        } // Postfix increment

        iterator& operator--()
        {
            --ptr;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        iterator& operator+=(difference_type n)
        {
            ptr += n;
            return *this;
        }
        iterator& operator-=(difference_type n)
        {
            ptr -= n;
            return *this;
        }

        friend iterator operator+(const iterator& it, difference_type n)
        {
            iterator temp = it;
            temp += n;
            return temp;
        }
        friend iterator operator+(difference_type n, const iterator& it) { return it + n; }
        friend iterator operator-(const iterator& it, difference_type n)
        {
            iterator temp = it;
            temp -= n;
            return temp;
        }
        friend difference_type operator-(const iterator& lhs, const iterator& rhs) { return lhs.ptr - rhs.ptr; }

        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr == rhs.ptr; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }
        friend bool operator<(const iterator& lhs, const iterator& rhs) { return lhs.ptr < rhs.ptr; }
        friend bool operator>(const iterator& lhs, const iterator& rhs) { return rhs < lhs; }
        friend bool operator<=(const iterator& lhs, const iterator& rhs) { return !(rhs < lhs); }
        friend bool operator>=(const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }

    private:
        pointer ptr;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        explicit const_iterator(pointer p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }
        reference operator[](difference_type n) const { return *(ptr + n); }

        const_iterator& operator++()
        {
            ++ptr;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }
        const_iterator& operator--()
        {
            --ptr;
            return *this;
        }
        const_iterator operator--(int)
        {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        const_iterator& operator+=(difference_type n)
        {
            ptr += n;
            return *this;
        }
        const_iterator& operator-=(difference_type n)
        {
            ptr -= n;
            return *this;
        }

        friend const_iterator operator+(const const_iterator& it, difference_type n)
        {
            iterator temp = it;
            temp += n;
            return temp;
        }
        friend const_iterator operator+(difference_type n, const const_iterator& it) { return it + n; }
        friend const_iterator operator-(const const_iterator& it, difference_type n)
        {
            const_iterator temp = it;
            temp -= n;
            return temp;
        }
        friend difference_type operator-(const const_iterator& lhs, const const_iterator& rhs)
        {
            return lhs.ptr - rhs.ptr;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) { return lhs.ptr == rhs.ptr; }
        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) { return !(lhs == rhs); }
        friend bool operator<(const const_iterator& lhs, const const_iterator& rhs) { return lhs.ptr < rhs.ptr; }
        friend bool operator>(const const_iterator& lhs, const const_iterator& rhs) { return rhs < lhs; }
        friend bool operator<=(const const_iterator& lhs, const const_iterator& rhs) { return !(rhs < lhs); }
        friend bool operator>=(const const_iterator& lhs, const const_iterator& rhs) { return !(lhs < rhs); }

    private:
        pointer ptr;
    };

    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data + _size); }

    const_iterator begin() const { return const_iterator(_data); }
    const_iterator end() const { return const_iterator(_data + _size); }
    const_iterator cbegin() const { return const_iterator(_data); }
    const_iterator cend() const { return const_iterator(_data + _size); }

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    // static
    static vector with_capacity(size_t capacity) noexcept
    {
        vector vec = vector();
        vec._data = vec.allocator.allocate(capacity);
        vec._size = 0;
        vec._capacity = capacity;
        return vec;
    }
};
} // namespace exercise