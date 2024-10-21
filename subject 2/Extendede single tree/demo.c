#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

void main(int argc, char *argv[])
 { int N, maxN = atoi(argv[1]);
    Key v;
	Item item;
    STinit();
    for (N = 0; N < maxN; N++)
      {
        if (ITEMscan(&item) == EOF) break;
		v = key(item);
        if (!eq(key(STsearch(v)), "")) continue;
        STinsert(item);
      }
    STsort(ITEMshow); printf("\n");
    printf("%d keys ", N);
    printf("%d distinct keys\n", STcount());
	printf("3os smallest is: ");
	ITEMshow(STselect(3-1));
	printf("1os smallest is: ");
	ITEMshow(STselect(1-1));
	printf("Book with isbn 70 is:");
	ITEMshow(STsearch("70"));
 }