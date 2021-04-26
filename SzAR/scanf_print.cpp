#include<iostream>
#include<ctime>
using namespace std;
int main() {
	const char *formatstring = "tesztint: %d, tesztfloat: %f, tesztdouble: %lf\n";
	int tesztint = 100; float tesztfloat; double tesztdouble = 654.32;
	//printf(formatstring, tesztint, tesztfloat, tesztdouble);
	//-----------------------------------------------------------------------------------------------------------------
	//-> 1. demó: scanf parancs meghívása asm-en belül
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
	//-> 2. demó: printf parancs meghívása asm-en belül
	//-----------------------------------------------------------------------------------------------------------------

	tesztint = 100; tesztfloat = 200.33; tesztdouble = 654.32;
	_asm
	{
		//függvényhívás elõtt a paramétereket fordított sorrendben kell a veremben elhelyezni:
		// tesztdouble, tesztfloat, tesztint és formatstring a sorrend
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