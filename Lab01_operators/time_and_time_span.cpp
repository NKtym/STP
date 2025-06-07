#include "time_and_time_span.hpp"
#include <iostream>

namespace my_namespace {

TimeSpan::TimeSpan(int d, int h, int m, int s)
    : days(d), hours(h), minutes(m), seconds(s) {}

TimeSpan TimeSpan::operator+(const TimeSpan& span) const {
  int result_seconds = seconds + span.getSeconds();
  int result_minutes = minutes + span.getMinutes() + result_seconds / 60;
  result_seconds %= 60;
  int result_hours = hours + span.getHours() + result_minutes / 60;
  result_minutes %= 60;
  int result_days = days + span.getDays() + result_hours / 24;
  result_hours %= 24;
  return TimeSpan(result_days, result_hours, result_minutes, result_seconds);
}
TimeSpan TimeSpan::operator-(const TimeSpan& span) const {
  int result_seconds = seconds - span.getSeconds();
  int result_minutes =
      minutes - span.getMinutes() + (result_seconds < 0 ? -1 : 0);
  result_seconds = (result_seconds + 60) % 60;
  int result_hours = hours - span.getHours() + (result_minutes < 0 ? -1 : 0);
  result_minutes = (result_minutes + 60) % 60;
  int result_days = days - span.getDays() + (result_hours < 0 ? -1 : 0);
  result_hours = (result_hours + 24) % 24;
  return TimeSpan(result_days, result_hours, result_minutes, result_seconds);
}

bool TimeSpan::operator==(const TimeSpan& span) const {
  return days == span.getDays() && hours == span.hours &&
         minutes == span.minutes && seconds == span.seconds;
}

bool TimeSpan::operator!=(const TimeSpan& span) const {
  return days != span.getDays() || hours != span.hours ||
         minutes != span.minutes || seconds != span.seconds;
}

bool TimeSpan::operator<(const TimeSpan& span) const {
  if (days != span.getDays())
    return days < span.getDays();
  if (hours != span.hours)
    return hours < span.hours;
  if (minutes != span.minutes)
    return minutes < span.minutes;
  return seconds < span.seconds;
}

bool TimeSpan::operator<=(const TimeSpan& span) const {
  if (days != span.getDays())
    return days < span.getDays();
  if (hours != span.hours)
    return hours < span.hours;
  if (minutes != span.minutes)
    return minutes < span.minutes;
  if (seconds != span.seconds)
    return seconds < span.seconds;
  return days == span.getDays() && hours == span.hours &&
         minutes == span.minutes && seconds == span.seconds;
}

bool TimeSpan::operator>(const TimeSpan& span) const {
  if (days != span.getDays())
    return days > span.getDays();
  if (hours != span.hours)
    return hours > span.hours;
  if (minutes != span.minutes)
    return minutes > span.minutes;
  return seconds > span.seconds;
}

bool TimeSpan::operator>=(const TimeSpan& span) const {
  if (days != span.getDays())
    return days > span.getDays();
  if (hours != span.hours)
    return hours > span.hours;
  if (minutes != span.minutes)
    return minutes > span.minutes;
  if (seconds != span.seconds)
    return seconds > span.seconds;
  return days == span.getDays() && hours == span.hours &&
         minutes == span.minutes && seconds == span.seconds;
}

std::ostream& operator<<(std::ostream& os, const TimeSpan& span) {
  os << span.getDays() << "d " << span.getHours() << "h " << span.getMinutes()
     << "m " << span.getSeconds() << "s";
  return os;
}

Time::Time(int d, int h, int m, int s)
    : days(d), hours(h), minutes(m), seconds(s) {}

Time Time::operator+(const TimeSpan& span) const {
  int result_seconds = seconds + span.getSeconds();
  int result_minutes = minutes + span.getMinutes() + result_seconds / 60;
  result_seconds %= 60;
  int result_hours = hours + span.getHours() + result_minutes / 60;
  result_minutes %= 60;
  int result_days = days + span.getDays() + result_hours / 24;
  result_hours %= 24;
  return Time(result_days, result_hours, result_minutes, result_seconds);
}

Time Time::operator-(const TimeSpan& span) const {
  int result_seconds = seconds - span.getSeconds();
  int result_minutes =
      minutes - span.getMinutes() + (result_seconds < 0 ? -1 : 0);
  result_seconds = (result_seconds + 60) % 60;
  int result_hours = hours - span.getHours() + (result_minutes < 0 ? -1 : 0);
  result_minutes = (result_minutes + 60) % 60;
  int result_days = days - span.getDays() + (result_hours < 0 ? -1 : 0);
  result_hours = (result_hours + 24) % 24;
  return Time(result_days, result_hours, result_minutes, result_seconds);
}

TimeSpan Time::operator-(const Time& t) const {
  int result_seconds = seconds - t.getSeconds();
  int result_minutes = minutes - t.getMinutes() + (result_seconds < 0 ? -1 : 0);
  result_seconds = (result_seconds + 60) % 60;
  int result_hours = hours - t.getHours() + (result_minutes < 0 ? -1 : 0);
  result_minutes = (result_minutes + 60) % 60;
  int result_days = days - t.getDays() + (result_hours < 0 ? -1 : 0);
  result_hours = (result_hours + 24) % 24;
  return TimeSpan(result_days, result_hours, result_minutes, result_seconds);
}

bool Time::operator==(const Time& t) const {
  return days == t.getDays() && hours == t.getHours() &&
         minutes == t.getMinutes() && seconds == t.getSeconds();
}

bool Time::operator!=(const Time& t) const {
  return days != t.getDays() || hours != t.hours || minutes != t.minutes ||
         seconds != t.seconds;
}

bool Time::operator<(const Time& t) const {
  if (days != t.getDays())
    return days < t.getDays();
  if (hours != t.getHours())
    return hours < t.getHours();
  if (minutes != t.getMinutes())
    return minutes < t.getMinutes();
  return seconds < t.getSeconds();
}

bool Time::operator<=(const Time& t) const {
  if (days != t.getDays())
    return days < t.getDays();
  if (hours != t.hours)
    return hours < t.hours;
  if (minutes != t.minutes)
    return minutes < t.minutes;
  if (seconds != t.seconds)
    return seconds < t.seconds;
  return days == t.getDays() && hours == t.hours && minutes == t.minutes &&
         seconds == t.seconds;
}

bool Time::operator>(const Time& t) const {
  if (days != t.getDays())
    return days > t.getDays();
  if (hours != t.hours)
    return hours > t.hours;
  if (minutes != t.minutes)
    return minutes > t.minutes;
  return seconds > t.seconds;
}

bool Time::operator>=(const Time& t) const {
  if (days != t.getDays())
    return days > t.getDays();
  if (hours != t.hours)
    return hours > t.hours;
  if (minutes != t.minutes)
    return minutes > t.minutes;
  if (seconds != t.seconds)
    return seconds > t.seconds;
  return days == t.getDays() && hours == t.hours && minutes == t.minutes &&
         seconds == t.seconds;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
  os << t.getDays() << "d " << t.getHours() << "h " << t.getMinutes() << "m "
     << t.getSeconds() << "s";
  return os;
}

namespace literals {
TimeSpan operator""_d(unsigned long long d) {
  return TimeSpan(d, 0, 0, 0);
}
TimeSpan operator""_h(unsigned long long h) {
  return TimeSpan(0, h, 0, 0);
}
TimeSpan operator""_m(unsigned long long m) {
  return TimeSpan(0, 0, m, 0);
}
TimeSpan operator""_s(unsigned long long s) {
  return TimeSpan(0, 0, 0, s);
}
}
}