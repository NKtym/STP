#pragma once
#ifdef __cplusplus
extern "C" {
#endif
typedef void* Instr;
Instr instr_start();
Instr instr_finish();
Instr instr_turn(const char* direction);
Instr instr_ringroad(int number);
Instr instr_forward(int lenght);
char* instr_to_string(Instr h);
void instr_destroy(Instr h);
#ifdef __cplusplus
}
#endif