#include <iostream>
using namespace std;
int main() {
	_asm {
		mov al, 0xff;
		mov ch, al;
		mov edx, 0xabcdef01;
		mov esi, edx;
		mov di, si;
		nop;
	}


	return 0;
}