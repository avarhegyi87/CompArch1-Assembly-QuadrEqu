#include<iostream>
#include<ctime>
using namespace std;
int main() {
	const char *formatstring = "tesztint: %d, tesztfloat: %f, tesztdouble: %lf\n";
	int tesztint = 100; float tesztfloat; double tesztdouble = 654.32;
	//printf(formatstring, tesztint, tesztfloat, tesztdouble);
	//-----------------------------------------------------------------------------------------------------------------
	//-> 1. dem�: scanf parancs megh�v�sa asm-en bel�l
	//-----------------------------------------------------------------------------------------------------------------
	//scanf_s("%d", &tesztint);
	const char *formatscanf = "%f %f";
	_asm
	{
		mov esi, esp;
		lea eax, [tesztfloat];
		push eax;
		lea eax, [tesztfloat];
		push eax;
		push formatscanf;
		call dword ptr scanf;
		fld dword ptr[tesztfloat];
		sub esp, 8;
		fstp qword ptr[esp];
		fld dword ptr[tesztfloat];
		sub esp, 8;
		fstp qword ptr[esp];
		push formatscanf;
		call dword ptr printf;
		mov esp, esi;
	}
	cout << endl;
	//-----------------------------------------------------------------------------------------------------------------
	//-> 2. dem�: printf parancs megh�v�sa asm-en bel�l
	//-----------------------------------------------------------------------------------------------------------------

	tesztint = 100; tesztfloat = 200.33; tesztdouble = 654.32;
	_asm
	{
		//f�ggv�nyh�v�s el�tt a param�tereket ford�tott sorrendben kell a veremben elhelyezni:
		// tesztdouble, tesztfloat, tesztint �s formatstring a sorrend
		mov esi, esp;
		sub esp, 8;
		fld qword ptr[tesztdouble];
		fstp qword ptr[esp];
		fld dword ptr[tesztfloat];
		sub esp, 8;
		fstp qword ptr[esp];
		mov eax, dword ptr[tesztint];
		push eax;
		mov ecx, dword ptr[formatstring];
		push ecx;
		call dword ptr printf;
		add esp, 18h;
	}
	system("pause");
	return 0;
}