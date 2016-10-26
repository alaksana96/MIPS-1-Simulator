/*
 * mips_cpu.cpp
 *
 *  Created on: 17 Oct 2016
 *      Author: apl115
 */

#include "mips.h"

#include "mips_cpu_decoder.h"
#include "mips_cpu_instructions.h"
#include <assert.h>
#include <iostream>

using namespace std;


struct mips_cpu_impl{
	uint32_t pc;
	uint32_t pcNext;
	uint32_t regs[32];
	mips_mem_h mem;
	unsigned logLevel;
	FILE *logFile;
};

mips_cpu_h mips_cpu_create(mips_mem_h mem){

	mips_cpu_impl *state = new mips_cpu_impl;

	state->pc = 0;
	for(unsigned i = 0; i < 32; i++){
		state->regs[i] = 0;
	}

	state->mem = mem;

	return state;
}

mips_error mips_cpu_reset(mips_cpu_h state){

	state->pc = 0;
	state->pcNext = 4;
	for(unsigned i = 0; i < 32; i++){
		state->regs[i] = 0;
	}
	return mips_Success;
}

mips_error mips_cpu_get_register(
		mips_cpu_h state,
		unsigned index,
		uint32_t *value

){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	} else if(index >= 32){
		return mips_ErrorInvalidArgument;
	} else if(value == 0){
		return mips_ErrorInvalidArgument;
	}

	*value = state->regs[index];
	return mips_Success;
}

mips_error mips_cpu_set_register(
		mips_cpu_h state,
		unsigned index,
		uint32_t value

){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	}else if(index>=32){
		return mips_ErrorInvalidArgument;
	}else if(index == 0){
		state->regs[0] = 0; //No error but won't change the value from 0.
	}

	state->regs[index] = value;
	return mips_Success;
}

mips_error mips_cpu_set_pc( //CHECK THIS SHIT BRO
		mips_cpu_h state,
		uint32_t pc

){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	}

	state->pc = pc;
	return mips_Success;
}

mips_error mips_cpu_get_pc(
		mips_cpu_h state,
		uint32_t *pc

){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	}

	*pc = state->pc;
	return mips_Success;
}

uint32_t littleToBig(const uint8_t *memData){
	return (((uint32_t)memData[0]) << 24) | (((uint32_t)memData[1] << 16)) | (((uint32_t)memData[2]) << 8) | (((uint32_t)memData[3]));
}

mips_error mips_cpu_step(
		mips_cpu_h state

){
	uint8_t buffer[4];

	uint32_t pcOrig, pcGot;

	mips_error err = mips_cpu_get_pc(state, &pcOrig);
	pcGot = pcOrig + 4;
	err = mips_mem_read(state->mem, state->pc, 4,buffer);

	if(err!=mips_Success){
		mips_cpu_get_pc(state, &pcGot);
		assert(pcOrig == pcGot);
		return err; //Why did this fail?
	}

	uint32_t instr = littleToBig(buffer); //Start working in BigEndian

	err = decodeInstruction(instr, state->mem, state);



	return mips_Success;



}

mips_error mips_cpu_set_debug_level(mips_cpu_h h, unsigned level, FILE *dest){

	h->logLevel = level;
	h->logFile = dest;
	return mips_Success;

}

void mips_cpu_free(mips_cpu_h state){
	mips_mem_free(state->mem);
}



/****************************************************************************/


mips_error mips_cpu_set_pc_next(mips_cpu_h state, uint32_t pc){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	}
	state->pcNext = pc;
	return mips_Success;
}

mips_error mips_cpu_get_pc_next(mips_cpu_h state, uint32_t *pc){
	if(state == 0){
		return mips_ErrorInvalidHandle;
	}
	*pc = state->pcNext;
	return mips_Success;
}







