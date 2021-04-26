#include <iostream>
using namespace std;

int main() {
	printf("Adattipuok merete byte-ban: char:%d\tshort int:%d\tint: %d\n", sizeof(char), sizeof(short int), sizeof(int));

	char i8;
	unsigned char u8;
	short int i16;
	unsigned short int u16;
	int i32;
	unsigned int u32;

	_asm {
		mov i8, 0xBF;
		mov u8, 0x3E;
		mov i16, 0xFFBF;
		mov u16, 0x003E;
		mov i32, 0xFFFFFFBF;
		mov u32, 0x0000003E;

		mov cl, i8;
		mov dx, u16;
		mov esi, i32;
	}

	_asm {
		mov al, 0x02;
		add al, u8;
		mov ax, 0x1000;
		add ax, i16;
		mov eax, 0x00000001;
		add eax, u32;
		mov ecx, 0;
		add ecx, i32;
		add al, cl;
		add ax, cx;
		add eax, ecx;
	}

	_asm {
		add ax, i16;
		adc ax, cx;
		stc;
		adc ah, cl;
	}
	system("pause");
	return 0;
}