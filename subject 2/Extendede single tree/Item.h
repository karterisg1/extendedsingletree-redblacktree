/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

/* Definitions for the interface for items - file Item.h */

#include <string.h>
typedef char *Key;

typedef struct
{
	Key ISBN;
	char *title;
	char *authors;
} Item;

#define key(A) (((Item)(A)).ISBN)
#define less(A, B) (strcmp(A, B) < 0)
#define eq(A, B) (!less(A, B) && !less(B, A))
typedef struct STnode* nlink;

int ITEMscan(Item *);
void ITEMshow(Item);