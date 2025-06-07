#include <gtest/gtest.h>
#include "time_and_time_span.hpp"

using namespace my_namespace;
using namespace my_namespace::literals;

TEST(TimeSpanTest, Add) {
  TimeSpan span1(1, 2, 30, 15);
  TimeSpan span2(0, 3, 20, 45);
  TimeSpan result = span1 + span2;
  EXPECT_EQ(result.getDays(), 1);
  EXPECT_EQ(result.getHours(), 5);
  EXPECT_EQ(result.getMinutes(), 51);
  EXPECT_EQ(result.getSeconds(), 0);
}

TEST(TimeSpanTest, SubTimeSpan) {
  TimeSpan span1(2, 5, 40, 30);
  TimeSpan span2(1, 3, 20, 15);
  TimeSpan result = span1 - span2;
  EXPECT_EQ(result.getDays(), 1);
  EXPECT_EQ(result.getHours(), 2);
  EXPECT_EQ(result.getMinutes(), 20);
  EXPECT_EQ(result.getSeconds(), 15);
}

TEST(TimeSpanTest, SubTimeSpan2) {
  TimeSpan span1(2, 5, 40, 30);
  TimeSpan span2(1, 3, 41, 15);
  TimeSpan result = span1 - span2;
  EXPECT_EQ(result.getDays(), 1);
  EXPECT_EQ(result.getHours(), 1);
  EXPECT_EQ(result.getMinutes(), 59);
  EXPECT_EQ(result.getSeconds(), 15);
}

TEST(TimeSpanTest, GetTimeSpan) {
  TimeSpan span(5, 6, 7, 8);
  std::stringstream ss;
  ss << span;
  EXPECT_EQ(ss.str(), "5d 6h 7m 8s");
}

TEST(TimeTest, AddTimeTimeSpan) {
  Time time(1, 10, 20, 30);
  TimeSpan span(0, 2, 30, 35);
  Time result = time + span;
  EXPECT_EQ(result.getDays(), 1);
  EXPECT_EQ(result.getHours(), 12);
  EXPECT_EQ(result.getMinutes(), 51);
  EXPECT_EQ(result.getSeconds(), 5);
}

TEST(TimeTest, AddTimeTimeSpan2) {
  Time time(1, 10, 20, 30);
  TimeSpan span(60, 2, 30, 35);
  Time result = time + span;
  EXPECT_EQ(result.getDays(), 61);
  EXPECT_EQ(result.getHours(), 12);
  EXPECT_EQ(result.getMinutes(), 51);
  EXPECT_EQ(result.getSeconds(), 5);
}

TEST(TimeTest, SubTimeTimeSpan) {
  Time time(2, 12, 30, 45);
  TimeSpan span(1, 13, 15, 30);
  Time result = time - span;
  EXPECT_EQ(result.getDays(), 0);
  EXPECT_EQ(result.getHours(), 23);
  EXPECT_EQ(result.getMinutes(), 15);
  EXPECT_EQ(result.getSeconds(), 15);
}

TEST(TimeTest, SubTime) {
  Time time1(3, 15, 45, 50);
  Time time2(1, 10, 30, 25);
  TimeSpan result = time1 - time2;
  EXPECT_EQ(result.getDays(), 2);
  EXPECT_EQ(result.getHours(), 5);
  EXPECT_EQ(result.getMinutes(), 15);
  EXPECT_EQ(result.getSeconds(), 25);
}

TEST(TimeSpanLiteralsTest, LiteralCreation) {
  TimeSpan span1 = 3_d;
  TimeSpan span2 = 5_h;
  TimeSpan span3 = 20_m;
  TimeSpan span4 = 45_s;
  EXPECT_EQ(span1.getDays(), 3);
  EXPECT_EQ(span1.getHours(), 0);
  EXPECT_EQ(span1.getMinutes(), 0);
  EXPECT_EQ(span1.getSeconds(), 0);
  EXPECT_EQ(span2.getDays(), 0);
  EXPECT_EQ(span2.getHours(), 5);
  EXPECT_EQ(span2.getMinutes(), 0);
  EXPECT_EQ(span2.getSeconds(), 0);
  EXPECT_EQ(span3.getDays(), 0);
  EXPECT_EQ(span3.getHours(), 0);
  EXPECT_EQ(span3.getMinutes(), 20);
  EXPECT_EQ(span3.getSeconds(), 0);
  EXPECT_EQ(span4.getDays(), 0);
  EXPECT_EQ(span4.getHours(), 0);
  EXPECT_EQ(span4.getMinutes(), 0);
  EXPECT_EQ(span4.getSeconds(), 45);
}

TEST(TimeSpanTest, EqualSpan) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 2, 30, 40);
  TimeSpan span3(1, 3, 30, 40);
  EXPECT_TRUE(span1 == span2);
  EXPECT_FALSE(span1 == span3);
}

TEST(TimeSpanTest, NotEqualSpan) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 2, 30, 40);
  TimeSpan span3(1, 3, 30, 40);
  EXPECT_FALSE(span1 != span2);
  EXPECT_TRUE(span1 != span3);
}

TEST(TimeSpanTest, Less) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 3, 30, 40);
  TimeSpan span3(2, 0, 0, 0);
  EXPECT_TRUE(span1 < span2);
  EXPECT_TRUE(span1 < span3);
  EXPECT_FALSE(span3 < span2);
}

TEST(TimeSpanTest, LessOrEqualSpan) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 2, 30, 40);
  TimeSpan span3(1, 3, 30, 40);
  EXPECT_TRUE(span1 <= span2);
  EXPECT_TRUE(span1 <= span3);
  EXPECT_FALSE(span3 <= span1);
}

TEST(TimeSpanTest, GreaterSpan) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 3, 30, 40);
  TimeSpan span3(0, 0, 0, 0);
  EXPECT_FALSE(span1 > span2);
  EXPECT_TRUE(span2 > span3);
  EXPECT_TRUE(span1 > span3);
}

TEST(TimeSpanTest, GreaterOrEqualSpan) {
  TimeSpan span1(1, 2, 30, 40);
  TimeSpan span2(1, 2, 30, 40);
  TimeSpan span3(1, 3, 30, 40);
  EXPECT_TRUE(span1 >= span2);
  EXPECT_TRUE(span3 >= span2);
  EXPECT_FALSE(span1 >= span3);
}

TEST(TimeTest, EqualTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 2, 30, 40);
  Time time3(1, 3, 30, 40);
  EXPECT_TRUE(time1 == time2);
  EXPECT_FALSE(time1 == time3);
}

TEST(TimeTest, NotEqualTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 2, 30, 40);
  Time time3(1, 3, 30, 40);
  EXPECT_FALSE(time1 != time2);
  EXPECT_TRUE(time1 != time3);
}

TEST(TimeTest, LessTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 3, 30, 40);
  Time time3(2, 0, 0, 0);
  EXPECT_TRUE(time1 < time2);
  EXPECT_TRUE(time1 < time3);
  EXPECT_FALSE(time3 < time2);
}

TEST(TimeTest, LessOrEqualTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 2, 30, 40);
  Time time3(1, 3, 30, 40);
  EXPECT_TRUE(time1 <= time2);
  EXPECT_TRUE(time1 <= time3);
  EXPECT_FALSE(time3 <= time1);
}

TEST(TimeTest, GreaterTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 3, 30, 40);
  Time time3(0, 0, 0, 0);
  EXPECT_FALSE(time1 > time2);
  EXPECT_TRUE(time2 > time3);
  EXPECT_TRUE(time1 > time3);
}

TEST(TimeTest, GreaterOrEqualTime) {
  Time time1(1, 2, 30, 40);
  Time time2(1, 2, 30, 40);
  Time time3(1, 3, 30, 40);
  EXPECT_TRUE(time1 >= time2);
  EXPECT_TRUE(time3 >= time2);
  EXPECT_FALSE(time1 >= time3);
}

TEST(TimeTest, GetTime) {
  Time time(5, 6, 7, 8);
  std::stringstream ss;
  ss << time;
  EXPECT_EQ(ss.str(), "5d 6h 7m 8s");
}

TEST(TimeTest, ArrayTime) {
  Time times[3];
}

TEST(TimeSpanTest, ArrayTimeSpan) {
  TimeSpan span[3];
}