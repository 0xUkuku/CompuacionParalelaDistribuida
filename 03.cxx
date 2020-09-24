#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int size_max = 1000;
int a[1000][1000], b[1000][1000], c[1000][1000];

void matrix_mult()
{
	srand(time(0));
	for (int i = 0; i < size_max; ++i) {
		for (int j = 0; j < size_max; ++j) {
			a[i][j] = rand() % 100;
			b[i][j] = rand() % 100;
		}
	}

	int blockSize = 4;

	for (int bi = 0; bi < size_max; bi += blockSize) {
		for (int bj = 0; bj < size_max; bj += blockSize) {
			for (int bk = 0; bk < size_max; bk += blockSize) {
				for (int i = 0; i < blockSize; i++) {
					for (int j = 0; j < blockSize; j++) {
						for (int k = 0; k < blockSize; k++) {
							c[bi + i][bj + j] += a[bi + i][bk + k] * b[bk + k][bj + j];
						}
					}
				}
			}
		}
	}
}

int main()
{
	matrix_mult();

	return 0;
}
