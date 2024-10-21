#include <stdio.h> 
#include "rb.h"

#define N 8

main() 
{
    int i, j = 7, x;

	Initialize(0);

    for (i = 0; i < N; i++)
	{
        InsertKey(j);
		j = (j + 7) % N;
	}
    printf("Inserts are complete\n");
	PrintElements();
	printf("\nDelete value: ");
	scanf("%d", &x);
	RemoveKey(x);
	printf("\nAfter deletion of %d\n", x);
	PrintElements();
	printf("\nSearch for: ");
	scanf("%d", &x);
	Search(x);
    return 0;
}