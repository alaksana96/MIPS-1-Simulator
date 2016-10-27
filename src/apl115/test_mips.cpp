/*
 * test_mips_revamped.cpp
 *
 *  Created on: 26 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include <bitset>
#include <iostream>
#include "mips_cpu_extra.h"

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

void setupTestR(mips_cpu_h state, mips_mem_h mem, uint32_t instr, uint32_t rsV, uint32_t rtV, uint32_t rdV, int test, uint32_t PC, uint32_t PCNext){
	uint32_t rs, rt, rd, shift, func;
	rs = instr >> 21;
	rt = (instr & 0x1F0000) >> 16;
	rd = (instr & 0xF800) >> 11;
	shift = (instr & 0x7C0) >> 6;
	func = instr & 0x3F;

	mips_cpu_set_register(state, rs, rsV);
	mips_cpu_set_register(state, rt, rtV);
	mips_cpu_set_register(state, rd, rdV);

	if(mips_cpu_get_debug_level(state) > 0){
		fprintf(stderr, "\ntest=%u, rd=%u, rs=%u, rt=%u, shift=%u.\n", test, rd, rs, rt, shift);
	}

	if(mips_cpu_get_debug_level(state) >=2){
		fprintf(stderr, "instruction=%08x, PC=%08x, PCNEXT=%08x.\n", instr, PC, PCNext);
	}
}

void setupTestI(mips_cpu_h state, mips_mem_h mem, uint32_t instr, uint32_t rsV, uint32_t rtV, int test, uint32_t PC, uint32_t PCNext){
	uint32_t opcode,rs, rt, immed;
	opcode = instr >> 26;
	rs = (instr & 0x3E00000) >> 21;
	rt = (instr & 0x1F0000) >> 16;
	immed = (instr & 0xFFFF);

	mips_cpu_set_register(state, rs, rsV);
	mips_cpu_set_register(state, rt, rtV);

	if(mips_cpu_get_debug_level(state) > 0){
		fprintf(stderr, "\ntest=%u, rs=%u, rt=%u, immed=%u.\n", test, rs, rt, immed);
	}

	if(mips_cpu_get_debug_level(state) >=2){
		fprintf(stderr, "instruction=%08x, PC=%08x, PCNEXT=%08x.\n", instr, PC, PCNext);
	}
}



int main(){

	mips_mem_h mem = mips_mem_create_ram(4096);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();

	mips_error err;
	int testId, passed;
	uint32_t instr, result;
	uint8_t temp8;
	uint8_t buffer[4];

	uint32_t PC, PCNEXT;

	mips_cpu_set_debug_level(cpu, 2, stderr);

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADD");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x00430820; //ADD R1 R2 R3
	setupTestR(cpu, mem, instr, 0x4350, 0x53900, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);

	mips_cpu_step(cpu); //Step CPU

	mips_cpu_get_register(cpu, 1, &result);

	passed = (result == 0x57C50);

	mips_test_end_test(testId, passed, "ADD 0x4350 + 0x53900 = 0x57C50");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADD");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x016C5020; //ADD R10 R11 R12
	setupTestR(cpu, mem, instr, -100, -400, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);

	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 10, &result);

	passed = (result == -500);
	mips_test_end_test(testId, passed, "ADD -100 + -400 = -500");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADD");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x035BC820; //ADD R25 R26 R27
	setupTestR(cpu, mem, instr, 0x7FFFFFFF, 0x1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);

	err = mips_cpu_step(cpu);
	passed = (err = mips_ExceptionArithmeticOverflow);
	mips_test_end_test(testId, passed, "Overflow");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADD");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x014E9820; //ADD R19 R10 R14
	setupTestR(cpu, mem, instr, 0x80000000, 0xFFFFFFFF, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	err = mips_cpu_step(cpu);
	passed = (err = mips_ExceptionArithmeticOverflow);
	mips_test_end_test(testId, passed, "Overflow");


	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x21CD200F; //addi r13 r14 0x200f
	setupTestI(cpu, mem, instr, 0x234, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	passed = (0x200f + 0x234);
	mips_test_end_test(testId, passed, "ADDI = 0x2243");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x21CDFF10; //addi r13 r14 0xFF10
	setupTestI(cpu, mem, instr, 0x1234, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	passed = (0x200f -240);
	mips_test_end_test(testId, passed, "ADDI = 4420");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x21CDFF10; //addi r13 r14 0xFF10
	setupTestI(cpu, mem, instr, 0x80000000, 420, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 13, &result);
	passed = (result == 420);
	mips_test_end_test(testId, passed, "Overflow, Negative");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x21CD0001; //addi r13 r14 0x0001
	setupTestI(cpu, mem, instr, 0x7FFFFFFF, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 13, &result);
	passed = (result == 0);
	mips_test_end_test(testId, passed, "Overflow, Positive");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDIU");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x25CDFF10; //addiu r13 r14 0xFF10
	setupTestI(cpu, mem, instr, 0x400, 420, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 13, &result);
	passed = (result == 0x10310);
	mips_test_end_test(testId, passed, "Answer = 0x10310");

	mips_test_end_suite();

}















