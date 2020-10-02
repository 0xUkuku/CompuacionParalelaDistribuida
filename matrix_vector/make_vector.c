#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	FILE *fp;
	int i, n;
	n = 5;
	fp = fopen("vector.txt", "w");

	srand(time(0));
	for (i = 0; i < n; i++) {
		fprintf(fp, "%d ", rand() % 10);
	}

fclose(fp);
return 0;
}
