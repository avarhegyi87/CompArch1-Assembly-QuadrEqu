#include <iostream>
using namespace std;

int main() {
	_asm {
	L1: stc;
	L2: jc L4;
	L3: jnc L7;
	L4: mov al, 0xff;
	L5: or al, al;
	L6: js L3;
	L7: mov al, 0x80;
	L8: mov bl, 0x81;
	L9: add al, bl;
	L10: jo L12;
	L11: xor eax, eax;
	L12: nop;
	}

	return 0;
}