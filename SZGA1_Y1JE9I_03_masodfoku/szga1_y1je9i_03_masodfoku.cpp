#include <iostream>
using namespace std;

int main() {

	const char *msg_szammegad_opcio_kerdes = "Milyen változókkal fusson a program? Gépelje be az opció számát és üssön Entert!\n"
		"(1) Én adom meg\n(2) A program generálja véletlenszerûen (-100 és 100 között)";
	const char *msg_szammegad_opcio_valasz = "\nA választott opció: ";
	const char *msg_hibas_opcio = "Hiba! Nem megfelelõ opciószám! Próbálja újra!\n";
	const char *msg_utasitas = "\nAdja meg az ax^2 + bx + c másodfokú egyenlet a, b, c (egész) együtthatóit szóközökkel elválasztva!\n"
		"A számoknak -100 és 100 közöttieknek kell lenniük.\n";
	const char *msg_hibas_szam = "Nem megfelelõ szám! A változóknak -100 és 100 között kell lenniük.\n"
		"Adjon meg új számokat!\n";
	const char *msg_megerosites = "\n\nA kiválasztott egyenlet: %dx^2 + %dx + %d = 0";
	const char *msg_egymegoldaskiir = "Az egyenletnek egy megoldása van:\nx = %.3lf";
	const char *msg_ketmegoldaskiir = "Az egyenletnek két megoldása van:\nx1 = %.3lf, x2 = %.3lf";
	const char *msg_nincsmo = "\nAz egyenletnek nincsen valós megoldása.\n";
	const char *msg_nemert = "\nNem értelmezhetõ mûvelet a diszkrimináns kiszámolása során.\n";
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

	//futtatási opció kiválasztása (1. beviteles, 2. random számmal)
	_asm {
		mov saveesp, esp;
		push msg_szammegad_opcio_kerdes;
		call dword ptr printf;
	opcio_megad:
		push msg_szammegad_opcio_valasz;
		call dword ptr printf;
		//opciószám bekérése
		lea eax, dword ptr[opcio];			//opció számának mozgatása eax regbe
		push eax;							//opció szám a stackbe
		push opcioformatum;
		call dword ptr scanf;
		mov esp, saveesp;
	ciklus_opciokontroll:
		cmp opcio, 2;						// 1 <= bevitt opció <= 2
		jg hibas_opcio;						// ha nagyobb, mint 2, hiba, új bevitel kell
		cmp opcio, 1;						// 1 <= bevitt opció <= 2
		jl hibas_opcio;						// ha kisebb, mint 1, hiba, új bevitel kell
		jmp kilep_opcio;
	hibas_opcio:
		mov saveesp, esp;
		push msg_hibas_opcio;				//szöveg a képernyõre a hibás opciószámról
		call dword ptr printf;
		mov esp, saveesp;
		jmp opcio_megad;					//visszatérés az opciószám megadásához
	kilep_opcio:
		nop;
		cmp opcio, 1;
		je valtozo_beker;					//1-es opció esetén a manuális bekéréshez ugrunk
		jmp random_feltoltes;				//ha nem 1-es opció, akkor 2-es: random szám generálás
	}

	//a, b, c változók feltöltése randomszám generálással
	_asm {
	random_feltoltes:
		//mov saveesp, esp;
		mov ecx, 3;							//ciklusszámláló: 3, mert három változónk van
		mov esi, 0;							//tömbindex: 0-ról indul, int változók miatt 4-esével nõ
	ciklus_feltolt:
		mov eax, 0;
		rdrand ax;							//randomszám generálása ax-re
		mov ebx, 201;
		mov edx, 0;
		div ebx;
		sub edx, 100;
		mov valtozok[esi], edx;				//randomszám eltárolása a változók tömb esi-edik elemében
		cmp esi, 0;							//0. elemet elmentjük az a változóba
		je savea;
		cmp esi, 4;							//1. elemet elmentjük az a változóba
		je saveb;
		cmp esi, 8;							//2. elemet elmentjük az a változóba
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
		add esi, 4;							//tömbindex növelése 4-el (int = 4 byte)
		loop ciklus_feltolt;
		//mov esp, saveesp;
		jmp egyenletkiir;
	}

	//a, b és c tényezõk bekérése konzolból
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

	//visszajelzés a programtól az a, b, c változókat illetõen
	_asm{
	egyenletkiir:
		//szövegesen kiírjuk a teljes egyenletet, behelyettesítve a, b, c-t
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
		//mindhárom változónál megnézzük, -100 és 100 közötti-e. Ha nem, hiba.
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
		jmp kilep_kontroll;					//kilépés, ha mindegyik változó -100 és 100 közötti
	kontroll_hiba:
		mov saveesp, esp;
		push msg_hibas_szam;
		call dword ptr printf;
		mov esp, saveesp;
		jmp valtozo_beker;					//visszaugrás a változók manuális bekéréséhez, volt -100 alatti/100 feletti

	kilep_kontroll:
		nop;
		jmp elsofoku_kontroll;
	}

	_asm {
	elsofoku_kontroll:
		//ha a 0, az egyenlet elsõfokú lesz: bx + c = 0
		mov saveesp, esp;
		xor eax, eax;
		mov eax, a;
		cmp eax, 0x0000;
		mov esp, saveesp;
		je elsofoku;
		jmp kalkul_diszk;					//ha a nem 0, ugrás a másodfokú megoldás elejére: diszkrimináns kiszámolása
	elsofoku:
		//elsõfokú egyenlet megoldása
		mov saveesp, esp;
		xor eax, eax;
		mov eax, b;
		cmp eax, 0x0000;
		je nincsmego;						//ha b is 0, az egyenletnek nincsen megoldása
		fild c;								//c egész változó a floating point verembe
		fchs;								//elõjelváltás
		fidiv b;							//st(0) = -c/b
		fstp x1;							//mentés x1-be, és pop
		mov esp, saveesp;
		jmp egy_megoldas_kiirasa;			//ugrás az egy megoldásos kiíráshoz
	}

	//diszkrimináns kiszámítása, megoldások számának eldöntése
	_asm {
	kalkul_diszk:
		//diszkriminánst számolunk elõször, hogy megállapítsuk a megoldások számát
		mov saveesp, esp;
		fild c;								//c egész változó a floating point verembe
		fimul a;							//st(0) = c * a
		fimul minusznegy;					//st(0) = st(0) * -4
		fild b;								//b egész változó a floating point verembe
		fimul b;							//st(0) = b*b
		fadd st(0), st(1);					//(b*b) + (-4ac)
		fist d;								//diszkrimináns mentése integerbe (ez még biztosan egész szám)
		//megj.: pop nélkül mentettünk, mivel a diszkriminánsra még szükség lesz x1 és x2 kiszámolásához

		ftst;								//tesztelés nullára
		fstsw ax;							//eredmény az ax regiszterbe
		test ax, 0x0100;					//ax AND 0x0100 --> d < 0
		mov esp, saveesp;
		jnz nincsmego;						//negatív diszkrimináns, nincsen valós megoldás, ugrás
		jmp vanmego;						//ha eddig nem ugrottunk, akkor van megoldás
	}

	_asm{
	vanmego:
		nop;
		mov saveesp, esp;
		fild a;								//a egész változó a floating point verembe
		fimul ketto;						//st(0) = 2a
		fistp nevezo;						//kimentés a nevezo változóba és pop
		mov esp, saveesp;
		mov saveesp, esp;
		fsqrt;								//diszk. van a verem tetején --> st(0) = gyök:diszk.
		fild b;								//b egész változó a floating point verembe
		fchs;								//st(0) = -b
		fsub st(0), st(1);					//st(0) = -b - gyök:d
		fidiv nevezo;						//st(0) = st(0)/2a
		fstp x1;							//x1 kimentése és pop

		cmp x1, 0x8000000000000000;			//tesztelés negatív nullára (pl. a=2,b=0,c=0 egyenletnél)
		jne megoldasok_szama;				//ha nem negatív nulla, ugrás a köv. lépésre
		fld x1;								//ha nem ugrottunk, x1-et (-0) visszatesszük a float stackbe
		fchs;								//elõjelváltás
		fstp x1;							//+0 kimentése x1-be és pop

	megoldasok_szama:
		ftst;								//tesztelés nullára
		fstsw ax;							//FUP kiírása ax regbe
		test ax, 0x4000;					//ax = 0?
		mov esp, saveesp;
		jnz egy_megoldas_kiirasa;			//ha diszk. = 0, 1 megoldás van. Nem számolunk x2-t, ugrás az eredménykiíráshoz

		mov saveesp, esp;
		fild d;								//ha itt tart a program, két megoldás van - diszkriminánst vissza a verembe
		fsqrt;								//st(0) = diszk. négyzetgyökét
		fild b;								//st(0) = b
		fchs;								//st(0) = -b
		fadd st(0), st(1);					//st(0) = -b + gyök:d
		fidiv nevezo;						//st(0) = st(0)/2a
		fstp x2;							//x2 kimentése és pop

		cmp x2, 0x8000000000000000;			//x2 tesztelése mínusz 0-ra, mint x1-nél. Javítjuk pozitívra, ha szükséges
		jne x2vege;
		fld x2;
		fchs;
		fstp x2;
	x2vege:
		mov esp, saveesp;
		jmp ket_megoldas_kiirasa;			//ugrás a kétmegoldásos verzió eredménykiírásához
	}

	_asm {
	egy_megoldas_kiirasa:
		//egymegoldásos egyenlet kiírása (elsõfokú, vagy diszkrimináns = 0)
		mov saveesp, esp;
		fld x1;
		sub esp, 8;
		fstp qword ptr[esp];
		push msg_egymegoldaskiir;
		call dword ptr printf;
		push ujsor;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;							//ugrás a program lezárásához
	}

	_asm{
	ket_megoldas_kiirasa:
		//kétmegoldásos egyenlet eredményeinek kiírása
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
		jmp vege;							//ugrás a program lezárásához
	}

	_asm {
	nincsmego:
		//kiírjuk, ha az egyenletnek nincsen megoldása
		mov saveesp, esp;
		mov ecx, dword ptr[msg_nincsmo];
		push ecx;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;							//ugrás a program lezárásához
	}

	_asm {
	ervenytelen:
		//egyelõre nem használt blokk (érvénytelen, pl. NaN eredményeknél használtam volna)
		//itt hagyom esetleges késõbbi verziók számára
		mov saveesp, esp;
		push msg_nemert;
		call dword ptr printf;
		mov esp, saveesp;
		jmp vege;
	}

	_asm {
	vege:
		//system("pause") és a program lezárása
		mov saveesp, esp;
		push ujsor;
		call dword ptr printf;
		push _pause;
		call dword ptr system;
		mov esp, saveesp;
	}

	return 0;
}