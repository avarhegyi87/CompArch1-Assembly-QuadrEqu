#include <iostream>
using namespace std;

int main() {
	unsigned char b6;
	b6 = 0xff;

	_asm {
		mov al, 0xbd;
		test al, 0x40;
		jz b6_0;
		mov b6, 1;
		jmp vege;
	b6_0: mov b6, 0;
	vege: nop;
	}
}