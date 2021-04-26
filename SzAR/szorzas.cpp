#include <iostream>
using namespace std;

int main() {

	unsigned char u8;
	unsigned short int u16;
	unsigned int u32;
	u8 = 0x08;
	u16 = 0x0101;
	u32 = 200;

	_asm {
		mov al, 0x03;
		mul u8;
		mov ax, 0x0004;
		mul u16;
		mov eax, 0x00000005;
		mul u32;
	}

	char i8;
	short int i16;
	int i32;

	i8 = -8;
	i16 = -257;
	i32 = -200;

	_asm {
		mov al, 0x03;
		imul i8;
		mov ax, 0x0004;
		imul i16;
		mov eax, 0x00000005;
		imul i32;
		nop;
	}

	system("pause");
	return 0;
}