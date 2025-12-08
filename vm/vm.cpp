#include "vm.h"
using namespace std;

/*
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format:
 * 0 => positive int
 * 1 => primitive instruction
 * 2 => negative int
 * 3 => undefined
 * */

// functions
VM::VM()
{
	memory.reserve(1*10^6); // word size
	
}
i_32 VM::getTyp(i_32 instruction)
{
	// returns the top two bits
	i_32 type =  0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}

i_32 VM::getData(i_32 instruction)
{
	// removes the top two bits and only has the last thirty bits
	i_32 data = 0x3fffffff;
	data = (data & instruction);
	return data;
}
void VM::fetch()
{
	PC+=1;
}
void VM::decode()
{
	// read the instruction at memory[PC] and then splits typ into the first 2 bits
	// and data into the next 30 bits
	typ = getTyp(memory[PC]);
	data = getData(memory[PC]);

}
void VM::execute()
{
	
	if(typ == 0 || typ == 2){
		SP+=1;
		memory[SP] = data; // literally push data on top of the stack, no calcualtion yet
	}else{
		doPrimitive();
	}
}
void VM::doPrimitive()
{
	switch(data){
	
		case 0: // STOP
			cout << "Stop"  << endl;
			running = 0;
			break;
		case 1: // ADD
			cout << "add " << memory[SP - 1] << " " << memory[SP] << endl;
		       memory[SP - 1] = memory[SP-1] + memory[SP]; // our stack grows upwards
			SP-=1;	
	       	       break;
		case 2: // SUB
			cout << "sub " << memory[SP -1] << " " << memory[SP] << endl;
			memory[SP-1] =  memory[SP-1] - memory[SP];
			SP--;
			break;
		case 3: // MUL
	      		cout << "mul " << memory[SP -1] << " " << memory[SP] << endl;
			memory[SP-1] =  memory[SP-1] * memory[SP];
			SP--;
			
			break;
		case 4: // DIV
			cout << "div " << memory[SP -1] << " " << memory[SP] << endl;
			memory[SP-1] =  memory[SP-1] /  memory[SP];
			SP--;
			break;

	}
}
void VM::run()
{
	PC -= 1;// to counteract the fetch method
	while(running == 1){// running = 0 when the STOP instruction is called
		fetch();
		decode();
		execute();
		cout << "tos (top of stack): " << memory[SP] << endl;
	}
}

// loading program into out memory in the stack for run() to read the instructions and exectute
void VM::loadProgram(vector<i_32> prog)
{
	for(i_32 i ; i < prog.size(); i++){
		memory[PC + i] = prog[i];
	}
}
