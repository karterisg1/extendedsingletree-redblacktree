/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

int ITEMscan(Item *x)
{
	char text[17];
	char text1[30];
	char text2[100];
	int t, t1, t2;
	
	t = scanf("%s", text);
	(*x).ISBN = strdup(text);
	t1 = scanf("%s", text1);
	(*x).title = strdup(text1);
	t2 = scanf("%s", text2);
	(*x).authors = strdup(text2);
	return  t == EOF || t1 == EOF || t2 == EOF; 
}

void ITEMshow(Item x)
{ printf("ISBN: %s\tTitle: %s\tAuthors:\%s\n", x.ISBN, x.title, x.authors); }
