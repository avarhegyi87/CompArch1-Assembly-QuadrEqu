#include <iostream>
using namespace std;

int main() {
	_asm {
		mov al, 0x80;
		cmp al, 0x7f;
		ja L1;
		xor al, al;
	L1: cmp al, 0x7f;
		jg L2;
		xor al, al;
	L2: nop;
	}

	return 0;
}