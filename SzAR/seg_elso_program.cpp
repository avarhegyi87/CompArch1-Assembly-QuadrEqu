#include <iostream>
#include <ctime>
using namespace std;

int main() {
	int x;
	char ch;
	x = 1;
	_asm {
		mov eax, x;
		add eax, eax;
		mov x, eax;
	}
	printf("x erteke: %d\n", x);
	printf("A befejezeshez nyomjon meg egy billentyut...\n");
	ch = getchar();
	system("pause");
	return 0;
}