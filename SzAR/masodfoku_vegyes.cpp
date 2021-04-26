#include <iostream>
#include <math.h>
using namespace std;

int main() {
	int a, b, c;
	cout << endl << "Adja meg az 'x^2' egyutthatojat: ";
	cin >> a;
	cout << endl << "Adja meg az 'x' egyutthatojat: ";
	cin >> b;
	cout << endl << "Adja meg a konstanst: ";
	cin >> c;


	int megoldasok;
	double diszkriminans;
	double gyok;
	double szamlalo;
	int nevezo;
	double x1, x2;

	diszkriminans = (float)b * (float)b - (float)4 * a * c;

	int assa, assb, assc;
	assa = a; assb = b; assc = c;
	int assdisz;

	_asm {

	}

	if (diszkriminans < 0) {
		cout << endl << "Az egyenletnek nincsen megoldasa." << endl;
	}
	else {
		gyok = sqrt(diszkriminans);
		nevezo = 2 * a;
		if (diszkriminans == 0) {
			cout << endl << "Az egyenletnek egy megoldasa van: ";
			cout << (double)-b / (double)nevezo << endl;
		}
		else {
			x1 = ((double)-b + gyok) / nevezo;
			x2 = ((double)-b - gyok) / nevezo;
			cout << endl << "Az egyenlet megoldasai:" << endl;
			cout << x1 << endl << x2 << endl << endl;
		}
	}

	system("pause");
	return EXIT_SUCCESS;
}