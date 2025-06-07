#include "sh.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(TestShared, Dereferenc) {
  SharedPtr<int> sh(new int(6));
  EXPECT_EQ(*sh, 6);
}

TEST(TestShared, Creation) {
  SharedPtr<int> sh(new int(6));
  EXPECT_NE(sh.get(), nullptr);
  EXPECT_EQ(sh.use_count(), 1);
}

TEST(TestShared, Copy) {
  SharedPtr<int> sh(new int(6));
  SharedPtr<int> sh2(sh);
  EXPECT_EQ(sh.get(), sh2.get());
  EXPECT_EQ(*sh, 6);
  EXPECT_EQ(sh.use_count(), 2);
}

TEST(TestShared, CopyAssignment) {
  SharedPtr<int> sh(new int(6));
  SharedPtr<int> sh2(new int(7));
  sh = sh2;
  EXPECT_EQ(sh.get(), sh2.get());
  EXPECT_EQ(*sh, 7);
  EXPECT_EQ(sh.use_count(), 2);
}

TEST(TestShared, Move) {
  SharedPtr<int> sh(new int(6));
  SharedPtr<int> sh2(std::move(sh));
  EXPECT_EQ(sh.get(), nullptr);
  EXPECT_NE(sh2.get(), nullptr);
  EXPECT_EQ(*sh2, 6);
  EXPECT_EQ(sh2.use_count(), 1);
}

TEST(TestShared, MoveAssignment) {
  SharedPtr<int> sh(new int(6));
  SharedPtr<int> sh2(new int(7));
  sh = std::move(sh2);
  EXPECT_NE(sh.get(), nullptr);
  EXPECT_EQ(sh2.get(), nullptr);
  EXPECT_EQ(*sh, 7);
  EXPECT_EQ(sh.use_count(), 1);
}

TEST(TestShared, Access) {
  struct TestStruct {
    int x = 6;
  };
  SharedPtr<TestStruct> sh(new TestStruct());
  EXPECT_EQ(sh->x, 6);
}
//
TEST(TestSharedReset, Reset) {
  SharedPtr<int> sh(new int(6));
  sh.reset(new int(7));
  EXPECT_EQ(*sh, 7);
}

TEST(TestShared, UseCount) {
  SharedPtr<int> sh(new int(6));
  SharedPtr<int> sh2(sh);
  SharedPtr<int> sh3(sh);
  EXPECT_EQ(sh.use_count(), 3);
}

TEST(TestShared, Destructor) {
  int* raw_ptr = new int(3);
  {
    SharedPtr<int> sh(raw_ptr);
    EXPECT_EQ(sh.use_count(), 1);
  }
  //Сугубо для проверки на утечки
}