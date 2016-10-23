/*
 * mips_instructions.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include <iostream>

using namespace std;

mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	int32_t as, bs;
	as = (int32_t)rs;
	bs = (int32_t)rt;


	int32_t result = as + bs;

	if(((as > 0 && bs > 0) && result < 0) || (((as < 0) && (bs < 0)) && result > 0)){
		return mips_ExceptionArithmeticOverflow;
	}

	return mips_cpu_set_register(state, rd, (uint32_t)result);

}
/*
 * Takes the values in the source registers rs and rt, does the ADDU and stores
 * the result in the register rd
 */
mips_error ADDU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs + rt;
	return mips_cpu_set_register(state, rd, result);

}

mips_error SUBU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs - rt;
	return mips_cpu_set_register(state, rd, result);
}

mips_error AND(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs & rt;
	return mips_cpu_set_register(state, rd, result);

}

mips_error OR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs | rt;
	return mips_cpu_set_register(state, rd, result);
}

mips_error XOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs ^ rt;
	return mips_cpu_set_register(state, rd, result);
}

mips_error SLTU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = (rs < rt);
	return mips_cpu_set_register(state, rd, result);

}
