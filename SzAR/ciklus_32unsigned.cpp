#include <iostream>
using namespace std;

int main() {

	unsigned int tmb[7] = { 1,2,3,4,5,6,7 };
	unsigned int osszeg = 0;
	unsigned int N = 7;

	_asm {
		mov edx, N;
		mov ebx, 0;
		mov eax, 0;

	CIKL: add eax, tmb[ebx];
		add ebx, 4;

		dec edx;
		jnz CIKL;

		mov osszeg, eax;
	}
	
	return 0;
}