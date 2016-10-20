/*
 * mips_cpu_decoder.h
 *
 *  Created on: 19 Oct 2016
 *      Author: alaksana
 */

#include "mips.h"

mips_error decodeRInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state);
mips_error decodeIInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state);
mips_error decodeJInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state);
mips_error decodeInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state);

