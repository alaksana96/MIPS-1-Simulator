/*
 * mips_cpu_pc_next_instructions.h
 *
 *  Created on: 26 Oct 2016
 *      Author: apl115
 */


#include "mips.h"

mips_error mips_cpu_set_pc_next(mips_cpu_h state, uint32_t pc);
mips_error mips_cpu_get_pc_next(mips_cpu_h state, uint32_t *pc);

