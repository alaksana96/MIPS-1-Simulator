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

bool isNegative32(uint32_t val){
	return ((val >> 31) == 1);
}

bool isNegative16(uint16_t val){
	return ((val >> 15) == 1);
}

uint32_t littleToBigRead(const uint8_t *memData){
	return (((uint32_t)memData[0]) << 24) | (((uint32_t)memData[1] << 16)) | (((uint32_t)memData[2]) << 8) | (((uint32_t)memData[3]));
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

mips_error SLLV(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rt << (rs & 0x1F)));
}


mips_error SRAV(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (uint32_t)(((int32_t)rt >> rs)));
}

mips_error ADD(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	if(((!isNegative32(rs) && !isNegative32(rt)) && isNegative32((uint32_t)((int32_t)rs + (int32_t)rt)))
		||
	((isNegative32(rs) && isNegative32(rt)) && !isNegative32((uint32_t)((int32_t)rs + (int32_t)rt)))){
		return mips_ExceptionArithmeticOverflow;
	}
	return mips_cpu_set_register(state, rd, (uint32_t)((int32_t)rs + (int32_t)rt));
}

mips_error ADDU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs + rt));
}

mips_error SUB(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	if(((!isNegative32(rs) && isNegative32(rt)) && isNegative32((uint32_t)((int32_t)rs - (int32_t)rt)))
		||
	((isNegative32(rs) && !isNegative32(rt)) && !isNegative32((uint32_t)((int32_t)rs - (int32_t)rt)))){
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

mips_error NOR(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, ~(rs | rt));
}


mips_error SLT(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (uint32_t)((int32_t)rs < (int32_t)rt));
}

mips_error SLTU(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rs < rt));
}

/**************************************************************************************/

mips_error ADDI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	int16_t immedSign = (int16_t)immed;
	if(((!isNegative32(rs) && !isNegative16(immed)) && isNegative32((uint32_t)((int32_t)rs + (int32_t)immedSign)))
		||
	((isNegative32(rs) && isNegative16(immed)) && !isNegative32((uint32_t)((int32_t)rs + (int32_t)immedSign)))){
		return mips_ExceptionArithmeticOverflow;
	}
	return mips_cpu_set_register(state, rt, (uint32_t)((int32_t)rs + (int32_t)immedSign));
}

mips_error ADDIU(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (rs + (uint32_t)immed));
}

mips_error SLTI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (uint32_t)(((int32_t)rs) < ((int32_t)((int16_t)immed))));
}

mips_error SLTIU(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (rs < ((uint32_t)((int32_t)((int16_t)immed)))));
}


mips_error ANDI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (rs & ((uint32_t)immed)));
}

mips_error ORI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (rs | ((uint32_t)immed)));
}

mips_error XORI(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (rs ^ ((uint32_t)immed)));
}

mips_error LW(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[4];
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 4, buffer);
	if((rs + (uint32_t)((int16_t)immed)) % 4 != 0){
		return mips_ExceptionInvalidAddress;
	}
	return mips_cpu_set_register(state, rt, (uint32_t)((int32_t)littleToBigRead(buffer)));
}

mips_error SW(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[4];
	buffer[0] = (rt >> 24) & 0xFF;
	buffer[1] = (rt >> 16) & 0xFF;
	buffer[2] = (rt >> 8) & 0xFF;
	buffer[3] = (rt>> 0) & 0xFF;
	if((rs + (uint32_t)((int16_t)immed)) % 4 != 0){
		return mips_ExceptionInvalidAddress;
	}
	return mips_mem_write(mem, (rs + (uint32_t)((int16_t)immed)), 4,buffer);

}
