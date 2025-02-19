#include "../vector.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <print>

template <typename T, typename U>
concept template_exists = requires { typename exercise::vector<T, U>; };
template <typename T>
concept template_exists_with_default = requires { typename exercise::vector<T>; };

TEST(vector, TemplateExist)
{
    ASSERT_TRUE((template_exists<int, std::allocator<int>>));
    ASSERT_TRUE((template_exists<bool, std::allocator<bool>>));
    ASSERT_TRUE((template_exists<std::unique_ptr<int>, std::allocator<std::unique_ptr<int>>>));
}

TEST(vector, DefaultTemplateArg)
{
    ASSERT_TRUE((template_exists_with_default<int>));
    ASSERT_TRUE((template_exists_with_default<std::unique_ptr<int>>));
}

TEST(vector, DefaultConstructor)
{
    exercise::vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 0);
}

TEST(vector, InitializerListConstructor)
{
    exercise::vector<int> vec{1, 2, 3, 4, 5};
    ASSERT_EQ(vec.size(), 5);
    ASSERT_GE(vec.capacity(), 5); // Capacity should be at least 5
}

TEST(vector, AllocatorConstructor)
{
    std::allocator<int> alloc;
    exercise::vector<int, std::allocator<int>> vec(alloc);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 0);
}

#include "../vector.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

//
// Constructor Tests
//

TEST(vector, CopyConstructor)
{
    exercise::vector<int> original{1, 2, 3};
    exercise::vector<int> copy(original);

    ASSERT_EQ(copy.size(), 3);
    ASSERT_EQ(copy.capacity(), 3);
    ASSERT_EQ(copy[0], 1);
    ASSERT_EQ(copy[1], 2);
    ASSERT_EQ(copy[2], 3);
}

TEST(vector, CopyAssignment)
{
    exercise::vector<int> original{10, 20, 30};
    exercise::vector<int> copy;
    copy = original;

    ASSERT_EQ(copy.size(), 3);
    ASSERT_EQ(copy.capacity(), 3);
    ASSERT_EQ(copy[0], 10);
    ASSERT_EQ(copy[1], 20);
    ASSERT_EQ(copy[2], 30);
}

TEST(vector, MoveConstructor)
{
    exercise::vector<int> original{5, 10, 15};
    exercise::vector<int> moved(std::move(original));

    ASSERT_EQ(moved.size(), 3);
    ASSERT_EQ(moved.capacity(), 3);
    ASSERT_EQ(moved[0], 5);
    ASSERT_EQ(moved[1], 10);
    ASSERT_EQ(moved[2], 15);

    ASSERT_EQ(original.size(), 0); // Moved-from object should be empty
    ASSERT_EQ(original.capacity(), 0);
}

TEST(vector, MoveAssignment)
{
    exercise::vector<int> original{100, 200, 300};
    exercise::vector<int> moved;
    moved = std::move(original);

    ASSERT_EQ(moved.size(), 3);
    ASSERT_EQ(moved.capacity(), 3);
    ASSERT_EQ(moved[0], 100);
    ASSERT_EQ(moved[1], 200);
    ASSERT_EQ(moved[2], 300);

    ASSERT_EQ(original.size(), 0);
    ASSERT_EQ(original.capacity(), 0);
}

TEST(vector, WithCapacity)
{
    auto vec = exercise::vector<int>::with_capacity(10);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 10);
}

TEST(vector, FillConstructor)
{
    exercise::vector<int> vec(5, 42); // Creates [42, 42, 42, 42, 42]

    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.capacity(), 5);
    for (size_t i = 0; i < 5; i++) {
        ASSERT_EQ(vec[i], 42);
    }
}

//
// Accessor Tests
//

TEST(vector, AccessorMethods)
{
    exercise::vector<int> vec{1, 2, 3};

    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_FALSE(vec.empty());

    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
    ASSERT_EQ(vec[2], 3);

    ASSERT_EQ(vec.front(), 1);
    ASSERT_EQ(vec.back(), 3);
}

TEST(vector, OutOfBoundsAccess)
{
    exercise::vector<int> vec{10, 20, 30};

    ASSERT_THROW(vec.at(3), std::out_of_range);
}

TEST(vector, DataMethod)
{
    exercise::vector<int> vec{7, 14, 21};

    int* ptr = vec.data();
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(ptr[0], 7);
    ASSERT_EQ(ptr[1], 14);
    ASSERT_EQ(ptr[2], 21);
}

//
// Modification Tests
//

TEST(vector, PushBackCopy)
{
    exercise::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 2); // Should grow at least to fit two elements
    ASSERT_EQ(vec[0], 10);
    ASSERT_EQ(vec[1], 20);
}

TEST(vector, PushBackMove)
{
    exercise::vector<std::unique_ptr<int>> vec;

    auto ptr1 = std::make_unique<int>(100);
    auto ptr2 = std::make_unique<int>(200);

    vec.push_back(std::move(ptr1));
    vec.push_back(std::move(ptr2));

    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 2);
    ASSERT_NE(vec[0], nullptr);
    ASSERT_NE(vec[1], nullptr);
    ASSERT_EQ(*vec[0], 100);
    ASSERT_EQ(*vec[1], 200);
}

TEST(vector, EmplaceBack)
{
    exercise::vector<std::string> vec;
    vec.emplace_back(5, 'a'); // Creates "aaaaa"
    vec.emplace_back(3, 'b'); // Creates "bbb"

    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 2);
    ASSERT_EQ(vec[0], "aaaaa");
    ASSERT_EQ(vec[1], "bbb");
}

TEST(vector, PopBack)
{
    exercise::vector<int> vec{1, 2, 3};
    vec.pop_back();

    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 3); // Capacity remains unchanged
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

TEST(vector, Reserve)
{
    exercise::vector<int> vec;
    vec.reserve(10);

    ASSERT_EQ(vec.size(), 0);
    ASSERT_GE(vec.capacity(), 10); // Capacity should be at least 10

    vec.reserve(5); // Should not shrink
    ASSERT_GE(vec.capacity(), 10);
}

TEST(vector, Clear)
{
    exercise::vector<int> vec{5, 10, 15};
    vec.clear();

    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 3); // Capacity should remain unchanged
}

TEST(vector, IteratorBeginEnd)
{
    exercise::vector<int> vec{1, 2, 3, 4, 5};

    auto it = vec.begin();
    auto end = vec.end();

    ASSERT_EQ(*it, 1);
    ASSERT_NE(it, end);
    ++it;
    ASSERT_EQ(*it, 2);
    it++;
    ASSERT_EQ(*it, 3);
}

TEST(vector, ConstIterator)
{
    const exercise::vector<int> vec{10, 20, 30};

    auto it = vec.begin();
    auto end = vec.end();

    ASSERT_EQ(*it, 10);
    ++it;
    ASSERT_EQ(*it, 20);
    it++;
    ASSERT_EQ(*it, 30);
    ASSERT_NE(it, end);
}

TEST(vector, ReverseIterator)
{
    exercise::vector<int> vec{1, 2, 3};

    auto it = vec.rbegin();
    auto end = vec.rend();

    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 2);
    it++;
    ASSERT_EQ(*it, 1);
    ASSERT_NE(it, end);
}

TEST(vector, ConstReverseIterator)
{
    const exercise::vector<int> vec{5, 6, 7};

    auto it = vec.rbegin();
    auto end = vec.rend();

    ASSERT_EQ(*it, 7);
    ++it;
    ASSERT_EQ(*it, 6);
    it++;
    ASSERT_EQ(*it, 5);
    ASSERT_NE(it, end);
}

TEST(vector, IteratorTraits)
{
    using iterator = typename exercise::vector<int>::iterator;
    using const_iterator = typename exercise::vector<int>::const_iterator;
    using reverse_iterator = typename exercise::vector<int>::reverse_iterator;
    using const_reverse_iterator = typename exercise::vector<int>::const_reverse_iterator;

    static_assert(std::input_iterator<iterator>);
    static_assert(std::forward_iterator<iterator>);
    static_assert(std::bidirectional_iterator<iterator>);
    static_assert(std::random_access_iterator<iterator>);

    static_assert(std::input_iterator<const_iterator>);
    static_assert(std::forward_iterator<const_iterator>);
    static_assert(std::bidirectional_iterator<const_iterator>);
    static_assert(std::random_access_iterator<const_iterator>);

    static_assert(sizeof(iterator) <= 8);
    static_assert(sizeof(const_iterator) <= 8);
    static_assert(sizeof(reverse_iterator) <= 8);
    static_assert(sizeof(const_reverse_iterator) <= 8);
}
