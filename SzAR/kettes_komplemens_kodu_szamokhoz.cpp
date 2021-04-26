#include <iostream>
using namespace std;

int main() {
	unsigned char u8;
	char i8;
	u8 = 0xA5;
	i8 = 0xA5;

	_asm {
		mov ah, u8;
		not ah;
		inc ah;
		mov al, i8;
		neg al;
		mov al, i8;
		cbw;
		cwd;
		cwde;

		nop;
	}

	system("pause");
	return 0;
}