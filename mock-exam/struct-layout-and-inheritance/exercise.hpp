#include <cstdint>
/*
namespace struct_layout_and_inheritance {
struct A
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
};
struct B : A
{
    uint8_t a[2];
    uint64_t b;
    uint8_t c[2];
};
struct C : B
{
    uint32_t a;
    char b;
    uint32_t c;
    char d;
};
struct D : A
{
    uint8_t a;
    uint64_t b;
    uint8_t c;
    C d;
};
} // namespace struct_layout_and_inheritance
*/
namespace struct_layout_and_inheritance {
struct A
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
};
struct B : A
{
    uint64_t b;
    uint8_t a[2];
    uint8_t c[2];
};
struct C : B
{
    uint32_t a;
    uint32_t c;
    char b;
    char d;
};
struct D : A
{
    C d;
    uint64_t b;
    uint8_t a;
    uint8_t c;
};
} // namespace struct_layout_and_inheritance