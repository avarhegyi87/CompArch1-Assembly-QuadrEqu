#include <iostream>
using namespace std;

int main() {

	const char *msg_szammegad_opcio_kerdes = "Milyen v�ltoz�kkal fusson a program? G�pelje be az opci� sz�m�t �s �ss�n Entert!\n"
		"(1) �n adom meg\n(2) A program gener�lja v�letlenszer�en (-100 �s 100 k�z�tt)";
	const char *msg_szammegad_opcio_valasz = "\nA v�lasztott opci�: ";
	const char *msg_hibas_opcio = "Hiba! Nem megfelel� opci�sz�m! Pr�b�lja �jra!\n";
	const char *msg_utasitas = "\nAdja meg az ax^2 + bx + c m�sodfok� egyenlet a, b, c (eg�sz) egy�tthat�it sz�k�z�kkel elv�lasztva!\n"
		"A sz�moknak -100 �s 100 k�z�ttieknek kell lenni�k.\n";
	const char *msg_hibas_szam = "Nem megfelel� sz�m! A v�ltoz�knak -100 �s 100 k�z�tt kell lenni�k.\n"
		"Adjon meg �j sz�mokat!\n";
	const char *msg_megerosites = "\n\nA kiv�lasztott egyenlet: %dx^2 + %dx + %d = 0";
	const char *msg_egymegoldaskiir = "Az egyenletnek egy megold�sa van:\nx = %.3lf";
	const char *msg_ketmegoldaskiir = "Az egyenletnek k�t megold�sa van:\nx1 = %.3lf, x2 = %.3lf";
	const char *msg_nincsmo = "\nAz egyenletnek nincsen val�s megold�sa.\n";
	const char *msg_nemert = "\nNem �rtelmezhet� m�velet a diszkrimin�ns kisz�mol�sa sor�n.\n";
	const char *ujsor = "\n";
	const char *opcioformatum = "%d";
	const char *beformatum = "%d %d %d";

	int opcio = 0;
	int valtozok[3] = { 0 };
	int a, b, c;
	int d;
	short int minusznegy = -4; //0xfc;
	short int ketto = 2;
	int nevezo;
	double x1, x2;

	const char *hun = "Hun";
	const char *_pause = "pause";
	int saveesp = 0;

	//setlocale HUN
	_asm {
		mov saveesp, esp;
		push hun;
		push 0;
		call dword ptr setlocale;
		mov esp, saveesp;
	}

	//futtat�si opci� kiv�laszt�sa (1. beviteles, 2. random sz�mmal)
	_asm {
		mov saveesp, esp;
		push msg_szammegad_opcio_kerdes;
		call dword ptr printf;
	opcio_megad:
		push msg_szammegad_opcio_valasz;
		call dword ptr printf;
		//opci�sz�m bek�r�se
		lea eax, dword ptr[opcio];			//opci� sz�m�nak mozgat�sa eax regbe
		push eax;							//opci� sz�m a stackbe
		push opcioformatum;
		call dword ptr scanf;
		mov esp, saveesp;
	ciklus_opciokontroll:
		cmp opcio, 2;						// 1 <= bevitt opci� <= 2
		jg hibas_opcio;						// ha nagyobb, mint 2, hiba, �j bevitel kell
		cmp opcio, 1;						// 1 <= bevitt opci� <= 2
		jl hibas_opcio;						// ha kisebb, mint 1, hiba, �j bevitel kell
		jmp kilep_opcio;
	hibas_opcio:
		mov saveesp, esp;
		push msg_hibas_opcio;				//sz�veg a k�perny�re a hib�s opci�sz�mr�l
		call dword ptr printf;
		mov esp, saveesp;
		jmp opcio_megad;					//visszat�r�s az opci�sz�m megad�s�hoz
	kilep_opcio:
		nop;
		cmp opcio, 1;
		je valtozo_beker;					//1-es opci� eset�n a manu�lis bek�r�shez ugrunk
		jmp random_feltoltes;				//ha nem 1-es opci�, akkor 2-es: random sz�m gener�l�s
	}

	//a, b, c v�ltoz�k felt�lt�se randomsz�m gener�l�ssal
	_asm {
	random_feltoltes:
		//mov saveesp, esp;
		mov ecx, 3;							//ciklussz�ml�l�: 3, mert h�rom v�ltoz�nk van
		mov esi, 0;							//t�mbindex: 0-r�l indul, int v�ltoz�k miatt 4-es�vel n�
	ciklus_feltolt:
		mov eax, 0;
		rdrand ax;							//randomsz�m gener�l�sa ax-re
		mov ebx, 201;
		mov edx, 0;
		div ebx;
		sub edx, 100;
		mov valtozok[esi], edx;				//randomsz�m elt�rol�sa a v�ltoz�k t�mb esi-edik elem�ben
		cmp esi, 0;							//0. elemet elmentj�k az a v�ltoz�ba
		je savea;
		cmp esi, 4;							//1. elemet elmentj�k az a v�ltoz�ba
		je saveb;
		cmp esi, 8;							//2. elemet elmentj�k az a v�ltoz�ba
		je savec;
	savea:
		mov a, edx;
		jmp folytat;
	saveb:
		mov b, edx;
		jmp folytat;
	savec:
		mov c, edx;
		jmp folytat;
	folytat:
		add esi, 4;							//t�mbindex n�vel�se 4-el (int = 4 byte)
		loop ciklus_feltolt;
		//mov esp, saveesp;
		jmp egyenletkiir;
	}

	//a, b �s c t�nyez�k bek�r�se konzolb�l
	_asm {
	valtozo_beker:
		mov saveesp, esp;
		push msg_utasitas;
		call dword ptr printf;
		lea eax, dword ptr[c];
		push eax;
		lea eax, dword ptr[b];
		push eax;
		lea eax, dword ptr[a];
		push eax;
		push beformatum;
		call dword ptr scanf;
		mov esp, saveesp;
	}

	//visszajelz�s a programt�l az a, b, c v�ltoz�kat illet�en
	_asm{
	egyenletkiir:
		//sz�vegesen ki�rjuk a teljes egyenletet, behelyettes�tve a, b, c-t
		mov saveesp, esp;
		push c;
		push b;
		push a;
		push msg_megerosites;
		call dword ptr printf;
		push ujsor;
		call dword ptr printf;
		mov esp, saveesp;
		cmp opcio, 2;
		je elsofoku_kontroll;
	valtozo_kontroll:
		//mindh�rom v�ltoz�n�l megn�zz�k, -100 �s 100 k�z�tti-e. Ha nem, hiba.
		cmp a, 100;
		jg kontroll_hiba;
		cmp a, -100;
		jl kontroll_hiba;
		cmp b, 100;
		jg kontroll_hiba;
		cmp b, -100;
		jl kontroll_hiba;
		cmp c, 100;
		jg kontroll_hiba;
		cmp c, -100;
		jl kontroll_hiba;
		jmp kilep_kontroll;					//kil�p�s, ha mindegyik v�ltoz� -100 �s 100 k�z�tti
	kontroll_hiba:
		mov saveesp, esp;
		push msg_hibas_szam;
		call dword ptr printf;
		mov esp, saveesp;
		jmp valtozo_beker;					//visszaugr�s a v�ltoz�k manu�lis bek�r�s�hez, volt -100 alatti/100 feletti

	kilep_kontroll:
		nop;
		jmp elsofoku_kontroll;
	}

	_asm {
	elsofoku_kontroll:
		//ha a 0, az egyenlet els�fok� lesz: bx + c = 0
		mov saveesp, esp;
		xor eax, eax;
		mov eax, a;
		cmp eax, 0x0000;
		mov esp, saveesp;
		je elsofoku;
		jmp kalkul_diszk;					//ha a nem 0, ugr�s a m�sodfok� megold�s elej�re: diszkrimin�ns kisz�mol�sa
	elsofoku:
		//els�fok� egyenlet megold�sa
		mov saveesp, esp;
		xor eax, eax;
		mov eax, b;
		cmp eax, 0x0000;
		je nincsmego;						//ha b is 0, az egyenletnek nincsen megold�sa
		fild c;								//c eg�sz v�ltoz� a floating point verembe
		fchs;								//el�jelv�lt�s
		fidiv b;							//st(0) = -c/b
		fstp x1;							//ment�s x1-be, �s pop
		mov esp, saveesp;
		jmp egy_megoldas_kiirasa;			//ugr�s az egy megold�sos ki�r�shoz
	}

	//diszkrimin�ns kisz�m�t�sa, megold�sok sz�m�nak eld�nt�se
	_asm {
	kalkul_diszk:
		//diszkrimin�nst sz�molunk el�sz�r, hogy meg�llap�tsuk a megold�sok sz�m�t
		mov saveesp, esp;
		fild c;								//c eg�sz v�ltoz� a floating point verembe
		fimul a;							//st(0) = c * a
		fimul minusznegy;					//st(0) = st(0) * -4
		fild b;								//b eg�sz v�ltoz� a floating point verembe
		fimul b;							//st(0) = b*b
		fadd st(0), st(1);					//(b*b) + (-4ac)
		fist d;								//diszkrimin�ns ment�se integerbe (ez m�g biztosan eg�sz sz�m)
		//megj.: pop n�lk�l mentett�nk, mivel a diszkrimin�nsra m�g sz�ks�g lesz x1 �s x2 kisz�mol�s�hoz

		ftst;								//tesztel�s null�ra
		fstsw ax;							//eredm�ny az ax regiszterbe
		test ax, 0x0100;					//ax AND 0x0100 --> d < 0
		mov esp, saveesp;
		jnz nincsmego;						//negat�v diszkrimin�ns, nincsen val�s megold�s, ugr�s
		jmp vanmego;						//ha eddig nem ugrottunk, akkor van megold�s
	}

	_asm{
	vanmego:
		nop;
		mov saveesp, esp;
		fild a;								//a eg�sz v�ltoz� a floating point verembe
		fimul ketto;						//st(0) = 2a
		fistp nevezo;						//kiment�s a nevezo v�ltoz�ba �s pop
		mov esp, saveesp;
		mov saveesp, esp;
		fsqrt;								//diszk. van a verem tetej�n --> st(0) = gy�k:diszk.
		fild b;								//b eg�sz v�ltoz� a floating point verembe
		fchs;								//st(0) = -b
		fsub st(0), st(1);					//st(0) = -b - gy�k:d
		fidiv nevezo;						//st(0) = st(0)/2a
		fstp x1;							//x1 kiment�se �s pop

		cmp x1, 0x8000000000000000;			//tesztel�s negat�v null�ra (pl. a=2,b=0,c=0 egyenletn�l)
		jne megoldasok_szama;				//ha nem negat�v nulla, ugr�s a k�v. l�p�sre
		fld x1;								//ha nem ugrottunk, x1-et (-0) visszatessz�k a float stackbe
		fchs;								//el�jelv�lt�s
		fstp x1;							//+0 kiment�se x1-be �s pop

	megoldasok_szama:
		ftst;								//tesztel�s null�ra
		fstsw ax;							//FUP ki�r�sa ax regbe
		test ax, 0x4000;					//ax = 0?
		mov esp, saveesp;
		jnz egy_megoldas_kiirasa;			//ha diszk. = 0, 1 megold�s van. Nem sz�molunk x2-t, ugr�s az eredm�nyki�r�shoz

		mov saveesp, esp;
		fild d;								//ha itt tart a program, k�t megold�s van - diszkrimin�nst vissza a verembe
		fsqrt;								//st(0) = diszk. n�gyzetgy�k�t
		fild b;								//st(0) = b
		fchs;								//st(0) = -b
		fadd st(0), st(1);					//st(0) = -b + gy�k:d
		fidiv nevezo;						//st(0) = st(0)/2a
		fstp x2;							//x2 kiment�se �s pop

		cmp x2, 0x8000000000000000;			//x2 tesztel�se m�nusz 0-ra, mint x1-n�l. Jav�tjuk pozit�vra, ha sz�ks�ges
		jne x2vege;
		fld x2;
		fchs;
		fstp x2;
	x2vege:
		mov esp, saveesp;
		jmp ket_megoldas_kiirasa;			//ugr�s a k�tmegold�sos verzi� eredm�nyki�r�s�hoz
	}

	_asm {
	egy_megoldas_kiirasa:
		//egymegold�sos egyenlet ki�r�sa (els�fok�, vagy diszkrimin�ns = 0)
		mov saveesp, esp;
		fld x1;
		sub esp, 8;
		fstp qword ptr[esp];
		push msg_egymegoldaskiir;
		call dword ptr printf;
		push ujsor;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;							//ugr�s a program lez�r�s�hoz
	}

	_asm{
	ket_megoldas_kiirasa:
		//k�tmegold�sos egyenlet eredm�nyeinek ki�r�sa
		mov saveesp, esp;
		fld x2;
		sub esp, 8;
		fstp qword ptr[esp];
		fld x1;
		sub esp, 8;
		fstp qword ptr[esp];
		push msg_ketmegoldaskiir;
		call dword ptr printf;
		push ujsor;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;							//ugr�s a program lez�r�s�hoz
	}

	_asm {
	nincsmego:
		//ki�rjuk, ha az egyenletnek nincsen megold�sa
		mov saveesp, esp;
		mov ecx, dword ptr[msg_nincsmo];
		push ecx;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;							//ugr�s a program lez�r�s�hoz
	}

	_asm {
	ervenytelen:
		//egyel�re nem haszn�lt blokk (�rv�nytelen, pl. NaN eredm�nyekn�l haszn�ltam volna)
		//itt hagyom esetleges k�s�bbi verzi�k sz�m�ra
		mov saveesp, esp;
		push msg_nemert;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;
	}

	_asm {
	vege:
		//system("pause") �s a program lez�r�sa
		mov saveesp, esp;
		push ujsor;
		call dword ptr printf;
		push _pause;
		call dword ptr system;
		mov esp, saveesp;
	}

	return 0;
}