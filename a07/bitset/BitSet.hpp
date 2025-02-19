#pragma once
#include <cstddef>
#include <iterator>
#include <vector>

//---------------------------------------------------------------------------
namespace bitset {
//---------------------------------------------------------------------------
/// A bitset
class BitSet
{
private:
    /// The number of elements in the bitset
    size_t elements = 0;
    /// The storage for the bitset (keep the name as it is used during testing)
    std::vector<unsigned char> bytes;
    /// Friend declaration for one of the tests
    friend class TestBitSet_correctVectorUsage_Test;

public:
    /// A read-write adapter for an individual bit
    class BitReference
    {
    private:
        unsigned char& byte;
        unsigned char mask;

    public:
        BitReference(unsigned char& byte, unsigned char mask) : byte(byte), mask(mask) {}
        operator bool() const;
        BitReference& operator=(bool value);
        BitReference& operator=(const BitReference& other);
    };
    /// A bit iterator
    class BitIterator
    {
        // using iterator_category = std::bidirectional_iterator_tag;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = bool;
        using reference = BitReference;

        BitIterator(unsigned char* bytePtr,
            size_t bitIndex) : bytePtr(bytePtr), bitIndex(bitIndex) {}
        BitIterator() : bytePtr(nullptr), bitIndex(0) {}

        bool operator==(const BitIterator& other) const;
        reference operator*() const;

        BitIterator operator++(int);
        BitIterator& operator++();
        BitIterator operator--(int);
        BitIterator& operator--();

    private:
        unsigned char* bytePtr;
        size_t bitIndex;
    };
    /// A bit iterator
    class ConstBitIterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = bool;
        using reference = bool;

        ConstBitIterator(const unsigned char* bytePtr, const size_t bitIndex) : bytePtr(bytePtr), bitIndex(bitIndex) {}
        ConstBitIterator() : bytePtr(nullptr), bitIndex(0) {}

        bool operator==(ConstBitIterator other) const;
        reference operator*() const;

        ConstBitIterator operator++(int);
        ConstBitIterator& operator++();
        ConstBitIterator operator--(int);
        ConstBitIterator& operator--();

    private:
        const unsigned char* bytePtr;
        size_t bitIndex;
    };
    /// Constructor
    BitSet() = default;
    /// Constructor
    explicit BitSet(size_t size);

    /// Return the number of bits in the bitset
    size_t size() const;
    /// Return the number of bits set to true
    size_t cardinality() const;

    /// Insert a bit at the end of the bit set
    void push_back(bool bit);

    /// Access the first bit
    BitReference front();
    /// Access the first bit
    bool front() const;
    /// Access the last bit
    BitReference back();
    /// Access the last bit
    bool back() const;

    /// Iterator pointing to the first element
    BitIterator begin();
    /// Iterator pointing past the end
    BitIterator end();

    /// ConstIterator pointing to the first element
    ConstBitIterator begin() const;
    /// ConstIterator pointing past the end
    ConstBitIterator end() const;

    /// Access a bit
    BitReference operator[](size_t bit);
    /// Access a bit
    bool operator[](size_t bit) const;
};
//---------------------------------------------------------------------------
} // namespace bitset
//---------------------------------------------------------------------------