#include "../exercise.hpp"
#include <gtest/gtest.h>

size_t allocations = 0;
size_t deallocations = 0;
void* operator new(size_t count)
{
    allocations += 1;
    return std::malloc(count);
}

void operator delete(void* ptr) noexcept
{
    deallocations += 1;
    std::free(ptr);
}

// check that allocation and deallocations still happen
TEST(MemoryAllocations, Allocations)
{
    allocations = 0;
    deallocations = 0;
    exercise();
    ASSERT_EQ(allocations, 2) << "No new happening!";
    ASSERT_EQ(deallocations, 2) << "No delete happening!";
}

// check that the function provides a valid answer
TEST(MemoryAllocations, ValidAnswer)
{
    const int answer = exercise();
    ASSERT_TRUE(answer == 1 || answer == 2 || answer == 3 || answer == 4) << "No answer provided! Pick one of 1, 2, 3, 4";
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}