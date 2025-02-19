#include "../exercise.hpp"
#include <gtest/gtest.h>

namespace check {
// struct A
// {
//   uint32_t a;
//   uint16_t b;
//   uint8_t c;
// };
template <typename T>
concept A = requires(T& t) {
    requires std::same_as<decltype(t.a), uint32_t>;
    requires std::same_as<decltype(t.b), uint16_t>;
    requires std::same_as<decltype(t.c), uint8_t>;
};
// struct B
// {
//   uint8_t a[2];
//   uint64_t b;
//   uint8_t c[2];
// };
template <typename T>
concept B = requires(T& t) {
    requires std::same_as<decltype(t.a), uint8_t[2]>;
    requires std::same_as<decltype(t.b), uint64_t>;
    requires std::same_as<decltype(t.c), uint8_t[2]>;
};
// struct C
// {
//   uint32_t a;
//   char b;
//   uint32_t c;
// };
template <typename T>
concept C = requires(T& t) {
    requires std::same_as<decltype(t.a), uint32_t>;
    requires std::same_as<decltype(t.b), char>;
    requires std::same_as<decltype(t.c), uint32_t>;
    requires std::same_as<decltype(t.d), char>;
};
// struct D
// {
//   uint8_t a;
//   uint64_t b;
//   uint8_t c;
//   C d;
// };
template <typename T>
concept D = requires(T& t) {
    requires std::same_as<decltype(t.a), uint8_t>;
    requires std::same_as<decltype(t.b), uint64_t>;
    requires std::same_as<decltype(t.c), uint8_t>;
    requires std::same_as<decltype(t.d), struct_layout_and_inheritance::C>;
};
}

// this checks that all members are still present and have their original type
TEST(StructLayoutAndInheritance, MembersStillExist)
{
    ASSERT_TRUE(check::A<struct_layout_and_inheritance::A>) << "Name or type of members in A changed!";
    ASSERT_TRUE(check::B<struct_layout_and_inheritance::B>) << "Name or type of members in B changed!";
    ASSERT_TRUE(check::C<struct_layout_and_inheritance::C>) << "Name or type of members in C changed!";
    ASSERT_TRUE(check::D<struct_layout_and_inheritance::D>) << "Name or type of members in D changed!";
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}