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
	i_32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}

i_32 VM::getData(i_32 instruction)
{
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
	this->typ = getTyp(memory[PC]);
	this->data = getData(memory[PC]);

}
void VM::execute()
{
	if(typ == 0 || typ == 2){
		this->SP+=1;
		memory[SP] = data;
	}else{
		doPrimitive();
	}
}
void VM::doPrimitive()
{
	switch(this->data){
	
		case 0: // STOP
			cout << "Stop"  << endl;
			running = 0;
			break;
		case 1: // ADD
			cout << "add " << memory[SP - 1] << " " << memory[SP] << endl;
		       memory[SP - 1] = memory[SP-1] + memory[SP]; // our stack grows upwards
			break;
		case 2: // SUB
			cout << "sub" << memory[SP -1] << " " << memory[SP] << endl;
			memory[SP-1] =  memory[SP-1] - memory[SP];
			break;	
	}
}
void VM::run()
{
	PC -= 1;// to counteract the fetch method
	while(running == 1){
		fetch();
		decode();
		execute();
		cout << "tos (top of stack): " << memory[SP] << endl;
	}
}

// loading program into out memory in the stack
void VM::loadProgram(vector<i_32> prog)
{
	for(i_32 i ; i < prog.size(); i++){
		memory[PC + i] = prog[i];
	}
}
