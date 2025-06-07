#include "instructions.hpp"
#include <sstream>

std::string Start::toString() const {
  return "Start";
}

std::string Finish::toString() const {
  return "Finish";
}

Turn::Turn(const std::string& direction) : direct(direction) {}
std::string Turn::toString() const {
  return "Turn " + direct;
}

Ringroad::Ringroad(int number) : num(number) {}
std::string Ringroad::toString() const {
  std::ostringstream os;
  os << "Ringroad exit " << num;
  return os.str();
}

Forward::Forward(int lenght) : len(lenght) {}
std::string Forward::toString() const {
  std::ostringstream os;
  os << "Forward " << len;
  return os.str();
}