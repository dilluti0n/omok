#include <iostream>
#include "board.h"

using namespace std;

void input(char pind, int &x, int &y) {
	for (;;) {
		cout << pind << "'s turn" << endl;
		cout << "\t\tx :";
		cin >> x;
		cout << "\t\ty :";
		cin >> y;
		if (x < 0 || x > 9 || y < 0 ||
		    y > 9 || valueofboard(x, y) != '+') {
			cout << "cannot place this location" << endl;
			continue;
		}
		break;
	}
}

int toggle(int first, int second) {
	static int t = 0;
	t = ~t;
	return t? first : second;
}
