/*
 * mips_instructions.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include "mips_cpu.h"
#include <iostream>
#include <bitset>
#include "mips_cpu_extra.h"

using namespace std;


bool isNegative32(uint32_t val){
	return ((val >> 31) == 1);
}

bool isNegative16(uint16_t val){
	return ((val >> 15) == 1);
}

uint32_t littleToBigReadWord(const uint8_t *memData){
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

mips_error SRLV(uint32_t rs, uint32_t rt, uint32_t rd, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rd, (rt >> (rs & 0x1F)));
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

mips_error BLTZ(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if((rs >> 31) == 1){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BGEZ(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if((rs >> 31) == 0){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BLTZAL(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC, nextNextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	nextNextPC = currentPC + 8;
	if((rs >> 31) == 1){
		err = mips_cpu_set_pc(state, nextPC);
		err = mips_cpu_set_register(state, 31, nextNextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BGEZAL(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC, nextNextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	nextNextPC = currentPC + 8;
	if((rs >> 31) == 0){
		err = mips_cpu_set_pc(state, nextPC);
		err = mips_cpu_set_register(state, 31, nextNextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BEQ(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if(rs == rt){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BNE(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if(rs != rt){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BLEZ(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if((rs >> 31 == 1) || (rs == 0)){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

mips_error BGTZ(uint32_t rs, uint16_t immed, mips_cpu_impl *state){
	uint32_t currentPC, nextPC;
	mips_error err = mips_cpu_get_pc(state, &currentPC);
	err = mips_cpu_get_pc_next(state, &nextPC);
	if((rs >> 31 == 0) && (rs != 0)){
		err = mips_cpu_set_pc(state, nextPC);
		return mips_cpu_set_pc_next(state, (uint32_t)((int32_t)nextPC + ((int32_t)((int16_t)immed) << 2)));
	}
	mips_cpu_set_pc_next(state, nextPC+4);
	return mips_cpu_set_pc(state, nextPC);
}

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
	return mips_cpu_set_register(state, rt, (rs + (int32_t)immed));
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

mips_error LUI(uint32_t rt, uint16_t immed, mips_cpu_impl *state){
	return mips_cpu_set_register(state, rt, (((uint32_t)immed) << 16) & 0xFFFF0000);
}

mips_error LB(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer;
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 1, &buffer);
	return mips_cpu_set_register(state, rt, ((int32_t)((int8_t)buffer)));
}

mips_error LH(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[2];
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 2, buffer);
	if((rs + (uint32_t)((int16_t)immed)) % 2 != 0){
		return mips_ExceptionInvalidAddress;
	}
	int32_t result = (int32_t)((int16_t)(((int8_t)buffer[0] << 8 | (uint8_t)buffer[1] << 0)));
	return mips_cpu_set_register(state, rt, (uint32_t)result);
}

mips_error LW(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[4];
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 4, buffer);
	if((rs + (uint32_t)((int16_t)immed)) % 4 != 0){
		return mips_ExceptionInvalidAddress;
	}
	return mips_cpu_set_register(state, rt, (uint32_t)((int32_t)littleToBigReadWord(buffer)));
}

mips_error LBU(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer;
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 1, &buffer);
	return mips_cpu_set_register(state, rt, (uint32_t)buffer);
}

mips_error LHU(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[2];
	mips_error c = mips_mem_read(mem, (rs + (uint32_t)((int16_t)immed)), 2, buffer);
	if((rs + (uint32_t)((int16_t)immed)) % 2 != 0){
		return mips_ExceptionInvalidAddress;
	}
	uint32_t result = ((buffer[0] << 8 | buffer[1] << 0));
	return mips_cpu_set_register(state, rt, result);
}

mips_error SB(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer = (uint8_t)(0x000000FF & rt);
	return mips_mem_write(mem,(rs + (uint32_t)((int16_t)immed)) , 1, &buffer);
}

mips_error SH(uint32_t rs, uint32_t rt, uint16_t immed, mips_cpu_impl *state, mips_mem_h mem){
	uint8_t buffer[2];
	buffer[0] = (rt >> 8) & 0xFF;
	buffer[1] = (rt>> 0) & 0xFF;
	if(((rs + (uint32_t)((int16_t)immed)) % 2) != 0){
		return mips_ExceptionInvalidAddress;
	}
	return mips_mem_write(mem,(rs + (int32_t)((int16_t)immed)) , 2, buffer);
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
