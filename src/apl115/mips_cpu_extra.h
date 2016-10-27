/*
 * mips_cpu_pc_next_instructions.h
 *
 *  Created on: 26 Oct 2016
 *      Author: apl115
 */


#include "mips.h"

mips_error mips_cpu_set_pc_next(mips_cpu_h state, uint32_t pc);
mips_error mips_cpu_get_pc_next(mips_cpu_h state, uint32_t *pc);
mips_error MFHI(uint32_t rd, mips_cpu_impl *state);
mips_error MTHI(uint32_t rs, mips_cpu_impl *state);
mips_error MFLO(uint32_t rd, mips_cpu_impl *state);
mips_error MTLO(uint32_t rs, mips_cpu_impl *state);

