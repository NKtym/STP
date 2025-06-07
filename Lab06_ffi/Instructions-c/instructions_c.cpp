#include "instructions_c.h"
#include <cstdlib>
#include <cstring>
#include "../Instructions/instructions.hpp"

extern "C" {
Instr instr_start() {
  return new Start();
}
Instr instr_finish() {
  return new Finish();
}
Instr instr_turn(const char* direction) {
  return new Turn(direction);
}
Instr instr_ringroad(int number) {
  return new Ringroad(number);
}
Instr instr_forward(int lenght) {
  return new Forward(lenght);
}
char* instr_to_string(Instr h) {
  Instruction* instr = static_cast<Instruction*>(h);
  std::string s = instr->toString();
  char* buf = (char*)std::malloc(s.size() + 1);
  std::memcpy(buf, s.c_str(), s.size() + 1);
  return buf;
}
void instr_destroy(Instr h) {
  delete static_cast<Instruction*>(h);
}
}