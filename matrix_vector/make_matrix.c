#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
   FILE * fp;
   int i,j,n;
   n=5;
   fp = fopen ("matrix.txt","w");

   srand(time(0));
   for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {

    		fprintf(fp,"%d ", (rand()%10)+1);
    	}
    	fprintf(fp,"\n");
    }

   fclose (fp);
   return 0;
}
