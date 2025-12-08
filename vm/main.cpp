#include "vm.h"
using namespace std;

int main()
{
	const uint32_t ADD = 0x40000001;
	const uint32_t SUB = 0x40000002;
	const uint32_t MUL = 0x40000003;
	const uint32_t DIV = 0x40000004;
	const uint32_t STOP = 0x40000000;
	VM vm;
	vector<i_32> prog{3, 4, ADD, 5, SUB, 3, MUL, STOP};
	vm.loadProgram(prog);
	vm.run();
	return 0;
}
