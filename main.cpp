#include "vm.h"
using namespace std;

int main()
{
	VM vm;
	vector<i_32> prog{3,4,0x20000001, 0x20000000};
	vm.loadProgram(prog);
	vm.run();
	return 0;
}
