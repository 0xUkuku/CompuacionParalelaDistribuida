#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int size_max = 750;
int a[750][750], b[750][750], c[750][750];

void matrix_mult()
{
	srand(time(0));
	for (int i = 0; i < size_max; ++i) {
		for (int j = 0; j < size_max; ++j) {
			a[i][j] = rand() % 100;
			b[i][j] = rand() % 100;
		}
	}

	for (int i = 0; i < size_max; i++) {
		for (int j = 0; j < size_max; j++) {
			c[i][j] = 0;
			for (int k = 0; k < size_max; k++) {
				c[i][j] += c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}

int main()
{
	matrix_mult();

	return 0;
}
