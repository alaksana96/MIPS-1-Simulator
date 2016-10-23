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


int main(){

	mips_mem_h mem = mips_mem_create_ram(4096);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();

	int testId, passed;
	mips_error err;
	uint32_t instruction, result;
	uint8_t buffer[4];
	uint32_t PC = 0;

	/*#######################################################################*/

	int32_t a = 100, b = 200;

	testId = mips_test_begin_test("ADD");
	passed = 0;

	instruction = (0ul << 26) | (13ul << 21) | (14ul << 16) | (15ul << 11) | (0ul << 6) | (0x20 << 0);

	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, PC, 4, buffer);

	err = mips_cpu_set_register(cpu, 13, a);
	err = mips_cpu_set_register(cpu, 14, b);
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

	err = mips_cpu_set_register(cpu, 13, 0x7FFFFFF);
	err = mips_cpu_set_register(cpu, 14, 2);
	err = mips_cpu_set_register(cpu, 15, 6969);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 15, &result);

	cout << bitset<32>(result) << endl;

	passed = (result == 6969);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");
/*
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

	passed = (err == mips_ExceptionArithmeticOverflow) && (result == 6969);
	mips_test_end_test(testId, passed, "Result was: mips_ExceptionArithmeticOverflow");
*/
	/*#######################################################################*/
	testId = mips_test_begin_test("ADDU");
	passed = 0;


	instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x21 << 0);

	buffer[4];
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


	err = mips_cpu_get_pc(cpu, &PC);


	err = mips_cpu_get_register(cpu, 3, &result);

	passed = (result == 100+60);

	mips_test_end_test(testId, passed, "Result was: 160");

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
	mips_test_end_test(testId, passed, "Result was: 40");
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


	mips_test_end_suite();


	return 0;
}


