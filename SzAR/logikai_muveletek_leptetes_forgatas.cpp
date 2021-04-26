#include <iostream>
using namespace std;

int main() {
	char i8;
	short int i16;
	int i32;

	i8 = 0xC2;
	i16 = 0xA5A5;
	i32 = 0x7F7F7F7F;

	_asm {
		and i8, 0x0f;
		or i16, 0x5a5a;
		mov eax, 0xf7f7f7f7;
		xor eax, i32;
	}

	_asm {
		mov ebx, 0x55555555;
		not ebx;
	}

	_asm {
		mov al, 0x01;
		shl al, 1;
		mov bx, 0x8000;
		sar bx, 2;
		ror bx, 4;
		mov edx, 0x7f000000;
		mov cl, 5;
		rcl edx, cl;
	}

	_asm {
		mov eax, 0xc2f3d4e5;
		xor eax, eax;
		mov ax, 0xffff;
		and ax, 0x1000;
		or ax, 0x8000;
		xor ax, 0x0001;
	}

	return 0;
}