/*
 * mips_instructions.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include <iostream>
#include <bitset>

using namespace std;

bool isNegative(uint32_t val){
	return ((val >> 31) == 1);
}

mips_error SLL(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rt << sa));
}

mips_error SRL(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rt >> sa));
}

mips_error SRA(uint32_t rt, uint32_t rd, uint32_t sa, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, ((uint32_t)((int32_t)rt >> sa)));
}

mips_error SRAV(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (uint32_t)(((int32_t)rt >> rs)));
}

mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	if(((!isNegative(rs) && !isNegative(rt)) && isNegative((uint32_t)((int32_t)rs + (int32_t)rt)))
		||
	((isNegative(rs) && isNegative(rt)) && !isNegative((uint32_t)((int32_t)rs + (int32_t)rt)))){
		return mips_ExceptionArithmeticOverflow;
	}
	return mips_cpu_set_register(state, rd, (uint32_t)((int32_t)rs + (int32_t)rt));
}

mips_error ADDU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs + rt));
}

mips_error SUB(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	if(((!isNegative(rs) && isNegative(rt)) && isNegative((uint32_t)((int32_t)rs - (int32_t)rt)))
		||
	((isNegative(rs) && !isNegative(rt)) && !isNegative((uint32_t)((int32_t)rs - (int32_t)rt)))){
		return mips_ExceptionArithmeticOverflow;
	}
	return mips_cpu_set_register(state, rd, (uint32_t)((int32_t)rs - (int32_t)rt));
}

mips_error SUBU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs - rt));
}

mips_error AND(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs & rt));
}

mips_error OR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, rs | rt);
}

mips_error XOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs ^ rt));
}

mips_error SLT(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (uint32_t)((int32_t)rs < (int32_t)rt));
}

mips_error SLTU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs < rt));
}

