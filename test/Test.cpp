#include "MyAllocator.h"
#include <vector>
#include "gtest/gtest.h"

struct MyAllocatorTest : testing::Test
{
};

TEST_F(MyAllocatorTest, test_for_my_allocator)
{
    int arr[3] {1, 2, 3};
    std::vector<int, MA::allocator<int>> vec{arr, arr + 3};
    ASSERT_EQ(1, vec[0]);
    ASSERT_EQ(2, vec[1]);
    ASSERT_EQ(3, vec[2]);
}
