/*
 * mips_cpu_decoder.cpp
 *
 *  Created on: 19 Oct 2016
 *      Author: alaksana
 */

#include "mips.h"
#include "mips_cpu_instructions.h"

#include <iostream>
#include <bitset>

using namespace std;

mips_error decodeRInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t rs, rt, rd, shift, func;

	rs = instr >> 21;
	rt = (instr & 0x1F0000) >> 16;
	rd = (instr & 0xF800) >> 11;
	shift = (instr & 0x7C0) >> 6;
	func = instr & 0x3F;

	uint32_t srca, srcb, result;
	mips_error err;
	err = mips_cpu_get_register(state, rs, &srca);
	err = mips_cpu_get_register(state, rt, &srcb);

	switch(func)
	{
		case 0:
			//SLL
			break;

		case 2:
			//SRL
			break;
		case 3:
			//SRA
			break;
		case 4:
			//SLLV
			break;
		case 6:
			//SRLV
			break;
		case 7:
			//SRAV
			break;
		case 8:
			//JR
			break;
		case 9:
			//JALR
			break;
		case 12:
			//SYSCALL
			break;
		case 13:
			//Break
			break;
		case 16:
			//MFHI
			break;
		case 17:
			//MTHI
			break;
		case 18:
			//MFLO
			break;
		case 19:
			//MTLO
			break;
		case 24:
			//MULT
			break;
		case 25:
			//MULTU
			break;
		case 26:
			//DIV
			break;
		case 27:
			//DIVU
			break;
		case 32:
			//ADD
			break;
		case 33:
			//ADDU
			return ADDU(srca, srcb, rd, state);
			break;
		case 34:
			//SUB
			break;
		case 35:
			//SUBU
			break;
		case 36:
			//AND
			return AND(srca, srcb, rd, state);
			break;
		case 37:
			//OR
			break;
		case 38:
			//XOR
			break;
		case 39:
			//NOR
			break;
		case 42:
			//SLT
			break;
		case 43:
			//SLTU
			break;
	}

}

mips_error decodeIInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode,rs, rt, immed;

	opcode = instr >> 26;
	rs = (instr & 0x3E00000) >> 21;
	rt = (instr & 0x1F0000) >> 16;
	immed = (instr & 0xFFFF);

}


mips_error decodeJInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode, target;

	opcode = instr >> 26;
	target = (instr & 0x3FFFFFF);

}

mips_error decodeInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode;

	opcode = instr >> 26;

	switch (opcode)
	{
	case 0b000000:
		decodeRInstruction(instr, mem, state);
		break;

	case 0b000001:
		cout << "fdas";
		break;

	}
}
