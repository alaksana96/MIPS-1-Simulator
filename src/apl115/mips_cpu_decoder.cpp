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
			return SLL(srcb, rd, shift, state);
			break;

		case 2:
			//SRL
			return SRL(srcb, rd, shift, state);
			break;
		case 3:
			//SRA
			return SRA(srcb, rd, shift, state);
			break;
		case 4:
			//SLLV
			return SLLV(srca, srcb, rd, state);
			break;
		case 6:
			//SRLV
			return SRLV(srca, srcb, rd, state);
			break;
		case 7:
			//SRAV
			return SRAV(srca, srcb, rd, state);
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
			return ADD(srca, srcb, rd, state);
			break;
		case 33:
			//ADDU
			return ADDU(srca, srcb, rd, state);
			break;
		case 34:
			//SUB
			return SUB(srca, srcb, rd, state);
			break;
		case 35:
			//SUBU
			return SUBU(srca, srcb, rd, state);
			break;
		case 36:
			//AND
			return AND(srca, srcb, rd, state);
			break;
		case 37:
			//OR
			return OR(srca, srcb, rd, state);
			break;
		case 38:
			//XOR
			return XOR(srca, srcb, rd, state);
			break;
		case 39:
			//NOR NOT IN DT SPEC
			return NOR(srca, srcb, rd, state);
			break;
		case 42:
			//SLT
			return SLT(srca, srcb, rd, state);
			break;
		case 43:
			//SLTU
			return SLTU(srca, srcb, rd, state);
			break;
	}




	return mips_ErrorNotImplemented;

}

mips_error decodeIInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode,rs, rt, immed;

	opcode = instr >> 26;
	rs = (instr & 0x3E00000) >> 21;
	rt = (instr & 0x1F0000) >> 16;
	immed = (instr & 0xFFFF);

	uint16_t immed16 = (uint16_t)immed;

	uint32_t srca, srcb;
	mips_error err;
	err = mips_cpu_get_register(state, rs, &srca);
	err = mips_cpu_get_register(state, rt, &srcb);


	switch(opcode)
	{
	case 1:

		switch(rt)
		{
		case 0:
			//BLTZ
			return BLTZ(rs, immed, state);
			break;
		case 1:
			//BGEZ
			return BGEZ(rs, immed, state);
			break;
		case 16:
			//BLTZAL
			return BLTZAL(rs, immed, state);
			break;
		case 17:
			//BGEZAL
			return BGEZAL(rs, immed, state);
			break;

		}

		break;

	case 4:
		//BEQ
		return BEQ(srca, srcb, immed16, state);
		break;
	case 5:
		//BNE
		return BNE(srca, srcb, immed16, state);
		break;
	case 6:
		//BLEZ
		return BLEZ(rs, immed16, state);
		break;
	case 7:
		//BGTZ
		return BGTZ(rs, immed16, state);
		break;
	case 8:
		//ADDI
		return ADDI(srca, rt, immed16, state);
		break;
	case 9:
		//ADDIU
		return ADDIU(srca, rt, immed16, state);
		break;
	case 10:
		//SLTI
		return SLTI(srca, rt, immed16, state);
		break;

	case 11:
		//SLTIU
		return SLTIU(srca, rt, immed16, state);
		break;
	case 12:
		//ANDI
		return ANDI(srca, rt, immed16, state);
		break;
	case 13:
		//ORI
		return ORI(srca, rt, immed16, state);
		break;
	case 14:
		//XORI
		return XORI(srca, rt, immed16, state);
		break;
	case 32:
		//LB
		return LB(srca, rt, immed16, state, mem);
		break;
	case 35:
		//LW
		return LW(srca, rt, immed16, state, mem);
		break;
	case 36:
		//LBU
		return LBU(srca, rt, immed16, state, mem);
		break;
	case 40:
		//SB
		return SB(srca, srcb, immed16, state, mem);
		break;
	case 41:
		//SH
		return SH(srca, srcb, immed16, state, mem);
		break;
	case 43:
		//SW
		return SW(srca, srcb, immed16, state, mem);
		break;

	}


	return mips_ErrorNotImplemented;

}


mips_error decodeJInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode, target;

	opcode = instr >> 26;
	target = (instr & 0x3FFFFFF);

	switch(opcode)
	{
	case 0b000010:
		//J
		break;

	case 0b000011:
		//JAL
		break;
	}

	return mips_ErrorNotImplemented;

}

mips_error decodeInstruction(uint32_t instr, mips_mem_h mem, mips_cpu_impl* state){

	uint32_t opcode;
	mips_error err;

	uint32_t originalPC, originalPCNext;
	err = mips_cpu_get_pc(state, &originalPC);
	err = mips_cpu_get_pc_next(state, &originalPCNext);

	bool flag = 0;

	opcode = instr >> 26;

	switch (opcode)
	{
	case 0:
		decodeRInstruction(instr, mem, state);
		break;

	case 2: //J
		decodeJInstruction(instr, mem, state);
		break;

	case 3: //JAL
		decodeJInstruction(instr, mem, state);
		break;

	default :
		decodeIInstruction(instr, mem, state);
		break;

	}

	uint32_t checkPC, checkPCNext;
	err = mips_cpu_get_pc(state, &checkPC);
	err = mips_cpu_get_pc_next(state, &checkPCNext);

	if(opcode != 1 && opcode != 4 && opcode != 5 && opcode != 6 && opcode != 7){
	err = mips_cpu_set_pc(state, originalPCNext);
	err = mips_cpu_set_pc_next(state, originalPCNext+4);
	}

	return mips_ErrorNotImplemented;
}
