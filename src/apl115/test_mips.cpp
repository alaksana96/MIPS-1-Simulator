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



int main(){

	mips_mem_h mem = mips_mem_create_ram(4096);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();

	/*#######################################################################*/
	int testId = mips_test_begin_test("ADDU");
	int passed = 0;

	mips_error err;

	uint32_t instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x21 << 0);

	uint8_t buffer[4];
	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	err = mips_mem_write(mem, 0, 4, buffer);

	err = mips_cpu_set_register(cpu, 4, 100);
	err = mips_cpu_set_register(cpu, 5, 60);
	err = mips_cpu_set_register(cpu, 3, 6969);

	err = mips_cpu_step(cpu);

	uint32_t result;
	err = mips_cpu_get_register(cpu, 3, &result);

	passed = (result == 100+60);

	mips_test_end_test(testId, passed, "nice");

	/*#######################################################################*/

	testId = mips_test_begin_test("AND");
	passed = 0;

	instruction = (0ul << 26) | (4ul << 21) | (5ul << 16) | (3ul) << 11 | (0ul << 6) | (0x24 << 0);


	buffer[0] = (instruction >> 24) & 0xFF;
	buffer[1] = (instruction >> 16) & 0xFF;
	buffer[2] = (instruction >> 8) & 0xFF;
	buffer[3] = (instruction >> 0) & 0xFF; //Convert to little-endian

	uint32_t PC;
	err = mips_cpu_get_pc(cpu, &PC);
	err = mips_mem_write(mem, 0, 4, buffer);

	err = mips_cpu_set_register(cpu, 4, 0b00001111);
	err = mips_cpu_set_register(cpu, 5, 0b10101010);
	err = mips_cpu_set_register(cpu, 3, 300);

	err = mips_cpu_set_pc(cpu, 0);

	err = mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 3, &result);

	passed = (result == 0b00001010);

	cout << result << endl;

	mips_test_end_test(testId, passed, "Nice");


	mips_test_end_suite();

	//uint32_t instruction = 0b00000010101011101010001010110000;

	//uint32_t rs,rt,rd,shft,func;

	//decodeJInstruction(instruction);
	//decodeOpCode(instruction);

	return 0;
}

