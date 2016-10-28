/*
 * mips_cpu_decoder.cpp
 *
 *  Created on: 19 Oct 2016
 *      Author: alaksana
 */

#include "mips.h"
#include "mips_cpu_instructions.h"
#include "mips_cpu_extra.h"
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
		return MFHI(rd, state);
		break;
	case 17:
		//MTHI
		return MTHI(srca, state);
		break;
	case 18:
		//MFLO
		return MFLO(rd, state);
		break;
	case 19:
		//MTLO
		return MTLO(srca, state);
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
		if(mips_cpu_get_debug_level(state) >= 1){
			fprintf(stderr, "ADD.\n");
			fprintf(stderr, "rsVal=%08x, rtVal=%08x.\n",srca, srcb);
		}
		return ADD(srca, srcb, rd, state);
		break;
	case 33:
		//ADDU
		if(mips_cpu_get_debug_level(state) >= 1){
			fprintf(stderr, "ADDU.\n");
			fprintf(stderr, "rsVal=%08x, rtVal=%08x.\n",srca, srcb);
		}
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
		if(mips_cpu_get_debug_level(state) >= 1){
			fprintf(stderr, "AND.\n");
			fprintf(stderr, "rsVal=%08x, rtVal=%08x.\n",srca, srcb);
		}
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

	uint32_t originalPC, originalPCNext;
	mips_cpu_get_pc(state, &originalPC);
	mips_cpu_get_pc_next(state, &originalPCNext);


	switch(opcode)
	{
	case 1:

		switch(rt)
		{
		case 0:
			//BLTZ
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BLTZ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BLTZ(srca, immed, state);
			break;
		case 1:
			//BGEZ
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BGEZ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BGEZ(srca, immed, state);
			break;
		case 16:
			//BLTZAL
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BLTZAL.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BLTZAL(srca, immed, state);
			break;
		case 17:
			//BGEZAL
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BGEZ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BGEZAL(srca, immed, state);
			break;

		}

		break;

		case 4:
			//BEQ
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BEQ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BEQ(srca, srcb, immed16, state);
			break;
		case 5:
			//BNE
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BNE.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BNE(srca, srcb, immed16, state);
			break;
		case 6:
			//BLEZ
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BLEZ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BLEZ(srca, immed16, state);
			break;
		case 7:
			//BGTZ
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "BGTZ.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			return BGTZ(srca, immed16, state);
			break;
		case 8:
			//ADDI
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "ADDI.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			err = ADDI(srca, rt, immed16, state);
			break;
		case 9:
			//ADDIU
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "ADDIU.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			err = ADDIU(srca, rt, immed16, state);
			break;
		case 10:
			//SLTI
			err = SLTI(srca, rt, immed16, state);
			break;

		case 11:
			//SLTIU
			err = SLTIU(srca, rt, immed16, state);
			break;
		case 12:
			//ANDI
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "ANDI.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			err = ANDI(srca, rt, immed16, state);
			break;
		case 13:
			//ORI
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "ORI.\n");
				fprintf(stderr, "rsVal=%08x, immed=%08x.\n",srca, immed);
			}
			err = ORI(srca, rt, immed16, state);
			break;
		case 14:
			//XORI
			XORI(srca, rt, immed16, state);
			break;
		case 15:
			//LUI
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LUI.\n");
				fprintf(stderr, "dest=%u immed=%08x.\n",rt,immed);
			}
			err = LUI(rt, immed16, state);
			break;
		case 32:
			//LB
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LB.\n");
				fprintf(stderr, "rsVal=%08x, dest=%u immed=%08x.\n",srca, rt,immed);
			}
			err = LB(srca, rt, immed16, state, mem);
			break;
		case 33:
			//LH
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LH.\n");
				fprintf(stderr, "rsVal=%08x, dest=%u immed=%08x.\n",srca, rt,immed);
			}
			err = LH(srca, rt, immed16, state, mem);
			break;
		case 35:
			//LW
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LW.\n");
				fprintf(stderr, "rsVal=%08x, dest=%u immed=%08x.\n",srca, rt,immed);
			}
			LW(srca, rt, immed16, state, mem);
			break;
		case 36:
			//LBU
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LBU.\n");
				fprintf(stderr, "rsVal=%08x, dest=%u immed=%08x.\n",srca, rt,immed);
			}
			err = LBU(srca, rt, immed16, state, mem);
			break;
		case 37:
			//LHU
			if(mips_cpu_get_debug_level(state) >= 1){
				fprintf(stderr, "LHU.\n");
				fprintf(stderr, "rsVal=%08x, dest=%u immed=%08x.\n",srca, rt,immed);
			}
			err = LHU(srca, rt, immed16, state, mem);
			break;
		case 40:
			//SB
			SB(srca, srcb, immed16, state, mem);
			break;
		case 41:
			//SH
			err = SH(srca, srcb, immed16, state, mem);

			break;
		case 43:
			//SW
			err = SW(srca, srcb, immed16, state, mem);
			break;

	}

	mips_cpu_set_pc(state, originalPCNext);
	mips_cpu_set_pc_next(state, originalPCNext+4);

	return err;

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

	uint32_t opcode, srca;
	mips_error err;

	uint32_t originalPC, originalPCNext;
	mips_cpu_get_pc(state, &originalPC);
	mips_cpu_get_pc_next(state, &originalPCNext);

	opcode = instr >> 26;

	switch (opcode)
	{
	case 0:
		err = decodeRInstruction(instr, mem, state);
		break;

	case 2: //J
		err = decodeJInstruction(instr, mem, state);
		break;

	case 3: //JAL
		err = decodeJInstruction(instr, mem, state);
		break;

	default :
		err = decodeIInstruction(instr, mem, state);

		break;

	}
	return err;
}
