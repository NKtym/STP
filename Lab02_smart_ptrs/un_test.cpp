#include "un.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(TestUnique, Dereferenc) {
  UniquePtr<int> un(new int(6));
  EXPECT_EQ(*un, 6);
}

TEST(TestUnique, Creation) {
  UniquePtr<int> un(new int(6));
  EXPECT_NE(un.get(), nullptr);
}

TEST(TestUnique, Move) {
  UniquePtr<int> un(new int(6));
  UniquePtr<int> un2(std::move(un));
  EXPECT_EQ(un.get(), nullptr);
  EXPECT_NE(un2.get(), nullptr);
  EXPECT_EQ(*un2, 6);
}

TEST(TestUnique, MoveAssignment) {
  UniquePtr<int> un(new int(6));
  UniquePtr<int> un2(new int(7));
  un2 = std::move(un);
  EXPECT_EQ(un.get(), nullptr);
  EXPECT_NE(un2.get(), nullptr);
  EXPECT_EQ(*un2, 6);
}

TEST(TestUnique, Access) {
  struct TestStruct {
    int x = 6;
  };
  UniquePtr<TestStruct> un(new TestStruct());
  EXPECT_EQ(un->x, 6);
}

TEST(TestUnique, Reset) {
  UniquePtr<int> un(new int(6));
  un.reset(new int(7));
  EXPECT_EQ(*un, 7);
}