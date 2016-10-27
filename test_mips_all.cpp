/*
 * test_mips_revamped.cpp
 *
 *  Created on: 26 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include "mips_cpu_pc_next_instructions.h"
#include <bitset>
#include <iostream>

using namespace std;

uint32_t littleToBigEnd(const uint8_t *memData){
	return (((uint32_t)memData[0]) << 24) | (((uint32_t)memData[1] << 16)) | (((uint32_t)memData[2]) << 8) | (((uint32_t)memData[3]));
}

mips_error writeInstrToMem(mips_cpu_h state, mips_mem_h mem, uint32_t addr, uint32_t instr){
	uint8_t buffer[4];
	buffer[0] = (instr >> 24) & 0xFF;
	buffer[1] = (instr >> 16) & 0xFF;
	buffer[2] = (instr >> 8) & 0xFF;
	buffer[3] = (instr >> 0) & 0xFF;
	return mips_mem_write(mem, addr, 4, buffer);
}

void setupTestR(mips_cpu_h state, mips_mem_h mem, uint32_t instr, uint32_t rsV, uint32_t rtV, uint32_t rdV){
	uint32_t rs, rt, rd, shift, func;
	rs = instr >> 21;
	rt = (instr & 0x1F0000) >> 16;
	rd = (instr & 0xF800) >> 11;
	shift = (instr & 0x7C0) >> 6;
	func = instr & 0x3F;

	mips_cpu_set_register(state, rs, rsV);
	mips_cpu_set_register(state, rt, rtV);
	mips_cpu_set_register(state, rd, rdV);
}

void setupTestI(mips_cpu_h state, mips_mem_h mem, uint32_t instr, uint32_t rsV, uint32_t rtV){
	uint32_t opcode,rs, rt, immed;
	opcode = instr >> 26;
	rs = (instr & 0x3E00000) >> 21;
	rt = (instr & 0x1F0000) >> 16;
	immed = (instr & 0xFFFF);

	mips_cpu_set_register(state, rs, rsV);
	mips_cpu_set_register(state, rt, rtV);
}

int main(){

	int testId, passed;
	mips_error err;
	uint32_t instruction, result;
	uint8_t temp8;
	uint8_t buffer[4];
	uint32_t PC = 0;
	uint32_t PCNext = 4;

	uint32_t branchedAddress;

	mips_mem_h mem = mips_mem_create_ram(4096);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();


	testId = mips_test_begin_test("BEQ");
	passed = 0;
	//BEQ R10 R11 0x2
	instruction = 0x114B0002;
	writeInstrToMem(cpu, mem, 0, instruction);
	setupTestI(cpu, mem, instruction, 13, 13); //Test if Equal

	mips_cpu_step(cpu);
	mips_cpu_get_pc_next(cpu, &branchedAddress);
	passed = (branchedAddress == 12);
	mips_test_end_test(testId, passed, "Address 12 executed after next instruction");

	mips_cpu_reset(cpu);

	testId = mips_test_begin_test("BEQ");
	passed = 0;
	instruction = 0x114B0200;
	writeInstrToMem(cpu, mem, 0, instruction);
	setupTestI(cpu, mem, instruction, 100, 100); //Test if Equal

	uint32_t immed = (instruction & 0xFFFF);

	mips_cpu_step(cpu);
	mips_cpu_get_pc_next(cpu, &branchedAddress);
	passed = (branchedAddress == (4 + immed << 2));
	mips_test_end_test(testId, passed, "BEQ was not executed");



	mips_test_end_suite();

}















