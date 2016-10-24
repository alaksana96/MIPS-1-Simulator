/*
 * mips_function.h
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"

mips_error SLL(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state);
mips_error SRL(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state);
mips_error SRA(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state);
mips_error SRAV(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error ADDU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SUB(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SUBU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error AND(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error OR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error XOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error NOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SLT(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);
mips_error SLTU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state);

/**********************************************************************************/

mips_error ADDI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state);
mips_error ADDIU(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state);
mips_error ANDI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state);
mips_error ORI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state);
mips_error XORI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state);
mips_error SW(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem);
