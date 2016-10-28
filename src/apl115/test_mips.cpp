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
	uint32_t linkReg;

	uint32_t PC, PCNEXT;

	mips_cpu_set_debug_level(cpu, 0, stderr);

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADD");
	passed = 0;
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
	passed = 0;
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
	passed = 0;
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
	passed = 0;
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
	passed = 0;
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
	passed = 0;
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
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x25CDFF10; //addiu r13 r14 0xFF10
	setupTestI(cpu, mem, instr, 0x400, 420, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 13, &result);
	passed = (result == 0x10310);
	mips_test_end_test(testId, passed, "Answer = 0x10310");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ADDU");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x02117821; //addu r15 r16 r17
	setupTestR(cpu, mem, instr, 0x400, 420, 0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);
	passed = (result == (0x400 + 420));
	mips_test_end_test(testId, passed, "Answer = 1444");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("AND");

	instr = 0x01AE6024; //and r12 r13 r14
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;
	setupTestR(cpu, mem, instr, 0xFF00, 0xAAAA, 0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 12, &result);
	passed = (result == (0xAA00));
	mips_test_end_test(testId, passed, "Answer = 0xAA00");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ANDI");

	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;
	instr = 0x3062AAAA; //andi r2 r3 0xaaaa
	setupTestI(cpu, mem, instr, 0xFFFF, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 2, &result);
	passed = (result == (0xAAAA));
	mips_test_end_test(testId, passed, "Answer = 0xAAAA");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BEQ");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x114B0010; //beq r10 r11 0x10 branch by 64
	setupTestI(cpu, mem, instr, 0x3, 0x3, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BEQ
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4)+64);

	mips_test_end_test(testId, passed, "branched");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BEQ");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x114B0010; //beq r10 r11 0x10 branch by 64
	setupTestI(cpu, mem, instr, 0x3, 0x4, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BEQ
	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == PC+4);
	mips_test_end_test(testId, passed, "Not branched");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGEZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x05410010;// bgez r10 0x10 branch by 64
	setupTestI(cpu, mem, instr, 0x3, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGEZ
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4)+64);

	mips_test_end_test(testId, passed, "BGEZ Branched");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGEZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	instr = 0x05410010;// bgez r10 0x10 branch by 64, less than zero so should not branch
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGEZ
	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4));

	mips_test_end_test(testId, passed, "BGEZ did not Branch");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGEZAL");
	passed = 0;passed =
			mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x05D10010; //bgezal r14 0x10
	setupTestI(cpu, mem, instr, 0x20, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGEZAL

	mips_cpu_get_pc_next(cpu, &result);
	mips_cpu_get_register(cpu, 31, &linkReg);

	passed = ((result == (PC+4)+64) && (linkReg == (PCNEXT+4)));
	mips_test_end_test(testId, passed, "BGEZAL branched and stored in Reg31");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGEZAL");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x05D10010; //bgezal r14 0x10
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	mips_cpu_set_register(cpu, 31, 0x0);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGEZAL

	mips_cpu_get_pc_next(cpu, &result);
	mips_cpu_get_register(cpu, 31, &linkReg);

	passed = ((result == (PC+4)+64) && (linkReg == 0));
	mips_test_end_test(testId, passed, "BGEZAL did not branch");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/


	testId = mips_test_begin_test("BGTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x1DE00010; //bgtz r15 0x10
	setupTestI(cpu, mem, instr, 0x20, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGTZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4)+64);
	mips_test_end_test(testId, passed, "BGTZ branched");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x1DE00010; //bgtz r15 0x10
	setupTestI(cpu, mem, instr, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGTZ

	mips_cpu_get_pc_next(cpu, &result);


	passed = (result == (PCNEXT+4));
	mips_test_end_test(testId, passed, "BGTZ did not branch because = 0");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BGTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);

	passed =
			instr = 0x1DE00010; //bgtz r15 0x10
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BGTZ

	mips_cpu_get_pc_next(cpu, &result);


	passed = (result == (PCNEXT+4));
	mips_test_end_test(testId, passed, "BGTZ did not branch because negative");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/


	testId = mips_test_begin_test("BLEZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x1A200010; //blez r17 0x10
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLEZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4)+64);
	mips_test_end_test(testId, passed, "BLEZ branched since negative");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLEZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x1A200010; //blez r17 0x10
	setupTestI(cpu, mem, instr, 0x20, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLEZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PCNEXT+4));
	mips_test_end_test(testId, passed, "BLEZ did not branched");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLEZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x1A200010; //blez r17 0x10
	setupTestI(cpu, mem, instr, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLEZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PC+4)+64);
	mips_test_end_test(testId, passed, "BLEZ branched since 0");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06600010; //bltz r19 0x10
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLTZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PCNEXT)+64);
	mips_test_end_test(testId, passed, "BLTZ branched since negative");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06600010; //bltz r19 0x10
	setupTestI(cpu, mem, instr, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLTZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PCNEXT + 4));
	mips_test_end_test(testId, passed, "BLTZ did not branched since 0");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZ");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06600010; //bltz r19 0x10
	setupTestI(cpu, mem, instr, 0x20, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLTZ

	mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PCNEXT+4));
	mips_test_end_test(testId, passed, "BLTZ branched since 0");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZAL");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06B00010; //bltzal r21 0x10
	setupTestI(cpu, mem, instr, 0xFFFFFFF1, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BLTZAL

	mips_cpu_get_pc_next(cpu, &result);
	mips_cpu_get_register(cpu, 31, &linkReg);


	passed = ((result == (PCNEXT)+64) && (linkReg == (PCNEXT+4)));
	mips_test_end_test(testId, passed, "BLTZAL branched and stored in Reg31");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZAL");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06B00010; //bltzal r21 0x10
	setupTestI(cpu, mem, instr, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_set_register(cpu, 31, 420);
	mips_cpu_step(cpu); //Does BLTZAL

	mips_cpu_get_pc_next(cpu, &result);
	mips_cpu_get_register(cpu, 31, &linkReg);


	passed = ((result == (PCNEXT+4)) && (linkReg == 420));
	mips_test_end_test(testId, passed, "BLTZAL did not branch, 420 stored in Reg31");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BLTZAL");
	passed = 0;
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);


	instr = 0x06B00010; //bltzal r21 0x10
	setupTestI(cpu, mem, instr, 0x2, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_set_register(cpu, 31, 690);
	mips_cpu_step(cpu); //Does BLTZAL

	mips_cpu_get_pc_next(cpu, &result);
	mips_cpu_get_register(cpu, 31, &linkReg);


	passed = ((result == (PCNEXT+4)) && (linkReg == 690));
	mips_test_end_test(testId, passed, "BLTZAL did not branch, 690 stored in Reg31");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BNE");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x152A0010; //bne r9 r10 0x10 branch by 64
	setupTestI(cpu, mem, instr, 0x3, 0x3, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BNE
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == PCNEXT+4);

	mips_test_end_test(testId, passed, "branched");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("BNE");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x152A0010; //bne r9 r10 0x10 branch by 64
	setupTestI(cpu, mem, instr, 0x3, 0x4, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu); //Does BEQ
	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_cpu_get_pc_next(cpu, &result);

	passed = (result == (PCNEXT)+64);
	mips_test_end_test(testId, passed, "Not branched");


	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/
	/*---------------------------------GOOD-----------------------------*/
	/*----------------------------------SIR-----------------------------*/
	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	instr = 0xAAFFBBCC; //Test Value
	writeInstrToMem(cpu, mem, 4000, instr); //Store Test Value in Mem at 4000
	instr = 0x01220BCC; //Test Value
	writeInstrToMem(cpu, mem, 4004, instr); //Store Test Value in Mem at 4004

	testId = mips_test_begin_test("LB");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x81EE0010; //lb r14 0x10 r15
	setupTestI(cpu, mem, instr, 3984, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xFFFFFFAA);
	mips_test_end_test(testId, passed, "Loaded 0xFFFFFFAA");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LB");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x81EEFFFE; //lb r14 0x10 r15
	setupTestI(cpu, mem, instr, 4006, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0x01);
	mips_test_end_test(testId, passed, "Loaded 0x01");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LBU");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x91EE0001; //lbu r14 0x1 r15
	setupTestI(cpu, mem, instr, 4000, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);
	passed = (result == 0xFF);
	mips_test_end_test(testId, passed, "Loaded 0xFF");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LBU");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x91EEFFFE; //lbu r14 0x1 r15
	setupTestI(cpu, mem, instr, 4009, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xCC);
	mips_test_end_test(testId, passed, "Loaded 0xCC");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LH");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x85EE0001; //lh r14 0x1 r15
	setupTestI(cpu, mem, instr, 3999, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xFFFFAAFF);
	mips_test_end_test(testId, passed, "Loaded 0xFFFFAAFF");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LH");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x85EEFFFF; //lh r14 0x1 r15
	setupTestI(cpu, mem, instr, 4007, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0x0BCC);
	mips_test_end_test(testId, passed, "Loaded 0x0BCC");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LHU");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x95EE0001; //lhu r14 0x1 r15
	setupTestI(cpu, mem, instr, 3999, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xAAFF);
	mips_test_end_test(testId, passed, "Loaded 0xAAFF");

	/*------------------------------------------------------------------*/
	testId = mips_test_begin_test("LHU");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x95EE0001; //lhu r14 0x1 r15
	setupTestI(cpu, mem, instr, 4005, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0x0BCC);
	mips_test_end_test(testId, passed, "Loaded 0x0BCC");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LUI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x3C0E0001; //lui r14 0x1
	setupTestI(cpu, mem, instr, 4005, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0x10000);
	mips_test_end_test(testId, passed, "Loaded 0x0BCC");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LUI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x3C0EF001; //lui r14 0x1
	setupTestI(cpu, mem, instr, 4005, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xF0010000);
	mips_test_end_test(testId, passed, "Loaded 0x0BCC");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LW");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x8DEE0001; //lw r14 0x1 r15
	setupTestI(cpu, mem, instr, 3999, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0xAAFFBBCC);
	mips_test_end_test(testId, passed, "Loaded 0xAAFFBBCC");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("LW");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x8DEEFFFF; //lw r14 0x1 r15
	setupTestI(cpu, mem, instr, 4005, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 14, &result);

	passed = (result == 0x01220BCC);
	mips_test_end_test(testId, passed, "Loaded 0x01220BCC");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/


	testId = mips_test_begin_test("MFHI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x0000A010; //mfhi r20
	setupTestR(cpu, mem, instr, 0x0, 0x0, 300, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 20, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Loaded MFHI");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("MFLO");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x0000A812; //mflo r21
	setupTestR(cpu, mem, instr, 0x0, 0x0, 420, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 21, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Loaded MFLO");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("MTHI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	mips_cpu_set_register(cpu, 20, 1000);

	instr = 0x02A00011; //mthi r21
	setupTestR(cpu, mem, instr, 420, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x0000A010; //mfhi r20
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 20, &result);

	passed = (result == 420);
	mips_test_end_test(testId, passed, "HI was set to 420");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("MTLO");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	mips_cpu_set_register(cpu, 20, 1000);

	instr = 0x02800013; //mtlo r20
	setupTestR(cpu, mem, instr, 420690, 0x0, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x0000A812; //mflo r21
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);
	mips_cpu_get_register(cpu, 20, &result);

	passed = (result == 420690);
	mips_test_end_test(testId, passed, "LO was set to 420690");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("OR");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x00430825; //or r1 r2 r3
	setupTestR(cpu, mem, instr, 0b10101010, 0b00001111, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 1, &result);

	passed = (result == 0b10101111);
	mips_test_end_test(testId, passed, "Or = 0b10101111");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("ORI");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0x3441AAAA; //ori r1 r2 0xffff
	setupTestI(cpu, mem, instr, 0xFFFF0000, 0b0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 1, &result);

	passed = (result == 0xFFFFAAAA);
	mips_test_end_test(testId, passed, "Ori = 0b10101010");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SB");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0xA3590001; //sb r25 0x1 r26
	setupTestI(cpu, mem, instr, 3500, 0xFF, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x837C0001; //lb r28 0x1 r27
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	setupTestI(cpu, mem, instr, 3500, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 28, &result);

	passed = (result == 0xFFFFFFFF); //Because using LB not LBU to check
	mips_test_end_test(testId, passed, "Wrote 0xFF to memory address 3501");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SB");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0xA359FFFF; //sb r25 0x1 r26
	setupTestI(cpu, mem, instr, 3500, 0xFF, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x937C0001; //lbU r28 0x1 r27
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	setupTestI(cpu, mem, instr, 3498, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 28, &result);

	passed = (result == 0xFF);
	mips_test_end_test(testId, passed,"Wrote 0xFF to memory address 3499");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SH");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0xA77C0001; //sh r28 0x1 r27
	setupTestI(cpu, mem, instr, 3503, 0xFFAA, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x97DD0001; //lhU r29 0x1 r30
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	setupTestI(cpu, mem, instr, 3503, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 29, &result);

	passed = (result == 0xFFAA);
	mips_test_end_test(testId, passed, "Wrote 0xFFAA to memory address 3504");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SH");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0xA77CFFFF; //sh r28 0x1 r27
	setupTestI(cpu, mem, instr, 3505, 0xAAFF, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	instr = 0x97DD0001; //lhU r29 0x1 r30
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	setupTestI(cpu, mem, instr, 3503, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 29, &result);
	passed = (result == 0xAAFF);
	mips_test_end_test(testId, passed, "Wrote 0xAAFF to memory address 3504");

	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SH");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = 0xA77C0001; //sh r28 0x1 r27
	setupTestI(cpu, mem, instr, 3506, 0xAAFF, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	err = mips_cpu_step(cpu);

	passed = (err == mips_ExceptionInvalidAddress);
	mips_test_end_test(testId, passed, "Invalid Address");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SLL");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = (0ul << 26) | (0ul << 21) | (14ul << 16) | (15ul << 11) | (2ul << 6) | (0x0 << 0);
	setupTestR(cpu, mem, instr, 0x0, 0b1010, 0b1, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0b101000);
	mips_test_end_test(testId, passed, "Result was: 0b101000");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/

	testId = mips_test_begin_test("SLL");
	mips_cpu_get_pc(cpu, &PC);
	mips_cpu_get_pc_next(cpu, &PCNEXT);
	passed = 0;

	instr = (0ul << 26) | (10ul << 21) | (11ul << 16) | (12ul) << 11 | (0ul << 6) | (0x4 << 0);
	setupTestR(cpu, mem, instr, 4, 0b10101010, 0x0, testId, PC, PCNEXT);
	writeInstrToMem(cpu, mem, PC, instr);
	mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 12, &result);

	passed = (result == 0xAA0);
	mips_test_end_test(testId, passed, "Result was 0b101010100000");

	/*------------------------------------------------------------------*/
	/*------------------------------------------------------------------*/


	mips_test_end_suite();

}















