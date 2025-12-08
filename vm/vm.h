#ifndef VM_H
#define VM_H

#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
// type definitions
using i_32  = int32_t;

class VM {
	i_32 PC = 100; // program counter
	i_32 SP = 0; // stack pointer
	vector<i_32> memory;
	i_32 typ = 0;
	i_32 data = 0;
	i_32 running = 1;

	// private funcs
	i_32 getTyp(i_32 instruction);
	i_32 getData(i_32 instruction);
	void fetch();
	void decode();
	void execute();
	void doPrimitive();

	public:
	VM();
	void run();
	void loadProgram(vector<i_32> prog);


};
#endif

