package main
/*
#cgo CFLAGS: -I../Instructions-c -I../Instructions
#cgo LDFLAGS: -L.. -Wl,-rpath='Go!/..' -linstructions-c -linstructions
#include "instructions_c.h"
#include <stdlib.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func printInstr(h C.Instr) {
	cs := C.instr_to_string(h)
	defer C.free(unsafe.Pointer(cs))
	fmt.Println(C.GoString(cs))
	C.instr_destroy(h)
}

func main() {
	dirl := C.CString("left")
	defer C.free(unsafe.Pointer(dirl))
	dirr := C.CString("right")
	defer C.free(unsafe.Pointer(dirr))
	route := []C.Instr{
		C.instr_start(),
		C.instr_forward(100),
		C.instr_ringroad(2),
		C.instr_turn(dirr),
		C.instr_forward(10),
		C.instr_ringroad(1),
		C.instr_forward(40),
		C.instr_turn(dirl),
		C.instr_forward(20),
		C.instr_turn(dirr),
		C.instr_forward(140),
		C.instr_turn(dirr),
		C.instr_forward(30),
		C.instr_finish(),
	}
	for _, h := range route {
		printInstr(h)
	}
}
