/*
 * mips_instructions.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"


using namespace std;

mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t a, b;

	mips_error err = mips_cpu_get_register(state, rs, &a);
	err = mips_cpu_get_register(state, rt, &b);

	int32_t result = (int32_t)a + (int32_t)b;

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

mips_error AND(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){

	uint32_t result;
	result = rs & rt;
	return mips_cpu_set_register(state, rd, result);

}
