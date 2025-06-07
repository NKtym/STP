#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "two_linked_list.hpp"

TEST(LinkedListTest, StdFindAlgorithm) {
  std::vector<int> data = {1, 2, 3, 4, 5};
  LinkedList<int> list(data.begin(), data.end());
  auto it = std::find(list.begin(), list.end(), 3);
  EXPECT_NE(it, list.end());
  EXPECT_EQ(*it, 3);
  it = std::find(list.begin(), list.end(), 100);
  EXPECT_EQ(it, list.end());
}

TEST(LinkedListTest, StdReverseAlgorithm) {
  std::vector<int> data = {1, 2, 3, 4, 5};
  LinkedList<int> list(data.begin(), data.end());
  std::reverse(list.begin(), list.end());
  std::vector<int> expected = {5, 4, 3, 2, 1};
  std::vector<int> result;
  for (auto it = list.begin(); it != list.end(); ++it)
    result.push_back(*it);
  EXPECT_EQ(result, expected);
}

/*TEST(LinkedListTest, StdSortAlgorithm) {
    std::vector<int> data = {5, 2, 8, 1, 9};
    LinkedList<int> list(data.begin(), data.end());
    std::sort(list.begin(), list.end());
}*/