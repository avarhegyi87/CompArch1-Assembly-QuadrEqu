#include <iostream>
using namespace std;

int main() {

	unsigned short int u16;
	u16 = 0x0001;

	_asm {
		mov al, 0x20;
		sub al, 0x11;

		mov al, 0;
		sub al, 1;

		mov ax, 2;
		mov cx, ax;
		sub ax, u16;
		sbb ax, cx;

		mov ah, 0;
		mov cl, 0;
		stc;
		sbb ah, cl;

		nop;
	}

	system("pause");
	return 0;
}