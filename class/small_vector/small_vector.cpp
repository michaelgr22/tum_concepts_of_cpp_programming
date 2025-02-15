#include <iostream>
#include <memory>
#include <cassert>

template <typename T, std::size_t N = 4>
class SmallVector {
private:
    std::size_t m_size = 0;
    std::size_t m_capacity = N;
    T* m_dynamic = nullptr;
    alignas(T) unsigned char m_inline[N * sizeof(T)]; // Inline storage

    T* data_ptr() {
        return m_dynamic ? m_dynamic : reinterpret_cast<T*>(m_inline);
    }

    void grow(std::size_t new_capacity) {
        T* new_data = new T[new_capacity];

        // Move elements
        for (std::size_t i = 0; i < m_size; ++i)
            new_data[i] = std::move(data_ptr()[i]);

        // Free old memory if dynamic
        if (m_dynamic) delete[] m_dynamic;

        m_dynamic = new_data;
        m_capacity = new_capacity;
    }

public:
    SmallVector() = default;

    ~SmallVector() {
        clear();
        if (m_dynamic) delete[] m_dynamic;
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) grow(m_capacity * 2);
        new (data_ptr() + m_size) T(value); // Placement new
        ++m_size;
    }

    void pop_back() {
        if (m_size > 0) {
            --m_size;
            data_ptr()[m_size].~T(); // Explicit destructor call
        }
    }

    T& operator[](std::size_t index) {
        assert(index < m_size);
        return data_ptr()[index];
    }

    std::size_t size() const { return m_size; }
    std::size_t capacity() const { return m_capacity; }

    void clear() {
        for (std::size_t i = 0; i < m_size; ++i)
            data_ptr()[i].~T();
        m_size = 0;
    }
};

int main() {
    SmallVector<int, 4> vec;
    
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50); // This will trigger dynamic allocation

    std::cout << "Size: " << vec.size() << "\n";
    std::cout << "Capacity: " << vec.capacity() << "\n";

    for (std::size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    
    return 0;
}

