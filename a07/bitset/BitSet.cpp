#include "BitSet.hpp"
#include <cstddef>
#include <print>

using namespace bitset;

BitSet::BitSet(size_t size)
{
    size_t number_of_bytes;
    if ((elements % 8) == 0) {
        number_of_bytes = size / 8;
    } else {
        number_of_bytes = (size / 8) + 1;
    }
    bytes.resize(number_of_bytes);
    for (size_t i = 0; i < number_of_bytes; i++) {
        bytes[i] = 0;
    }
    elements = size;
}

size_t BitSet::size() const
{
    return elements;
}

size_t BitSet::cardinality() const
{
    int count_true = 0;
    unsigned char mask = 0b00000001;
    for (unsigned char byte : bytes) {
        for (int i = 0; i < 8; i++) {
            count_true += (byte & mask);
            byte >>= 1;
        }
    }
    return count_true;
}

void BitSet::push_back(bool bit)
{
    if (elements % 8 == 0) {
        // Need a new byte if the current byte is full
        bytes.push_back(bit ? 0b10000000 : 0);
    } else {
        // Add bit to the last byte
        bytes.back() |= (bit << (7 - (elements % 8)));
    }
    elements++;
}

bool BitSet::operator[](size_t bit) const
{
    size_t byte = bit / 8;
    size_t bit_pos = bit % 8; // Correctly get bit position within byte
    unsigned char mask = 0b10000000 >> bit_pos; // Shift right by the bit position
    return (bytes[byte] & mask) != 0;
}

BitSet::BitReference BitSet::operator[](size_t bit)
{
    size_t byte = bit / 8;
    size_t bit_pos = bit % 8;
    unsigned char mask = 0b10000000 >> bit_pos; // Shift right by bit position

    return {bytes[byte], mask};
}

BitSet::BitReference BitSet::front()
{
    unsigned char mask = 0b10000000;
    return {bytes.front(), mask};
}

bool BitSet::front() const
{
    unsigned char mask = 0b10000000;
    return (bytes.front() & mask) != 0;
}

BitSet::BitReference BitSet::back()
{
    size_t last_bit_pos = (elements - 1) % 8; // Find the last bit position
    unsigned char mask = 0b10000000 >> last_bit_pos; // Shift right accordingly
    return {bytes.back(), mask};
}

bool BitSet::back() const
{
    size_t last_bit_pos = (elements - 1) % 8;
    unsigned char mask = 0b10000000 >> last_bit_pos;
    return (bytes.back() & mask) != 0;
}

BitSet::BitIterator BitSet::begin()
{
    return {&bytes[0], 0};
}

BitSet::BitIterator BitSet::end()
{
    size_t last_bit_pos = (elements - 1) % 8;
    return {&bytes.back(), last_bit_pos};
}

BitSet::ConstBitIterator BitSet::begin() const
{
    return {&bytes[0], 0};
}

BitSet::ConstBitIterator BitSet::end() const
{
    size_t last_bit_pos = (elements - 1) % 8;
    return {&bytes.back(), last_bit_pos};
}
// ########################################################

BitSet::BitReference::operator bool() const
{
    return (byte & mask) != 0;
}

BitSet::BitReference& BitSet::BitReference::operator=(bool value)
{
    if (value)
        byte |= mask;
    else
        byte &= ~mask;
    return *this;
}

BitSet::BitReference& BitSet::BitReference::operator=(const BitReference& other)
{
    return *this = static_cast<bool>(other);
}

// ########################################################

bool BitSet::BitIterator::operator==(const BitIterator& other) const { return (*bytePtr == *other.bytePtr && bitIndex == other.bitIndex); }
BitSet::BitIterator::reference BitSet::BitIterator::operator*() const
{
    return {*bytePtr, static_cast<unsigned char>(1 << (7 - bitIndex))};
}
BitSet::BitIterator BitSet::BitIterator::operator++(int)
{
    BitIterator retval = *this;
    if (bitIndex == 7) {
        bitIndex = 0;
        bytePtr++;
    } else {
        bitIndex++;
    }
    return retval;
}
BitSet::BitIterator& BitSet::BitIterator::operator++()
{
    if (bitIndex == 7) {
        bitIndex = 0;
        bytePtr++; // Move to the next byte
    } else {
        bitIndex++; // Just increment the bit index
    }
    return *this; // Return the updated iterator
}
BitSet::BitIterator BitSet::BitIterator::operator--(int)
{
    BitIterator retval = *this;
    if (bitIndex == 0) {
        bitIndex = 7;
        bytePtr--;
    } else {
        bitIndex--;
    }
    return retval;
}
BitSet::BitIterator& BitSet::BitIterator::operator--()
{
    if (bitIndex == 0) {
        bitIndex = 7;
        bytePtr--; // Move to the next byte
    } else {
        bitIndex--; // Just increment the bit index
    }
    return *this; // Return the updated iterator
}

// ################################################################
bool BitSet::ConstBitIterator::operator==(ConstBitIterator other) const
{
    return (*bytePtr == *other.bytePtr && bitIndex == other.bitIndex);
}

BitSet::ConstBitIterator::reference BitSet::ConstBitIterator::operator*() const
{
    unsigned char mask = static_cast<unsigned char>(1 << (7 - bitIndex));
    return (*bytePtr & mask) != 0;
}

BitSet::ConstBitIterator BitSet::ConstBitIterator::operator++(int)
{
    ConstBitIterator retval = *this;
    if (bitIndex == 7) {
        bitIndex = 0;
        bytePtr++;
    } else {
        bitIndex++;
    }
    return retval;
}

BitSet::ConstBitIterator& BitSet::ConstBitIterator::operator++()
{
    if (bitIndex == 7) {
        bitIndex = 0;
        bytePtr++;
    } else {
        bitIndex++;
    }
    return *this;
}

BitSet::ConstBitIterator BitSet::ConstBitIterator::operator--(int)
{
    ConstBitIterator retval = *this;
    if (bitIndex == 0) {
        bitIndex = 7;
        bytePtr--;
    } else {
        bitIndex--;
    }
    return retval;
}

BitSet::ConstBitIterator& BitSet::ConstBitIterator::operator--()
{
    if (bitIndex == 0) {
        bitIndex = 7;
        bytePtr--;
    } else {
        bitIndex--;
    }
    return *this;
}