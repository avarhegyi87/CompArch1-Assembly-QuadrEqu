#include <iostream>
using namespace std;

int main() {
	_asm {
		mov eax, 1;
		mov eax, 2;
		jmp c1;
		mov eax, 3;
	c1: mov eax, 4;
		jmp c2;
	c2: jmp c3;
		mov eax, 6;
	c3: nop;
	}

	//system("pause");
	return 0;
}