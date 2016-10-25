/*
 * test_mips.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"
#include <bitset>
#include <iostream>
#include "mips_cpu_decoder.h"

using namespace std;

#define INT32_MAX 0x7FFFFFFF
#define INT32_MIN 0x80000000

#define INT16_MAX 0x7FFF
#define INT16_MIN 0x8000

uint32_t littleToBigBoy(const uint8_t *memData);


uint32_t littleToBigBoy(const uint8_t *memData){
	return (((uint32_t)memData[0]) << 24) | (((uint32_t)memData[1] << 16)) | (((uint32_t)memData[2]) << 8) | (((uint32_t)memData[3]));
}


int main(){

	mips_mem_h mem = mips_mem_create_ram(16777204);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();

	int testId, passed;
	mips_error err;
	uint32_t instruction, result;
	uint8_t temp8;
	uint8_t buffer[4];
	uint32_t PC = 0;


	/*#######################################################################*/

	testId = mips_test_begin_test("SLL");
	passed = 0;

	instruction = (0ul << 26) | (0ul << 21) | (14ul << 16) | (15ul << 11) | (2ul << 6) | (0x0 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 14, 0b1010);
	err = mips_cpu_set_register(cpu, 15, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0b101000);
	mips_test_end_test(testId, passed, "Result was: 0b101000");

	/*#######################################################################*/

	testId = mips_test_begin_test("SRL");
	passed = 0;

	instruction = (0ul << 26) | (0ul << 21) | (14ul << 16) | (15ul << 11) | (2ul << 6) | (0x2 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 14, 0b11111111);
	err = mips_cpu_set_register(cpu, 15, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0b111111);
	mips_test_end_test(testId, passed, "Result was: 0b111111");

	/*#######################################################################*/

	testId = mips_test_begin_test("SRA");
	passed = 0;

	instruction = (0ul << 26) | (0ul << 21) | (14ul << 16) | (15ul << 11) | (2ul << 6) | (0x3 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 14, 0x80000000);
	err = mips_cpu_set_register(cpu, 15, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0xE0000000);
	mips_test_end_test(testId, passed, "Result was: 0xE0000000");

	testId = mips_test_begin_test("SRA");
	passed = 0;

	instruction = (0ul << 26) | (0ul << 21) | (14ul << 16) | (15ul << 11) | (2ul << 6) | (0x3 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 14, 0x7FFFFFFF);
	err = mips_cpu_set_register(cpu, 15, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0x1FFFFFFF);
	mips_test_end_test(testId, passed, "Result was: 0x1FFFFFFF");


	/*#######################################################################*/

	testId = mips_test_begin_test("SRAV");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x7 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, 1);
	err = mips_cpu_set_register(cpu, 14, 0x80000000);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0xC0000000);
	mips_test_end_test(testId, passed, "Result was: 0xC0000000");


	testId = mips_test_begin_test("SRAV");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x7 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, 1);
	err = mips_cpu_set_register(cpu, 14, 0x7FFFFFFF);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 0x3FFFFFFF);
	mips_test_end_test(testId, passed, "Result was: 0x3FFFFFFF");

	/*#######################################################################*/

	testId = mips_test_begin_test("ADD");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x20 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, 100);
	err = mips_cpu_set_register(cpu, 14, 200);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 300);
	mips_test_end_test(testId, passed, "Result was: 300");

	testId = mips_test_begin_test("ADD");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x20 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, (uint32_t)-100);
	err = mips_cpu_set_register(cpu, 14, (uint32_t)-200);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == (uint32_t)-300);
	mips_test_end_test(testId, passed, "Result was: -300");

	testId = mips_test_begin_test("ADD");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x20 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, INT32_MAX);
	err = mips_cpu_set_register(cpu, 14, 1);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 6969);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");

	testId = mips_test_begin_test("ADD");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x20 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, INT32_MIN);
	err = mips_cpu_set_register(cpu, 14, -1);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 6969);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");

	/*#######################################################################*/
	testId = mips_test_begin_test("ADDU");
	passed = 0;


	instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x21 << 0);


	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 4, 100);
	err = mips_cpu_set_register(cpu, 5, 60);
	err = mips_cpu_set_register(cpu, 3, 6969);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 3, &result);

	passed = (result == 100+60);

	mips_test_end_test(testId, passed, "Result was: 160");

	/*#######################################################################*/

	testId = mips_test_begin_test("SUB");
	passed = 0;

	instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x22 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 4, 100);
	err = mips_cpu_set_register(cpu, 5, 60);
	err = mips_cpu_set_register(cpu, 3, 6969);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 3, &result);
	passed = (result == 100-60);

	mips_test_end_test(testId, passed, "Result was: 40");

	testId = mips_test_begin_test("SUB");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x22 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, -100);
	err = mips_cpu_set_register(cpu, 14, -60);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == -40);
	mips_test_end_test(testId, passed, "Result was: -40");


	testId = mips_test_begin_test("SUB");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x22 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, INT32_MAX);
	err = mips_cpu_set_register(cpu, 14, INT32_MIN);
	err = mips_cpu_set_register(cpu, 15, 10);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 10);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");


	testId = mips_test_begin_test("SUB");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x22 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, INT32_MIN);
	err = mips_cpu_set_register(cpu, 14, 1);
	err = mips_cpu_set_register(cpu, 15, 10);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 10);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");
	/*#######################################################################*/

	testId = mips_test_begin_test("SUBU");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x23 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, 100);
	err = mips_cpu_set_register(cpu, 14, 60);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	passed = (result == 40);
	mips_test_end_test(testId, passed, "Result was: 160");



	/*#######################################################################*/

	testId = mips_test_begin_test("AND");
	passed = 0;

	instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x24 << 0);


	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer); //Write into next address after ADDU

	err = mips_cpu_set_register(cpu, 4, 0b00001111);
	err = mips_cpu_set_register(cpu, 5, 0b10101010);
	err = mips_cpu_set_register(cpu, 3, 300);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 3, &result);

	passed = (result == 0b00001010);
	mips_test_end_test(testId, passed, "Result was: 0b00001010");

	/*#######################################################################*/

	testId = mips_test_begin_test("OR");
	passed = 0;

	instruction = (0ul << 26) | (10ul << 21) | (11ul << 16) | (12ul) << 11 | (0ul << 6) | (0x25 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 10, 0b00001111);
	err = mips_cpu_set_register(cpu, 11, 0b10101010);
	err = mips_cpu_set_register(cpu, 12, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 12, &result);

	passed = (result == 0b10101111);
	mips_test_end_test(testId, passed, "Result was 0b10101111");

	/*#######################################################################*/

	testId = mips_test_begin_test("XOR");
	passed = 0;

	instruction = (0ul << 26) | (7ul << 21) | (8ul << 16) | (9ul) << 11 | (0ul << 6) | (0x26 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 7, 0b00001111);
	err = mips_cpu_set_register(cpu, 8, 0b10101010);
	err = mips_cpu_set_register(cpu, 9, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 9, &result);

	passed = (result == 0b10100101);
	mips_test_end_test(testId, passed, "Result was: 0b10100101");

	/*#######################################################################*/

	testId = mips_test_begin_test("SLT");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2A << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, -60);
	err = mips_cpu_set_register(cpu, 17, 780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 1);
	mips_test_end_test(testId, passed, "Result was: True");

	testId = mips_test_begin_test("SLT");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2A << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 6000);
	err = mips_cpu_set_register(cpu, 17, -780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Result was: False");

	testId = mips_test_begin_test("SLT");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2A << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, -6000);
	err = mips_cpu_set_register(cpu, 17, -780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 1);
	mips_test_end_test(testId, passed, "Result was: True");

	testId = mips_test_begin_test("SLT");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2A << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 6000);
	err = mips_cpu_set_register(cpu, 17, 780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Result was: False");

	/*#######################################################################*/

	testId = mips_test_begin_test("SLTU");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2B << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 60);
	err = mips_cpu_set_register(cpu, 17, 780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 1);
	mips_test_end_test(testId, passed, "Result was: True");

	testId = mips_test_begin_test("SLTU");
	passed = 0;

	instruction = (0ul << 26) | (16ul << 21) | (17ul << 16) | (18ul) << 11 | (0ul << 6) | (0x2B << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 6000);
	err = mips_cpu_set_register(cpu, 17, 780);
	err = mips_cpu_set_register(cpu, 18, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 18, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Result was: False");


/***************************************************************************************************************/

	testId = mips_test_begin_test("ADDI");
	passed = 0;

	instruction = (0b001000 << 26) | (16ul << 21) | (17ul << 16) | (0x1 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 60);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 61);
	mips_test_end_test(testId, passed, "Result was: 61");


	testId = mips_test_begin_test("ADDI");
	passed = 0;

	instruction = (0b001000 << 26) | (16ul << 21) | (17ul << 16) | (0xF001 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, -60);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == -4155);
	mips_test_end_test(testId, passed, "Result was: -4155");


	testId = mips_test_begin_test("ADDI");
	passed = 0;

	instruction = (0b001000 << 26) | (16ul << 21) | (17ul << 16) | (0x1 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, INT32_MAX);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 780);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");

	testId = mips_test_begin_test("ADDI");
	passed = 0;

	instruction = (0b001000 << 26) | (16ul << 21) | (17ul << 16) | (0x8000 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, INT32_MIN);
	err = mips_cpu_set_register(cpu, 17, 100);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 100);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");

	/*#######################################################################*/

	testId = mips_test_begin_test("ADDIU");
	passed = 0;

	instruction = (0b001001 << 26) | (16ul << 21) | (17ul << 16) | (0x1 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 60);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 61);
	mips_test_end_test(testId, passed, "Result was: 61");

	/*#######################################################################*/


	testId = mips_test_begin_test("ANDI");
	passed = 0;

	instruction = (0b001100 << 26) | (16ul << 21) | (17ul << 16) | (0xAAAA << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0xFFFFFFFF);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 0xAAAA);
	mips_test_end_test(testId, passed, "Result was: 0xAAAA");

	/*#######################################################################*/

	testId = mips_test_begin_test("ORI");
	passed = 0;

	instruction = (0b001101 << 26) | (16ul << 21) | (17ul << 16) | (0xAAAA << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0xFFFF0000);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 0xFFFFAAAA);
	mips_test_end_test(testId, passed, "Result was: 0xFFFFAAAA");

	/*#######################################################################*/

	testId = mips_test_begin_test("XORI");
	passed = 0;

	instruction = (0b001110 << 26) | (16ul << 21) | (17ul << 16) | (0xAAAF << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0xFFFF0000);
	err = mips_cpu_set_register(cpu, 17, 780);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 0xFFFFAAAF);
	mips_test_end_test(testId, passed, "Result was: 0xFFFFAAAF");

	/*#######################################################################*/


	testId = mips_test_begin_test("SW");
	passed = 0;

	instruction = (0b101011 << 26) | (16ul << 21) | (17ul << 16) | (0x0004 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 50000);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0008, 4, buffer);

	result = littleToBigBoy(buffer);
	passed = (result == 50000);
	mips_test_end_test(testId, passed, "Result: 50000, was written to 0x000F0008");

	testId = mips_test_begin_test("SW");
	passed = 0;

	instruction = (0b101011 << 26) | (16ul << 21) | (17ul << 16) | (0xFFFC << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 420);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0000, 4, buffer);

	result = littleToBigBoy(buffer);
	passed = (result == 420);
	mips_test_end_test(testId, passed, "Result: 420, was written to 0x000F0000");


	testId = mips_test_begin_test("SW");
	passed = 0;

	instruction = (0b101011 << 26) | (16ul << 21) | (17ul << 16) | (0x0001 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_mem_read(mem, 0x000F0000, 4, buffer);
	uint32_t previous = littleToBigBoy(buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0000, 4, buffer);

	result = littleToBigBoy(buffer);
	passed = (result == previous);
	mips_test_end_test(testId, passed, "mips_ExceptionInvalidAddress");

	/*#######################################################################*/

	testId = mips_test_begin_test("LW");
	passed = 0;

	instruction = (0b100011 << 26) | (16ul << 21) | (17ul << 16) | (0x0004 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 50000);
	mips_test_end_test(testId, passed, "Result was: 50000");


	/*#######################################################################*/

	testId = mips_test_begin_test("SLTIU");
	passed = 0;

	instruction = (0b001011 << 26) | (16ul << 21) | (17ul << 16) | (0x00FF << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 1);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 1);
	mips_test_end_test(testId, passed, "Result was: True");

	testId = mips_test_begin_test("SLTIU");
	passed = 0;

	instruction = (0b001011 << 26) | (16ul << 21) | (17ul << 16) | (0x00FF << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 1000);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 0);
	mips_test_end_test(testId, passed, "Result was: False");

	/*#######################################################################*/

	testId = mips_test_begin_test("SLLV");
	passed = 0;

	instruction = (0ul << 26) | (10ul << 21) | (11ul << 16) | (12ul) << 11 | (0ul << 6) | (0x4 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 10, 4);
	err = mips_cpu_set_register(cpu, 11, 0b10101010);
	err = mips_cpu_set_register(cpu, 12, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 12, &result);

	passed = (result == 0xAA0);
	mips_test_end_test(testId, passed, "Result was 0b101010100000");

	/*#######################################################################*/

	testId = mips_test_begin_test("SRLV");
	passed = 0;

	instruction = (0ul << 26) | (10ul << 21) | (11ul << 16) | (12ul) << 11 | (0ul << 6) | (0x6 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 10, 4);
	err = mips_cpu_set_register(cpu, 11, 0b10101010);
	err = mips_cpu_set_register(cpu, 12, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 12, &result);

	passed = (result == 0b1010);
	mips_test_end_test(testId, passed, "Result was 0b1010");


	/*#######################################################################*/

	testId = mips_test_begin_test("SRLV");
	passed = 0;

	instruction = (0ul << 26) | (10ul << 21) | (11ul << 16) | (12ul) << 11 | (0ul << 6) | (0x6 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 10, 4);
	err = mips_cpu_set_register(cpu, 11, 0b10101010);
	err = mips_cpu_set_register(cpu, 12, 69);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 12, &result);

	passed = (result == 0b1010);
	mips_test_end_test(testId, passed, "Result was 0b1010");

	/*#######################################################################*/

	testId = mips_test_begin_test("SB");
	passed = 0;

	instruction = (0b101000 << 26) | (16ul << 21) | (17ul << 16) | (0xFFFC << 0); //-4
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 210);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0000, 1, &temp8);

	result = (uint32_t)temp8;

	passed = (result == 210);
	mips_test_end_test(testId, passed, "Result: 210, was written to 0x000F0000"); //-2

	testId = mips_test_begin_test("SB");
	passed = 0;

	instruction = (0b101000 << 26) | (16ul << 21) | (17ul << 16) | (0xFFFE << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0xFF);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0002, 1, &temp8);

	result = (uint32_t)temp8;

	passed = (result == 0xFF);
	mips_test_end_test(testId, passed, "Result: 0xFF, was written to 0x000F0002");


	testId = mips_test_begin_test("SB");
	passed = 0;

	instruction = (0b101000 << 26) | (16ul << 21) | (17ul << 16) | (0xFFFF << 0); //-1
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0xEE);

	err = mips_cpu_step(cpu);
	err = mips_mem_read(mem, 0x000F0003, 1, &temp8);

	result = (uint32_t)temp8;

	cout << result << endl;
	passed = (result == 0xEE);
	mips_test_end_test(testId, passed, "Result: 0xEE, was written to 0x000F0003");



	testId = mips_test_begin_test("SB");
	passed = 0;

	instruction = (0b101000 << 26) | (16ul << 21) | (17ul << 16) | (0x0002 << 0); //+2
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 69);

	err = mips_cpu_step(cpu);

	err = mips_mem_read(mem, 0x000F0006, 1, &temp8);

	result = (uint32_t)temp8;

	passed = (result == 69);
	mips_test_end_test(testId, passed, "Result: 40, was written to 0x000F0006");



	testId = mips_test_begin_test("SB");
	passed = 0;

	instruction = (0b101000 << 26) | (16ul << 21) | (17ul << 16) | (0x0001 << 0); //+1
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 40);

	err = mips_cpu_step(cpu);

	err = mips_mem_read(mem, 0x000F0005, 1, &temp8);

	result = (uint32_t)temp8;

	passed = (result == 40);
	mips_test_end_test(testId, passed, "Result: 40, was written to 0x000F0005");

	/*#######################################################################*/


	testId = mips_test_begin_test("LB");
	passed = 0;

	instruction = (0b100000 << 26) | (16ul << 21) | (17ul << 16) | (0x1 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 40);
	mips_test_end_test(testId, passed, "Result was: 50000");


	testId = mips_test_begin_test("LB");
	passed = 0;

	instruction = (0b100000 << 26) | (16ul << 21) | (17ul << 16) | (0xFFFC << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 210);
	mips_test_end_test(testId, passed, "Result was: 50000");


	testId = mips_test_begin_test("LB");
	passed = 0;

	instruction = (0b100000 << 26) | (16ul << 21) | (17ul << 16) | (0x2 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 0b1);

	err = mips_cpu_step(cpu);

	err = mips_cpu_get_register(cpu, 17, &result);

	passed = (result == 69);
	mips_test_end_test(testId, passed, "Result was: 50000");

	/*#######################################################################*/

	testId = mips_test_begin_test("SH");
	passed = 0;


	instruction = (0b101001 << 26) | (16ul << 21) | (17ul << 16) | (0x0006 << 0);
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian


	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 16, 0x000F0004);
	err = mips_cpu_set_register(cpu, 17, 400);

	instruction = 0;
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian
	err = mips_mem_write(mem, 0x000F000A, 4, buffer);


	err = mips_cpu_step(cpu);

	err = mips_mem_read(mem, 0x000F000A, 2, buffer);

	result = (buffer[0] << 8 | buffer[1] << 0);

	passed = (result == 400);
	mips_test_end_test(testId, passed, "Result: 40, was written to 0x000F0005");



	mips_test_end_suite();



	return 0;
}


