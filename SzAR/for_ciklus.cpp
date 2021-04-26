#include <iostream>
using namespace std;
int main() {
	_asm {
		MODEL SMALL

		.STACK

		ADAT		SEGMENT
		ElemSzam	EQU			5
		Vekt1		DB			6,-1,17,100,-8
		Vekt2		DW			1000,1999,-32768,4,32767
		Eredm		DW			ElemSzam DUP (?)
		ADAT		ENDS

		KOD			SEGMENT
					ASSUME CS:KOD,DS:ADAT

		@Start:
					MOV			AX,ADAT
					MOV			DS,AX
					MOV			CX,ElemSzam
					XOR			BX,BX
					MOV			SI,BX
		@Ciklus:
					MOV			AL,[Vekt1+BX]
					CBW
					ADD			AX,[Vekt2+SI]
					MOV			[Eredm+SI],AX
					INC			BX
					LEA			SI,[SI+2]
					LOOP		@Ciklus
					MOV			AX,4C00h
					INT			21h
		KOD			ENDS
					END			@Start
	}


	return 0;
}