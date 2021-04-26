int main() {
	unsigned short int tmb[7] = { 1,2,3,4,5,6,7 };
	unsigned int osszeg = 0;
	unsigned int N = 7;

	_asm {
		mov edx, 0;
		mov ebx, 0;
		mov eax, 0;

	CIKL: cmp edx, N;
		je CIKL_VEGE;
		inc edx;

		xor ecx, ecx;
		mov cx, tmb[ebx];
		add eax, ecx;
		add ebx, 2;

		jmp CIKL;
	CIKL_VEGE: mov osszeg, eax;
		nop;
	}

	return 0;
}