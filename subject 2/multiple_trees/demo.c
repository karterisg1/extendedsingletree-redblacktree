#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

void main(int argc, char *argv[])
{
	int N, maxN = atoi(argv[1]), sw = atoi(argv[2]);
    Key v; Item item;
	nlink Tree1, Tree2, z1, z2;
    Tree1 = STinit(&z1);
    for (N = 0; N < maxN; N++)
      {
        if (sw) v = ITEMrand();
          else if (ITEMscan(&v) == EOF) break;
        if (STsearch(Tree1, z1, v) != NULLitem) continue;
        key(item) = v;
        Tree1 = STinsert(Tree1, z1, item);
      }
	  printf("Tree1\n");
    STsort(Tree1, z1, ITEMshow); printf("\n");
    printf("%d keys ", N);
    printf("%d distinct keys\n", STcount(Tree1));
	
	Tree2 = STinit(&z2);
    for (N = 0; N < maxN; N++)
      {
        if (sw) v = ITEMrand();
          else if (ITEMscan(&v) == EOF) break;
        if (STsearch(Tree2, z2, v) != NULLitem) continue;
        key(item) = v;
        Tree2 = STinsert(Tree2, z2, item);
      }
	printf("Tree2\n");
    STsort(Tree2, z2, ITEMshow); printf("\n");
    printf("%d keys ", N);
    printf("%d distinct keys\n", STcount(Tree2));
	printf("3os smallest of Tree1 is: ");
	ITEMshow(STselect(Tree1, z1, 3-1));
	printf("1os smallest of Tree2 is: ");
	ITEMshow(STselect(Tree2, z2, 1-1));
	printf("70 IN Tree1:");
	ITEMshow(STsearch(Tree1, z1, 70));
	printf("\nDelete 70 IN Tree1:\n");
	Tree1 = STdelete(Tree1, z1, 70);
	STsort(Tree1, z1, ITEMshow); printf("\n");
}