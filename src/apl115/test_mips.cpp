#include "mips.h"
#include <iostream>
#include <string>

using namespace std;

void setregisters(mips_cpu_h state);
int test_addu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_add(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_subu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sub(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_and(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_or(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_xor(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_addiu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_addi(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_ori(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_andi(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_xori(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sltu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_slt(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sltiu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_slti(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sll(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_srl(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sllv(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_srlv(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sra(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_srav(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sw(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lw(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sb(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lb(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_sh(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lh(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lhu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lbu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_lui(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_beq(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bne(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bgtz(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_blez(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bgez(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bltz(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bgezal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bltzal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);

int test_beqNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bneNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bgtzNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_blezNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bgezNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_bltzNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);

int test_j(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_jal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_jr(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);
int test_jalr(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err);



uint32_t to_big(const uint8_t *pData);
uint32_t to_big16(const uint8_t *pData);



int main(){

	mips_mem_h mem = mips_mem_create_ram(4096); //create memory

    mips_cpu_h cpu = mips_cpu_create(mem); //create cpu

    mips_error err;

    mips_test_begin_suite(); // begin test suite

    int passed;

//ADDU----------------------------------------------------
    uint32_t decodedBinary = 0x00832821;

    int testId = mips_test_begin_test("ADDU");

    setregisters(cpu); //set the registers

    passed = test_addu(decodedBinary, cpu, mem, err);

    mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADDU (not writing to R0)");

    err = mips_cpu_reset(cpu);
//========================================================
    decodedBinary = 0x00220021;

    testId = mips_test_begin_test("ADDU");

	setregisters(cpu); //set the registers

	passed = test_addu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADDU (writing to R0)");

	err = mips_cpu_reset(cpu);
//ADD-----------------------------------------------------
	decodedBinary = 0x00432021; //-1+1

	testId = mips_test_begin_test("ADD");

	setregisters(cpu); //set the registers

	passed = test_add(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADD (-1+1)");

	err = mips_cpu_reset(cpu);
//=========================================================
	decodedBinary = 0x00851820; //overflow

	testId = mips_test_begin_test("ADD");

	setregisters(cpu); //set the registers

	passed = test_add(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADD (overflow)");

	err = mips_cpu_reset(cpu);
//=========================================================
	decodedBinary = 0x00C62820; //overflow

	testId = mips_test_begin_test("ADD");

	setregisters(cpu); //set the registers

	passed = test_add(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADD (overflow)");

	err = mips_cpu_reset(cpu);
//=========================================================
	decodedBinary = 0x00E92820; //no overflow

	testId = mips_test_begin_test("ADD");

	setregisters(cpu); //set the registers

	passed = test_add(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADD (no overflow)");

	err = mips_cpu_reset(cpu);
//=========================================================
	decodedBinary = 0x00220020; //writing into r0

	testId = mips_test_begin_test("ADD");

	setregisters(cpu); //set the registers

	passed = test_add(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADD (writing into r0)");

	err = mips_cpu_reset(cpu);
//SUBU------------------------------------------------------
	decodedBinary = 0x00EA2823; //no overflow

	testId = mips_test_begin_test("SUBU");

	setregisters(cpu); //set the registers

	passed = test_subu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing SUBU");

	err = mips_cpu_reset(cpu);
//=========================================================------------------------------------------------------
	decodedBinary = 0x00220023; //writing into r0

	testId = mips_test_begin_test("SUBU");

	setregisters(cpu); //set the registers

	passed = test_subu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing SUBU(writing into r0)");

	err = mips_cpu_reset(cpu);
//SUB----------------------------------------------------------
	decodedBinary = 0x00E92822; //no overflow

	testId = mips_test_begin_test("SUB");

	setregisters(cpu); //set the registers

	passed = test_sub(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing SUB (no overflow)");

	err = mips_cpu_reset(cpu);
//=============================================================
	decodedBinary = 0x00853022; //no overflow

	testId = mips_test_begin_test("SUB");

	setregisters(cpu); //set the registers

	passed = test_sub(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing SUB (no overflow)");

	err = mips_cpu_reset(cpu);
//=============================================================
	decodedBinary = 0x00A61022; //overflow

	testId = mips_test_begin_test("SUB");

	setregisters(cpu); //set the registers

	passed = test_sub(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing SUB (overflow)");

	err = mips_cpu_reset(cpu);
//=============================================================
	decodedBinary = 0x00A31022; //overflow

	testId = mips_test_begin_test("SUB");

	setregisters(cpu); //set the registers

	passed = test_sub(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing SUB (overflow)");

	err = mips_cpu_reset(cpu);
//=============================================================
	decodedBinary = 0x00220022; //writing in register 0

	testId = mips_test_begin_test("SUB");

	setregisters(cpu); //set the registers

	passed = test_sub(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing SUB (writing in register 0)");

	err = mips_cpu_reset(cpu);

	err = mips_cpu_reset(cpu);
//AND-----------------------------------------------------------

	decodedBinary = 0x00220024; //writing in register 0

	testId = mips_test_begin_test("AND");

	setregisters(cpu); //set the registers

	passed = test_and(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing AND (writing in register 0)");

	err = mips_cpu_reset(cpu);
//========================================================

	decodedBinary = 0x00833824; //writing in register 0

	testId = mips_test_begin_test("AND");

	setregisters(cpu); //set the registers

	passed = test_and(decodedBinary, cpu, mem, err);


	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing AND");
	err = mips_cpu_reset(cpu);
	//OR--------------------------------------------------------

	decodedBinary = 0x00280025; //writing in register 0

	testId = mips_test_begin_test("OR");

	setregisters(cpu); //set the registers

	passed = test_or(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing OR (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================

	decodedBinary = 0x00283825; //

	testId = mips_test_begin_test("OR");

	setregisters(cpu); //set the registers

	passed = test_or(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing OR");
	err = mips_cpu_reset(cpu);
//XOR--------------------------------------------------------

	decodedBinary = 0x00280026; //writing in register 0

	testId = mips_test_begin_test("XOR");

	setregisters(cpu); //set the registers

	passed = test_xor(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing XOR (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================

	decodedBinary = 0x00283826; //

	testId = mips_test_begin_test("XOR");

	setregisters(cpu); //set the registers

	passed = test_xor(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing XOR");
	err = mips_cpu_reset(cpu);
//ADDIU--------------------------------------------------------

	decodedBinary = 0x2420FFFF; //writing in register 0

	testId = mips_test_begin_test("ADDIU");

	setregisters(cpu); //set the registers

	passed = test_addiu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADDIU (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x2425FFFF; //writing in register 0

	testId = mips_test_begin_test("ADDIU");

	setregisters(cpu); //set the registers

	passed = test_addiu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADDIU (writing in register 0)");
	err = mips_cpu_reset(cpu);
//ADDI--------------------------------------------------------

	decodedBinary = 0x2020FFFF; //writing in register 0

	testId = mips_test_begin_test("ADDI");

	setregisters(cpu); //set the registers

	passed = test_addi(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ADDIU (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x2025FFFF; //writing in register 0

	testId = mips_test_begin_test("ADDI");

	setregisters(cpu); //set the registers

	passed = test_addi(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADDIU (no overflow)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x20278000; //writing in register 0

	testId = mips_test_begin_test("ADDI");

	setregisters(cpu); //set the registers

	passed = test_addi(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ADDIU (no overflow)");
	err = mips_cpu_reset(cpu);
//ORI--------------------------------------------------------

	decodedBinary = 0x34400194; //writing in register 0

	testId = mips_test_begin_test("ORI");

	setregisters(cpu); //set the registers

	passed = test_ori(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ORI (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x34470194; //

	testId = mips_test_begin_test("ORI");

	setregisters(cpu); //set the registers

	passed = test_ori(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ORI ");
	err = mips_cpu_reset(cpu);
//ANDI--------------------------------------------------------

	decodedBinary = 0x30400194; //writing in register 0

	testId = mips_test_begin_test("ANDI");

	setregisters(cpu); //set the registers

	passed = test_andi(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing ANDI (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x30450194; //

	testId = mips_test_begin_test("ANDI");

	setregisters(cpu); //set the registers

	passed = test_andi(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing ANDI ");
	err = mips_cpu_reset(cpu);
//XORI--------------------------------------------------------
	decodedBinary = 0x38400194; //writing in register 0

	testId = mips_test_begin_test("XORI");

	setregisters(cpu); //set the registers

	passed = test_xori(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing XORI (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x38450194; //

	testId = mips_test_begin_test("XORI");

	setregisters(cpu); //set the registers

	passed = test_xori(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing XORI ");
	err = mips_cpu_reset(cpu);
//SLTU--------------------------------------------------------
	decodedBinary = 0x0024002B; //writing in register 0

	testId = mips_test_begin_test("SLTU");

	setregisters(cpu); //set the registers

	passed = test_sltu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing sltu (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x0024282B; //

	testId = mips_test_begin_test("SLTU");

	setregisters(cpu); //set the registers

	passed = test_sltu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sltu ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x0081402B; //

	testId = mips_test_begin_test("SLTU");

	setregisters(cpu); //set the registers

	passed = test_sltu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sltu ");

	err = mips_cpu_reset(cpu);

//SLT--------------------------------------------------------
	decodedBinary = 0x0024002A; //writing in register 0

	testId = mips_test_begin_test("SLT");

	setregisters(cpu); //set the registers

	passed = test_slt(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing slt (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x0024502A; //

	testId = mips_test_begin_test("SLT");

	setregisters(cpu); //set the registers

	passed = test_slt(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slt ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x0081402A; //

	testId = mips_test_begin_test("SLT");

	setregisters(cpu); //set the registers

	passed = test_slt(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slt ");

	err = mips_cpu_reset(cpu);

//SLTIU--------------------------------------------------------

//========================================================
	decodedBinary = 0x2C260200; //

	testId = mips_test_begin_test("SLTIU");

	setregisters(cpu); //set the registers

	passed = test_sltiu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sltiu ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x2C26FFFF; //

	testId = mips_test_begin_test("SLTIU");

	setregisters(cpu); //set the registers

	passed = test_sltiu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sltiu ");

	err = mips_cpu_reset(cpu);

//SLTI--------------------------------------------------------
	decodedBinary = 0x28207FFF; //writing in register 0

	testId = mips_test_begin_test("SLTI");

	setregisters(cpu); //set the registers

	passed = test_slti(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing slti (writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x28267FFF; //

	testId = mips_test_begin_test("SLTI");

	setregisters(cpu); //set the registers

	passed = test_slti(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x2826FFFF; //

	testId = mips_test_begin_test("SLTI");

	setregisters(cpu); //set the registers

	passed = test_slti(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti ");

	err = mips_cpu_reset(cpu);

//SLL--------------------------------------------------------
	decodedBinary = 0x00020080; //writing in register 0

	testId = mips_test_begin_test("SLL");

	setregisters(cpu); //set the registers

	passed = test_sll(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing sll(writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x00022880; //

	testId = mips_test_begin_test("SLL");

	setregisters(cpu); //set the registers

	passed = test_sll(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sll ");

	err = mips_cpu_reset(cpu);
//SRL------========================================================
	decodedBinary = 0x00020082; //

	testId = mips_test_begin_test("SRL");

	setregisters(cpu); //set the registers

	passed = test_srl(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing srl ");

	err = mips_cpu_reset(cpu);
//--------------------------------------------------------
	decodedBinary = 0x00022882; //writing in register 0

	testId = mips_test_begin_test("SRL");

	setregisters(cpu); //set the registers

	passed = test_srl(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti (writing in register 0)");
	err = mips_cpu_reset(cpu);
//SRA========================================================
	decodedBinary = 0x00020083; //

	testId = mips_test_begin_test("SRA");

	setregisters(cpu); //set the registers

	passed = test_sra(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing slti ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x00023883; //

	testId = mips_test_begin_test("SRA");

	setregisters(cpu); //set the registers

	passed = test_sra(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti ");

	err = mips_cpu_reset(cpu);

//SLLV--------------------------------------------------------
	decodedBinary = 0x01820004; //writing in register 0

	testId = mips_test_begin_test("SLLV");

	setregisters(cpu); //set the registers

	passed = test_sllv(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing sll(writing in register 0)");
	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x01820804; //

	testId = mips_test_begin_test("SLLV");

	setregisters(cpu); //set the registers

	passed = test_sllv(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sll ");

	err = mips_cpu_reset(cpu);
//SRLV------========================================================
	decodedBinary = 0x01820006; //

	testId = mips_test_begin_test("SRLV");

	setregisters(cpu); //set the registers

	passed = test_srlv(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing srl ");

	err = mips_cpu_reset(cpu);
//--------------------------------------------------------
	decodedBinary = 0x01820806; //writing in register 0

	testId = mips_test_begin_test("SRLV");

	setregisters(cpu); //set the registers

	passed = test_srlv(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti (writing in register 0)");
	err = mips_cpu_reset(cpu);
//SRAV========================================================
	decodedBinary = 0x01820007; //

	testId = mips_test_begin_test("SRAV");

	setregisters(cpu); //set the registers

	passed = test_srav(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing slti ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x01820807; //

	testId = mips_test_begin_test("SRAV");

	setregisters(cpu); //set the registers

	passed = test_srav(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing slti ");

	err = mips_cpu_reset(cpu);
//SW========================================================
	decodedBinary = 0xAEEFFFFC; //

	testId = mips_test_begin_test("SW");

	setregisters(cpu); //set the registers

	passed = test_sw(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sw ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0xAE2D0020; //

	testId = mips_test_begin_test("SW");

	setregisters(cpu); //set the registers

	passed = test_sw(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sw ");

	err = mips_cpu_reset(cpu);

//LW========================================================
	decodedBinary = 0x8EEFFFFC; //

	testId = mips_test_begin_test("LW");

	setregisters(cpu); //set the registers

	passed = test_lw(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lw ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x8E2D0020; //

	testId = mips_test_begin_test("LW");

	setregisters(cpu); //set the registers

	passed = test_lw(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lw ");

	err = mips_cpu_reset(cpu);

//========================================================
	decodedBinary = 0x8E200020; //

	testId = mips_test_begin_test("LW");

	setregisters(cpu); //set the registers

	passed = test_lw(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lw(writing to r0) ");

	err = mips_cpu_reset(cpu);

//SB========================================================
	decodedBinary = 0xA22DFFFC; //

	testId = mips_test_begin_test("SB");

	setregisters(cpu); //set the registers

	passed = test_sb(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sb ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0xA22D0020; //

	testId = mips_test_begin_test("SB");

	setregisters(cpu); //set the registers

	passed = test_sb(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sb ");

	err = mips_cpu_reset(cpu);

//LB========================================================
	decodedBinary = 0x822D0020; //

	testId = mips_test_begin_test("LB");

	setregisters(cpu); //set the registers

	passed = test_lb(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lb ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x822DFFFC; //

	testId = mips_test_begin_test("LB");

	setregisters(cpu); //set the registers

	passed = test_lb(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lb ");

	err = mips_cpu_reset(cpu);

//========================================================
	decodedBinary = 0x82200020; //

	testId = mips_test_begin_test("LB");

	setregisters(cpu); //set the registers

	passed = test_lb(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lb(writing to r0) ");

	err = mips_cpu_reset(cpu);

//SH========================================================
	decodedBinary = 0xA6F30020; //

	testId = mips_test_begin_test("SH");

	setregisters(cpu); //set the registers

	passed = test_sh(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sh ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0xA6F30020; //

	testId = mips_test_begin_test("SH");

	setregisters(cpu); //set the registers

	passed = test_sh(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing sh ");

	err = mips_cpu_reset(cpu);

//LH========================================================
	decodedBinary = 0x86F30020; //

	testId = mips_test_begin_test("LH");

	setregisters(cpu); //set the registers

	passed = test_lh(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lh ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x86F30020; //

	testId = mips_test_begin_test("LH");

	setregisters(cpu); //set the registers

	passed = test_lh(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lh ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x86E00020; //

	testId = mips_test_begin_test("LH");

	setregisters(cpu); //set the registers

	passed = test_lh(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lh (writing to r0) ");

	err = mips_cpu_reset(cpu);

//LHU========================================================
	decodedBinary = 0x96200020; //

	testId = mips_test_begin_test("LHU");

	setregisters(cpu); //set the registers

	passed = test_lhu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lhu (writing to r0)");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x96270020; //

	testId = mips_test_begin_test("LHU");

	setregisters(cpu); //set the registers

	passed = test_lhu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lhu ");

	err = mips_cpu_reset(cpu);

//LB========================================================
	decodedBinary = 0x92200020; //

	testId = mips_test_begin_test("LBU");

	setregisters(cpu); //set the registers

	passed = test_lbu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lbu(writing to zero) ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x92280020; //

	testId = mips_test_begin_test("LBU");

	setregisters(cpu); //set the registers

	passed = test_lbu(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lbu ");

	err = mips_cpu_reset(cpu);

//LUI========================================================
	decodedBinary = 0x3C000200; //

	testId = mips_test_begin_test("LUI");

	setregisters(cpu); //set the registers

	passed = test_lui(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 0), "Testing lui(writing to zero) ");

	err = mips_cpu_reset(cpu);
//========================================================
	decodedBinary = 0x3C060200; //

	testId = mips_test_begin_test("LUI");

	setregisters(cpu); //set the registers

	passed = test_lui(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing lui ");

	err = mips_cpu_reset(cpu);

//BQE========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BEQ");

	setregisters(cpu); //set the registers

	passed = test_beq(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing beq ");

	err = mips_cpu_reset(cpu);

//BNE========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BNE");

	setregisters(cpu); //set the registers

	passed = test_bne(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bne ");

	err = mips_cpu_reset(cpu);

//BGTZ========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BGTZ");

	setregisters(cpu); //set the registers

	passed = test_bgtz(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bbgtz ");

	err = mips_cpu_reset(cpu);

//BLEZ========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BLEZ");

	setregisters(cpu); //set the registers

	passed = test_blez(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing blez ");

	err = mips_cpu_reset(cpu);

//BGEZ========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BGEZ");

	setregisters(cpu); //set the registers

	passed = test_bgez(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bbgez ");

	err = mips_cpu_reset(cpu);

//BLTZ========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BLTZ");

	setregisters(cpu); //set the registers

	passed = test_bltz(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bltz ");

	err = mips_cpu_reset(cpu);

//BLTZAL========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BLTZAL");

	setregisters(cpu); //set the registers

	passed = test_bltzal(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bltzal ");

	err = mips_cpu_reset(cpu);

//BEQZAL========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BGEZAL");

	setregisters(cpu); //set the registers

	passed = test_bgezal(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing beqzal ");

	err = mips_cpu_reset(cpu);

//J========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("J");

	setregisters(cpu); //set the registers

	passed = test_j(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing j");

	err = mips_cpu_reset(cpu);

//JAL========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("JAL");

	setregisters(cpu); //set the registers

	passed = test_jal(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing jal");

	err = mips_cpu_reset(cpu);

//JR========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("JR");

	setregisters(cpu); //set the registers

	passed = test_jr(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing jr");

	err = mips_cpu_reset(cpu);

//JALR========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("JALR");

	setregisters(cpu); //set the registers

	passed = test_jalr(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing jalr");

	err = mips_cpu_reset(cpu);

//BQENEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BEQ");

	setregisters(cpu); //set the registers

	passed = test_beqNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing beq negative offset");

	err = mips_cpu_reset(cpu);

//BNENEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BNE");

	setregisters(cpu); //set the registers

	passed = test_bneNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bne negative offset");

	err = mips_cpu_reset(cpu);

//BGTZNEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BGTZ");

	setregisters(cpu); //set the registers

	passed = test_bgtzNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bgtz negative offset");

	err = mips_cpu_reset(cpu);

//BLEZNEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BLEZ");

	setregisters(cpu); //set the registers

	passed = test_blezNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing blez negative offset");

	err = mips_cpu_reset(cpu);

//BGEZNEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BGEZ");

	setregisters(cpu); //set the registers

	passed = test_bgezNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bgez negative offset");

	err = mips_cpu_reset(cpu);

//BLTZNEG========================================================
	decodedBinary = 0x01AE7820; //

	testId = mips_test_begin_test("BLTZ");

	setregisters(cpu); //set the registers

	passed = test_bltzNeg(decodedBinary, cpu, mem, err);

	mips_test_end_test(testId, (err == mips_Success) && (passed == 1), "Testing bltz negative offset");

	err = mips_cpu_reset(cpu);



    mips_test_end_suite();

    mips_cpu_free(cpu);
    mips_mem_free(mem);
}

int test_addu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){

		uint32_t source1, source2, dest;

		source1 = decodedBinary << 6;
		source1 = source1 >> 27;

		source2 = decodedBinary << 11;
		source2 = source2 >> 27;

		dest = decodedBinary << 16;
		dest = dest >> 27;

		uint8_t instr[4];

		instr[0] = (decodedBinary >> 24) & 0xFF;
		instr[1] = (decodedBinary >> 16) & 0xFF;
		instr[2] = (decodedBinary >> 8) & 0xFF;
		instr[3] = decodedBinary & 0xFF;

		uint32_t unsignedout, pc,unsignedout1, unsignedout2;

		err = mips_cpu_get_pc(cpu, &pc);

		err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

		mips_cpu_step(cpu); //call the main decode function

		err = mips_cpu_get_register(cpu, dest, &unsignedout);


		err = mips_cpu_get_register(cpu, source1, &unsignedout1);
		err = mips_cpu_get_register(cpu, source2, &unsignedout2);


		if(unsignedout == unsignedout1 + unsignedout2){
		   return 1;
		} else {
		   return 0;
		}
}

int test_add(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
		uint32_t source1, source2, dest;

		source1 = decodedBinary << 6;
		source1 = source1 >> 27;

		source2 = decodedBinary << 11;
		source2 = source2 >> 27;

		dest = decodedBinary << 16;
		dest = dest >> 27;

		uint8_t instr[4];

		instr[0] = (decodedBinary >> 24) & 0xFF;
		instr[1] = (decodedBinary >> 16) & 0xFF;
		instr[2] = (decodedBinary >> 8) & 0xFF;
		instr[3] = decodedBinary & 0xFF;

		uint32_t unsignedout, pc,unsignedout1, unsignedout2;

		err = mips_cpu_get_pc(cpu, &pc);

		err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

		mips_cpu_step(cpu); //call the main decode function

		err = mips_cpu_get_register(cpu, dest, &unsignedout);


		err = mips_cpu_get_register(cpu, source1, &unsignedout1);
		err = mips_cpu_get_register(cpu, source2, &unsignedout2);
		int32_t signedout;

		int32_t signedout1, signedout2;

		signedout1 = (int32_t)unsignedout1;
		signedout2 = (int32_t)unsignedout2;

		signedout = (int32_t) unsignedout;

		if(signedout == signedout1 + signedout2){
			return 1;
		}else{
			return 0;
		}
}

int test_subu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, dest;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	if(unsignedout == unsignedout1 - unsignedout2){
	   return 1;
	} else {
	   return 0;
	}
}

int test_sub(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, dest;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	int32_t signedout1, signedout2;

	signedout1 = (int32_t)unsignedout1;
	signedout2 = (int32_t)unsignedout2;

	int32_t signedout = (int32_t) unsignedout;

	if(signedout == signedout1 - signedout2){
	   return 1;
	} else {
	   return 0;
	}
}

int test_and(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){

	uint32_t source1, source2, dest;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	if(unsignedout == (unsignedout1 & unsignedout2)){
	   return 1;
	} else {
	   return 0;
	}
}

int test_or(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){

	uint32_t source1, source2, dest;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	if(unsignedout == (unsignedout1 | unsignedout2)){
	   return 1;
	} else {
	   return 0;
	}
}

int test_xor(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){

	uint32_t source1, source2, dest;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	if(unsignedout == (unsignedout1 ^ unsignedout2)){
	   return 1;
	} else {
	   return 0;
	}
}

int test_addiu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	//cout << unsignedout << " " << unsignedout1 << " " << imm << endl;

	if(unsignedout == imm + unsignedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_addi(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	int32_t signedout = (int32_t) unsignedout;
    imm = (int16_t) imm;
	int32_t imme = (int32_t)imm;

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	int32_t signedout1 = (int32_t) unsignedout1;

	if(signedout == imme + signedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_ori(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	//cout << unsignedout << " " << unsignedout1 << " " << imm << endl;

	if(unsignedout == (imm | unsignedout1)){
		return 1;
	} else {
		return 0;
	}
}

int test_andi(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	//cout << unsignedout << " " << unsignedout1 << " " << imm << endl;

	if(unsignedout == (imm & unsignedout1)){
		return 1;
	} else {
		return 0;
	}
}

int test_xori(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	//cout << unsignedout << " " << unsignedout1 << " " << imm << endl;

	if(unsignedout == (imm ^ unsignedout1)){
		return 1;
	} else {
		return 0;
	}
}

int test_sltu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2,shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	if(unsignedout1 < unsignedout2){
		unsignedout1 = 1;
	} else {
		unsignedout1 = 0;
	}

	if(unsignedout == unsignedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_slt(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	int32_t signedout = (int32_t)unsignedout;
	int32_t signedout1 = (int32_t)unsignedout1;
	int32_t signedout2 = (int32_t)unsignedout2;

	if(signedout1 < signedout2){
		signedout1 = 1;
	} else {
		signedout1 = 0;
	}

	if(signedout1 == signedout){
		return 1;
	} else {
		return 0;
	}
}

int test_sltiu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);


	if(unsignedout1 < imm){
		unsignedout1 = 1;
	} else {
		unsignedout1 = 0;
	}

	if(unsignedout1 == unsignedout){
		return 1;
	} else {
		return 0;
	}
}

int test_slti(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	if((int32_t)unsignedout1 < (int32_t)(int16_t)imm){
		unsignedout1 = 1;
	} else {
		unsignedout1 = 0;
	}

	if(unsignedout1 == unsignedout){
		return 1;
	} else {
		return 0;
	}
}

int test_sll(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);



	if(unsignedout == unsignedout2 << shift){
		return 1;
	}else{
		return 0;
	}
}

int test_srl(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);



	if(unsignedout == unsignedout2 >> shift){
		return 1;
	}else{
		return 0;
	}
}

int test_sllv(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);


	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);



	if(unsignedout == unsignedout2 << unsignedout1){
		return 1;
	}else{
		return 0;
	}
}

int test_srlv(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);



	if(unsignedout == unsignedout2 >> unsignedout1){
		return 1;
	}else{
		return 0;
	}
}

int test_sra(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	int32_t signedout = (int32_t)unsignedout;
	int32_t signedout1 = (int32_t)unsignedout1;
	int32_t signedout2 = (int32_t)unsignedout2;

	if(signedout == signedout2 >> shift){
		return 1;
	}else{
		return 0;
	}
}

int test_srav(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, source2, shift, dest, pc, unsignedout, unsignedout1, unsignedout2;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	source2 = decodedBinary << 11;
	source2 = source2 >> 27;

	dest = decodedBinary << 16;
	dest = dest >> 27;

	if(dest == 0){
		return 0;
	}

	shift = decodedBinary << 21;
	shift = shift >> 27;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout);

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, source2, &unsignedout2);

	int32_t signedout = (int32_t)unsignedout;
	int32_t signedout1 = (int32_t)unsignedout1;
	int32_t signedout2 = (int32_t)unsignedout2;

	if(signedout == signedout2 >> signedout1){
		return 1;
	}else{
		return 0;
	}
}

int test_sw(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;

	mips_mem_read(mem, unsignedout1, 4, buffer);

	unsignedout1 = to_big(buffer);

	if(unsignedout1 == unsignedout2){
		return 1;
	} else {
		return 0;
	}
}

int test_lw(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;



	err = mips_mem_read(mem, unsignedout1, 4, buffer);

	unsignedout1 = to_big(buffer);
	//cout << unsignedout1 << " " << unsignedout2 <<  endl;
	if(unsignedout1 == unsignedout2){
		return 1;
	} else {
		return 0;
	}
}

int test_sb(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;

	//cout << unsignedout1 << " " << imm <<  endl;

	uint8_t read;

	err = mips_mem_read(mem, unsignedout1, 1, &read);

	//cout << unsignedout1 << " " << (int32_t)(int16_t)imm << endl;

	//cout << (uint32_t)read << " " << unsignedout2 << endl;
	if(read == unsignedout2){
		return 1;
	} else {
		return 0;
	}

}

int test_lb(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;

	//cout << unsignedout1 << " " << imm <<  endl;

	uint8_t read;

	err = mips_mem_read(mem, unsignedout1, 1, &read);

	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	if(unsignedout2 == (uint32_t)read){
		return 1;
	} else {
		return 0;
	}
}

int test_sh(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);
	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;

	uint8_t buff[2];

	mips_mem_read(mem, unsignedout1, 2, buff);

	unsignedout1 = to_big16(buff);

	//unsignedout2 = unsignedout2 << 16;
//	unsignedout2 = unsignedout2 >> 16;

	//cout << "sh" << unsignedout1 << " " << unsignedout2 << endl;

	if(unsignedout1 == unsignedout2){
		return 1;
	} else {
		return 0;
	}

}

int test_lh(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (int32_t)(int16_t)imm;

	//cout << unsignedout1 << " " << imm <<  endl;

	uint8_t buff[2];

	mips_mem_read(mem, unsignedout1, 2, buff);

	unsignedout1 = to_big16(buff);

	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	unsignedout2 = unsignedout2 << 16;
	unsignedout2 = unsignedout2 >> 16;

	//cout << "lh" << unsignedout1 << " " << unsignedout2 << endl;

	if(unsignedout2 == unsignedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_lhu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (uint32_t)imm;

	//cout << unsignedout1 << " " << imm <<  endl;

	uint8_t buff[2];

	mips_mem_read(mem, unsignedout1, 2, buff);

	unsignedout1 = to_big16(buff);

	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	unsignedout2 = unsignedout2 << 16;
	unsignedout2 = unsignedout2 >> 16;

	//cout << "lh" << unsignedout1 << " " << unsignedout2 << endl;

	if(unsignedout2 == unsignedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_lbu(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, source1, &unsignedout1);

	mips_cpu_step(cpu); //call the main decode function

	unsignedout1 += (uint32_t)imm;

	//cout << unsignedout1 << " " << imm <<  endl;

	uint8_t read;

	err = mips_mem_read(mem, unsignedout1, 1, &read);

	err = mips_cpu_get_register(cpu, dest, &unsignedout2);

	if(unsignedout2 == (uint32_t)read){
		return 1;
	} else {
		return 0;
	}
}

int test_lui(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;


	uint8_t instr[4];
	uint8_t buffer[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc, unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, pc, 4, instr); //read the instruction binary

	mips_cpu_step(cpu); //call the main decode function

	err = mips_cpu_get_register(cpu, dest, &unsignedout1);

	if(imm == unsignedout1){
		return 1;
	} else {
		return 0;
	}
}

int test_beq(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
//	cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
// FF9C
}

int test_bne(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x173A0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_bgtz(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x1E800024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_blez(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x18400024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_bgez(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x06810024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_bltz(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x04400024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);


	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_bgezal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x06910024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary

	///////////////////////////////////////////////////////////////////////////
		decodedBinary = 0x8C01012C;

		source1 = decodedBinary << 6;
		source1 = source1 >> 27;

		dest = decodedBinary << 11;
		dest = dest >> 27;

		imm = decodedBinary << 16;
		imm = imm >> 16;



		instr[0] = (decodedBinary >> 24) & 0xFF;
		instr[1] = (decodedBinary >> 16) & 0xFF;
		instr[2] = (decodedBinary >> 8) & 0xFF;
		instr[3] = decodedBinary & 0xFF;



		err = mips_cpu_get_pc(cpu, &pc);
		//cout << pc << endl;
		err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_cpu_get_register(cpu, 31, &unsignedout);
	err = mips_cpu_set_pc(cpu, unsignedout);

	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 1, &unsignedout2);


	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_bltzal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x04500024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;




	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary

/////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary

	///////////////////////////////////////////////////////////////////////////
		decodedBinary = 0x8C01012C;

		source1 = decodedBinary << 6;
		source1 = source1 >> 27;

		dest = decodedBinary << 11;
		dest = dest >> 27;

		imm = decodedBinary << 16;
		imm = imm >> 16;



		instr[0] = (decodedBinary >> 24) & 0xFF;
		instr[1] = (decodedBinary >> 16) & 0xFF;
		instr[2] = (decodedBinary >> 8) & 0xFF;
		instr[3] = decodedBinary & 0xFF;



		err = mips_cpu_get_pc(cpu, &pc);
		//cout << pc << endl;
		err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary

	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 31, &unsignedout);
	err = mips_cpu_set_pc(cpu, unsignedout);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);


	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_j(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x08000026;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);

	//cout << unsignedout << " " << unsignedout1 << endl;

	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_jal(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x0C000026;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;




	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary

/////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary

	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 31, &unsignedout);
	err = mips_cpu_set_pc(cpu, unsignedout);
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);


	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_jr(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x03C00008;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary


	decodedBinary = 0x016C5020;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary


	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;

	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);

	//cout << unsignedout << " " << unsignedout1 << endl;

	if(unsignedout == 5 and unsignedout1 == 1){
		return 1;
	} else {
		return 0;
	}
}

int test_jalr(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm, destt;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;




	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x03C0E809;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	destt = decodedBinary << 16;
	destt = destt >> 27;


	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary

/////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x016C5020;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary

	err = mips_cpu_get_register(cpu, 1, &unsignedout2);

		cout << unsignedout2 << endl;

	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, destt, &unsignedout);
	cout << unsignedout << endl;
	err = mips_cpu_set_pc(cpu, unsignedout);

	mips_cpu_step(cpu);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);

	cout << unsignedout2 << endl;

	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_beqNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x135BFFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
		decodedBinary = 0x8C01012C;

		source1 = decodedBinary << 6;
		source1 = source1 >> 27;

		dest = decodedBinary << 11;
		dest = dest >> 27;

		imm = decodedBinary << 16;
		imm = imm >> 16;

		instr[0] = (decodedBinary >> 24) & 0xFF;
		instr[1] = (decodedBinary >> 16) & 0xFF;
		instr[2] = (decodedBinary >> 8) & 0xFF;
		instr[3] = decodedBinary & 0xFF;

		err = mips_cpu_get_pc(cpu, &pc);
		//cout << pc << endl;
		err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_bneNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x173BFFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_bgtzNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x1F40FFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_blezNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x1840FFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_bgezNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x0621FFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int test_bltzNeg(uint32_t decodedBinary, mips_cpu_h cpu, mips_mem_h mem, mips_error &err){
	uint32_t source1, dest, imm;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	uint8_t instr[4];

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	uint32_t unsignedout, pc,unsignedout1, unsignedout2;

	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 0, 4, instr); //read the instruction binary
//////////////////////////////////////////////////
	decodedBinary = 0x124F0024;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;
	int32_t imme = (int16_t) imm << 2;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 4, 4, instr); //read the instruction binary

///////////////////////////////////////////////////
	decodedBinary = 0x016A9822;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;


	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;



	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 8, 4, instr); //read the instruction binary
///////////////////////////////////////////////////////

	decodedBinary = 0x0440FFDC;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 152, 4, instr); //read the instruction binary
/////////////////////////////////////////////////////////////////
	decodedBinary = 0x016A9822;



	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;



	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;


	err = mips_cpu_get_pc(cpu, &pc);

	err = mips_mem_write(mem, 156, 4, instr); //read the instruction binary

///////////////////////////////////////////////////////////////////////////
	decodedBinary = 0x8C01012C;

	source1 = decodedBinary << 6;
	source1 = source1 >> 27;

	dest = decodedBinary << 11;
	dest = dest >> 27;

	imm = decodedBinary << 16;
	imm = imm >> 16;

	instr[0] = (decodedBinary >> 24) & 0xFF;
	instr[1] = (decodedBinary >> 16) & 0xFF;
	instr[2] = (decodedBinary >> 8) & 0xFF;
	instr[3] = decodedBinary & 0xFF;

	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	err = mips_mem_write(mem, 12, 4, instr); //read the instruction binary




	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;
	mips_cpu_step(cpu);
	err = mips_cpu_get_pc(cpu, &pc);
	//cout << pc << endl;


	err = mips_cpu_get_register(cpu, 10, &unsignedout);
	err = mips_cpu_get_register(cpu, 19, &unsignedout1);
	err = mips_cpu_get_register(cpu, 1, &unsignedout2);



	if(unsignedout2 == 0){
		return 1;
	} else {
		return 0;
	}
}




void setregisters(mips_cpu_h state){
	mips_error err;
	err = mips_cpu_set_register(state, 1, 0xf9da6b6c);
	err = mips_cpu_set_register(state, 2, 0xffffffff);
	err = mips_cpu_set_register(state, 3, 0x00000001);
	err = mips_cpu_set_register(state, 4, 0x8fffffff);
	err = mips_cpu_set_register(state, 5, 0x80000000);
	err = mips_cpu_set_register(state, 6, 0x7FFFFFFF);
	err = mips_cpu_set_register(state, 7, 0x2085E449);
	err = mips_cpu_set_register(state, 8, 0x7a14f5fa);
	err = mips_cpu_set_register(state, 9, 0x2b00f3ef);
	err = mips_cpu_set_register(state, 10, 1);
	err = mips_cpu_set_register(state, 11, 2);
	err = mips_cpu_set_register(state, 12, 3);
	err = mips_cpu_set_register(state, 13, 4);
	err = mips_cpu_set_register(state, 14, 5);
	err = mips_cpu_set_register(state, 15, 6);
	err = mips_cpu_set_register(state, 16, 7);
	err = mips_cpu_set_register(state, 17, 8);
	err = mips_cpu_set_register(state, 18, 9);
	err = mips_cpu_set_register(state, 19, 10);
	err = mips_cpu_set_register(state, 20, 0x2a702d28);
	err = mips_cpu_set_register(state, 21, 0x51e9a5ec);
	err = mips_cpu_set_register(state, 22, 0x75187d19);
	err = mips_cpu_set_register(state, 23, 16);
	err = mips_cpu_set_register(state, 24, 0x95d50e0c);
	err = mips_cpu_set_register(state, 25, 0xbae741e3);
	err = mips_cpu_set_register(state, 26, 0x3596cf7f);
	err = mips_cpu_set_register(state, 27, 0x3596cf7f);
	err = mips_cpu_set_register(state, 28, 0x097e98da);
	err = mips_cpu_set_register(state, 29, 0xc1409114);
	err = mips_cpu_set_register(state, 30, 152);
	err = mips_cpu_set_register(state, 31, 0x02c99aa9);
}


uint32_t to_big(const uint8_t *pData){
    return
        (((uint32_t)pData[0])<<24)
        |
        (((uint32_t)pData[1])<<16)
        |
        (((uint32_t)pData[2])<<8)
        |
        (((uint32_t)pData[3])<<0);
}

uint32_t to_big16(const uint8_t *pData){
    return
        (((uint32_t)0x00)<<24)
        |
        (((uint32_t)0x00)<<16)
        |
        (((uint32_t)pData[0])<<8)
        |
        (((uint32_t)pData[1])<<0);
}
