/*
 * mips_function.h
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"

mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error ADDU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SUB(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SUBU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error AND(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error OR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error XOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SLTU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
