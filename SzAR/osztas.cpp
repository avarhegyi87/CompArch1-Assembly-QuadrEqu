#include <iostream>
using namespace std;

int main() {
	unsigned char u8;
	unsigned short int u16;
	unsigned int u32;
	u8 = 0x80;
	u16 = 0x0101;
	u32 = 200;

	_asm {
		mov ax, 0x1001;
		div u8;
		mov dx, 0x0020;
		mov ax, 0xf211;
		div u16;
		mov edx, 0x00000011;
		mov eax, 0x1000f211;
		div u32;
	}

	char i8;
	short int i16;
	int i32;
	i8 = -108;
	i16 = -257;
	i32 = -200;

	_asm {
		mov ax, 0x1000;
		idiv i8;
		mov dx, 0x0001;
		mov ax, 0xf211;
		idiv i16;
		mov edx, 0x00000011;
		mov eax, 0x1000f211;
		idiv i32;
	}

	system("pause");
	return 0;
}