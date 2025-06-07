#pragma once
#include <iosfwd>

namespace my_namespace {

class TimeSpan {
 private:
  int days, hours, minutes, seconds;

 public:
  TimeSpan(int d, int h, int m, int s);
  TimeSpan() : days(0), hours(0), minutes(0), seconds(0) {}
  int getDays() const { return days; }
  int getHours() const { return hours; }
  int getMinutes() const { return minutes; }
  int getSeconds() const { return seconds; }
  TimeSpan operator+(const TimeSpan& span) const;
  TimeSpan operator-(const TimeSpan& span) const;
  bool operator==(const TimeSpan& other) const;
  bool operator!=(const TimeSpan& other) const;
  bool operator<(const TimeSpan& other) const;
  bool operator<=(const TimeSpan& other) const;
  bool operator>(const TimeSpan& other) const;
  bool operator>=(const TimeSpan& other) const;
  friend std::ostream& operator<<(std::ostream& os, const TimeSpan& span);
};

class Time {
 private:
  int days, hours, minutes, seconds;

 public:
  Time(int d, int h, int m, int s);
  Time() : days(0), hours(0), minutes(0), seconds(0) {}
  int getDays() const { return days; }
  int getHours() const { return hours; }
  int getMinutes() const { return minutes; }
  int getSeconds() const { return seconds; }
  Time operator+(const TimeSpan& span) const;
  Time operator-(const TimeSpan& span) const;
  TimeSpan operator-(const Time& t) const;
  bool operator==(const Time& other) const;
  bool operator!=(const Time& other) const;
  bool operator<(const Time& other) const;
  bool operator<=(const Time& other) const;
  bool operator>(const Time& other) const;
  bool operator>=(const Time& other) const;
  friend std::ostream& operator<<(std::ostream& os, const Time& t);
};

std::ostream& operator<<(std::ostream& os, const TimeSpan& span);
std::ostream& operator<<(std::ostream& os, const Time& t);

namespace literals {
TimeSpan operator""_d(unsigned long long d);
TimeSpan operator""_h(unsigned long long h);
TimeSpan operator""_m(unsigned long long m);
TimeSpan operator""_s(unsigned long long s);
}
}